#include "main.h"
#include "backend.h"
#include "camera.h"
#include "glad/glad.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "light.h"
#include "perlin_noise.h"
#include "rendering_engine.h"
#include "shader.h"
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
#include <random>

#include <ft2build.h>
#include FT_FREETYPE_H

void new_perlin_seed(PerlinNoise *p_perlin,
                     std::vector<glm::vec3> *p_dirt_block_positions,
                     std::vector<glm::vec3> *p_grass_block_positions,
                     float p_seed);

glm::vec3 light_source_position(23.0f, 15.0f, 14.0f); // lighting

int main(int argc, char *argv[]) {
  // OpenGL and SDL3 Setup
  Backend::setup();

  // Start font system
  Backend::initialize_font_system();

  // ===============================================
  //
  //						   User program start
  //
  // ===============================================

  Texture block_atlas = Texture("assets/textures/block_atlas.png");
  block_atlas.load_texture();

  int width, height, nrChannels;

  // Creation of vertex shader
  Shader lightShader("assets/shaders/main.vs.glsl",
                     "assets/shaders/main.fs.glsl");
  Shader lightCubeShader("assets/shaders/light.vs.glsl",
                         "assets/shaders/light.fs.glsl");

  Cube grass_block = Cube("grass_block", &block_atlas);
  Cube dirt_block = Cube("dirt", &block_atlas);
  Light light_block = Light();

  grass_block.render_setup();
  dirt_block.render_setup();

  // TODO: enable camera view matrix default set
  Camera *camera = new Camera(glm::vec3(1.0f, 8.0f, 30.0f));

  // initialize perlin noise
  PerlinNoise *perlin = new PerlinNoise();
  std::vector<glm::vec3> grassBlockPositions;
  std::vector<glm::vec3> dirtBlockPositions;
  new_perlin_seed(perlin, &dirtBlockPositions, &grassBlockPositions, 0.5f);

  // ===============================================
  //
  //								Main loop start
  //
  // ===============================================

  SPDLOG_INFO("Entering main loop");
  bool running = true;

  // variables for deltaTime calculation and mouse position
  float deltaTime = 0.0f;
  float lastFrame = 0.0f;
  bool firstMouse = true;
  float lastX = 400, lastY = 300;

  int nbFrames = 0;
  int lastTime = 0;

  int frames_per_second = 0;

  // randomness
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> distrib(0.0f, 1.0f);

  while (running) {
    float currentFrame = static_cast<float>(SDL_GetTicks() / 1000.0f);
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    SDL_MouseMotionEvent mouseEvent;

    // Find frames per second
    nbFrames++;
    if (currentFrame - (float)lastTime >= 1.0f) {
      frames_per_second = nbFrames;
      nbFrames = 0;
      lastTime += 1.0f;
    }

    // ===============================================
    //
    //								Event loop
    //
    // ===============================================
    // TODO: separate object and ui text rendering

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
      } else if (e.type == SDL_EVENT_KEY_DOWN) {
        if (e.key.key == SDLK_C) {
          dirtBlockPositions.clear();
          grassBlockPositions.clear();
          float seed = distrib(gen);
          new_perlin_seed(perlin, &dirtBlockPositions, &grassBlockPositions,
                          seed);
          SPDLOG_DEBUG("Change perlin noise seed to {:.4f}", seed);
        }
      }
    }
    SDL_SetWindowRelativeMouseMode(Backend::window, true);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // keyboard input
    const bool *state = SDL_GetKeyboardState(nullptr);
    camera->ProcessKeyboard(state, deltaTime);

    // activate shader
    lightShader.use();
    lightShader.setVec3("lightPos", light_source_position);
    lightShader.setVec3("lightColor", 1.0f, 0.6f, 0.6f);
    lightShader.setFloat("lightStrength", 1.0f);
    lightShader.setVec3("viewPos", camera->Position);
    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f,
        100.0f);
    lightShader.setMat4("projection", projection);
    glm::mat4 view = camera->GetViewMatrix();
    lightShader.setMat4("view", view);

    // Render terrain
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, block_atlas.GlTextureData);
    for (unsigned int i = 0; i < grassBlockPositions.size(); i++) {
      glBindVertexArray(grass_block.VAO);
      glBindTexture(GL_TEXTURE_2D, block_atlas.GlTextureData);
      float angle = 20.0f * i;
      glm::mat4 model = glm::mat4(1.0f);
      model = glm::translate(model, grassBlockPositions[i]);
      lightShader.setMat4("model", model);
      glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    for (unsigned int i = 0; i < dirtBlockPositions.size(); i++) {
      glBindVertexArray(dirt_block.VAO);
      glBindTexture(GL_TEXTURE_2D, block_atlas.GlTextureData);
      glm::mat4 model = glm::mat4(1.0f);
      model = glm::translate(model, dirtBlockPositions[i]);
      lightShader.setMat4("model", model);
      glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    // Render light source
    lightCubeShader.use();
    glBindTexture(GL_TEXTURE_2D, light_block.VBO);
    glBindVertexArray(light_block.VAO);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, light_source_position);
    lightCubeShader.setMat4("model", model);
    lightCubeShader.setMat4("view", view);
    lightCubeShader.setMat4("projection", projection);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Render text
    glEnable(GL_CULL_FACE);
    std::string camera_lookat_debug = std::format(
        "Camera lookat: ({:.2f}, {:.2f}, {:.2f}) - Camera position: "
        "({:.2f}, {:.2f}, {:.2f})",
        camera->Front.x, camera->Front.y, camera->Front.z, camera->Position.x,
        camera->Position.y, camera->Position.z);

    Backend::textRenderer.RenderText(camera_lookat_debug, 5.0f,
                                     static_cast<float>(WINDOW_HEIGHT) - 30.0f,
                                     0.4f, glm::vec3(0.0f, 0.0f, 0.0f));

    camera_lookat_debug = std::format("{:d}fps", frames_per_second);
    Backend::textRenderer.RenderText(camera_lookat_debug, 5.0f,
                                     static_cast<float>(WINDOW_HEIGHT) - 55.0f,
                                     0.4f, glm::vec3(0));
    glDisable(GL_CULL_FACE);

    SDL_GL_SwapWindow(Backend::window);
  }
  SPDLOG_INFO("Program exit");
  return 0;
}

void new_perlin_seed(PerlinNoise *p_perlin,
                     std::vector<glm::vec3> *p_dirt_block_positions,
                     std::vector<glm::vec3> *p_grass_block_positions,
                     float p_seed = 1.0f) {
  int x_num = 32;
  int z_num = 32;
  const float SCALE = 8.0f;
  const float MAX_HEIGHT_CHUNK = 9.0f;
  const float BASE_HEIGHT = 1.0f;
  float offset = 0.5f;

  int noise_arr[x_num][z_num];
  for (int i = 0; i < x_num; i++) {
    for (int j = 0; j < z_num; j++) {
      float perlin_noise =
          p_perlin->noise((float)(p_seed * 50 + i) / SCALE, 0.0f,
                          (float)(p_seed * 50 + j) / SCALE);
      float normalized_noise = (perlin_noise + 1.0f) / 2.0f;
      int height =
          static_cast<int>(BASE_HEIGHT + (normalized_noise)*MAX_HEIGHT_CHUNK);

      noise_arr[i][j] = height;
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
