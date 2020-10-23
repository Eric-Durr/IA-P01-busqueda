#include "../include/catch/catch.h"
#include "../include/smart_car.hpp"

SCENARIO( "Creating the car" ) {
    GIVEN ("A car"){
        SmartCar car1;
        REQUIRE(car1.env_pos() == 0);
        WHEN ( "Environmet is checked" ) {
            THEN("Coordinates must acord to top left") {
                std::vector<int> expected = {0, 0};
                CHECK(car1.pos() == expected);
            }
            THEN("Sensor must be right") {
                std::vector<bool> expected = {1,1,0,0};
                CHECK(car1.sensor() == expected);
                CHECK(car1.sensor(N) == 1);
                CHECK(car1.sensor(S) == 1);
                CHECK(car1.sensor(E) == 0);
                CHECK(car1.sensor(W) == 0);
            }
        }
    }
}