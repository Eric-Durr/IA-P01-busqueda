#ifndef ENV_HPP_
#define ENV_HPP_

#include <stdlib.h>

#include <iostream>
#include <vector>

#include "math.h"
#include "slot.hpp"

class Environment {
 private:
  int m_, n_;
  std::vector<Slot> slots_;

 public:
  Environment(int row = 0, int col = 0);
  Environment(Environment& env);
  ~Environment() {}

  int size() { return slots_.size(); }
  int get_n() const { return n_; }
  int get_m() const { return m_; }

  Slot& at(int i, int j);  // Checked
  int pos(int i, int j) const;
  SmartCar& get_car();
  Slot& get_goal();

  int set_obs(int i, int j);   // Cambia a Obstaculo #checked
  int set_goal(int i, int j);  // Cambia a meta #checked
  int set_car(int i, int j);

  void delete_obs(int i, int j) {
    slots_[pos(i, j)].s_type(V);
  }                  // Elimina una casilla determinada
  void clear_obs();  // Limpia el entorno
  void clear_car();  // Limpia el entorno

  void random_obs(float ratio);  // Genarador de obstaculos

  void move_car(cardinal x, int steps);

  double lineal_d(
      void);  // Funcion heuristica lineal por defecto (coche - meta)
  double manhattan_d(
      void);  // Funcion heuristica manhattan por defecto (coche - meta)

  double lineal_d(const Slot& begin);  // Funcion heuristica lineal por defecto
                                       // (Slot - meta)
  double manhattan_d(const Slot& begin);  // Funcion heuristica manhattan por
                                          // defecto (Slot - meta)
  double lineal_d(const Slot& begin,
                  const Slot& end);  // Funcion heuristica lineal (Slot -Slot)
  double manhattan_d(
      const Slot& begin,
      const Slot& end);  // Funcion heuristica manhattan (Slot -Slot)

  friend std::ostream& operator<<(std::ostream& os, Environment& obj);

 private:
  int set(int i, int j, slot_t type);  // Cambia a un tipo concreto de elemento
};

#endif
