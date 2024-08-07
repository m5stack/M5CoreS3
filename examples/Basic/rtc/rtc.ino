/*
 * SPDX-FileCopyrightText: 2024 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */

/*
 * @file rtc.ino
 * @author SeanKwok (shaoxiang@m5stack.com)
 * @brief M5CoreS3 RTC SNTP Test
 * @version 0.1
 * @date 2023-12-25
 *
 *
 * @Hardwares: M5CoreS3
 * @Platform Version: Arduino M5Stack Board Manager v2.0.9
 * @Dependent Library:
 * M5GFX: https://github.com/m5stack/M5GFX
 * M5Unified: https://github.com/m5stack/M5Unified
 * M5CoreS3: https://github.com/m5stack/M5CoreS3
 */

#if defined(ARDUINO)

#define WIFI_SSID     "YOUR WIFI SSID NAME"
#define WIFI_PASSWORD "YOUR WIFI PASSWORD"
#define NTP_TIMEZONE  "UTC-8"
#define NTP_SERVER1   "0.pool.ntp.org"
#define NTP_SERVER2   "1.pool.ntp.org"
#define NTP_SERVER3   "2.pool.ntp.org"

#include <WiFi.h>

// Different versions of the framework have different SNTP header file names and
// availability.
#if __has_include(<esp_sntp.h>)
#include <esp_sntp.h>
#define SNTP_ENABLED 1
#elif __has_include(<sntp.h>)
#include <sntp.h>
#define SNTP_ENABLED 1
#endif

#endif

#ifndef SNTP_ENABLED
#define SNTP_ENABLED 0
#endif

#include <M5CoreS3.h>

void setup(void) {
    CoreS3.begin();

    if (!CoreS3.Rtc.isEnabled()) {
        Serial.println("RTC not found.");
        for (;;) {
            vTaskDelay(500);
        }
    }

    Serial.println("RTC found.");

    // It is recommended to set UTC for the RTC and ESP32 internal clocks.
    /* /// setup RTC ( direct setting )
      //                      YYYY  MM  DD      hh  mm  ss
      CoreS3.Rtc.setDateTime( { { 2021, 12, 31 }, { 12, 34, 56 } } );

    //*/

    /// setup RTC ( NTP auto setting )

    CoreS3.Display.println("WiFi Connecting...");

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print('.');
        delay(500);
    }
    CoreS3.Display.println("WiFi Connected.");
    Serial.println("\r\n WiFi Connected.");

    configTzTime(NTP_TIMEZONE, NTP_SERVER1, NTP_SERVER2, NTP_SERVER3);

#if SNTP_ENABLED
    while (sntp_get_sync_status() != SNTP_SYNC_STATUS_COMPLETED) {
        Serial.print('.');
        delay(1000);
    }
    Serial.println("\r\n NTP Connected.");
    CoreS3.Display.println("NTP Connected");
#else
    delay(1600);
    struct tm timeInfo;
    while (!getLocalTime(&timeInfo, 1000)) {
        Serial.print('.');
    };
#endif

    time_t t = time(nullptr) + 1;  // Advance one second.
    while (t > time(nullptr));     /// Synchronization in seconds
    CoreS3.Rtc.setDateTime(gmtime(&t));
    CoreS3.Display.clear();
}

void loop(void) {
    static constexpr const char* const wd[7] = {"Sun", "Mon", "Tue", "Wed",
                                                "Thr", "Fri", "Sat"};

    delay(500);

    auto dt = CoreS3.Rtc.getDateTime();
    Serial.printf("RTC   UTC  :%04d/%02d/%02d (%s)  %02d:%02d:%02d\r\n",
                  dt.date.year, dt.date.month, dt.date.date,
                  wd[dt.date.weekDay], dt.time.hours, dt.time.minutes,
                  dt.time.seconds);
    CoreS3.Display.setCursor(0, 0);
    CoreS3.Display.printf("RTC   UTC  :%04d/%02d/%02d (%s)  %02d:%02d:%02d",
                          dt.date.year, dt.date.month, dt.date.date,
                          wd[dt.date.weekDay], dt.time.hours, dt.time.minutes,
                          dt.time.seconds);

    /// ESP32 internal timer
    auto t = time(nullptr);
    {
        auto tm = gmtime(&t);  // for UTC.
        Serial.printf("ESP32 UTC  :%04d/%02d/%02d (%s)  %02d:%02d:%02d\r\n",
                      tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
                      wd[tm->tm_wday], tm->tm_hour, tm->tm_min, tm->tm_sec);
        CoreS3.Display.setCursor(0, 20);
        CoreS3.Display.printf("ESP32 UTC  :%04d/%02d/%02d (%s)  %02d:%02d:%02d",
                              tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
                              wd[tm->tm_wday], tm->tm_hour, tm->tm_min,
                              tm->tm_sec);
    }

    {
        auto tm = localtime(&t);  // for local timezone.
        Serial.printf("ESP32 %s:%04d/%02d/%02d (%s)  %02d:%02d:%02d\r\n",
                      NTP_TIMEZONE, tm->tm_year + 1900, tm->tm_mon + 1,
                      tm->tm_mday, wd[tm->tm_wday], tm->tm_hour, tm->tm_min,
                      tm->tm_sec);
        CoreS3.Display.setCursor(0, 40);
        CoreS3.Display.printf("ESP32 %s:%04d/%02d/%02d (%s)  %02d:%02d:%02d",
                              NTP_TIMEZONE, tm->tm_year + 1900, tm->tm_mon + 1,
                              tm->tm_mday, wd[tm->tm_wday], tm->tm_hour,
                              tm->tm_min, tm->tm_sec);
    }
}
