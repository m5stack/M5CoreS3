#include "AppWiFiModel.h"

using namespace Page;

void AppWiFiModel::Init() {
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
}

void AppWiFiModel::Scan() {
    WiFi.scanNetworks(true);
}

int16_t AppWiFiModel::GetScanCount() {
    return WiFi.scanComplete();
}

char* AppWiFiModel::GetSSID(uint8_t index) {
    static char ssid[27];
    ssid[26] = '\0';
    strncpy(ssid, WiFi.SSID(index).c_str(), 26);
    return ssid;
}

int32_t AppWiFiModel::GetRSSI(uint8_t index) {
    return WiFi.RSSI(index);
}
