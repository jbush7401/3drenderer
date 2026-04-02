#include "display.h"

bool isRunning = true;

bool setup() {
    // Initialize your 3D renderer here
    if (!initialize_window()) {
        return false;
    }

    // Initialize color buffer
    color_buffer = (uint32_t*)malloc(w_width * w_height * sizeof(uint32_t));

    color_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, w_width, w_height);
    return true;
}

void process_input() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type) {
        case SDL_EVENT_QUIT:
            isRunning = false;
            break;
        case SDL_EVENT_KEY_DOWN:
            if (event.key.key == SDLK_ESCAPE) {
                isRunning = false;
            }
            break;
    }
}

void update(){

}

void render() {
 // set render draw color
    SDL_SetRenderDrawColor(renderer, 10, 0, 0, 255);
    // clear the screen
    SDL_RenderClear(renderer);
    draw_grid(50);
    draw_pixel(400, 303, 0XFF00FF00);
    draw_rect(100, 200, 200, 150, 0XFFFF0000);
    render_color_buffer();
    clear_color_buffer(0XFF333333);
    // present the backbuffer
    SDL_RenderPresent(renderer);
}

int main(void) {
    if (!setup()) {
        return 1;
    }
    while(isRunning){
        process_input();
        update();
        render();
     }

    cleanup();

    return 0;
}