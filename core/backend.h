#ifndef BACKEND_H
#define BACKEND_H

#include "text.h"
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

namespace Backend {

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern TextRenderer textRenderer;
extern bool running;

int setup();
int initialize_font_system();

} // namespace Backend

#endif // BACKEND_H
