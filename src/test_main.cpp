#include "SensorReader.hpp"
#include "HVACState.hpp"
#include <iostream>
#include <cassert>

class HVACControllerTest {
public:
    static void testStateTransitions() {
        SensorData test_data;

        test_data.occupant_count = 0;
        test_data.ambient_temp = 24.0f;
        assert(test_data.occupant_count == 0);

        test_data.occupant_count = 2;
        test_data.ambient_temp = 20.0f;
        bool is_heating = (test_data.ambient_temp < 22.0f);
        assert(is_heating == true);

        test_data.ambient_temp = 28.0f;
        bool is_cooling = (test_data.ambient_temp > 26.0f);
        assert(is_cooling == true);

        std::cout << "All tests passed successfully." << std::endl;
    }
};

int main() {
    HVACControllerTest::testStateTransitions();
    return 0;
}
