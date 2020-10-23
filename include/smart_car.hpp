#pragma once
#include <iostream>
#include <vector>

enum cardinal {N, S, E, W};

class SmartCar {
    private:
        int loc_i_, loc_j_;
        std::vector<bool> sensor_;
    public:
        SmartCar();
        ~SmartCar(){};

        void pos(int i, int j);
        std::vector<int> pos();
        int  env_pos();

        void inc_i(int num) { loc_i_ += num; }
        void inc_j(int num) { loc_j_ += num; }
        std::vector<bool>& sensor(void) { return sensor_; }
        bool sensor(cardinal x) { return sensor_[x]; }
};