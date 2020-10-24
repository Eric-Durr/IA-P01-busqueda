#include "../include/slot.hpp"
#include "../include/environment.hpp"
#include "../include/smart_car.hpp"

#include <iostream>


int main (void) 
{
    Environment obj1(20,20);
    obj1.clear_obs();
    obj1.set_obs(8, 11);
    obj1.set_obs(3, 6);
    obj1.set_car(0, 0);
    obj1.set_goal(19, 19);
    std::cout << obj1 << std::endl;

    return 0;
}