#include "../include/environment.hpp"

#include <cassert>
#include <iostream>

Environment::Environment(int row, int col) : m_(row), n_(col) {
  slots_.resize(m_ * n_);
  /* for (int i = 1; i <= row; i++) {
    for (int j = 1; j <= row; j++) {
      Slot aux(i, j);
      slots_.push_back(aux);
    }
  } */
}
Environment::Environment(Environment& env) {
  m_ = env.m_;
  n_ = env.n_;

  for (int i = 1; i <= m_; i++) {
    for (int j = 1; j <= n_; j++) {
      slots_[pos(i, j)] = env.at(i, j);
    }
  }
}

Slot& Environment::at(int i, int j) {
  // assert(i >= 1 && j >= 1 && i <= m_ && j <= n_);

  return slots_[pos(i, j)];
}

int Environment::pos(int i, int j) const {
  if (i >= 1 && j >= 1 && i <= m_ && j <= n_) {
    return (i - 1) * n_ + j - 1;
  } else {
    return -1;
  }
}

int Environment::set(int i, int j, slot_t type) {
  if ((i >= 1 && i <= m_) && (j >= 1 && j <= n_)) {
    slots_[pos(i, j)].s_change(type);
    return 0;
  } else {
    return 1;
  }
}

int Environment::set_obs(int i, int j) { return set(i, j, O); }
int Environment::set_goal(int i, int j) { return set(i, j, G); }
int Environment::set_car(int i, int j) { return set(i, j, C); }

void Environment::clear_obs() {
  for (int i = 1; i <= m_; i++) {
    for (int j = 1; j <= n_; j++) {
      delete_obs(i, j);
    }
  }
}

SmartCar& Environment::get_car() {
  for (unsigned i = 0; i < slots_.size(); i++)
    if (slots_[i].s_type() == C) return slots_[i].get_car();
}

void Environment::random_obs(float ratio) {
  clear_obs();
  srand(time(NULL));
  int size = m_ * n_;
  int r_obs = size * ratio;

  for (int i = 1; i < r_obs; i++) {
    int r_m = rand() % m_ + 1;
    int r_n = rand() % n_ + 1;
    set_obs(r_n, r_m);
  }
}

void Environment::move_car(cardinal x, int steps, Environment& env) {
  std::vector<int> current_pos = get_car().pos();
  std::cout << current_pos[0] << current_pos[1] << "\n";
  get_car().report_env(std::cout);
  get_car().check_environment(env);
  switch (x) {
    case N:
      if (get_car().sensor(N) == false) {
        at(current_pos[0], current_pos[1]).s_change(V);
        at(current_pos[0] - steps, current_pos[1]).s_change(C);
        get_car().move(N, steps);
      }
      break;
    case S:
      if (get_car().sensor(S) == false) {
        at(current_pos[0], current_pos[1]).s_change(V);
        at(current_pos[0] + steps, current_pos[1]).s_change(C);
        get_car().move(S, steps);
      }
      break;
    case E:
      if (get_car().sensor(E) == false) {
        at(current_pos[0], current_pos[1]).s_change(V);
        at(current_pos[0], current_pos[1] + steps).s_change(C);
        get_car().move(E, steps);
      }
      break;
    case W:
      if (get_car().sensor(W) == false) {
        at(current_pos[0], current_pos[1]).s_change(V);
        at(current_pos[0], current_pos[1] - steps).s_change(C);
        get_car().move(W, steps);
      }
      break;
    default:
      break;
  }

  current_pos = get_car().pos();
  std::cout << current_pos[0] << current_pos[1] << "\n";
}

std::ostream& operator<<(std::ostream& os, Environment& obj) {
  os << "┌";
  for (int i = 0; i < obj.n_; i++) os << "─";
  os << "┐\n";

  for (int i = 1; i <= obj.m_; i++) {
    os << "│";
    for (int j = 1; j <= obj.n_; j++) {
      os << obj.at(i, j);
    }
    os << "│" << i << "\n";
  }

  os << "└";
  for (int i = 0; i < obj.n_; i++) os << "─";
  os << "┘\n\n";

  return os;
}
