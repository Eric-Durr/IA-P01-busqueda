#include "../include/environment.hpp"

#include <iostream>

int Environment::pos(int i, int j) const{
  return (i -1)* n_ + j - 1;     
}

int Environment::set(int i, int j, int type) {
  if ((i >= 0 && i < m_) && (j >= 0 && j < n_)) {
    slots_[pos(i, j)].s_change(type);
    return 0;
  } else {
    return 1;
  }
}

int Environment::set_obs(int i, int j) {
  return set(i,j,1);  
}

int Environment::set_meta(int i, int j) {
  return set(i,j,3);
}

void Environment::clear_obs() {
  for (int i = 1; i <= m_; i++) {
    for (int j = 1; j <= n_; j++) {
      delete_obs(i,j);
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
