#include "../include/catch/catch.h"
#include "../include/slot.hpp"

SCENARIO("Creation of the slot")
{
    GIVEN("default slot") {
        Slot default_slot;
        REQUIRE(default_slot.is_obs() == false);
        WHEN( "Slot type is checked") {
            THEN( "Type is 0"){
                REQUIRE(default_slot.s_type() == 0);
                CHECK(default_slot.s_type() != 1);
                CHECK(default_slot.s_type() != 2);
            }
        }
        AND_WHEN( "Slot is changed "){
            default_slot.s_change(1);
            THEN( "type is 1" ) {
                REQUIRE(default_slot.s_type() == 1);
                CHECK(default_slot.s_type() != 0);
                CHECK(default_slot.s_type() != 2);
            }
        }
        AND_WHEN( "Slot is changed "){
            default_slot.s_change(2);
            THEN( "type is 2" ) {
                REQUIRE(default_slot.s_type() == 2);
                CHECK(default_slot.s_type() != 0);
                CHECK(default_slot.s_type() != 1);
            }
        }

    }
}