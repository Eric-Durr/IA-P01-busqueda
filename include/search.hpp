
#ifndef INCLUDE_SEARCH_HPP_
#define INCLUDE_SEARCH_HPP_

#include <iostream>
#include <stack>
#include <vector>

#include "environment.hpp"

class Search {
 private:
  std::vector<Slot> open_;
  std::vector<Slot> close_;
  Slot start_, goal_;
  std::stack<Slot> path_;
  Environment env_;

 public:
  Search(Environment env);
  Search(Search& other);

  bool o_list_empty(void) { return open_.size() == 0; }
  bool c_list_empty(void) { return close_.size() == 0; }

  int o_list_size(void) { return open_.size(); }
  std::vector<int> get_start_pos(void) {
    return std::vector<int>{start_.pos_i(), start_.pos_j()};
  }
  std::vector<int> get_car_pos(void) { return env_.get_car().pos(); }
  std::vector<int> get_goal_pos(void) {
    return std::vector<int>{goal_.pos_i(), goal_.pos_j()};
  }
  int linear_value(void) { return env_.lineal_d(); }
  int manhattan_value(void) { return env_.manhattan_d(); }

  void a_star_algorithm(void);
};

#endif  // INCLUDE_SEARCH_HPP_