#pragma once

enum class HVACState {
    IDLE,
    ECO_HEATING,
    ECO_COOLING,
    ACTIVE_COMFORT,
    AWAY_MODE
};

inline const char* stateToString(HVACState state) {
    switch (state) {
        case HVACState::IDLE: return "IDLE";
        case HVACState::ECO_HEATING: return "ECO_HEATING";
        case HVACState::ECO_COOLING: return "ECO_COOLING";
        case HVACState::ACTIVE_COMFORT: return "ACTIVE_COMFORT";
        case HVACState::AWAY_MODE: return "AWAY_MODE";
    }
    return "UNKNOWN";
}
