#include "../include/search.hpp"

Search::Search(Environment env) : goal_(env.get_goal()), env_(env) {
  start_.pos_i(env_.get_car().pos()[0]);
  start_.pos_j(env_.get_car().pos()[1]);
}

Search::Search(Search& other)
    : goal_(other.goal_), start_(other.start_), env_(other.env_) {
  for (auto slot : other.open_) {
    open_.push_back(slot);
  }
  for (auto slot : other.close_) {
    close_.push_back(slot);
  }
}
