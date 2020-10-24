#include "../include/slot.hpp"
#include "../include/environment.hpp"
#include "../include/obstacle.hpp"
#include "../include/smart_car.hpp"

#include <iostream>


int main (void) 
{
    Environment obj1(6,12);

    obj1.set_obs(3, 2);
    obj1.set_obs(5, 10);
    obj1.set_meta(2,2);
    std::cout << obj1 << std::endl;

    obj1.delete_obs(3,2);
    std::cout << obj1 << std::endl;

    obj1.clear_obs();
    std::cout << obj1 << std::endl;


    return 0;
}