#include "../include/slot.hpp"

Slot::Slot(int loc_i, int loc_j, slot_t op)
    : loc_i_(loc_i), loc_j_(loc_j), obstacle_(op) {
  if (op == C) car_.pos(loc_i, loc_j);
}

void Slot::s_change(slot_t op) { obstacle_ = op; }

std::ostream& operator<<(std::ostream& os, const Slot& obj) {
  switch (obj.obstacle_) {
    case V:
      os << VOID_CHR;
      break;
    case O:
      os << OBST_CHR;
      break;
    case C:
      os << CAR__CHR;
      break;
    case G:
      os << GOAL_CHR;
      break;
    default:
      os << "?";
      break;
  }
  return os;
}