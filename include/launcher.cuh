#include "body.hpp"

#pragma once


namespace nbody {

    namespace kernel {

        void launcher(body::orbital_entity<body::Vector3> *entities, size_t length, double scope, long long time_end, long long time_d); // Launcher for 3D space
        void launcher(body::orbital_entity<body::Vector2> *entities, size_t length, double scope, long time_end, long time_d); // Lancher for 2D space

    }
}