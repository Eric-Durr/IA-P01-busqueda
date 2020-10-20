#include "../include/slot.hpp"

Slot::Slot(int op)
{
    switch (op)
    {
    case 0:
        obstacle_ = false;
        break;
        
    case 1:
        obstacle_ = true;
        break;
                
    case 3:
        /* coche */
        break;
    default:
        obstacle_ = false;
        break;
    }
}

std::ostream& operator<< (std::ostream& os, const Slot& obj)
{
    if (obj.obstacle_) 
    {
        os << "■";
    } else {
        os << " ";
    } 
    return os;
}