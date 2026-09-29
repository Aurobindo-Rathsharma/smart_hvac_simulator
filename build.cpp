#include <iostream>
#include <cstdlib>

int main() {
    std::cout << "[C++ Builder] Compiling Smart HVAC Simulator..." << std::endl;

    std::string sim_cmd = "g++ -std=c++20 -Iinclude src/main.cpp src/SensorReader.cpp -o hvac_sim";
    if (std::system(sim_cmd.c_str()) != 0) {
        std::cerr << "[Error] Failed to compile main simulator." << std::endl;
        return 1;
    }

    std::string test_cmd = "g++ -std=c++20 -Iinclude src/test_main.cpp src/SensorReader.cpp -o hvac_tests";
    if (std::system(test_cmd.c_str()) != 0) {
        std::cerr << "[Error] Failed to compile unit tests." << std::endl;
        return 1;
    }

    std::cout << "[C++ Builder] Build completed successfully." << std::endl;
    return 0;
}
