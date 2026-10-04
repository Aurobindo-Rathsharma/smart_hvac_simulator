# Smart Home Occupancy & HVAC Control Simulator

A robust, production-grade Linux daemon designed to monitor indoor environmental telemetry and dynamically optimize HVAC states using a deterministic Finite State Machine (FSM). Built with Modern C++20 principles and a zero-dependency native C++ compilation pipeline.

---

## Project Development Stages

The repository has been systematically developed across six distinct engineering stages:

### Stage 1: Architecture Design
* **System Pattern:** Designed around a lightweight Linux daemon structure for continuous, headless background execution.
* **Resource Safety:** Utilizes RAII (Resource Acquisition Is Initialization) wrappers for file descriptors and system resources to prevent leaks and ensure deterministic teardowns.
* **Signal Handling:** Integrates custom POSIX signal handlers (`SIGTERM`, `SIGINT`) for clean, safe state persistence upon shutdown.
* **Asynchronous Logging:** Implements a lightweight, non-blocking logging pipeline to record system health and state changes without halting execution.
* **Pipeline Workflow:**
  ```mermaid
  graph LR
      A[System Boot] --> B[Daemon Forking]
      B --> C[Signal Registration]
      C --> D[Main Event Loop]
### Stage 2: Product Requirements Document (PRD) & Specs
* **Performance Goals:** Targets sub-millisecond state evaluation latency and a minimal memory footprint suitable for resource-constrained embedded edge deployment.
* **Core Constraints:** Strict adherence to Modern C++ standards with minimal legacy C interface layers (10-15%) reserved strictly for low-level system calls.
* **Memory Management:** Enforces strict bounds on dynamic memory allocation to eliminate heap fragmentation risks during long-running daemon lifecycles.
* **Concurrency Contracts:** Defines clear thread-safety boundaries to safely manage concurrent sensor polling threads without race conditions.
* **Pipeline Workflow:**
  ```mermaid
  graph LR
      A[Requirement Analysis] --> B[Constraint Definition]
      B --> C[Resource Budgeting]
      C --> D[API Contract Design]
### Stage 3: Deterministic FSM Design
* **State Space:** Engineered a robust Finite State Machine managing distinct operational modes:
  * `IDLE`: Baseline low-power standby when the space is unoccupied.
  * `ECO_HEATING` / `ECO_COOLING`: Energy-saving thermal regulation based on ambient variance.
  * `ACTIVE_COMFORT`: High-performance mode triggered by high occupant density.
  * `AWAY_MODE`: Extended conservation state for prolonged vacancy.
* **Hysteresis Buffering:** Implements thermal threshold buffers to prevent rapid oscillation ("flapping") between heating and cooling states during fluctuating boundary conditions.
* **Transition Matrix:** Enforces a strict, deterministic transition validation matrix that guarantees zero invalid state hops.
* **Pipeline Workflow:**
  ```mermaid
  graph LR
      A[Sensor Input] --> B[Threshold Evaluation]
      B --> C[Transition Matrix Lookup]
      C --> D[State Resolution]
### Stage 4: Modular C++ Implementation
* **Component Breakdown:** Developed modular subsystems for real-time sensor data ingestion (`SensorReader`), thermal logic evaluation, and daemon control loops.
* **Language Compliance:** Implemented using strongly typed `enum class` definitions, smart pointers, and clean header-implementation separation.
* **Zero-Copy Optimization:** Utilizes efficient data-passing structures between telemetry parsers and the FSM evaluation engine to minimize CPU cycles.
* **Exception Safety:** Establishes strong exception-neutral error propagation boundaries to maintain high availability under fault conditions.
* **Pipeline Workflow:**
  ```mermaid
  graph LR
      A[Telemetry Ingestion] --> B[Data Parsing]
      B --> C[FSM Evaluation]
      C --> D[Actuator Command]
### Stage 5: Unit Testing Suite
* **Verification Framework:** Developed an integrated, standalone testing harness (`test_main.cpp`) to validate edge cases, sensor parsing, and FSM transition rules.
* **Reliability:** Automated test execution to guarantee regression-free code updates prior to deployment.
* **Mock Injection:** Incorporates mock sensor generators to simulate extreme thermal spikes, sensor dropouts, and intermittent hardware signals.
* **Boundary Assertions:** Validates extreme occupant density scenarios, ranging from zero-occupancy edge cases to maximum building capacity limits.
* **Pipeline Workflow:**
  ```mermaid
  graph LR
      A[Test Suite Init] --> B[Mock Data Injection]
      B --> C[Assertion Validation]
      C --> D[Regression Report]
### Stage 6: Native C++ Build Integration
* **Build Automation:** Completely eliminated external build systems in favor of a native C++ build program (`build.cpp`) compiled directly via `g++`.
* **Clean Repository:** Maintained a sanitized, professional Git history and lightweight directory tree containing only source code, headers, and the custom builder.
* **Compiler Optimization:** Injects production optimization flags (`-O3 -flto`) directly via the builder script for maximum runtime performance.
* **Pre-Flight Validation:** Implements automated header inclusion and dependency checks within the C++ builder before triggering compilation.
* **Pipeline Workflow:**
  ```mermaid
  graph LR
      A[Builder Execution] --> B[Dependency Check]
      B --> C[g++ Direct Compilation]
      C --> D[Binary Output]
## Compilation And Execution
* ** Compile the Custom Build Automation Script
Compile the meta-builder program directly using g++:


  g++ -std=c++20 build.cpp -o builder
* ** Run the Native Builder (Zero-Dependency Compilation)
Execute the builder script to trigger automated source scanning and compiler optimizations:


./builder
* **Execute the HVAC Simulator Daemon
Launch the headless background daemon to monitor telemetry and evaluate state transitions:


./hvac_sim 
* **then next
./hvac_tests

# Conclusion

The Smart Home Occupancy & HVAC Control Simulator successfully showcases an enterprise-grade intersection of embedded Linux systems engineering and modern C++20 software design. By employing a deterministic Finite State Machine with advanced hysteresis buffering, robust RAII resource management, and a zero-dependency native compilation pipeline, this project delivers high reliability, sub-millisecond evaluation latency, and seamless hardware-to-simulation fallback capabilities. It serves as a comprehensive, production-ready blueprint for resource-constrained edge automation environments.
### Live Execution Preview
*Below is a capture of the daemon running successfully in simulation mode, demonstrating real-time telemetry logging, FSM state transitions (`AWAY_MODE`, `ECO_COOLING`, `ACTIVE_COMFORT`), and test harness execution:*


(<img width="986" height="580" alt="Screenshot 2026-10-04 214002" src="https://github.com/user-attachments/assets/4f215e59-d4ef-4972-a8f6-c15994d02939" />
)




# Project Directory Structure

```text
smart_hvac_simulator/
├── build.cpp
├── README.md
├── include/
│   ├── HVACState.hpp
│   └── SensorReader.hpp
└── src/
    ├── main.cpp
    ├── SensorReader.cpp
    └── test_main.cpp
