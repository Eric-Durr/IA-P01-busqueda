#include "../include/catch/catch.h"
#include "../include/environment.hpp"

SCENARIO("Testing the enviroment")
{
    GIVEN ( "Dimensions 5 x 7" )
    {
        Enviroment first_env(5, 7);
        REQUIRE(first_env.size() == 35);
       
    }
}
