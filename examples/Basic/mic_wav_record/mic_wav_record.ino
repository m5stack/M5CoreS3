/*
 * SPDX-FileCopyrightText: 2024 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 *
 * @Hardwares: M5CoreS3
 * @Platform Version: Arduino M5Stack Board Manager v2.0.9
 * @Dependent Library:
 * M5GFX: https://github.com/m5stack/M5GFX
 * M5Unified: https://github.com/m5stack/M5Unified
 * M5CoreS3: https://github.com/m5stack/M5CoreS3
 */

#include <M5CoreS3.h>
#include <SPI.h>
#include <SD.h>

// Btn A is to record audio. Btn A 是录音音频
// Btn B is to play audio. Btn B是播放音频
// Btn C is to delete file. Btn C是删除文件
// PWR is to select a file. PWR是选择文件
// The selected file is yellow, the unselected file is white, and the playing
// file is the selected file.
// 选中的文件是黄色的,未选中的文件是白色的,播放的文件是选中的文件.

#define SD_SPI_SCK_PIN  (36)
#define SD_SPI_MISO_PIN (35)
#define SD_SPI_MOSI_PIN (37)
#define SD_SPI_CS_PIN   (4)

static constexpr const size_t record_number     = 256;
static constexpr const size_t record_length     = 320;
static constexpr const size_t record_size       = record_number * record_length;
static constexpr const size_t record_samplerate = 17000;
static int16_t prev_y[record_length];
static int16_t prev_h[record_length];
static size_t rec_record_idx  = 2;
static size_t draw_record_idx = 0;
static int16_t* rec_data;

static uint32_t file_counter     = 0;
static uint8_t selectedFileIndex = 0;
static std::vector<String> wavFiles;

static m5::touch_state_t prev_state;

// AV file header definition
struct WAVHeader {
    char riff[4]           = {'R', 'I', 'F', 'F'};
    uint32_t fileSize      = 0;
    char wave[4]           = {'W', 'A', 'V', 'E'};
    char fmt[4]            = {'f', 'm', 't', ' '};
    uint32_t fmtSize       = 16;
    uint16_t audioFormat   = 1;
    uint16_t numChannels   = 1;
    uint32_t sampleRate    = record_samplerate;
    uint32_t byteRate      = record_samplerate * sizeof(int16_t);
    uint16_t blockAlign    = sizeof(int16_t);
    uint16_t bitsPerSample = 16;
    char data[4]           = {'d', 'a', 't', 'a'};
    uint32_t dataSize      = 0;
};

void micRecord(void);  // Record audio.
void viewBtn(void);    // Display button
bool saveWAVToSD(int16_t* data,
                 size_t dataSize);  // Save the WAV file to the SD card.
void scanAndDisplayWAVFiles(
    void);  // Scan and display the WAV files on the SD card on the screen.
bool playSelectedWAVFile(
    const String& fileName);        // Play the selected WAV file.
void playWAV(uint32_t sampleRate);  // Play the WAV file.
void updateDisplay(
    std::vector<String> wavFiles,
    uint8_t selectedFileIndex);  // Update the displayed information.
void setup(void) {
    CoreS3.begin();
    Serial.begin(115200);

    CoreS3.Display.startWrite();
    CoreS3.Display.setRotation(1);
    CoreS3.Display.setTextDatum(top_center);
    CoreS3.Display.setTextColor(WHITE);
    CoreS3.Display.setFont(&fonts::FreeSansBoldOblique12pt7b);
    CoreS3.Display.endWrite();

    // SD Card Initialization
    SPI.begin(SD_SPI_SCK_PIN, SD_SPI_MISO_PIN, SD_SPI_MOSI_PIN, SD_SPI_CS_PIN);

    if (!SD.begin(SD_SPI_CS_PIN, SPI, 25000000)) {
        printf("Card failed, or not present\r\n");
        while (1);
    }
    uint8_t cardType = SD.cardType();
    if (cardType == CARD_NONE) {
        printf("No SD card attached\r\n");
        return;
    }
    printf("SD Card Type: ");
    if (cardType == CARD_MMC) {
        printf("MMC\r\n");
    } else if (cardType == CARD_SD) {
        printf("SDSC\r\n");
    } else if (cardType == CARD_SDHC) {
        printf("SDHC\r\n");
    } else {
        printf("UNKNOWN\r\n");
    }
    uint64_t cardSize = SD.cardSize() / (1024 * 1024);
    printf("SD Card Size: %lluMB\r\n", cardSize);

    rec_data = (typeof(rec_data))heap_caps_malloc(record_size * sizeof(int16_t),
                                                  MALLOC_CAP_8BIT);
    memset(rec_data, 0, record_size * sizeof(int16_t));
    CoreS3.Speaker.setVolume(255);

    /// Since the microphone and speaker cannot be used at the same time,
    // turn
    /// off the speaker here.
    CoreS3.Speaker.end();
    CoreS3.Mic.begin();
    viewBtn();
    scanAndDisplayWAVFiles();
    updateDisplay(wavFiles, selectedFileIndex);
}

