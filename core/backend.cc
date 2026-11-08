#include "backend.h"
#include "SDL3/SDL.h"
#include "glad/glad.h"
#include "spdlog/spdlog.h"
#include <SDL3/SDL_video.h>

namespace Backend {

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;
bool running = true;

int setup() {
  // ===============================================
  //
  //								SDL3 setup
  //
  // ===============================================

  // https://github.com/gabime/spdlog/wiki/Custom-formatting
  // spdlog::set_pattern("[%H:%M:%S] [%^%l%$] %v");
  spdlog::set_pattern("[%H:%M:%S] [%^%l%$] [%s:%#] %v");
  spdlog::set_level(spdlog::level::debug);
  SPDLOG_INFO("Start of program");
  if (SDL_Init(SDL_INIT_VIDEO) == false) {
    SPDLOG_CRITICAL("SDL could not initialize. SDL error: {}", SDL_GetError());
    return -1;
  };

  // Create a window
  if (!SDL_CreateWindowAndRenderer("SDL3 Tutorial", WINDOW_WIDTH, WINDOW_HEIGHT,
                                   (SDL_WINDOW_MINIMIZED), &window,
                                   &renderer)) {
    SPDLOG_CRITICAL("Couldn't create window/renderer: {}", SDL_GetError());
    return -1;
  }
  SPDLOG_INFO("Initialized SDL window width {}px and window height {}px",
              WINDOW_WIDTH, WINDOW_HEIGHT);

  // Set OpenGL attributes
  unsigned int sdl_version = 3;
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, sdl_version);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, sdl_version);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SPDLOG_INFO("Initialized SDL with version {}", sdl_version);

  // Context
  SDL_GLContext gl_context = SDL_GL_CreateContext(window);
  if (!gl_context) {
    SPDLOG_CRITICAL("Could not create opengl context, shutting down program");
    SDL_DestroyWindow(window);
    SDL_Quit();
    return -1;
  }
  SDL_GL_MakeCurrent(window, gl_context);

  // App scale
  SDL_SetRenderScale(renderer, 1.0, 1.0);

  // Load GLAD
  int version = gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
  return 0;
}
} // namespace Backend
