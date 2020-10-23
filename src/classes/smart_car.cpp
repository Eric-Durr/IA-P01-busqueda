#include "../include/smart_car.hpp"


void SmartCar::pos(int i, int j) {
    loc_i_ = i;
    loc_j_ = j;
}
std::vector<int> SmartCar::pos() {
    return std::vector<int> {loc_i_, loc_j_};
}