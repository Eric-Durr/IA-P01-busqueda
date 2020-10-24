#include "../include/slot.hpp"

Slot::Slot(int loc_i, int loc_j, slot_t op = V):
loc_i_(loc_i), 
loc_j_(loc_j) {
  
  SmartCar car(loc_i, loc_j);
  switch (op) {
    case V:
      obstacle_ = 0;
      break;
    case O:
      obstacle_ = 1;
      break;
    case C:
      car_ = car;
      obstacle_ = 2;
      break;    
    case G:
      obstacle_ = 3;
      break;
    default:
      obstacle_ = 0;
      break;
  }
}
int Slot::s_change(slot_t op) {
    switch (op) {
    case V:
      obstacle_ = 0;
      break;
    case O:
      obstacle_ = 1;
      break;
    case C:
      obstacle_ = 2;
      break;    
    case G:
      obstacle_ = 3;
      break;
    default:
      return 1;
      break;
  }
  return 0;
}

std::ostream& operator<<(std::ostream& os, const Slot& obj) {
  switch (obj.obstacle_) {
    case V:
      os << " ";
      break;
    case O:
      os << "■";
      break;
    case C:
      os << "©";
      break;    
    case G:
      os << "x";
      break;
    default:
      os << "?";
      break;
  }
  return os;
}