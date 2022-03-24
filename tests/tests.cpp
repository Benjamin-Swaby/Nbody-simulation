/*

    tests.cpp by Benjamin Swaby.

    This file will only be called during development to test.
    This file will not be called in the final distribution
    This file will not be linked in the final distribution

    If you intend to edit and or modify this code.
    re-link this file and call run_tests() to run the tests


*/


#include <iostream>
#include <string>

#include "body.hpp"
#include "colors.h"

using namespace nbody;


struct result {
    std::string name;
    bool output;
};

bool particle_creation_2D() {
    body::orbital_entity<body::Vector2> test2D = {{1,2}, {1,2}, 20};
    return sizeof(test2D) == 40;
}

bool particle_creation_3D() {
    body::orbital_entity<body::Vector3> test = {{1,2,3}, {1,2,3} , 10};
    return sizeof(test) == 56;
}


#define number 1
void run_tests() {

    result tests[800];
    tests[0] = result{"Particle Creation 2D", particle_creation_2D()};
    tests[1] = result{"Particle Creation 3D ", particle_creation_3D()};

    for (int i = 0; i <= number; i++) {
        
        std::string result_str;

        if(tests[i].output) {
            result_str = "Passed";
            std::cout << GRN;
        } else {
            result_str = "Failed";
            std::cout << RED;
        }


        std::cout << tests[i].name << " : " << result_str << std::endl; 
        std::cout << reset;
    }



}
