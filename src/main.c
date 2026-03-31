#include <stdio.h>
#include <SDL3/SDL.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
bool isRunning = true;
int w_width = 800;
int w_height = 600;
uint32_t* color_buffer = NULL;
SDL_Texture* color_buffer_texture = NULL;

void cleanup() {
    free(color_buffer);
    color_buffer = NULL;

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

    // Query what is the fullscreen display mode of the current display
    const SDL_DisplayMode* display_mode;
    SDL_DisplayID display = SDL_GetPrimaryDisplay();
    display_mode = SDL_GetCurrentDisplayMode(display);
    if (display_mode == NULL) {
        fprintf(stderr, "Failed to get current display mode: %s\n", SDL_GetError());
        cleanup();
        exit(1);
    }
    w_width = display_mode->w;
    w_height = display_mode->h;

    window = SDL_CreateWindow("3d Renderer", w_width, w_height, 0);

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

    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    return true;
}

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

void render_color_buffer() {
    SDL_UpdateTexture(color_buffer_texture, NULL, color_buffer, (int)(w_width * sizeof(uint32_t)));
    SDL_RenderTexture(renderer, color_buffer_texture, NULL, NULL);
}

void clear_color_buffer(uint32_t color) {
    for (int i = 0; i < w_width * w_height; i++) {
        color_buffer[i] = color;
    }
}

void draw_grid(int grid_size) {
    for (int y = 0; y < w_height; y += grid_size) {
        for (int x = 0; x < w_width; x += grid_size) {
            int index = y * w_width + x;
            color_buffer[index] = 0xFF000000; // black grid lines
        }
    }
}

void draw_rect(int x, int y, int width, int height, uint32_t color) {
    for (int i = y; i < height+y; i++) {
        for (int j = x; j < width+x; j++) {
            if (j >= 0 && j < w_width && i >= 0 && i < w_height) {
                color_buffer[i * w_width + j] = color;
            }
        }
    }
}

void render() {
 // set render draw color
    SDL_SetRenderDrawColor(renderer, 10, 0, 0, 255);
    // clear the screen
    SDL_RenderClear(renderer);
    draw_grid(50);
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