void loop(void) {
    CoreS3.update();
    auto touchPoint = CoreS3.Touch.getDetail();
    if (prev_state != touchPoint.state) {
        prev_state = touchPoint.state;
    }
    if ((CoreS3.Display.height() > touchPoint.y &&
         touchPoint.y > CoreS3.Display.height() - 40) &&
        touchPoint.state == m5::touch_state_t::touch_begin) {
        if (CoreS3.Display.width() / 3 > touchPoint.x &&
            touchPoint.x > 0) {  // Record an audio file.
            micRecord();
            if (saveWAVToSD(rec_data, record_size)) {
                printf("WAV file saved successfully.\n");
            } else {
                printf("Failed to save WAV file.\n");
            }
            viewBtn();
            scanAndDisplayWAVFiles();
        }
        if ((CoreS3.Display.width() / 3) * 2 > touchPoint.x &&
            touchPoint.x > CoreS3.Display.width() / 3) {  // Play an audio file.
            playSelectedWAVFile(wavFiles[selectedFileIndex]);
            viewBtn();
        }
        if (CoreS3.Display.width() > touchPoint.x &&
            touchPoint.x > (CoreS3.Display.width() / 3) * 2) {  // 删除音频文件
            String filePath = "/" + wavFiles[selectedFileIndex];
            if (SD.remove(filePath.c_str())) {
                printf("Deleted file: %s\n", filePath.c_str());
                wavFiles.erase(wavFiles.begin() + selectedFileIndex);
                if (selectedFileIndex >= wavFiles.size() && !wavFiles.empty()) {
                    selectedFileIndex--;
                }
            } else {
                printf("Failed to delete file: %s\n", filePath.c_str());
            }
            scanAndDisplayWAVFiles();
        }
    }
    int state = M5.BtnPWR.wasClicked();  // Delete an audio file.
    if (state) {
        selectedFileIndex = (++selectedFileIndex) % wavFiles.size();
        updateDisplay(wavFiles, selectedFileIndex);
    }
}

void micRecord(void) {
    CoreS3.Display.startWrite();
    CoreS3.Display.clear();
    CoreS3.Display.setTextColor(WHITE);
    // Record
    if (CoreS3.Mic.isEnabled()) {
        CoreS3.Display.fillCircle(130, 15, 8, RED);
        CoreS3.Display.drawString("REC", 180, 15);
        static constexpr int shift = 6;
        for (uint16_t i = 0; i < record_number; i++) {
            auto data = &rec_data[i * record_length];
            if (CoreS3.Mic.record(data, record_length, record_samplerate)) {
                if (i >= 2) {
                    data      = &rec_data[(i - 2) * record_length];
                    int32_t w = CoreS3.Display.width();
                    if (w > record_length - 1) {
                        w = record_length - 1;
                    }
                    for (int32_t x = 0; x < w; ++x) {
                        CoreS3.Display.writeFastVLine(x, prev_y[x], prev_h[x],
                                                      TFT_BLACK);
                        int32_t y1 = (data[x] >> shift);
                        int32_t y2 = (data[x + 1] >> shift);
                        if (y1 > y2) {
                            int32_t tmp = y1;
                            y1          = y2;
                            y2          = tmp;
                        }
                        int32_t y = ((CoreS3.Display.height()) >> 1) + y1;
                        int32_t h =
                            ((CoreS3.Display.height()) >> 1) + y2 + 1 - y;
                        prev_y[x] = y;
                        prev_h[x] = h;
                        CoreS3.Display.writeFastVLine(x, prev_y[x], prev_h[x],
                                                      WHITE);
                    }
                }
            }
            CoreS3.Display.display();
            CoreS3.Display.fillCircle(130, 15, 8, RED);
            CoreS3.Display.drawString("REC", 180, 15);
        }
        CoreS3.Display.clear();
    }
    CoreS3.Display.endWrite();
}

