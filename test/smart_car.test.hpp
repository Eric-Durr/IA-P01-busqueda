#include "../include/catch/catch.h"
#include "../include/smart_car.hpp"
#include "../src/smart_car.cpp"

SCENARIO( "Creating the car" ) {
    GIVEN ("A car"){
        SmartCar car1;
        REQUIRE(car1.pos() == 0);
        WHEN ( "Environmet is checked" ){
            THEN("Coordinates must been provided"){
                std::vector<int> expected = {1,1,0,0};
                CHECK(car1.sensor() == expected);
            }
        }
    }
}