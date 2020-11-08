
#ifndef INCLUDE_SEARCH_HPP_
#define INCLUDE_SEARCH_HPP_

#include <iostream>
#include <stack>
#include <vector>

#include "environment.hpp"

const int MOVE_VAL = 1;

class Search {
 private:
  std::vector<Slot> open_;
  std::vector<Slot> closed_;
  Slot start_, goal_;
  std::vector<Slot> path_;
  Environment env_;
  int opcion_;

 public:
  Search(Environment env, int opcion = 1);
  Search(Search& other);

  bool o_list_empty(void) { return open_.size() == 0; }
  bool c_list_empty(void) { return closed_.size() == 0; }

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

  void trace_path(Slot end);
  std::string path_to_string(void);

  double heuristic_function(const Slot& valor);

 private:
  std::vector<Slot> get_successors(const Slot& q);
  bool is_in_open(const Slot& other);
  bool lower_in_open(const Slot& other);
  bool is_in_close(const Slot& other);
  void update_open_val(const Slot& other);
};

#endif  // INCLUDE_SEARCH_HPP_
