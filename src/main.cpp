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
    
    run_tests(); //TODO remove at runtime

    std::cout << "Main" << std::endl;

    body::orbital_entity<body::Vector3> objects[4] = {
        {{57.909e9,0.0,0.0},{0.0,47.36e3,0.0}, 0.33011e24},
        {{0.0,0.0,0.0},{0,0,0}, 1.989e30}, //sun
        {{7.0,8.0,9.0},{1.0,2.0,3.0}, 10.0},
        {{10.0,11.0,12.0},{1,2,3}, 10.0}
    };

    kernel::launcher(objects,4);

    
}