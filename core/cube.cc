#include "cube.h"
#include "glad/glad.h"
#include "stb_image/stb_image.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <spdlog/spdlog.h>

Cube::Cube(glm::vec2 p_top, glm::vec2 p_bot, glm::vec2 p_front,
           glm::vec2 p_left, glm::vec2 p_back, glm::vec2 p_right,
           Texture *p_atlas) {
  atlas = p_atlas;
  // Immediately load the vertices
  // 1. Back face
  // 2. Front face
  // 3. Left
  // 4. Right
  // 5. Bottom
  // 6. Top
  Vertices = {-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 0.0f,
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

  // HACK: a bit of hardcoding. might be necessary
  int vertices_arr_idx = 0;

  // 1. Back face
  std::array<glm::vec2, 4> pixel_coords =
      p_atlas->get_pixel_coords(p_back.x, p_back.y);
  std::array<glm::vec2, 4> uv_coords = p_atlas->get_uv_coords(pixel_coords);

  std::array<int, 6> indices = {0, 1, 2, 2, 3, 0};

  for (int i = 0; i < 6; i++) {
    Vertices[vertices_arr_idx + 3] = uv_coords[indices[i]].x;
    Vertices[vertices_arr_idx + 4] = uv_coords[indices[i]].y;
    vertices_arr_idx += 5;
  }

  SPDLOG_DEBUG("Sampled bottom face texture.");

  // 2. Front face
  pixel_coords = p_atlas->get_pixel_coords(p_front.x, p_front.y);
  uv_coords = p_atlas->get_uv_coords(pixel_coords);

  for (int i = 0; i < 6; i++) {
    Vertices[vertices_arr_idx + 3] = uv_coords[indices[i]].x;
    Vertices[vertices_arr_idx + 4] = uv_coords[indices[i]].y;
    vertices_arr_idx += 5;
  }

  SPDLOG_DEBUG("Sampled front face texture.");

  // 3. Left
  indices = {2, 3, 0, 0, 1, 2};
  pixel_coords = p_atlas->get_pixel_coords(p_left.x, p_left.y);
  uv_coords = p_atlas->get_uv_coords(pixel_coords);

  for (int i = 0; i < 6; i++) {
    Vertices[vertices_arr_idx + 3] = uv_coords[indices[i]].x;
    Vertices[vertices_arr_idx + 4] = uv_coords[indices[i]].y;
    vertices_arr_idx += 5;
  }

  SPDLOG_DEBUG("Sampled left face texture.");

  // 4. Right
  pixel_coords = p_atlas->get_pixel_coords(p_right.x, p_right.y);
  uv_coords = p_atlas->get_uv_coords(pixel_coords);

  for (int i = 0; i < 6; i++) {
    Vertices[vertices_arr_idx + 3] = uv_coords[indices[i]].x;
    Vertices[vertices_arr_idx + 4] = uv_coords[indices[i]].y;
    vertices_arr_idx += 5;
  }

  SPDLOG_DEBUG("Sampled right face texture.");

  indices = {0, 1, 2, 2, 3, 0};

  // 5. Bottom
  pixel_coords = p_atlas->get_pixel_coords(p_bot.x, p_bot.y);
  uv_coords = p_atlas->get_uv_coords(pixel_coords);

  for (int i = 0; i < 6; i++) {
    Vertices[vertices_arr_idx + 3] = uv_coords[indices[i]].x;
    Vertices[vertices_arr_idx + 4] = uv_coords[indices[i]].y;
    vertices_arr_idx += 5;
  }

  SPDLOG_DEBUG("Sampled right face texture.");

  // 6. Top
  pixel_coords = p_atlas->get_pixel_coords(p_top.x, p_top.y);
  uv_coords = p_atlas->get_uv_coords(pixel_coords);

  for (int i = 0; i < 6; i++) {
    Vertices[vertices_arr_idx + 3] = uv_coords[indices[i]].x;
    Vertices[vertices_arr_idx + 4] = uv_coords[indices[i]].y;
    vertices_arr_idx += 5;
  }

  SPDLOG_DEBUG("Sampled right face texture.");
};

int Cube::render_setup() {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices.data(),
               GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void *)nullptr);
  glEnableVertexAttribArray(0);
  // texture attribute
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  SPDLOG_DEBUG("Finalized cube for rendering.");
  return 0;
};

void Cube::render() { return; }

glm::vec3 Cube::get_local_position() { return glm::vec3(0); };
glm::vec3 Cube::get_global_position() { return glm::vec3(0); };
glm::vec3 Cube::get_rotation_axis() { return glm::vec3(0); };
float Cube::get_rotation_radians() { return 0.0f; };
