#include "SensorReader.hpp"
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

SensorReader::SensorReader(std::string path) : device_path_(std::move(path)), fd_(-1) {}

SensorReader::~SensorReader() {
    if (fd_ >= 0) {
        close(fd_);
    }
}

bool SensorReader::initialize() {
    fd_ = open(device_path_.c_str(), O_RDONLY);
    if (fd_ < 0) {
        // Fallback for simulation prototype if device node doesn't exist yet
        std::cerr << "[Warning] Could not open " << device_path_ << ". Using simulation mode." << std::endl;
        return false;
    }
    return true;
}

std::optional<SensorData> SensorReader::readSensorData() {
    SensorData data;
    if (fd_ >= 0) {
        ssize_t bytes_read = read(fd_, &data, sizeof(SensorData));
        if (bytes_read == sizeof(SensorData)) {
            return data;
        }
    }
    
    // Fallback simulation mock data generator for Stage 4 prototype demonstration
    static uint32_t t = 0;
    data.timestamp = ++t;
    data.ambient_temp = 24.5f + (t % 3);
    data.motion_detected = (t % 2 == 0);
    data.occupant_count = data.motion_detected ? 2 : 0;
    return data;
}