void viewBtn(void) {
    CoreS3.Display.startWrite();
    CoreS3.Display.setTextColor(RED);
    CoreS3.Display.setTextDatum(middle_center);
    CoreS3.Display.setFont(&fonts::Orbitron_Light_24);
    CoreS3.Display.setTextSize(1);
    CoreS3.Display.fillRect(0, CoreS3.Display.height() - 40,
                            CoreS3.Display.width() / 3, 40, WHITE);
    CoreS3.Display.fillRect(CoreS3.Display.width() / 3,
                            CoreS3.Display.height() - 40,
                            CoreS3.Display.width() / 3, 40, GREEN);
    CoreS3.Display.fillRect((CoreS3.Display.width() / 3) * 2,
                            CoreS3.Display.height() - 40,
                            CoreS3.Display.width() / 3, 40, YELLOW);
    CoreS3.Display.drawString("Btn A    Btn B    Btn C",
                              CoreS3.Display.width() / 2,
                              CoreS3.Display.height() - 20);
    CoreS3.Display.endWrite();
}

void scanAndDisplayWAVFiles() {
    static std::vector<String> previousWavFiles;

    // Scan the WAV files on the SD card and store them in wavFiles.
    File dir = SD.open("/");
    if (!dir) {
        printf("Failed to open directory.\n");
        return;
    }
    wavFiles.clear();
    while (File entry = dir.openNextFile()) {
        if (!entry.isDirectory() && String(entry.name()).endsWith(".wav")) {
            wavFiles.push_back(
                String(entry.name()));  // Only add .wav files to the list.
        }
        entry.close();
    }
    dir.close();

    // If wavFiles changes, clear the interface and update the display.
    if (wavFiles != previousWavFiles) {
        previousWavFiles = wavFiles;  // Update the previous file list.
        updateDisplay(wavFiles, selectedFileIndex);
    }
}

void updateDisplay(std::vector<String> wavFiles, uint8_t selectedFileIndex) {
    CoreS3.Display.startWrite();
    if (wavFiles.empty()) {
        printf("No WAV files found on SD card.\n");
        CoreS3.Display.fillRect(0, 0, 320, 200, BLACK);
        CoreS3.Display.setTextColor(RED);
        int xPos = (CoreS3.Display.width()) / 2;
        int yPos = CoreS3.Display.height() / 2 - 20;
        CoreS3.Display.drawString("No WAV files found", xPos, yPos);
        CoreS3.Display.endWrite();
        return;
    }
    const uint8_t maxVisibleFiles = 7;
    uint8_t startIndex            = 0;

    // Ensure the selected file is within the visible area.
    if (selectedFileIndex >= maxVisibleFiles) {
        startIndex = selectedFileIndex - (maxVisibleFiles - 1);
    }
    CoreS3.Display.fillRect(0, 0, 320, 200, BLACK);

    // Display the list of WAV files, centered. The selected file's font will be
    // yellow, and the unselected files' font will be white.
    for (size_t i = startIndex;
         i < startIndex + maxVisibleFiles && i < wavFiles.size(); i++) {
        uint16_t color = (i == selectedFileIndex) ? YELLOW : WHITE;
        CoreS3.Display.setTextColor(color);
        CoreS3.Display.drawString(wavFiles[i], CoreS3.Display.width() / 2,
                                  25 + (i - startIndex) * 25);
    }
    CoreS3.Display.endWrite();
}
bool saveWAVToSD(int16_t* data, size_t dataSize) {
    // Validate input data.
    if (!data || dataSize == 0) {
        printf("Invalid data or dataSize.\n");
        return false;  // Invalid data or size, return false.
    }

    // Generate the filename using the counter.
    char filename[32];
    snprintf(filename, sizeof(filename), "/recorded%lu.wav", file_counter);
    file_counter++;  // Increment the counter for the next file.

    // Open the file for writing (it will overwrite the file if it exists).
    File file = SD.open(filename, FILE_WRITE);
    if (!file) {
        printf("Failed to open file for writing: %s\n", filename);
        return false;  // Failed to open the file, return false.
    }

    // Initialize WAV header.
    WAVHeader header;
    header.fileSize =
        36 +
        dataSize * sizeof(int16_t);  // Calculate file size (including header).
    header.dataSize = dataSize * sizeof(int16_t);  // Calculate data size.

    // Write the WAV header to the file.
    if (file.write((uint8_t*)&header, sizeof(WAVHeader)) != sizeof(WAVHeader)) {
        printf("Failed to write WAV header.\n");
        file.close();
        return false;  // Failed to write header, close file and return false.
    }

    // Write the audio data to the file.
    if (file.write((uint8_t*)data, dataSize * sizeof(int16_t)) !=
        dataSize * sizeof(int16_t)) {
        printf("Failed to write WAV data.\n");
        file.close();
        return false;  // Failed to write data, close file and return false.
    }

    // Close the file after writing.
    file.close();
    printf("WAV file saved successfully: %s\n", filename);
    return true;  // Successfully saved the file, return true.
}

