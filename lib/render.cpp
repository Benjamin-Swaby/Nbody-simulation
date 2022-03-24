#include "render.hpp"
#include "body.hpp"

#include <iostream>
#include <SDL2/SDL.h>
#include <colors.h>

using namespace nbody;


render::render_object render::init() {
    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    SDL_Window* win = SDL_CreateWindow("Nbody",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       1000, 1000, 0);

    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);



    return render::render_object{win, rend};
}



render::render_object render::render(body::orbital_entity<body::Vector3> *entites, size_t length, render_object ro, double scope) {

    SDL_Window* window = ro.window;
    SDL_Renderer* rend = ro.rend;

    SDL_Surface* surface = SDL_GetWindowSurface(window);
    SDL_RenderClear(rend);


    SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);

    for (int i = 0; i < length; i++) {
        
        SDL_Rect rect;
        rect.x = 500 + (entites[i].position_vector.e[0] / scope) * 1000; //normalise to window size of 1000x1000
        rect.y = 500 + (entites[i].position_vector.e[2] / scope) * 1000;
        rect.w = ((entites[i].mass / 1.989e30) * 30) + 10;
        rect.h = ((entites[i].mass / 1.989e30) * 30) + 10;

        std::cout << BYEL;
        std::cout << i << " Rendering particle " <<  " (x,y): " << rect.x << " , " << rect.y << std::endl;
        std::cout << reset;

        std::cout << BRED;
        
        //std::cout << i << " Projection " << "(" << entites[i].projection_vector.e[0] << " , " 
        //                << entites[i].projection_vector.e[1] << " , " 
        //               << entites[i].projection_vector.e[2] <<")" << std::endl;
        //std::cout << reset;

        SDL_RenderFillRect(rend, &rect);
    }

    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);

    SDL_RenderPresent(rend);   

    return render::render_object{window, rend};
}