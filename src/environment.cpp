#include "../include/environment.hpp"
#include <iostream>
#include <cassert>

Environment::Environment(int row = 0, int col = 0): 
  m_(row),
  n_(col) {
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < row; j++) {
        Slot aux(i, j, V);
        slots_.push_back(aux);
      }  
    }
}
Environment::Environment(Environment& env) {
  m_ = env.m_;
  n_ = env.n_;
  
    for (int i = 0; i < m_; i++) {
      for (int j = 0; j < n_; j++) {
        slots_[pos(i, j)] = env.at(i, j);
      }  
    }
}

Slot Environment::at(int i, int j) {
  assert(i >= 0 && j >= 0 && 
         i <= m_ && j <= n_);

  return slots_[pos(i, j)]; 
}



int Environment::pos(int i, int j) const {
  if ( i >= 0 && j >= 0 && 
       i <= m_ && j <= n_) {
    return (i -1)* n_ + j - 1;
  } else {
    return -1;
  }
}

int Environment::set_obs(int i, int j) {
  if ((i >= 0 && i < m_) && (j >= 0 && j < n_)) {
    slots_[pos(i, j)].set_obs(O);
    return 0;
  } else {
    return 1;
  }
}

int Environment::set_car(int i, int j) {
  if ((i >= 0 && i < m_) && (j >= 0 && j < n_)) {
    slots_[pos(i, j)].set_obs(C);
    return 0;
  } else {
    return 1;
  }
}

int Environment::set_goal(int i, int j) {
if ((i >= 0 && i < m_) && (j >= 0 && j < n_)) {
    slots_[pos(i, j)].set_obs(G);
    return 0;
  } else {
    return 1;
  }
}

SmartCar& Environment::get_car() {
  for (unsigned i = 0; i < slots_.size(); i++)  
    if (slots_[i].s_type() == 2)
      return slots_[i].get_car(); 
}


void Environment::clear_obs() {
  for (int i = 0; i < m_; i++) {
    for (int j = 0; j < n_; j++) {
      at(i, j).set_obs(V);
    }
  }
}

void Environment::move_car(cardinal x, int steps) {
    std::vector<int> current_pos = get_car().pos(); 
    switch (x) {
    case N:
        if (get_car().sensor(N) == false) 
            at(current_pos[0], current_pos[1]).s_change(V);
            at(current_pos[0] - steps, current_pos[1]).s_change(C);
        break;
    case S:
        if (get_car().sensor(S) == false)
            at(current_pos[0], current_pos[1]).s_change(V);
            at(current_pos[0] + steps, current_pos[1]).s_change(C);
        break;
    case E:
        if (get_car().sensor(E) == false)            
            at(current_pos[0], current_pos[1]).s_change(V);
            at(current_pos[0], current_pos[1] + steps).s_change(C);
        break;
    case W:
        if (get_car().sensor(W) == false)
            at(current_pos[0], current_pos[1]).s_change(V);
            at(current_pos[0], current_pos[1] - steps).s_change(C);
        break;
    default:
        break;
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
