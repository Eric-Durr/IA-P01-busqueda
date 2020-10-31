#include "../include/slot.hpp"

Slot::Slot(int loc_i, int loc_j, slot_t op)
    : loc_i_(loc_i), loc_j_(loc_j), obstacle_(op) {
  if (op == C) car_.pos(loc_i, loc_j);
}

std::ostream& operator<<(std::ostream& os, const Slot& obj) {
  switch (obj.obstacle_) {
    case 0:
      os << VOID_CHR;
      break;
    case 1:
      os << OBST_CHR;
      break;
    case 2:
      os << CAR__CHR;
      break;
    case 3:
      os << GOAL_CHR;
      break;
    default:
      os << "?";
      break;
  }
  return os;
}