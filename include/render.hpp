#pragma once

#include "body.hpp"
#include <SDL2/SDL.h>




namespace nbody {
    namespace render {

        struct render_object {
            SDL_Window* window;
            SDL_Renderer *rend;
        };

        render_object init();
        render_object render(body::orbital_entity<body::Vector3> *entites, size_t length, render_object ro,double scope);
        render_object render(body::orbital_entity<body::Vector2> *entites, size_t length, render_object ro,double scope);
    }

}

