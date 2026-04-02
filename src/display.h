#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL3/SDL.h>
#include <stdio.h>

extern SDL_Window* window;
extern SDL_Renderer* renderer;

extern uint32_t* color_buffer;
extern SDL_Texture* color_buffer_texture;

extern int w_width;
extern int w_height;

bool initialize_window();
void render_color_buffer();
void clear_color_buffer(uint32_t color);
void draw_pixel(int x, int y, uint32_t color);
void draw_grid(int grid_size);
void draw_rect(int x, int y, int width, int height, uint32_t color);
void cleanup();

#endif // DISPLAY_H
