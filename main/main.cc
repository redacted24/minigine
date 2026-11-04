#include "main.h"
#include "camera.h"
#include "perlin_noise.h"
#include "rendering_engine.h"
#define SPDLOG_ACTIVE_LEVEL SPDLOG_DEBUG
#include "spdlog/spdlog.h"
#include "stb_image/stb_image.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <glad/glad.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_transform.hpp>
#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#include <ft2build.h>
#include FT_FREETYPE_H

static SDL_Window *window = nullptr;
static SDL_Renderer *renderer = nullptr;

int success;

void new_perlin_seed(PerlinNoise *p_perlin,
                     std::vector<glm::vec3> *p_dirt_block_positions,
                     std::vector<glm::vec3> *p_grass_block_positions,
                     float p_seed = 1.0f) {
  int x_num = 15;
  int z_num = 15;
  const int MAX_HEIGHT_CHUNK = 7;
  float offset = 0.5f;

  int noise_arr[x_num][z_num];
  for (int i = 0; i < x_num; i++) {
    for (int j = 0; j < z_num; j++) {
      float perlin_noise = p_perlin->noise(i + p_seed, j + p_seed, p_seed);
      perlin_noise = ((perlin_noise + 1.0f) / 2.0f) *
                     (float)MAX_HEIGHT_CHUNK; // scale to [0, 5]
      noise_arr[i][j] = perlin_noise;
    }
  }

  for (int i = 0; i < x_num; i++) {
    for (int j = 0; j < z_num; j++) {
      int k;
      for (k = 0; k < noise_arr[i][j] - 1; k++) {
        p_dirt_block_positions->push_back({(float)i, (float)k, (float)j});
      }
      p_grass_block_positions->push_back({(float)i, (float)k, (float)j});
    }
  }
}

