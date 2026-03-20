#include <stdio.h>
#include <SDL3/SDL.h>

int main(void) {
    // Initialize SDL
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("3d Renderer", 800, 600, 0);

    if (!window) {
        fprintf(stderr, "Failed to create window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Event event;
    int running = 1; 
    while(running){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_EVENT_QUIT){
                running = 0;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}