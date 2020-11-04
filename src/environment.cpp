#include "../include/environment.hpp"

#include <cassert>
#include <iostream>

Environment::Environment(int row, int col) : m_(row), n_(col) {
  slots_.resize(m_ * n_);
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

Slot& Environment::at(int i, int j) {
  // assert(i >= 1 && j >= 1 && i <= m_ && j <= n_);

  return slots_[pos(i, j)];
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
    at(i, j).s_change(type);
    return 0;
  } else {
    return 1;
  }
}

int Environment::set_obs(int i, int j) { return set(i, j, O); }
int Environment::set_goal(int i, int j) {
  g_i_ = i;
  g_j_ = j;
  return set(i, j, G);
}
int Environment::set_car(int i, int j) {
  if ((i >= 0 && i < m_) && (j >= 0 && j < n_)) {
    at(i, j).s_change(C);
    at(i, j).get_car().pos(i, j);
    return 0;
  } else {
    return 1;
  }
}

void Environment::clear_obs() {
  for (int i = 0; i < m_; i++) {
    for (int j = 0; j < n_; j++) {
      at(i, j).s_change(V);
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

void Environment::move_car(cardinal x, int steps) {
  std::vector<int> current_pos = get_car().pos();
  get_car().check_environment(*this);
  switch (x) {
    case N:
      if (get_car().sensor(N) == false) {
        at(current_pos[0], current_pos[1]).s_change(V);
        at(current_pos[0] - steps, current_pos[1]).s_change(C);
        get_car().pos(current_pos[0] - steps, current_pos[1]);
      }
      break;
    case S:
      if (get_car().sensor(S) == false) {
        at(current_pos[0], current_pos[1]).s_change(V);
        at(current_pos[0] + steps, current_pos[1]).s_change(C);
        get_car().pos(current_pos[0] + steps, current_pos[1]);
      }
      break;
    case E:
      if (get_car().sensor(E) == false) {
        at(current_pos[0], current_pos[1]).s_change(V);
        at(current_pos[0], current_pos[1] + steps).s_change(C);
        get_car().pos(current_pos[0], current_pos[1] + steps);
      }
      break;
    case W:
      if (get_car().sensor(W) == false) {
        at(current_pos[0], current_pos[1]).s_change(V);
        at(current_pos[0], current_pos[1] - steps).s_change(C);

        get_car().pos(current_pos[0], current_pos[1] - steps);
      }
      break;
    default:
      break;
  }
}

int Environment::lineal_d() {  // Funcion Euclidea
  /* std::cout << "meta j:" << g_j_ << "\n";                 // 9
   std::cout << "coche j:" << get_car().pos()[1] << "\n";  // 0
   std::cout << "meta i:" << g_i_ << "\n";                 // 9
   std::cout << "coche i:" << get_car().pos()[0] << "\n";  // 0
   std::cout << "resultado: "
             << sqrt(pow(g_j_ - get_car().pos()[1], 2) +
                     pow(g_i_ - get_car().pos()[0], 2))
             << "\n";
 */
  return sqrt(pow(g_j_ - get_car().pos()[1], 2) +
              pow(g_i_ - get_car().pos()[0], 2));
}

int Environment::manhattan_d() {
  return (abs(g_i_ - get_car().pos()[0]) + abs(g_j_ - get_car().pos()[1]));
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
    os << "│" << i + 1 << "\n";
  }

  os << "└";
  for (int i = 0; i < obj.n_; i++) os << "─";
  os << "┘\n\n";

  return os;
}
