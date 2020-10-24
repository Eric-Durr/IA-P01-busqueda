#pragma once
#include "slot.hpp"
#include <iostream>
#include <vector>

class Environment
{
    private:
        int m_, n_;
        std::vector<Slot> slots_;
    public:
        Environment(int row, int col): 
        m_(row),
        n_(col) 
        {
            slots_.resize(m_ * n_);
        }
        ~Environment(){}
        int size() { return slots_.size(); }
        Slot& at(int i, int j) { return slots_[pos(i, j)]; } 
        int set_obs(int i, int j); //Cambia a Obstaculo
        int set_meta(int i, int j); //Cambia a meta
        void delete_obs(int i, int j) { slots_[pos(i, j)].s_change(0); } //Elimina una casilla determinada
        void clear_obs(); //Limpia el entorno

        friend std::ostream& operator<< (std::ostream& os,  Environment& obj);

        private:

        int pos(int i, int j) const;
        int set(int i, int j, int type); //Cambia a un tipo concreto de elemento
};