bool playSelectedWAVFile(const String& fileName) {
    String filePath = "/" + fileName;
    printf("Playing WAV file: %s\n", filePath.c_str());

    // Open the WAV file
    File file = SD.open(filePath.c_str());
    if (!file) {
        printf("Failed to open WAV file: %s\n", filePath.c_str());
        return false;  // Return false if the file cannot be opened
    }

    // Read the WAV file header to extract relevant information (e.g., sample
    // rate)
    WAVHeader header;
    file.read((uint8_t*)&header, sizeof(WAVHeader));

    // Validate the WAV file header
    if (header.riff[0] != 'R' || header.riff[1] != 'I' ||
        header.riff[2] != 'F' || header.riff[3] != 'F') {
        printf("Invalid WAV file: 'RIFF' header not found.\n");
        file.close();
        return false;  // Return false if the header is invalid
    }
    if (header.wave[0] != 'W' || header.wave[1] != 'A' ||
        header.wave[2] != 'V' || header.wave[3] != 'E') {
        printf("Invalid WAV file: 'WAVE' header not found.\n");
        file.close();
        return false;  // Return false if the header is invalid
    }

    // Extract sample rate from the header (bytes 24-27)
    printf("Sample Rate from WAV header: %lu\n", header.sampleRate);

    // Skip the rest of the WAV file header (typically 44 bytes)
    file.seek(44);  // Skip to the data section

    // Read audio data into the buffer
    size_t bytesRead =
        file.read((uint8_t*)rec_data, record_size * sizeof(int16_t));
    file.close();

    if (bytesRead == 0) {
        printf("Failed to read WAV file data.\n");
        return false;  // Return false if no data was read
    }

    // Play the WAV data
    playWAV(header.sampleRate);
    printf("Playback finished.\n");
    return true;
}

void playWAV(uint32_t sampleRate) {
    CoreS3.Display.startWrite();
    CoreS3.Display.clear();
    CoreS3.Mic.end();        // Disable the microphone
    CoreS3.Speaker.begin();  // Enable the speaker for playback
    CoreS3.Display.setTextColor(WHITE);
    CoreS3.Display.fillTriangle(120 - 8, 15 - 8, 120 - 8, 15 + 8, 120 + 8, 15,
                                0x1c9f);
    CoreS3.Display.drawString("PLAY", 180,
                              15);  // Display "PLAY" text on the screen
    static constexpr int shift = 6;

    // Loop through all the data blocks and play them
    for (uint16_t i = 0; i < record_number; i++) {
        auto data = &rec_data[i * record_length];

        // Play the data block using the sample rate extracted from the WAV
        // header
        CoreS3.Speaker.playRaw(&rec_data[i * record_length], record_length,
                               sampleRate);

        // Wait until playback finishes
        do {
            delay(1);
            CoreS3.update();
        } while (CoreS3.Speaker.isPlaying());

        // If more than two data blocks have been played, display the waveform
        if (i >= 2) {
            data      = &rec_data[(i - 2) * record_length];
            int32_t w = CoreS3.Display.width();
            if (w > record_length - 1) {
                w = record_length - 1;
            }
            for (int32_t x = 0; x < w; ++x) {
                CoreS3.Display.writeFastVLine(
                    x, prev_y[x], prev_h[x],
                    TFT_BLACK);  // Erase previous lines
                int32_t y1 = (data[x] >> shift);
                int32_t y2 = (data[x + 1] >> shift);
                if (y1 > y2) {
                    int32_t tmp = y1;
                    y1          = y2;
                    y2          = tmp;  // Ensure y1 is less than y2
                }
                int32_t y = ((CoreS3.Display.height()) >> 1) + y1;
                int32_t h = ((CoreS3.Display.height()) >> 1) + y2 + 1 - y;
                prev_y[x] = y;
                prev_h[x] = h;
                CoreS3.Display.writeFastVLine(x, prev_y[x], prev_h[x],
                                              WHITE);  // Draw new lines
            }
        }

        // Continuously update the "PLAY" text and triangle icon during playback
        CoreS3.Display.fillTriangle(120 - 8, 15 - 8, 120 - 8, 15 + 8, 120 + 8,
                                    15, 0x1c9f);
        CoreS3.Display.drawString("PLAY", 180, 15);
    }

    // End the playback
    CoreS3.Speaker.end();
    CoreS3.Mic.begin();                          // Re-enable the microphone
    CoreS3.Display.clear();                      // Clear the display
    updateDisplay(wavFiles, selectedFileIndex);  // Update the file display
    CoreS3.Display.endWrite();
}
