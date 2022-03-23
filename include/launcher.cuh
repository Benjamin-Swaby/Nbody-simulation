#include "body.hpp"

#pragma once


namespace nbody {

    namespace kernel {

        void launcher(body::orbital_entity<body::Vector3> *entities, size_t length); // Launcher for 3D space
        void launcher(body::orbital_entity<body::Vector2> *entities, size_t length); // Lancher for 2D space

    }
}