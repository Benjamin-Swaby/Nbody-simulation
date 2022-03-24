/*

    main.cpp by Benjamin Swaby
    main entry point and hotpath for program
*/





#include <iostream>

#include "body.hpp"
#include "launcher.cuh"
#include "tests.h"

using namespace nbody;

int main(void) {
    
    const long long Decade_In_Secs = 86400 * 365 * 10;
    const long long Day_In_Secs = 86400;
    const long long Centuary = 86400 * 365 * 10;

    run_tests(); //TODO remove at runtime

    std::cout << "Main" << std::endl;

    body::orbital_entity<body::Vector3> objects[4] = {
        {{0.0,0.0,0.0},{0,0,0}, 1.989e30}, // SUN
        {{57.909e9,0.0,0.0},{0.0,0.0,8.6e6}, 0.33011e24},
        {{-57.909e9,0.0,0.0},{0.0,0.0,-8.6e6}, 0.33011e24},
    };

    kernel::launcher(objects,3,(57.909e9 * 4),86400 * 365 * 10,Day_In_Secs);   
}