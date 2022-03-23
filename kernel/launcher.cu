#include "launcher.cuh"
#include "body.hpp"

using namespace nbody;
 
/*
    Laucher.cu by Benjamin Swaby

    This file will aim to prepare the date structures ready to be augmented by
    the kernel. 

    It will account for both 2D and 3D space with function overloading of 2 launcher functions that will
    ultimately have to call 2 different kernels to deal with the extra dimension.

*/



void kernel::launcher(body::orbital_entity<body::Vector3> *entities, size_t length){
    
}
void kernel::launcher(body::orbital_entity<body::Vector2> *entities, size_t length) {

}