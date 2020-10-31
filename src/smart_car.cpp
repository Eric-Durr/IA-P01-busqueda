#include "../include/smart_car.hpp"

#include "../include/environment.hpp"

SmartCar::SmartCar(int loc_i, int loc_j) : loc_i_(loc_i), loc_j_(loc_j) {
  for (int i = 0; i < 4; i++) {
    sensor_.push_back(false);
  }
}

SmartCar::SmartCar(const SmartCar& car) {
  loc_i_ = car.loc_i_;
  loc_j_ = car.loc_j_;

  sensor_.resize(4);
  sensor_[N] = car.sensor_[N];
  sensor_[S] = car.sensor_[S];
  sensor_[E] = car.sensor_[E];
  sensor_[W] = car.sensor_[W];
}

void SmartCar::pos(int i, int j) {
  loc_i_ = i;
  loc_j_ = j;
}
std::vector<int> SmartCar::pos() { return std::vector<int>{loc_i_, loc_j_}; }

void SmartCar::move(cardinal x, int steps) {
  switch (x) {
    case N:
      dec_i(steps);
      break;
    case S:
      inc_i(steps);
      break;
    case E:
      inc_j(steps);
      break;
    case W:
      dec_j(steps);
      break;
    default:
      break;
  }
}

std::ostream& SmartCar::report_env(std::ostream& os) {
  os << "N: ";
  sensor_[N] ? os << "Obstacle" : os << "Free";
  os << "S: ";
  sensor_[S] ? os << "Obstacle" : os << "Free";
  os << "E: ";
  sensor_[E] ? os << "Obstacle" : os << "Free";
  os << "W: ";
  sensor_[W] ? os << "Obstacle" : os << "Free";
  os << "\n";
  return os;
}

void SmartCar::check_environment(Environment& env) {
  if (env.pos(loc_i_ - 1, loc_j_) == -1) {
    sensor_[N] = true;
  } else {
    sensor_[N] = env.at(loc_i_ - 1, loc_j_).is_obs();
  }
  if (env.pos(loc_i_ + 1, loc_j_) == -1) {
    sensor_[S] = true;
  } else {
    sensor_[S] = env.at(loc_i_ + 1, loc_j_).is_obs();
  }

  if (env.pos(loc_i_, loc_j_ + 1) == -1) {
    sensor_[E] = true;
  } else {
    sensor_[E] = env.at(loc_i_, loc_j_ + 1).is_obs();
  }

  if (env.pos(loc_i_, loc_j_ - 1) == -1) {
    sensor_[W] = true;
  } else {
    sensor_[W] = env.at(loc_i_, loc_j_ - 1).is_obs();
  }
}