#include "../include/search.hpp"

Search::Search(Environment env, int opcion)
    : goal_(env.get_goal()), env_(env), opcion_(opcion), n_expanded_(0) {
  start_.pos_i(env_.get_car().pos()[0]);
  start_.pos_j(env_.get_car().pos()[1]);
}

Search::Search(Search& other)
    : start_(other.start_),
      goal_(other.goal_),
      env_(other.env_),
      opcion_(other.opcion_),
      n_expanded_(other.n_expanded_) {
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
  return 0;
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

        std::cout << std::endl;
        std::cout << "\nGOAL FOUND !\n";
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

          open_.push_back(var);
          n_expanded_++;
        }
      }
    }
    /*  ---  */
  }

  if (found_goal == false) {
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "VEHICLE CANT REACH THE GOAL\n ";
    std::cout << "Nodes expanded: " << n_expanded_ << std::endl;
  }
  return;
}

void Search::trace_path(Slot temp) {
  while (temp.parent_i() != -1 && temp.parent_j() != -1) {
    path_.push_back(temp);
    temp = env_.at(temp.parent_i(), temp.parent_j());
  }

  std::cout << "\n";
}

std::string Search::path_to_string(void) {
  std::string path = "";
  if (path_.size() != 0) {
    for (int i = path_.size() - 1; i >= 0; i--) {
      path += "(";
      path += std::to_string(path_[i].pos_i() + 1);
      path += ",";
      path += std::to_string(path_[i].pos_j() + 1);
      if (i == 0) {
        path += ")";
      } else {
        path += ")->";
      }
    }
  }
  return path;
}

std::ostream& operator<<(std::ostream& os, Search& object) {
  os << " --- MOVES TRACEBACK ---\n\n";

  os << "Number of moves: " << object.path_size() << "\n";
  std::cout << "Nodes expanded: " << object.nodes_expanded() << std::endl;
  os << "MOVES: " << object.path_to_string() << "\n";
  for (int i = object.path_size() - 1; i > 0; i--) {
    if (object.path_[i].pos_i() == object.path_[i].parent_i() &&
        object.path_[i].pos_j() < object.path_[i].parent_j()) {
      object.env_.at(object.path_[i].pos_i(), object.path_[i].pos_j())
          .s_type(L);
    }
    if (object.path_[i].pos_i() == object.path_[i].parent_i() &&
        object.path_[i].pos_j() > object.path_[i].parent_j()) {
      object.env_.at(object.path_[i].pos_i(), object.path_[i].pos_j())
          .s_type(R);
    }
    if (object.path_[i].pos_i() < object.path_[i].parent_i() &&
        object.path_[i].pos_j() == object.path_[i].parent_j()) {
      object.env_.at(object.path_[i].pos_i(), object.path_[i].pos_j())
          .s_type(U);
    }
    if (object.path_[i].pos_i() > object.path_[i].parent_i() &&
        object.path_[i].pos_j() == object.path_[i].parent_j()) {
      object.env_.at(object.path_[i].pos_i(), object.path_[i].pos_j())
          .s_type(D);
    }
  }
  os << object.env_ << std::endl;
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