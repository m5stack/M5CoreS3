// This header file contains a list of user setup files and defines which one
// the compiler uses when the IDE performs a Verify/Compile or Upload.
//
// Users can create configurations for different boards and TFT displays.
// This makes selecting between hardware setups easy by "uncommenting" one line.

// The advantage of this hardware configuration method is that the examples
// provided with the library should work with immediately without any other
// changes being needed. It also improves the portability of users sketches to
// other hardware configurations and compatible libraries.
//
// Create a shortcut to this file on your desktop to permit quick access for
// editing. Re-compile and upload after making and saving any changes to this
// file.

// Customised User_Setup files are stored in the "User_Setups" folder.

// It is also possible for the user tft settings to be included with the sketch,
// see the "Sketch_with_tft_setup" generic example. This may be more convenient
// for multiple projects.

///////////////////////////////////////////////////////
//   User configuration selection lines are below    //
///////////////////////////////////////////////////////

// Only ONE line below should be uncommented to define your setup.  Add extra
// lines and files as needed.

//                            USER DEFINED SETTINGS
//   Set driver type, fonts to be loaded, pins used and SPI control method etc
//
//   See the In_eSPI_Setup.h file if you wish to be able to define multiple
//   setups and then easily select which setup file is used by the compiler.
//
//   If this file is edited correctly then all the library example sketches
//   should run without the need to make any more changes for a particular
//   hardware setup! Note that some sketches are designed for a particular TFT
//   pixel width/height

// User defined information reported by "Read_User_Setup" test & diagnostics
// example

// #define TFT_RGB_ORDER TFT_MAD_RGB  // Use the correct RGB order for the
// display

#define TFT_RGB_ORDER TFT_BGR  // Colour order Blue-Green-Red

#define ILI9341_DRIVER  // Generic driver for common displays

#include "In_eSPI_Drivers/ILI9341_Defines.h"

#define TFT_DRIVER 0x9341

#define USER_SETUP_INFO "User_Setup"

#define M5STACK

// Define to disable all #warnings in library (can be put in In_eSPI_Setup.h)
//#define DISABLE_ALL_LIBRARY_WARNINGS

// ##################################################################################
//
// Section 1. Call up the right driver file and any options for it
//
// ##################################################################################
// Only define one driver, the other ones must be commented out

// Some displays support SPI reads via the MISO pin, other displays have a
// single bi-directional SDA pin and the library will try to read this via the
// MOSI line. To use the SDA line for reading data from the TFT uncomment the
// following line:

// #define TFT_SDA_READ      // This option is for ESP32 ONLY, tested with
// ST7789 and GC9A01 display only

// For ST7735, ST7789 and ILI9341 ONLY, define the colour order IF the blue and
// red are swapped on your display Try ONE option at a time to find the correct
// colour order for your display

// For M5Stack ESP32 module with integrated ILI9341 display ONLY, remove // in
// line below

// If colours are inverted (white shows as black) then uncomment one of the next
// 2 lines try both options, one of the options should correct the inversion.

#define TFT_INVERSION_ON
// #define TFT_INVERSION_OFF

// ##################################################################################
//
// Section 2. Define the pins that are used to interface with the display here
//
// ##################################################################################

// If a backlight control signal is available then define the TFT_BL pin in
// Section 2 below. The backlight will be turned ON when tft.begin() is called,
// but the library needs to know if the LEDs are ON with the pin HIGH or LOW. If
// the LEDs are to be driven with a PWM signal or turned OFF/ON then this must
// be handled by the user sketch. e.g. with digitalWrite(TFT_BL, LOW);

// #define TFT_BL   32            // LED back-light control pin
// #define TFT_BACKLIGHT_ON HIGH  // Level to turn ON back-light (HIGH or LOW)

// We must use hardware SPI, a minimum of 3 GPIO pins is needed.
// The DC (Data Command) pin may be labelled AO or RS (Register Select)
//
// With some displays such as the ILI9341 the TFT CS pin can be connected to GND
// if no more SPI devices (e.g. an SD Card) are connected, in this case comment
// out the #define TFT_CS line below so it is NOT defined. Other displays such
// at the ST7735 require the TFT CS pin to be toggled during setup, so in these
// cases the TFT_CS line must be defined and connected.

// ###### EDIT THE PIN NUMBERS IN THE LINES FOLLOWING TO SUIT YOUR ESP32 SETUP
// ######

