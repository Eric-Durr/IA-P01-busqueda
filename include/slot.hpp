#pragma once

#include "smart_car.hpp"
#include <iostream>

class Slot
{
    private:
        int  obstacle_;
        SmartCar car_; 
    public:
        Slot(int op = 0);
        ~Slot(){}
        
        bool is_obs() { return obstacle_; }
        void set_obs( bool op ) { obstacle_ = op;}
        int s_type() {return obstacle_;}
        int s_change(int stype);

        friend std::ostream& operator<< (std::ostream& os, const Slot& obj);
};