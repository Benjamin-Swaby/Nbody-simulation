#pragma once

#include <string>

namespace nbody {


    namespace body {

        struct Vector3 {
            double e[3];

            Vector3(){}
            ~Vector3(){}

            inline Vector3(double x, double y, double z) {
                this->e[0] = x;
                this->e[1] = y;
                this->e[2] = z;
            }
        };


        struct Vector2 {
            double e[2];

            Vector2(){}
            ~Vector2(){}

            inline Vector2(double x, double y) {
                this->e[0] = x;
                this->e[1] = y;
            }
        };



        template<typename T>
        struct orbital_entity {
            std::string name;
            T position_vector;
            T projection_vector;
            double mass;

            orbital_entity(){}
            ~orbital_entity(){}

            inline orbital_entity(T position_vector, T projection_vector, double mass) {
                this->position_vector = position_vector;
                this->projection_vector = projection_vector;
                this->mass = mass;
            }
        };


        void properties(orbital_entity<Vector3> oe);
        void properties(orbital_entity<Vector2> oe);
    }
}