// For the M5Stack module use these #define lines
#define TFT_MISO 35
#define TFT_MOSI 37
#define TFT_SCLK 36
#define TFT_CS   3   // Chip select control pin
#define TFT_DC   35  // Data Command control pin
#define TFT_RST  -1  // Reset pin (could connect to Arduino RESET pin)
//#define TFT_BL   32  // LED back-light (required for M5Stack)

// ######       EDIT THE PINs BELOW TO SUIT YOUR ESP32 PARALLEL TFT SETUP ######

// The library supports 8 bit parallel TFTs with the ESP32, the pin
// selection below is compatible with ESP32 boards in UNO format.
// Wemos D32 boards need to be modified, see diagram in Tools folder.
// Only ILI9481 and ILI9341 based displays have been tested!

// ##################################################################################
//
// Section 3. Define the fonts that are to be used here
//
// ##################################################################################

// Comment out the #defines below with // to stop that font being loaded
// The ESP8366 and ESP32 have plenty of memory so commenting out fonts is not
// normally necessary. If all fonts are loaded the extra FLASH space required is
// about 17Kbytes. To save FLASH space only enable the fonts you need!

#define LOAD_GLCD   // Font 1. Original Adafruit 8 pixel font needs ~1820 bytes
                    // in FLASH
#define LOAD_FONT2  // Font 2. Small 16 pixel high font, needs ~3534 bytes in
                    // FLASH, 96 characters
#define LOAD_FONT4  // Font 4. Medium 26 pixel high font, needs ~5848 bytes in
                    // FLASH, 96 characters
#define LOAD_FONT6  // Font 6. Large 48 pixel font, needs ~2666 bytes in FLASH,
                    // only characters 1234567890:-.apm
#define LOAD_FONT7  // Font 7. 7 segment 48 pixel font, needs ~2438 bytes in
                    // FLASH, only characters 1234567890:-.
#define LOAD_FONT8  // Font 8. Large 75 pixel font needs ~3256 bytes in FLASH,
                    // only characters 1234567890:-.
//#define LOAD_FONT8N // Font 8. Alternative to Font 8 above, slightly narrower,
// so 3 digits fit a 160 pixel TFT
#define LOAD_GFXFF  // FreeFonts. Include access to the 48 Adafruit_GFX free
                    // fonts FF1 to FF48 and custom fonts

// Comment out the #define below to stop the SPIFFS filing system and smooth
// font code being loaded this will save ~20kbytes of FLASH #define SMOOTH_FONT

// ##################################################################################
//
// Section 4. Other options
//
// ##################################################################################

// Define the SPI clock frequency, this affects the graphics rendering speed.
// Too fast and the TFT driver will not keep up and display corruption appears.
// With an ILI9341 display 40MHz works OK, 80MHz sometimes fails
// With a ST7735 display more than 27MHz may not work (spurious pixels and
// lines) With an ILI9163 display 27 MHz works OK.

// #define SPI_FREQUENCY   1000000
// #define SPI_FREQUENCY   5000000
// #define SPI_FREQUENCY  10000000
// #define SPI_FREQUENCY  20000000
#define SPI_FREQUENCY 27000000
// #define SPI_FREQUENCY  40000000
// #define SPI_FREQUENCY  80000000

// Optional reduced SPI frequency for reading TFT
#define SPI_READ_FREQUENCY 20000000

// The XPT2046 requires a lower SPI clock rate of 2.5MHz so we define that here:
#define SPI_TOUCH_FREQUENCY 2500000

// The ESP32 has 2 free SPI ports i.e. VSPI and HSPI, the VSPI is the default.
// If the VSPI port is in use and pins are not accessible (e.g. TTGO T-Beam)
// then uncomment the following line:
#define USE_HSPI_PORT

// Comment out the following #define if "SPI Transactions" do not need to be
// supported. When commented out the code size will be smaller and sketches will
// run slightly faster, so leave it commented out unless you need it!

// Transaction support is needed to work with SD library but not needed with
// TFT_SdFat Transaction support is required if other SPI devices are connected.

// Transactions are automatically enabled by the library for an ESP32 (to use
// HAL mutex) so changing it here has no effect

// #define SUPPORT_TRANSACTIONS

// Identical looking TFT displays may have a different colour ordering in the 16
// bit colour
#define TFT_BGR 0  // Colour order Blue-Green-Red
#define TFT_RGB 1  // Colour order Red-Green-Blue
