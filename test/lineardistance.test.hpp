#include "../include/catch/catch.h"
#include "../include/environment.hpp"

SCENARIO("Testing the linear funtion") {
  GIVEN("Environment 10 * 10") {
    Environment env(10, 10);
    WHEN("El coche este en la posicion 0, 0 y la meta en 9, 9") {
      env.set_car(0, 0);
      env.set_goal(9, 9);
      THEN("La funcion lineal sera 9") { CHECK(env.lineal_d() == 12); }
    }
  }
}