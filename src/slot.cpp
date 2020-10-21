#include "../include/slot.hpp"

Slot::Slot(int op) {
  switch (op) {
    case 0:
      obstacle_ = 0;
      break;

    case 1:
      obstacle_ = 1;
      break;

    case 3:
      /* coche */
      break;
    default:
      obstacle_ = 0;
      break;
  }
}
int Slot::s_change(int stype) {
  switch (stype) {
    case 0:
      obstacle_ = 0;
      break;

    case 1:
      obstacle_ = 1;
      break;

    case 2:
      obstacle_ = 2;
      break;

    default:
      return 1;
      break;
  }
  return 0;
}

std::ostream& operator<<(std::ostream& os, const Slot& obj) {
  if (obj.obstacle_) {
    os << "■";
  } else {
    os << " ";
  }
  return os;
}