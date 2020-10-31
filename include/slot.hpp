#ifndef SLOT_HPP_
#define SLOT_HPP_

#include <iostream>

#include "smart_car.hpp"

#define OBST_CHR "■"
#define VOID_CHR " "
#define CAR__CHR "©"
#define GOAL_CHR "X"

enum slot_t { V, O, C, G };

class Slot {
 private:
  int loc_i_, loc_j_;
  slot_t obstacle_;
  SmartCar car_;

 public:
  Slot(int loc_i = 0, int loc_j = 0, slot_t op = V);

  ~Slot() {}

  bool is_obs() { return obstacle_ == O; }
  void set_obs() { obstacle_ = O; }  // Pone obstaculo a 1
  slot_t& s_type() { return obstacle_; }
  slot_t& s_type(slot_t op) { obstacle_ = op; }
  void s_change(slot_t op);

  SmartCar& get_car() { return car_; }

  friend std::ostream& operator<<(std::ostream& os, const Slot& obj);
};

#endif