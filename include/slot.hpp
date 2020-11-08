#ifndef SLOT_HPP_
#define SLOT_HPP_

#include <iostream>

#include "smart_car.hpp"

#define OBST_CHR " ■ "
#define VOID_CHR " · "
#define CAR__CHR " © "
#define GOAL_CHR " X "

enum slot_t { V, O, C, G };

class Slot {
 private:
  int loc_i_, loc_j_;
  int parent_i_, parent_j_; /* path trace atributes */
  double f_, g_;
  slot_t obstacle_;
  SmartCar car_;

 public:
  Slot(int loc_i = 0, int loc_j = 0, slot_t op = V);

  ~Slot() {}

  bool is_obs() { return obstacle_ == O; }
  void set_obs() { obstacle_ = O; }  // Pone obstaculo a 1
  slot_t get_obs() const { return obstacle_; }

  void set_f(double f) { f_ = f; }
  void set_g(double g) { g_ = g; }
  double get_f(void) const { return f_; }
  double get_g(void) const { return g_; }

  slot_t& s_type() { return obstacle_; }
  slot_t& s_type(slot_t op) { obstacle_ = op; }
  void s_change(slot_t op);

  int pos_i(void) const { return loc_i_; }
  int pos_j(void) const { return loc_j_; }
  void pos_i(int i) { loc_i_ = i; }
  void pos_j(int j) { loc_j_ = j; }

  int parent_i(void) const { return parent_i_; }
  int parent_j(void) const { return parent_j_; }
  void set_parents(int i = 0, int j = 0) {
    parent_i_ = i;
    parent_j_ = j;
  }

  SmartCar& get_car() { return car_; }

  friend std::ostream& operator<<(std::ostream& os, const Slot& obj);

  bool operator==(const Slot& obj);
};

#endif