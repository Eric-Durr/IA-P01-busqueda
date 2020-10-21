#include "../include/catch/catch.h"
#include "../include/environment.hpp"
#include "../src/environment.cpp"


SCENARIO("Testing the enviroment")
{
    GIVEN ( "Dimensions 5 x 7" )
    {
        Environment first_env(5, 7);
        REQUIRE(first_env.size() == 35);
        WHEN ( "Obstacles are added" )
        {
            first_env.set_obs(2,1);
            THEN ( "Detection must be true" )
            {
                CHECK(first_env.at(2,1).is_obs() == true);
                CHECK(first_env.at(1,1).is_obs() == false);
            }
        }
        WHEN( "Obstacles add outside boundries" ) {
            THEN ( "set_obstacles must fail") {
                REQUIRE(first_env.set_obs(8,9) == 1);
            }
        }
    }
}
