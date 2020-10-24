#include "../include/slot.hpp"

Slot::Slot(int op) {
  s_change(op);
}

int Slot::s_change(int stype) {
  switch (stype) {
    case 0:
    case 1:
    case 2:
    case 3:
      obstacle_ = stype;
      break;
      
    default:
      return 1;
      break;
  }
  return 0;
}

std::ostream& operator<<(std::ostream& os, const Slot& obj) {
  if (obj.obstacle_ == 1) {
    os << "■";
  } else if (obj.obstacle_ == 3){
    os << "X";
  } else {
    os << " ";
  }
  return os;
}