# Smart Home Occupancy & HVAC Control Simulator

## What is this project?
This is my individual project for the Wipro embedded systems recruitment. I built a lightweight, high-performance embedded Linux controller simulator in **Modern C++ (C++20)**. Instead of using bloated web backends or cloud services, this system runs locally as a Linux daemon—reading sensor data, tracking room occupancy, and managing climate states with minimal resource usage and near-zero latency.

- **Assigned Topic:** Smart Home Occupancy & HVAC Control Simulator[cite: 1]
- **Environment:** Ubuntu Linux (System Programming & C++)

---

## How I Developed It (6-Stage Breakdown)

### Stage 1 – Project Introduction
* **The Goal:** Build an autonomous, localized embedded controller simulation that handles sensor inputs and drives an HVAC state machine efficiently.
* **Why it matters:** Smart home devices often rely too much on heavy cloud servers. This project focuses on edge computing—processing everything right on the device for speed and reliability.
* **Scope:** Focused purely on Linux system programming, character device interfaces, multi-threading, and clean C++ code with zero web dependencies.

### Stage 2 – Project Requirements & Development Plan
* **What I needed it to do:** 
  * Read asynchronous occupancy and temperature metrics from a Linux file node (`/dev/smart_hvac_sensors`).
  * Run a deterministic state machine (`IDLE`, `ECO_HEATING`, `ECO_COOLING`, `ACTIVE_COMFORT`, `AWAY_MODE`).
  * Keep memory usage under 15 MB and loop latency under 5 ms.
* **Approach:** Kept the codebase strictly Modern C++ ($\ge 80\%$) to align with low-level embedded constraints.

### Stage 3 – System Design & Architecture
* **How it's structured:** 
  * **Driver Interface Layer:** Uses RAII to safely wrap Linux file descriptors.
  * **Core Business Logic:** Handles multithreaded sensor polling and state evaluation.
* **Tools used:** C++20, CMake build system, Git for version control, and Linux system calls.

### Stage 4 – Initial Implementation & Prototype
* **What I built first:** I wrote the `SensorReader` class to handle file reads (with a fallback simulation generator so it can run smoothly out-of-the-box). 
* **The FSM:** Tied it to an `HVACController` class that evaluates temperature and motion changes in real-time, printing out clean telemetry logs.

### Stage 5 – Testing, Integration & Improvement
* **Ensuring stability:** Tested the data flow from mock sensor inputs all the way to the state machine output. 
* **Code quality:** Used smart pointers and RAII to ensure there are no memory leaks, keeping it robust for embedded targets.

### Stage 6 – Final Implementation & Presentation
* **Final Deliverables:** Clean source code, PRD documentation, CMake configuration, and a complete Git commit history showing step-by-step progress.
* **Key takeaways:** Successfully delivered a zero-backend, high-performance Linux simulator meeting all strict recruiter constraints.

---

## Project Structure
```text
smart_hvac_simulator/
├── CMakeLists.txt         # CMake build configuration
├── docs/
│   └── PRD.md             # Project Requirements Document
├── include/
│   ├── HVACState.hpp      # HVAC states and transition logic
│   └── SensorReader.hpp   # Sensor interface and data structs
└── src/
    ├── main.cpp           # Main application daemon loop
    └── SensorReader.cpp   # Linux file node / simulation mock handler
