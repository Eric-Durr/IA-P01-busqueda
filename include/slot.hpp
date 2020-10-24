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
        void set_obs() { obstacle_ = 1; }  //Pone obstaculo a 1
        int s_type() {return obstacle_;}  //devuelve lo que hay
        int s_change(int stype); //Pone el tipo de correspondiente

        friend std::ostream& operator<< (std::ostream& os, const Slot& obj);
};