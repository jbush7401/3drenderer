#include "display.h"
#include "vector.h"


/// @brief Declare an array of vectors/points representing a 9x9x9 cube
/// @note The cube consists of 9 points along each axis, for a total of 9*9*9 points
/// @note Each point in the cube is represented as a vec3_t struct containing x, y, z coordinates


const int N_POINTS = 9*9*9;
vec3_t cube_points[N_POINTS]; // 9x9x9 points for a cube
vec2_t projected_points[N_POINTS]; // 9x9x9 projected points for a cube

float fov_factor = 128.0f;

bool isRunning = true;

bool setup() {
    // Initialize your 3D renderer here
    if (!initialize_window()) {
        return false;
    }

    // Initialize color buffer
    color_buffer = (uint32_t*)malloc(w_width * w_height * sizeof(uint32_t));

    color_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, w_width, w_height);

    // Load a 9x9x9 grid of points from -1.0 to 1.0 in 0.25 steps.
    // Integer indices avoid float comparison/casting edge cases.
    for (int xi = 0; xi < 9; xi++) {
        for (int yi = 0; yi < 9; yi++) {
            for (int zi = 0; zi < 9; zi++) {
                int index = xi * 81 + yi * 9 + zi;
                cube_points[index].x = -1.0f + (float)xi * 0.25f;
                cube_points[index].y = -1.0f + (float)yi * 0.25f;
                cube_points[index].z = -1.0f + (float)zi * 0.25f;
            }
        }
    }

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

/// @brief Function that received a 3d vector and returns a projected 2d point
/// @param point 
/// @return 
vec2_t project(vec3_t point) {
    vec2_t projected = {
        .x = point.x * fov_factor,
        .y = point.y * fov_factor
    };
    return projected;       
}

void update(){
    for (int i = 0; i < N_POINTS; i++) {
       vec3_t point = cube_points[i];

       // Project the current point
       vec2_t projected_point = project(point);

       // Save the projected point in the projected_points array
       projected_points[i] = projected_point;

    }
}

void render() {
   
    draw_grid(50);
     // draw the projected points
    for (int i = 0; i < N_POINTS; i++) {
        vec2_t point = projected_points[i];
        draw_rect(
            (int)point.x + w_width / 2, 
            (int)point.y + w_height / 2, 
        4, 4, 0XFFFFFF00);
    }
    render_color_buffer();
    clear_color_buffer(0XFF333333);
    // present the backbuffer
    SDL_RenderPresent(renderer);
}

int main(void) {
    if (!setup()) {
        return 1;
    }

    vec3_t myvector = {1.0f, 2.0f, 3.0f};
    
    while(isRunning){
        process_input();
        update();
        render();
     }

    cleanup();

    return 0;
}