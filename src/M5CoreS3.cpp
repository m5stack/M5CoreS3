#include "M5CoreS3.h"

using namespace m5;

M5CoreS3 CoreS3;

void M5CoreS3::begin() {
    M5.begin();
}

void M5CoreS3::begin(m5::M5Unified::config_t cfg) {
    M5.begin(cfg);
}

void M5CoreS3::update() {
    M5.update();
}

void M5CoreS3::delay(uint32_t msec) {
    M5.delay(msec);
}
