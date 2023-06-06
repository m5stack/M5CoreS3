#include "AppMicModel.h"
#include "M5Unified.h"

using namespace Page;

bool AppMicModel::ReadMicData() {
    return M5.Mic.record(mic_buf[buf_index], MIC_BUF_SIZE, 16000);
}

bool AppMicModel::IsMicEnable() {
    return M5.Mic.isEnabled();
}

bool AppMicModel::IsSpeakerEnable() {
    return M5.Speaker.isEnabled();
}

void AppMicModel::MicEnd() {
    M5.Mic.end();
    M5.Speaker.begin();
}

void AppMicModel::MicBegin() {
    M5.Speaker.end();
    M5.Mic.begin();
}
