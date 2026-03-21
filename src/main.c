#include <stdio.h>
#include <SDL3/SDL.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
bool isRunning = true;

void cleanup() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}   

bool initialize_window(){
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    window = SDL_CreateWindow("3d Renderer", 800, 600, 0);

    if (!window) {
        fprintf(stderr, "Failed to create window: %s\n", SDL_GetError());
        cleanup();
        exit(1);
    }

    // Create a renderer for the window
    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        fprintf(stderr, "Failed to create renderer: %s\n", SDL_GetError());
        cleanup();
        exit(1);
    }

    return true;
}

int main(void) {
    if (!initialize_window()) {
        return 1;
    }
    
    SDL_Event event;
    while(isRunning){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_EVENT_QUIT){
                isRunning = false;
            }
        }
    }

    cleanup();

    return 0;
}