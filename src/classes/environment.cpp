#include "../include/environment.hpp"

#include <iostream>

int Environment::set_obs(int i, int j) {
  if ((i >= 0 && i < m_) && (j >= 0 && j < n_)) {
    slots_[pos(i, j)].set_obs(true);
    return 0;
  } else {
    return 1;
  }
}

void Environment::clear_obs() {
  for (int i = 0; i < m_; i++) {
    for (int j = 0; j < n_; j++) {
      at(i, j).set_obs(false);
    }
  }
}

std::ostream& operator<<(std::ostream& os, Environment& obj) {
  os << "┌";
  for (int i = 0; i < obj.n_; i++) os << "─";
  os << "┐\n";

  for (int i = 0; i < obj.m_; i++) {
    os << "│";
    for (int j = 0; j < obj.n_; j++) {
      os << obj.at(i, j);
    }
    os << "│" << i << "\n";
  }

  os << "└";
  for (int i = 0; i < obj.n_; i++) os << "─";
  os << "┘\n\n";

  return os;
}
