#include "../include/search.hpp"

Search::Search(Environment env, int opcion)
    : goal_(env.get_goal()), opcion_(opcion), env_(env) {
  start_.pos_i(env_.get_car().pos()[0]);
  start_.pos_j(env_.get_car().pos()[1]);
}

Search::Search(Search& other)
    : goal_(other.goal_),
      start_(other.start_),
      opcion_(other.opcion_),
      env_(other.env_) {
  for (auto slot : other.open_) {
    open_.push_back(slot);
  }
  for (auto slot : other.closed_) {
    closed_.push_back(slot);
  }
}

double Search::heuristic_function(const Slot& valor) {
  switch (opcion_) {
    case 1:
      return env_.lineal_d(valor);
      break;

    case 2:
      return env_.manhattan_d(valor);
      break;
    default:
      break;
  }
}

void Search::a_star_algorithm(void) {
  start_.set_f(0);
  open_.push_back(start_);
  bool found_goal = false;

  while (o_list_empty() == false) {
    /* Searching the Slot with least f on open list */
    Slot min = open_.back();
    for (auto current : open_)
      if (min.get_f() >= current.get_f()) {
        min = current;
      }
    open_.erase(std::find(open_.begin(), open_.end(), min));
    /*  ---  */

    closed_.push_back(min);

    /* Generating successors */
    std::vector<Slot> successors = get_successors(min);
    /*  ---  */

    /* Measure values */
    double new_g, new_h, new_f;
    /*  ---  */

    /* For each successor: */
    for (auto var : successors) {
      if (var.get_obs() == G) {
        env_.at(var.pos_i(), var.pos_j()).set_parents(min.pos_i(), min.pos_j());
        var.set_parents(min.pos_i(), min.pos_j());
        var.set_g(min.get_g() + MOVE_VAL); /* 2nd arg is in doubt */
        var.set_f(var.get_g() + heuristic_function(var)); /* blocked h */
        std::cout << "Goal slot found\n";
        trace_path(var);
        found_goal = true;
        return;

        /* If it's not yet at close list and it´s not an obstacle */
      } else if ((is_in_close(var) == false) && (var.is_obs() == false)) {
        new_g = min.get_g() + MOVE_VAL;
        new_h = heuristic_function(var);
        new_f = new_g + new_h;

        /* If it's not at open list or it is but with lower f, insert it */
        if (is_in_open(var) == false) {
          env_.at(var.pos_i(), var.pos_j())
              .set_parents(min.pos_i(), min.pos_j());
          var.set_parents(min.pos_i(), min.pos_j());
          var.set_g(new_g);
          var.set_f(new_f);
          if ((is_in_open(var) == true) && (lower_in_open(var) == false)) {
            update_open_val(var);
          } else {
            open_.push_back(var);
          }
        }
      }
    }
    /*  ---  */
  }

  if (found_goal == false) {
    std::cout << "Failed to find the goal\n";
  }
  return;
}

void Search::trace_path(Slot temp) {
  while (temp.parent_i() != -1 && temp.parent_j() != -1) {
    path_.push_back(temp);
    temp = env_.at(temp.parent_i(), temp.parent_j());
  }
  path_.push_back(start_);
  std::cout << "\n";
  for (int i = path_.size() - 1; i >= 0; i--) {
    std::cout << "(" << path_[i].pos_i() + 1 << "," << path_[i].pos_j() + 1
              << ")->";
  }
  std::cout << "\n";
}

std::string Search::path_to_string(void) {
  std::string path = "";
  for (int i = path_.size() - 1; i >= 0; i--) {
    path += "(";
    path += std::to_string(path_[i].pos_i() + 1);
    path += ",";
    path += std::to_string(path_[i].pos_j() + 1);
    path += ")->";
  }
  std::cout << "\n";
}

std::ostream& operator<<(std::ostream& os, Search& object) {
  os << " --- TRAZA DE MOVIMIENTO ---\n\n";
  os << object.path_size() << "\n";
  for (int i = object.path_size(); i >= 0; i--) {
    object.env_.delete_obs(object.path_[i].parent_i(),
                           object.path_[i].parent_j());
    object.env_.set_car(object.path_[i].pos_i(), object.path_[i].pos_j());
    os << object.env_ << std::endl;
  }
  return os;
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
  for (auto var : closed_) {
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

void Search::update_open_val(const Slot& other) {
  for (auto var : open_) {
    if ((var.pos_i() == other.pos_i()) && (var.pos_j() == other.pos_j())) {
      var.set_f(other.get_f());
      var.set_g(other.get_g());
      var.set_parents(other.parent_i(), other.parent_j());
    }
  }
}