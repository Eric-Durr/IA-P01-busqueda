#pragma once

#include "smart_car.hpp"
#include <iostream>

class Slot
{
    private:
        bool obstacle_;
        SmartCar car_; 
    public:
        Slot(int op = 0);
        ~Slot(){}
        
        bool is_obs() { return obstacle_; }
        void set_obs( bool op ) { obstacle_ = op;}

        friend std::ostream& operator<< (std::ostream& os, const Slot& obj);
};