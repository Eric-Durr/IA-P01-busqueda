#include "../include/catch/catch.h"
#include "../include/environment.hpp"
#include "../include/search.hpp"

SCENARIO("Creando el objeto de busqueda") {
  GIVEN(
      "Entorno de 10 * 10, un coche en la posicion por defecto, y una meta en "
      "la 9*9 ") {
    Environment env(50, 50);
    env.set_car(0, 0);
    env.set_goal(49, 49);
    env.set_obs(0, 1);

    env.set_obs(1, 1);
    env.set_obs(2, 1);
    env.set_obs(3, 1);
    env.set_obs(4, 1);
    env.set_obs(5, 1);
    env.set_obs(6, 1);
    env.set_obs(7, 1);
    env.set_obs(9, 1);

    Search a_star(env, 2);
    WHEN("Comprobamos atributos") {
      THEN("Lista abierta y lista cerrada vacia") {
        CHECK(a_star.o_list_empty() == true);
        CHECK(a_star.o_list_size() == 0);
        CHECK(a_star.c_list_empty() == true);
      }
      AND_THEN("meta, coche, start y funciones h inicializados") {
        std::vector<int> s_expected = {0, 0};
        CHECK(a_star.get_start_pos() == s_expected);
        std::vector<int> c_expected = {0, 0};
        CHECK(a_star.get_car_pos() == c_expected);
        std::vector<int> g_expected = {2, 2};
        CHECK(a_star.get_goal_pos() == g_expected);

        CHECK(a_star.linear_value() == 2);
        CHECK(a_star.manhattan_value() == 4);
      }
    }
    AND_WHEN("Se lanza el algoritmo") {
      a_star.a_star_algorithm();
      std::cout << env << std::endl;

      std::cout << a_star << std::endl;
    }
  }
}
