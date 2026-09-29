#pragma once
#include <string>
#include <cstdint>
#include <optional>

struct SensorData {
    uint32_t timestamp;
    float ambient_temp;
    bool motion_detected;
    uint8_t occupant_count;
};

class SensorReader {
private:
    std::string device_path_;
    int fd_;

public:
    explicit SensorReader(std::string path);
    ~SensorReader();

    // Prevent copying
    SensorReader(const SensorReader&) = delete;
    SensorReader& operator=(const SensorReader&) = delete;

    bool initialize();
    std::optional<SensorData> readSensorData();
};
