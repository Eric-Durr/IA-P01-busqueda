#include "../include/slot.hpp"

Slot::Slot(int loc_i, int loc_j, slot_t op)
    : loc_i_(loc_i),
      loc_j_(loc_j),
      parent_i_(-1),
      parent_j_(-1),
      g_(0),
      obstacle_(op) {
  if (op == C) car_.pos(loc_i, loc_j);
}

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

    case U:
      os << U_PATH_CHR;
      break;

    case R:
      os << R_PATH_CHR;
      break;

    case D:
      os << D_PATH_CHR;
      break;

    case L:
      os << L_PATH_CHR;
      break;
    default:
      os << "?";
      break;
  }
  return os;
}

bool Slot::operator==(const Slot& obj) {
  return (this->f_ == obj.f_ && this->loc_i_ == obj.loc_i_ &&
          this->loc_j_ == obj.loc_j_);
}