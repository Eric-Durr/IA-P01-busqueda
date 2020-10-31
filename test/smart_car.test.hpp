#include "../include/catch/catch.h"
#include "../include/environment.hpp"
#include "../include/smart_car.hpp"

SCENARIO("Creating the car") {
  GIVEN("A car") {
    SmartCar car1;
    Environment ent1(6, 6);
    ent1.clear_obs();
    ent1.set_car(0, 0);
    WHEN("Environmet is checked") {
      car1.check_environment(ent1);
      THEN("Coordinates must acord to top left") {
        std::vector<int> expected = {0, 0};
        CHECK(car1.pos() == expected);
      }
      THEN("Sensor must be right") {
        std::vector<bool> expected = {1, 1, 0, 0};
        CHECK(car1.sensor() == expected);
        CHECK(car1.sensor(N) == 1);
        CHECK(car1.sensor(W) == 1);
        CHECK(car1.sensor(S) == 0);
        CHECK(car1.sensor(E) == 0);
      }
      std::cout << ent1 << std::endl;
    }
  }
}