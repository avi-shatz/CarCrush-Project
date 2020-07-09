#pragma once

#include "Obj.h"
#include "Car.h"
#include "Wall.h"
#include "Joint.h"
#include "RobotDriver.h"

#include <iostream>
#include <typeinfo>

// Sample struct for exception throwing
struct UnknownCollision : public std::exception
{
    UnknownCollision(Obj& a, Obj& b) : first(a), second(b)
    {
        std::cout << "Unknown collision of " << typeid(a).name() << " and "
                     << typeid(b).name() << std::endl;
    }
    Obj& first;
    Obj& second;
};

void processCollision(Obj& object1, Obj& object2);
