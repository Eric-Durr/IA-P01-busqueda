#ifndef SLOT_HPP_
#define SLOT_HPP_

#include "smart_car.hpp"
#include <iostream>

enum slot_t {V, O, C, G} ;

class Slot {
    private:
        int  obstacle_;
        int  loc_i_, loc_j_;
        SmartCar car_; 
    public:
        Slot(int loc_i, int loc_j, slot_t op = V);
        ~Slot(){}
        
        bool is_obs() { return obstacle_; }
        void set_obs( slot_t op ) { obstacle_ = op;}
        int s_type() {return obstacle_;}
        int s_change(slot_t op);

        SmartCar& get_car() { return car_; }

        friend std::ostream& operator<< (std::ostream& os, const Slot& obj);
};

#endif