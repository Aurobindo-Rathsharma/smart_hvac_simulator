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
* **Pipeline / Workflow:** 
  $$\text{System Boot} \rightarrow \text{Daemon Forking} \rightarrow \text{Signal Registration} \rightarrow \text{Main Event Loop}$$

### Stage 2: Product Requirements Document (PRD) & Specs
* **Performance Goals:** Targets sub-millisecond state evaluation latency and a minimal memory footprint suitable for resource-constrained embedded edge deployment.
* **Core Constraints:** Strict adherence to Modern C++ standards with minimal legacy C interface layers (10-15%) reserved strictly for low-level system calls.
* **Memory Management:** Enforces strict bounds on dynamic memory allocation to eliminate heap fragmentation risks during long-running daemon lifecycles.
* **Concurrency Contracts:** Defines clear thread-safety boundaries to safely manage concurrent sensor polling threads without race conditions.
* **Pipeline / Workflow:** 
  $$\text{Requirement Analysis} \rightarrow \text{Constraint Definition} \rightarrow \text{Resource Budgeting} \rightarrow \text{API Contract Design}$$

### Stage 3: Deterministic FSM Design
* **State Space:** Engineered a robust Finite State Machine managing distinct operational modes:
  * `IDLE`: Baseline low-power standby when the space is unoccupied.
  * `ECO_HEATING` / `ECO_COOLING`: Energy-saving thermal regulation based on ambient variance.
  * `ACTIVE_COMFORT`: High-performance mode triggered by high occupant density.
  * `AWAY_MODE`: Extended conservation state for prolonged vacancy.
* **Hysteresis Buffering:** Implements thermal threshold buffers to prevent rapid oscillation ("flapping") between heating and cooling states during fluctuating boundary conditions.
* **Transition Matrix:** Enforces a strict, deterministic transition validation matrix that guarantees zero invalid state hops.
* **Pipeline / Workflow:** 
  $$\text{Sensor Input} \rightarrow \text{Threshold Evaluation} \rightarrow \text{Transition Matrix Lookup} \rightarrow \text{State Resolution}$$

### Stage 4: Modular C++ Implementation
* **Component Breakdown:** Developed modular subsystems for real-time sensor data ingestion (`SensorReader`), thermal logic evaluation, and daemon control loops.
* **Language Compliance:** Implemented using strongly typed `enum class` definitions, smart pointers, and clean header-implementation separation.
* **Zero-Copy Optimization:** Utilizes efficient data-passing structures between telemetry parsers and the FSM evaluation engine to minimize CPU cycles.
* **Exception Safety:** Establishes strong exception-neutral error propagation boundaries to maintain high availability under fault conditions.
* **Pipeline / Workflow:** 
  $$\text{Telemetry Ingestion} \rightarrow \text{Data Parsing} \rightarrow \text{FSM Evaluation} \rightarrow \text{Actuator Command}$$

### Stage 5: Unit Testing Suite
* **Verification Framework:** Developed an integrated, standalone testing harness (`test_main.cpp`) to validate edge cases, sensor parsing, and FSM transition rules.
* **Reliability:** Automated test execution to guarantee regression-free code updates prior to deployment.
* **Mock Injection:** Incorporates mock sensor generators to simulate extreme thermal spikes, sensor dropouts, and intermittent hardware signals.
* **Boundary Assertions:** Validates extreme occupant density scenarios, ranging from zero-occupancy edge cases to maximum building capacity limits.
* **Pipeline / Workflow:** 
  $$\text{Test Suite Init} \rightarrow \text{Mock Data Injection} \rightarrow \text{Assertion Validation} \rightarrow \text{Regression Report}$$

### Stage 6: Native C++ Build Integration
* **Build Automation:** Completely eliminated external build systems in favor of a native C++ build program (`build.cpp`) compiled directly via `g++`.
* **Clean Repository:** Maintained a sanitized, professional Git history and lightweight directory tree containing only source code, headers, and the custom builder.
* **Compiler Optimization:** Injects production optimization flags (`-O3 -flto`) directly via the builder script for maximum runtime performance.
* **Pre-Flight Validation:** Implements automated header inclusion and dependency checks within the C++ builder before triggering compilation.
* **Pipeline / Workflow:** 
  $$\text{Builder Execution} \rightarrow \text{Dependency Check} \rightarrow \text{g++ Direct Compilation} \rightarrow \text{Binary Output}$$

---

## Project Directory Structure

```text
smart_hvac_simulator/
├── build.cpp              # Native C++20 custom compilation script
├── README.md              # Comprehensive 6-stage project documentation
├── include/
│   ├── HVACState.hpp      # HVAC states and deterministic FSM logic
│   └── SensorReader.hpp   # Sensor interface and telemetry data structs
└── src/
    ├── main.cpp           # Main application daemon execution loop
    ├── SensorReader.cpp   # Linux file node / simulation mock handler
    └── test_main.cpp      # Standalone unit testing verification suite
