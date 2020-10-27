#ifndef SLOT_HPP_
#define SLOT_HPP_

#include <iostream>

#include "smart_car.hpp"

enum slot_t { V, O, C, G };

class Slot {
 private:
  int loc_i_, loc_j_;
  int obstacle_;
  SmartCar car_;

 public:
  Slot(int loc_i = 1, int loc_j = 1, slot_t op = V);

  ~Slot() {}

  bool is_obs() { return obstacle_; }
  void set_obs() { obstacle_ = O; }  // Pone obstaculo a 1
  int s_type() { return obstacle_; }
  int s_change(slot_t op);

  SmartCar& get_car() { return car_; }

  friend std::ostream& operator<<(std::ostream& os, const Slot& obj);
};

#endif