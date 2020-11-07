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

void Search::a_star_algorithm(void) {
  start_.set_f(0);
  open_.push_back(start_);

  while (o_list_empty() == false) {
    /* Searching the Slot with least f on open list */
    Slot min = open_.back();
    for (auto current : open_)
      if (min.get_f() >= current.get_f()) {
        min = current;
      }
    open_.erase(std::find(open_.begin(), open_.end(), min));
    /*  ---  */

    close_.push_back(min);
    /* Generating successors */
    std::vector<Slot> successors = get_successors(min);
    /*  ---  */

    /* Measure values */
    int new_g, new_h, new_f;
    /*  ---  */

    /* For each successor: */
    for (auto var : successors) {
      if (var.get_obs() == G) {
        env_.at(var.pos_i(), var.pos_j()).set_parents(min.pos_i(), min.pos_j());
        var.set_parents(min.pos_i(), min.pos_j());
        var.set_g(min.get_g() + MOVE_VAL);           /* 2nd arg is in doubt */
        var.set_f(var.get_g() + env_.lineal_d(var)); /* blocked h */
        std::cout << "Goal slot found\n";
        std::cout << "(" << var.pos_i() << "," << var.pos_i() << ")\n";

        trace_path(var);
        return;

        /* If it's not yet at close list and it´s not an obstacle */
      } else if ((is_in_close(var) == false) && (var.is_obs() == false)) {
        new_g = min.get_g() + MOVE_VAL;
        new_h = env_.lineal_d(var);
        new_f = new_g + new_h;

        /* If it's not at open list or it is but with lower f, insert it */

        if ((is_in_open(var) == false) ||
            ((is_in_open(var) == true) && (lower_in_open(var) == false))) {
          env_.at(var.pos_i(), var.pos_j())
              .set_parents(min.pos_i(), min.pos_j());
          var.set_parents(min.pos_i(), min.pos_j());
          var.set_g(new_g);
          var.set_f(new_f);
          std::cout << "Introducing to open a new step\n";
          std::cout << "(" << var.pos_i() << "," << var.pos_j() << ")\n";
          std::cout << "G: " << var.get_g() << "\n";
          std::cout << "H: " << env_.lineal_d(var) << "\n";
          std::cout << "F: " << var.get_f() << "\n";

          open_.push_back(var);
        }
      }
      /*  ---  */
    }

    /* Controll with found dest */
  }
}

void Search::trace_path(Slot temp) {
  std::vector<Slot> path;
  while (temp.parent_i() != -1 && temp.parent_j() != -1) {
    std::cout << "(" << temp.pos_i() << "," << temp.pos_j() << ")->";
    path.push_back(temp);
    temp = env_.at(temp.parent_i(), temp.parent_j());
  }

  std::cout << "\n";
  for (int i = path.size() - 1; i >= 0; i--) {
    std::cout << "(" << path[i].pos_i() << "," << path[i].pos_j() << ")->";
  }
  std::cout << "\n";
}

/* Private methods */
std::vector<Slot> Search::get_successors(const Slot& q) {
  Slot north = env_.pos(q.pos_i() - 1, q.pos_j()) != -1
                   ? env_.at(q.pos_i() - 1, q.pos_j())
                   : Slot(-1, -1, O);
  Slot west = env_.pos(q.pos_i(), q.pos_j() - 1) != -1
                  ? env_.at(q.pos_i(), q.pos_j() - 1)
                  : Slot(-1, -1, O);
  Slot south = env_.pos(q.pos_i() + 1, q.pos_j()) != -1
                   ? env_.at(q.pos_i() + 1, q.pos_j())
                   : Slot(-1, -1, O);
  Slot east = env_.pos(q.pos_i(), q.pos_j() + 1) != -1
                  ? env_.at(q.pos_i(), q.pos_j() + 1)
                  : Slot(-1, -1, O);
  return std::vector<Slot>{north, west, south, east};
}

bool Search::is_in_open(const Slot& other) {
  bool flag = false;
  for (auto var : open_) {
    if ((var.pos_i() == other.pos_i()) && (var.pos_j() == other.pos_j())) {
      flag = true;
    }
  }
  return flag;
}

bool Search::is_in_close(const Slot& other) {
  bool flag = false;
  for (auto var : close_) {
    if ((var.pos_i() == other.pos_i()) && (var.pos_j() == other.pos_j())) {
      flag = true;
    }
  }
  return flag;
}

bool Search::lower_in_open(const Slot& other) {
  bool flag = false;

  for (auto var : open_) {
    if ((var.pos_i() == other.pos_i()) && (var.pos_j() == other.pos_j())) {
      if (var.get_f() < other.get_f()) {
        flag = true;
      }
    }
  }
  return flag;
}