int main(int argc, char *argv[]) {
  // ===============================================
  //
  //								SDL3 setup
  //
  // ===============================================

  // https://github.com/gabime/spdlog/wiki/Custom-formatting
  // spdlog::set_pattern("[%H:%M:%S] [%^%l%$] %v");
  spdlog::set_pattern("[%H:%M:%S] [%^%l%$] [%s:%#] [in %!()] %v");
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

  // ===============================================
  //
  //						   User program start
  //
  // ===============================================

  Texture block_atlas = Texture("assets/textures/block_atlas.png");
  block_atlas.load_texture();

  // int width, height, nrChannels;
  //
  // glEnable(GL_BLEND);
  // SPDLOG_DEBUG("Enabling GL_BLEND");
  // glEnable(GL_DEPTH_TEST);
  // SPDLOG_DEBUG("Enabling GL_DEPTH_TEST");
  // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  //
  // // Creation of vertex shader
  // Shader myShader("assets/shaders/main.vs.glsl",
  // "assets/shaders/main.fs.glsl");
  //
  // Cube *cube = new Cube("Grass cube", "assets/textures/grass_block_side.png",
  //                       "assets/textures/grass_top.png");
  //
  // unsigned int VAO, VBO, VAO_topface, VBO_topface, VAO_dirtblock,
  // VBO_dirtblock; unsigned int texture1, texture2, texture3;
  //
  // // VAO/VBO SIDES
  // glGenVertexArrays(1, &VAO);
  // glGenBuffers(1, &VBO);
  //
  // glBindVertexArray(VAO);
  // glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // glBufferData(GL_ARRAY_BUFFER, sizeof(Cube::Vertices), Cube::Vertices,
  //              GL_STATIC_DRAW);
  //
  // // position attribute
  // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
  //                       (void *)nullptr);
  // glEnableVertexAttribArray(0);
  // // texture attribute
  // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
  //                       (void *)(3 * sizeof(float)));
  // glEnableVertexAttribArray(1);
  //
  // // VAO/VBO TOPFACE
  // glGenVertexArrays(1, &VAO_topface);
  // glGenBuffers(1, &VBO_topface);
  //
  // glBindVertexArray(VAO_topface);
  // glBindBuffer(GL_ARRAY_BUFFER, VBO_topface);
  // glBufferData(GL_ARRAY_BUFFER, sizeof(Cube::TopFaceVertices),
  //              Cube::TopFaceVertices, GL_STATIC_DRAW);
  //
  // // position attribute
  // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
  //                       (void *)nullptr);
  // glEnableVertexAttribArray(0);
  //
  // // texture attribute
  // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
  //                       (void *)(3 * sizeof(float)));
  // glEnableVertexAttribArray(1);
  //
  // // TEXTURE 1
  // // Check that object has required fields
  // SPDLOG_DEBUG("Creating texture for side faces of cube");
  // glGenTextures(1, &texture1);
  // glBindTexture(GL_TEXTURE_2D, texture1);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  //
  // if (!cube->TextureWidth) {
  //   SPDLOG_DEBUG("Node {} does not have a texture width.", cube->Name);
  // } else if (!cube->TextureHeight) {
  //   SPDLOG_DEBUG("Node {} does not have a texture height.", cube->Name);
  // }
  // unsigned char *data = stbi_load("assets/textures/grass_block_side.png",
  //                                 &width, &height, &nrChannels, 0);
  // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
  //              GL_UNSIGNED_BYTE, data);
  // glGenerateMipmap(GL_TEXTURE_2D);
  // myShader.use();
  // myShader.setInt("texture1", 0);
  //
  // // TEXTURE 2
  // SPDLOG_DEBUG("Creating texture for top face of cube");
  // glGenTextures(1, &texture2);
  // glBindTexture(GL_TEXTURE_2D, texture2);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  //
  // if (!cube->TextureWidth) {
  //   SPDLOG_DEBUG("Node {} does not have a texture width.", cube->Name);
  // } else if (!cube->TextureHeight) {
  //   SPDLOG_DEBUG("Node {} does not have a texture height.", cube->Name);
  // }
  // data = stbi_load("assets/textures/grass_top.png", &width, &height,
  //                  &nrChannels, 0);
  // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
  //              GL_UNSIGNED_BYTE, data);
  // glGenerateMipmap(GL_TEXTURE_2D);
  // myShader.use();
  //
  // // VAO/VBO dirt block
  // glGenVertexArrays(1, &VAO_dirtblock);
  // glGenBuffers(1, &VBO_dirtblock);
  //
  // glBindVertexArray(VAO_dirtblock);
  // glBindBuffer(GL_ARRAY_BUFFER, VBO_dirtblock);
  // glBufferData(GL_ARRAY_BUFFER, sizeof(Cube::FullBlockVertices),
  //              Cube::FullBlockVertices, GL_STATIC_DRAW);
  //
  // // position attribute
  // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
  //                       (void *)nullptr);
  // glEnableVertexAttribArray(0);
  // // texture attribute
  // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
  //                       (void *)(3 * sizeof(float)));
  // glEnableVertexAttribArray(1);
  //
  // // TEXTURE 3
  // SPDLOG_DEBUG("Creating texture for dirt block");
  // glGenTextures(1, &texture3);
  // glBindTexture(GL_TEXTURE_2D, texture3);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  //
  // data = stbi_load("assets/textures/dirt.png", &width, &height, &nrChannels,
  // 0); if (!data) {
  //   spdlog::error("Failed loading dirt texture.");
  // }
  // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
  //              GL_UNSIGNED_BYTE, data);
  // glGenerateMipmap(GL_TEXTURE_2D);
  // myShader.use();
  //
  // Camera *camera = new Camera(glm::vec3(0.0f, 5.0f, 10.0f));
  //
  // // initialize perlin noise
  // PerlinNoise *perlin = new PerlinNoise();
  // std::vector<glm::vec3> grassBlockPositions;
  // std::vector<glm::vec3> dirtBlockPositions;
  // new_perlin_seed(perlin, &dirtBlockPositions, &grassBlockPositions, 0.5f);
  //
  // TextRenderer textRenderer;
  // textRenderer.initialize_shaders("assets/shaders/text.vs.glsl",
  //                                 "assets/shaders/text.fs.glsl");
  // textRenderer.initialize_font("assets/fonts/arial.ttf");
  // textRenderer.TextShader.use();
  //
  // glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(WINDOW_WIDTH),
  //                                   0.0f, static_cast<float>(WINDOW_HEIGHT));
  // glUniformMatrix4fv(
  //     glGetUniformLocation(textRenderer.TextShader.ID, "projection"), 1,
  //     GL_FALSE, glm::value_ptr(projection));
  //
  // // ===============================================
  // //
  // //								Main loop start
  // //
  // // ===============================================
  // SPDLOG_INFO("Entering main loop");
  // bool running = true;
  //
  // // variables for deltaTime calculation and mouse position
  // float deltaTime = 0.0f;
  // float lastFrame = 0.0f;
  // bool firstMouse = true;
  // float lastX = 400, lastY = 300;
  //
  // int nbFrames = 0;
  // int lastTime = 0;
  //
  // int frames_per_second = 0;
  //
  // // randomness
  // std::random_device rd;
  // std::mt19937 gen(rd());
  // std::uniform_real_distribution<float> distrib(0.2, 0.8);
  //
  // while (running) {
  //   float currentFrame = static_cast<float>(SDL_GetTicks() / 1000.0f);
  //   deltaTime = currentFrame - lastFrame;
  //   lastFrame = currentFrame;
  //   SDL_MouseMotionEvent mouseEvent;
  //
  //   // Find frames per second
  //   nbFrames++;
  //   if (currentFrame - (float)lastTime >= 1.0f) {
  //     frames_per_second = nbFrames;
  //     nbFrames = 0;
  //     lastTime += 1.0f;
  //   }
  //
  //   // ===============================================
  //   //
  //   //								Event
  //   loop
  //   //
  //   // ===============================================
  //   SDL_Event e;
  //   while (SDL_PollEvent(&e)) {
  //     if (e.type == SDL_EVENT_QUIT) {
  //       running = false;
  //     } else if (e.type == SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED) {
  //       int pixel_width = e.window.data1;
  //       int pixel_height = e.window.data2;
  //       glViewport(0, 0, pixel_width, pixel_height);
  //     } else if (e.type == SDL_EVENT_MOUSE_MOTION) {
  //       mouseEvent = e.motion;
  //       camera->ProcessMouseMovement(mouseEvent.xrel, -mouseEvent.yrel);
  //     } else if (e.type == SDL_EVENT_KEY_DOWN) {
  //       if (e.key.key == SDLK_C) {
  //         dirtBlockPositions.clear();
  //         grassBlockPositions.clear();
  //         float seed = distrib(gen);
  //         new_perlin_seed(perlin, &dirtBlockPositions, &grassBlockPositions,
  //                         seed);
  //         SPDLOG_DEBUG("Change perlin noise seed to {:.4f}", seed);
  //       }
  //     }
  //   }
  //
  //   // TODO: separate object and ui text rendering
  //
  //   // keyboard input
  //   const bool *state = SDL_GetKeyboardState(nullptr);
  //   camera->ProcessKeyboard(state, deltaTime);
  //
  //   // render
  //   glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  //   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //
  //   // bind texture
  //   glActiveTexture(GL_TEXTURE0);
  //   glBindTexture(GL_TEXTURE_2D, texture1);
  //
  //   // activate shader
  //   myShader.use();
  //
  //   SDL_SetWindowRelativeMouseMode(window, true);
  //
  //   glm::mat4 projection = glm::perspective(
  //       glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT,
  //       0.1f, 100.0f);
  //   myShader.setMat4("projection", projection);
  //
  //   glm::mat4 view = camera->GetViewMatrix();
  //   myShader.setMat4("view", view);
  //
  //   for (unsigned int i = 0; i < grassBlockPositions.size(); i++) {
  //     glBindVertexArray(VAO);
  //     glBindTexture(GL_TEXTURE_2D, texture1);
  //     float angle = 20.0f * i;
  //     glm::mat4 model = glm::mat4(1.0f);
  //     model = glm::rotate(glm::translate(model, grassBlockPositions[i]),
  //                         cube->LocalRotationRadians,
  //                         cube->LocalRotationAxis);
  //     myShader.setMat4("model", model);
  //     glDrawArrays(GL_TRIANGLES, 0, 36);
  //
  //     glBindVertexArray(VAO_topface);
  //     glBindTexture(GL_TEXTURE_2D, texture2);
  //     glDrawArrays(GL_TRIANGLES, 0, 36);
  //   }
  //
  //   for (unsigned int i = 0; i < dirtBlockPositions.size(); i++) {
  //     glBindVertexArray(VAO_dirtblock);
  //     glBindTexture(GL_TEXTURE_2D, texture3);
  //     glm::mat4 model = glm::mat4(1.0f);
  //     model = glm::translate(model, dirtBlockPositions[i]);
  //     myShader.setMat4("model", model);
  //     glDrawArrays(GL_TRIANGLES, 0, 36);
  //   }
  //
  //   glEnable(GL_CULL_FACE);
  //   std::string camera_lookat_debug = std::format(
  //       "Camera lookat: ({:.2f}, {:.2f}, {:.2f}) - Camera position: "
  //       "({:.2f}, {:.2f}, {:.2f})",
  //       camera->Front.x, camera->Front.y, camera->Front.z,
  //       camera->Position.x, camera->Position.y, camera->Position.z);
  //   textRenderer.RenderText(camera_lookat_debug, 5.0f,
  //                           static_cast<float>(WINDOW_HEIGHT) - 30.0f, 0.4f,
  //                           glm::vec3(0.0f, 0.0f, 0.0f));
  //
  //   camera_lookat_debug = std::format("{:d}fps", frames_per_second);
  //   textRenderer.RenderText(camera_lookat_debug, 5.0f,
  //                           static_cast<float>(WINDOW_HEIGHT) - 55.0f, 0.4f,
  //                           glm::vec3(0));
  //   glDisable(GL_CULL_FACE);
  //
  //   SDL_GL_SwapWindow(window);
  // }
  // glDeleteVertexArrays(1, &VAO);
  // glDeleteBuffers(1, &VBO);
  // SPDLOG_INFO("Program exit");
  // return 0;
}
