#include "../include/environment.hpp"

#include <cassert>
#include <iostream>

Environment::Environment(int row, int col) : m_(row), n_(col) {
  slots_.resize(m_ * n_);
  for (int i = 0; i < m_; i++) {
    for (int j = 0; j < n_; j++) {
      at(i, j).pos_i(i);
      at(i, j).pos_j(j);
    }
  }
}

Environment::Environment(Environment& env) {
  m_ = env.m_;
  n_ = env.n_;

  slots_.resize(m_ * n_);
  for (int i = 0; i < m_; i++) {
    for (int j = 0; j < n_; j++) {
      at(i, j) = env.at(i, j);
    }
  }
}

Slot& Environment::at(int i, int j) {
  /* if (i >= 0 && j >= 0 && i < m_ && j < n_) { */
  return slots_[pos(i, j)];
  /* } else {
    Slot obs(-1, -1, O);
    return obs;
  } */
}

int Environment::pos(int i, int j) const {
  if (i >= 0 && j >= 0 && i < m_ && j < n_) {
    return (i)*n_ + j;
  } else {
    return -1;
  }
}

int Environment::set(int i, int j, slot_t type) {
  if ((i >= 0 && i < m_) && (j >= 0 && j < n_)) {
    at(i, j).s_type(type);
    return 0;
  } else {
    return 1;
  }
}

int Environment::set_obs(int i, int j) { return set(i, j, O); }
int Environment::set_goal(int i, int j) { return set(i, j, G); }
int Environment::set_car(int i, int j) {
  if ((i >= 0 && i < m_) && (j >= 0 && j < n_)) {
    at(i, j).s_type(C);
    at(i, j).get_car().pos(i, j);
    return 0;
  } else {
    return 1;
  }
}

void Environment::clear_obs() {
  for (int i = 0; i < m_; i++) {
    for (int j = 0; j < n_; j++) {
      at(i, j).s_type(V);
    }
  }
}

SmartCar& Environment::get_car() {
  for (int i = 0; i < m_; i++) {
    for (int j = 0; j < n_; j++) {
      if (at(i, j).s_type() == C) {
        return at(i, j).get_car();
      }
    }
  }
}
Slot& Environment::get_goal() {
  for (int i = 0; i < m_; i++) {
    for (int j = 0; j < n_; j++) {
      if (at(i, j).s_type() == G) {
        return at(i, j);
      }
    }
  }
}

void Environment::random_obs(float ratio) {
  srand(time(NULL));
  int r_obs = ratio * n_ * m_;

  for (int i = 0; i < r_obs; i++) {
    int r_m = rand() % m_;
    int r_n = rand() % n_;
    if ((at(r_n, r_m).s_type() != C) && (at(r_n, r_m).s_type() != G)) {
      set_obs(r_n, r_m);
    }
  }
}

void Environment::move_car(cardinal x, int steps) {
  std::vector<int> current_pos = get_car().pos();
  get_car().check_environment(*this);
  switch (x) {
    case N:
      if (get_car().sensor(N) == false) {
        at(current_pos[0], current_pos[1]).s_type(V);
        at(current_pos[0] - steps, current_pos[1]).s_type(C);
        get_car().pos(current_pos[0] - steps, current_pos[1]);
      }
      break;
    case S:
      if (get_car().sensor(S) == false) {
        at(current_pos[0], current_pos[1]).s_type(V);
        at(current_pos[0] + steps, current_pos[1]).s_type(C);
        get_car().pos(current_pos[0] + steps, current_pos[1]);
      }
      break;
    case E:
      if (get_car().sensor(E) == false) {
        at(current_pos[0], current_pos[1]).s_type(V);
        at(current_pos[0], current_pos[1] + steps).s_type(C);
        get_car().pos(current_pos[0], current_pos[1] + steps);
      }
      break;
    case W:
      if (get_car().sensor(W) == false) {
        at(current_pos[0], current_pos[1]).s_type(V);
        at(current_pos[0], current_pos[1] - steps).s_type(C);

        get_car().pos(current_pos[0], current_pos[1] - steps);
      }
      break;
    default:
      break;
  }
}

double Environment::lineal_d() {
  return sqrt(pow(get_goal().pos_j() - get_car().pos()[1], 2) +
              pow(get_goal().pos_i() - get_car().pos()[0], 2));
}

double Environment::manhattan_d() {
  return (abs(get_goal().pos_i() - get_car().pos()[0]) +
          abs(get_goal().pos_j() - get_car().pos()[1]));
}

double Environment::lineal_d(const Slot& begin) {
  return sqrt(pow(get_goal().pos_j() - begin.pos_j(), 2) +
              pow(get_goal().pos_i() - begin.pos_i(), 2));
}

double Environment::manhattan_d(const Slot& begin) {
  return (abs(get_goal().pos_i() - begin.pos_i()) +
          abs(get_goal().pos_j() - begin.pos_j()));
}

double Environment::lineal_d(const Slot& begin, const Slot& end) {
  return sqrt(pow(end.pos_j() - begin.pos_j(), 2) +
              pow(end.pos_i() - begin.pos_i(), 2));
}

double Environment::manhattan_d(const Slot& begin, const Slot& end) {
  return (abs(end.pos_i() - begin.pos_i()) + abs(end.pos_j() - begin.pos_j()));
}

std::ostream& operator<<(std::ostream& os, Environment& obj) {
  os << "┌";
  for (int i = 0; i < obj.n_; i++) os << "───";
  os << "┐\n";

  for (int i = 0; i < obj.m_; i++) {
    os << "│";
    for (int j = 0; j < obj.n_; j++) {
      os << obj.at(i, j);
    }
    os << "│" << i + 1 << "\n";
  }

  os << "└";
  for (int i = 0; i < obj.n_; i++) os << "───";
  os << "┘\n\n";

  return os;
}
