#ifndef ENV_HPP_
#define ENV_HPP_


#include "slot.hpp"
#include <iostream>
#include <vector>

class Environment
{
    private:
        int m_, n_;
        std::vector<Slot> slots_;
    public:
        Environment(int row = 0, int col = 0);
        Environment(Environment& env);
        ~Environment(){}
        int size() { return slots_.size(); }
        Slot& at(int i, int j);
        int pos(int i, int j) const;
        

        int set_obs(int i, int j);
        int set_car(int i, int j);
        int set_goal(int i, int j);
        SmartCar& get_car();

        void delete_obs(int i, int j) { slots_[pos(i, j)].set_obs(V); }
        void clear_obs();

        void move_car(cardinal x, int steps);

        
        friend std::ostream& operator<< (std::ostream& os,  Environment& obj);

        private:

        

};

#endif