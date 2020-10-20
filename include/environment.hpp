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
        void set_obs(int i, int j) { slots_[pos(i, j)].set_obs(true); }
        void delete_obs(int i, int j) { slots_[pos(i, j)].set_obs(false); }
        void clear_obs();

        
        friend std::ostream& operator<< (std::ostream& os,  Environment& obj);

        private:

        int pos(int i, int j) const
        {
            return (i -1)* n_ + j - 1;
        }

};