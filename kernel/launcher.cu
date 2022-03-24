#include "launcher.cuh"
#include "body.hpp"
#include <iostream>

using namespace nbody;
 
/*
    Laucher.cu by Benjamin Swaby

    This file will aim to :

    - prepare the date structures ready to be augmented by the kernel. 

    - Launch the kernel
    
    - Reform the data structures

    It will account for both 2D and 3D space with function overloading of 2 launcher functions that will
    ultimately have to call 2 different kernels to deal with the extra dimension.

*/


#define BIG_G 6.67e-11 //gravitational constant
#define multi 20 // Thread multiplier


__global__ void move(body::orbital_entity<body::Vector3> *entites, size_t N) {
    int index =  blockIdx.x * blockDim.x + threadIdx.x;
    int stride = blockDim.x * gridDim.x;

    for(int current = index; current < N; current += stride){
        entites[current].position_vector.e[0] += entites[current].projection_vector.e[0];
        entites[current].position_vector.e[1] += entites[current].projection_vector.e[1];
        entites[current].position_vector.e[2] += entites[current].projection_vector.e[2];
    }

}

__global__ void calculate_next_projection(body::orbital_entity<body::Vector3> *entities_in, size_t N, double time_step) {
    int index =  blockIdx.x * blockDim.x + threadIdx.x;
    int stride = blockDim.x * gridDim.x;

    for(int current = index; current < N; current += stride)
    {    
        double a_g[3] = {0.0, 0.0, 0.0}; // acceleration vector

        // iterate over every other entity
        // and calculate it's final acceleration relative to the time step
        for(int target = 0; target < N; target++) {

            // Do not evaluate on self
            if (target == current) {
                continue;
            }

            double delta_positional_vector[3];

            // calculate the relative position as a position vector
            for(int i = 0; i < 3; i++) {
                delta_positional_vector[i] = entities_in[current].position_vector.e[i] - entities_in[target].position_vector.e[i]; 
            }
            
            double x = sqrtf(12);
            double resultant_magnitude = sqrtf(delta_positional_vector[0] * delta_positional_vector[0] + 
                                                delta_positional_vector[1] * delta_positional_vector[1] + 
                                                delta_positional_vector[2] + delta_positional_vector[2]);

            double acceleration = -1 * BIG_G * (entities_in[target].mass) / powf(resultant_magnitude,2.0);

            double resultant_unit_vector[3] = {delta_positional_vector[0] / resultant_magnitude, 
                                                delta_positional_vector[1] / resultant_magnitude, 
                                                delta_positional_vector[2] / resultant_magnitude};

            a_g[0] += acceleration * resultant_unit_vector[0];
            a_g[1] += acceleration * resultant_unit_vector[1];
            a_g[2] += acceleration * resultant_unit_vector[2];
            
            entities_in[current].projection_vector.e[0] += a_g[0] * time_step;
            entities_in[current].projection_vector.e[1] += a_g[1] * time_step;
            entities_in[current].projection_vector.e[2] += a_g[2] * time_step;
       }
    }
}


cudaDeviceProp getDetails(int deviceId)
{
    cudaDeviceProp props;
    cudaGetDeviceProperties(&props, deviceId);
    return props;
}


// 3D launcher 
void kernel::launcher(body::orbital_entity<body::Vector3> *entities, size_t length){

    std::cout << "Initialising GPU:" << std::endl;

    int deviceId;
    cudaGetDevice(&deviceId);
    cudaDeviceProp props = getDetails(deviceId);

    size_t size = sizeof(double) * 7 * length;

    body::orbital_entity<body::Vector3> *d_entities;
    
    cudaMalloc((void **)&d_entities, size);
    cudaMemcpy(d_entities, entities, size, cudaMemcpyHostToDevice);

    int threads_per_block = 512;
    std::cout << "Number of SMs: " << props.multiProcessorCount << std::endl;
    int number_of_blocks = props.multiProcessorCount * multi;

    cudaError_t step_error;
    cudaError_t async_error;    



    double time = 0.0;
    double time_step = 86400;

    int iterations = 0;
    // main program loop

    std::cout << "Start" << std::endl;
    body::properties(entities[0]);

    while (time < 86400 * 365 * 10) { 
    

        calculate_next_projection<<<threads_per_block, number_of_blocks>>>(d_entities, length, time_step);
        step_error = cudaGetLastError();
        if (step_error != cudaSuccess){std::cout << "STEP ERROR (calculate next projection)" << std::endl;}
        async_error = cudaDeviceSynchronize();
        if(async_error != cudaSuccess){std::cout << "ASYNC ERROR (calculate next projection)" << std::endl;}


        move<<<threads_per_block, number_of_blocks>>>(d_entities, length);
        step_error = cudaGetLastError();
        if (step_error != cudaSuccess){std::cout << "STEP ERROR (Move)" << std::endl;}
        async_error = cudaDeviceSynchronize();
        if(async_error != cudaSuccess){std::cout << "ASYNC ERROR (Move)" << std::endl;}


        cudaMemcpy(entities, d_entities, size, cudaMemcpyDeviceToHost);
        // call rendering stuff now //

        time+=time_step;
    }
    

    std::cout << "End:" << std::endl;
    body::properties(entities[0]);

}

// 2D launcher
void kernel::launcher(body::orbital_entity<body::Vector2> *entities, size_t length) {

}




