#include "body.hpp"

#include <iostream>

namespace nbody {

    namespace body
    {
        
        void properties(orbital_entity<Vector3> oe) {
            
            if (oe.name != "") {
                std::cout << "--- " << oe.name << " ---" <<std::endl;
            }

            std::cout << "Mass : " << oe.mass << std::endl;
            std::cout << "Position Vector: " << "[" << oe.position_vector.e[0] << "," << oe.position_vector.e[1] << "," << oe.position_vector.e[2] << "]"<< std::endl;
            std::cout << "Projection Vector: " << "[" << oe.projection_vector.e[0] << "," << oe.projection_vector.e[1] << "," << oe.projection_vector.e[2] << "]"<< std::endl;
            std::cout << "\n\n";

        }


        void properties(orbital_entity<Vector2> oe) {
            
            if (oe.name != "") {
                std::cout << "--- " << oe.name << " ---" <<std::endl;
            }

            std::cout << "Mass : " << oe.mass << std::endl;
            std::cout << "Position Vector: " << "[" << oe.position_vector.e[0] << "," << oe.position_vector.e[1] << "]"<< std::endl;
            std::cout << "Projection Vector: " << "[" << oe.projection_vector.e[0] << "," << oe.projection_vector.e[1] << "]"<< std::endl;
            std::cout << "\n\n";

        }
    } 
    

}