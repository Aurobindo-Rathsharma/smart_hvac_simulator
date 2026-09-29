#include "SensorReader.hpp"
#include "HVACState.hpp"
#include <iostream>
#include <thread>
#include <chrono>

class HVACController {
private:
    HVACState current_state_ { HVACState::IDLE };

public:
    void evaluate(const SensorData& data) {
        if (data.occupant_count == 0) {
            current_state_ = HVACState::AWAY_MODE;
        } else if (data.ambient_temp < 22.0f) {
            current_state_ = HVACState::ECO_HEATING;
        } else if (data.ambient_temp > 26.0f) {
            current_state_ = HVACState::ECO_COOLING;
        } else {
            current_state_ = HVACState::ACTIVE_COMFORT;
        }
    }

    HVACState getState() const { return current_state_; }
};

int main() {
    std::cout << "=== Starting Smart Home Occupancy & HVAC Simulator (Stage 4 Prototype) ===" << std::endl;

    SensorReader reader("/dev/smart_hvac_sensors");
    reader.initialize();

    HVACController controller;

    // Run prototype loop for 10 iterations to demonstrate functionality
    for (int i = 0; i < 10; ++i) {
        auto sensor_opt = reader.readSensorData();
        if (sensor_opt.has_value()) {
            const auto& data = sensor_opt.value();
            controller.evaluate(data);

            std::cout << "[Telemetry] Time: " << data.timestamp 
                      << "s | Temp: " << data.ambient_temp << "°C"
                      << " | Motion: " << (data.motion_detected ? "YES" : "NO")
                      << " | Occupants: " << static_cast<int>(data.occupant_count)
                      << " --> [HVAC State]: " << stateToString(controller.getState()) 
                      << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    std::cout << "=== Stage 4 Prototype Execution Completed Successfully ===" << std::endl;
    return 0;
}
