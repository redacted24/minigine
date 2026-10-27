#include "main.h"
#include "camera.h"
#include "cube.h"
#include "perlin_noise.h"
#include "rendering_engine.h"
#include "shader.h"
#include "spdlog/spdlog.h"
#include "stb/stb_image.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <freetype2/ft2build.h>
#include <glad/glad.h>
#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>
#include <stdio.h>
#include FT_FREETYPE_H
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

float vertices[] = {
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 0.0f,
    0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
    -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

    -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,

    -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  0.5f,  1.0f, 0.0f,

    0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
    0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 1.0f,
    0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

    -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f};

// uint32_t indices[] = {0, 1, 3, 1, 2, 3};

uint32_t VAO, VBO, EBO;
uint32_t vertexShader;
uint32_t fragmentShader;
uint32_t shaderProgram;

const char *vertexShaderSource;
const char *fragmentShaderSource;

int success;
char infolog[512];

int main(int argc, char *argv[]) {
  // https://github.com/gabime/spdlog/wiki/Custom-formatting
  // spdlog::set_pattern("[%H:%M:%S] [%^%l%$] %v");
  spdlog::set_level(spdlog::level::debug);
  spdlog::info("Start of program");
  if (SDL_Init(SDL_INIT_VIDEO) == false) {
    spdlog::critical("SDL could not initialize. SDL error: {}", SDL_GetError());
    return -1;
  };
  // Create a window
  if (!SDL_CreateWindowAndRenderer("SDL3 Tutorial", WINDOW_WIDTH, WINDOW_HEIGHT,
                                   (SDL_WINDOW_MINIMIZED), &window,
                                   &renderer)) {
    spdlog::critical("Couldn't create window/renderer: {}", SDL_GetError());
    return -1;
  }
  spdlog::info("Initialized SDL window width {}px and window height {}px",
               WINDOW_WIDTH, WINDOW_HEIGHT);

  // Set OpenGL attributes
  unsigned int sdl_version = 3;
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, sdl_version);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, sdl_version);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  spdlog::info("Initialized SDL with version {}", sdl_version);

  // Context
  SDL_GLContext gl_context = SDL_GL_CreateContext(window);
  if (!gl_context) {
    spdlog::critical("Could not create opengl context, shutting down program");
    SDL_DestroyWindow(window);
    SDL_Quit();
    return -1;
  }

  SDL_GL_MakeCurrent(window, gl_context);

  // Load GLAD
  int version = gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

  // App scale
  SDL_SetRenderScale(renderer, 1.0, 1.0);

  // Creation of vertex shader
  Shader myShader("assets/shaders/main.vs.glsl", "assets/shaders/main.fs.glsl");

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  // bind vao, then bind vbo and set, then configure vertex attributes
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  // texture attribute
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  int width, height, nrChannels;

  // TEXTURE
  unsigned int texture1;
  // -------------------------
  // texture 1
  Cube *cube = new Cube("Container cube", "assets/container.jpg");
  RenderingEngine::prepare_cube_for_render(cube);

  myShader.use();

  glUniform1i(glGetUniformLocation(myShader.ID, "texture1"), 0);
  glEnable(GL_DEPTH_TEST);

  bool running = true;
  SDL_Event event;
  spdlog::info("Main loop start");

  // variables for deltaTime calculation and mouse position
  float deltaTime = 0.0f;
  float lastFrame = 0.0f;
  bool firstMouse = true;
  float lastX = 400, lastY = 300;

  // FREETYPE
  // each ft returns nonzero on error
  FT_Library ft;
  if (FT_Init_FreeType(&ft)) {
    spdlog::error("Could not initialize Freetype library.");
    return -1;
  }

  FT_Face face;
  std::string font = "fonts/CaskaydiaMonoNerdFont-Regular.ttf";
  if (FT_New_Face(ft, font.c_str(), 0, &face)) {
    spdlog::error("Could not load font {}", font);
    return -1;
  }

  FT_Set_Pixel_Sizes(face, 0, 48);

  if (FT_Load_Char(face, 'X', FT_LOAD_RENDER)) {
    spdlog::error("Freetype failed to load glyph {}", 'X');
    return -1;
  }

  // * -------------------------------------------------- *
  //
  //
  //
  // Start
  //
  //
  //
  // * -------------------------------------------------- *

  PerlinNoise *perlin = new PerlinNoise(); // initialize perlin noise class

  Camera *camera = new Camera(glm::vec3(0.0f, 5.0f, 10.0f));
  int x_num = 10;
  int z_num = 10;
  const int MAX_HEIGHT_CHUNK = 5;

  std::vector<glm::vec3> cubePositions;
  int noise_arr[x_num][z_num];
  for (int i = 0; i < x_num; i++) {
    for (int j = 0; j < z_num; j++) {
      float perlin_noise = perlin->noise(i + 0.5f, j + 0.5f, 0.0f + 0.5f);
      perlin_noise = ((perlin_noise + 1.0f) / 2.0f) *
                     (float)MAX_HEIGHT_CHUNK; // scale to [0, 5]
      noise_arr[i][j] = perlin_noise;
    }
  }

  for (int i = 0; i < x_num; i++) {
    for (int j = 0; j < z_num; j++) {
      if (noise_arr[i][j] > MAX_HEIGHT_CHUNK) {
        spdlog::critical(
            "noise array has value {} which is larger than {}, shutting down",
            noise_arr[i][j], MAX_HEIGHT_CHUNK);
        return 1;
      } else {
        for (int k = 0; k < noise_arr[i][j]; k++) {
          cubePositions.push_back({(float)i, (float)k, (float)j});
        }
      }
    }
  }

  // Main loop
  while (running) {
    float currentFrame = static_cast<float>(SDL_GetTicks() / 1000.0f);
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    SDL_MouseMotionEvent mouseEvent;

    // Event loop
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_EVENT_QUIT) {
        running = false;
      } else if (e.type == SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED) {
        int pixel_width = e.window.data1;
        int pixel_height = e.window.data2;
        glViewport(0, 0, pixel_width, pixel_height);
      } else if (e.type == SDL_EVENT_MOUSE_MOTION) {
        mouseEvent = e.motion;
        camera->ProcessMouseMovement(mouseEvent.xrel, -mouseEvent.yrel);
      }
    }

    // keyboard input
    const bool *state = SDL_GetKeyboardState(NULL);

    // PERF: Change direction input to allow multidirectional movement
    camera->ProcessKeyboard(state, deltaTime);

    // render
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);

    // activate shader
    myShader.use();

    SDL_SetWindowRelativeMouseMode(window, true);

    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f,
        100.0f);
    myShader.setMat4("projection", projection);

    glm::mat4 view = camera->GetViewMatrix();
    myShader.setMat4("view", view);

    glBindVertexArray(VAO);

    for (unsigned int i = 0; i < cubePositions.size(); i++) {
      glm::mat4 model = glm::mat4(1.0f);
      model = glm::translate(model, cubePositions[i]);
      float angle = 20.0f * i;
      myShader.setMat4("model", model);
      glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    SDL_GL_SwapWindow(window);
  }
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  spdlog::info("Program exit");
  return 0;
}
