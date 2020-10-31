#ifndef S_CAR_HPP_
#define S_CAR_HPP_

#include <algorithm>
#include <iostream>
#include <vector>

enum cardinal { N, W, S, E };
const short i_d[] = {-1, 0, 1, 0};
const short j_d[] = {0, 1, 0, -1};

class Environment;
class SmartCar {
 private:
  int loc_i_, loc_j_;
  std::vector<bool> sensor_;

 public:
  SmartCar(int loc_i = 0, int loc_j = 0);
  SmartCar(const SmartCar& car);
  ~SmartCar(){};

  void pos(int i, int j);
  std::vector<int> pos();

  std::vector<bool>& sensor(void) { return sensor_; }
  bool sensor(cardinal x) { return sensor_[x]; }
  void move(cardinal x, int steps);
  std::ostream& report_env(std::ostream& os);

  void check_environment(Environment& env);

 private:
  void inc_i(int num) { loc_i_ += num; }
  void inc_j(int num) { loc_j_ += num; }
  void dec_i(int num) { loc_i_ -= num; }
  void dec_j(int num) { loc_j_ -= num; }
};

#endif