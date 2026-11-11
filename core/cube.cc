#include "cube.h"
#include "glad/glad.h"
#include "stb_image/stb_image.h"
#include "json/json.hpp"
#include <fstream>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <spdlog/spdlog.h>
#include <string>
#include <unordered_map>

using nlohmann::json;

Cube::Cube(std::string p_blockname, Texture *p_atlas) {
  std::ifstream blocks_json_file("assets/blocks/blocks.json");
  atlas = p_atlas;

  json data = json::parse(blocks_json_file);
  if (!data.contains(p_blockname)) {
    // soft fail
    SPDLOG_ERROR("Blockname {} could not be found in blocks.json", p_blockname);
  } else {
    std::unordered_map<std::string, std::pair<float, float>> uv_coords =
        data[p_blockname]
            .get<std::unordered_map<std::string, std::pair<float, float>>>();
    setup_vertices(
        glm::vec2(uv_coords["top"].first, uv_coords["top"].second),
        glm::vec2(uv_coords["bot"].first, uv_coords["bot"].second),
        glm::vec2(uv_coords["front"].first, uv_coords["front"].second),
        glm::vec2(uv_coords["left"].first, uv_coords["left"].second),
        glm::vec2(uv_coords["back"].first, uv_coords["back"].second),
        glm::vec2(uv_coords["right"].first, uv_coords["right"].second));
  }
  blocks_json_file.close();
}

Cube::Cube(glm::vec2 p_top, glm::vec2 p_bot, glm::vec2 p_front,
           glm::vec2 p_left, glm::vec2 p_back, glm::vec2 p_right,
           Texture *p_atlas) {
  SPDLOG_WARN("The cube constructor with pixel coordinates is deprecated. Use "
              "the constructor with block name instead.");
  atlas = p_atlas;
  setup_vertices(p_top, p_bot, p_front, p_left, p_back, p_right);
}

int Cube::setup_vertices(glm::vec2 p_top, glm::vec2 p_bot, glm::vec2 p_front,
                         glm::vec2 p_left, glm::vec2 p_back,
                         glm::vec2 p_right) {
  assert(atlas != nullptr && "Texture atlas cannot be null.");
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
      atlas->get_pixel_coords(p_back.x, p_back.y);
  std::array<glm::vec2, 4> uv_coords = atlas->get_uv_coords(pixel_coords);

  std::array<int, 6> indices = {0, 1, 2, 2, 3, 0};

  for (int i = 0; i < 6; i++) {
    Vertices[vertices_arr_idx + 3] = uv_coords[indices[i]].x;
    Vertices[vertices_arr_idx + 4] = uv_coords[indices[i]].y;
    vertices_arr_idx += 5;
  }

  SPDLOG_DEBUG("Sampled back face texture.");

  // 2. Front face
  pixel_coords = atlas->get_pixel_coords(p_front.x, p_front.y);
  uv_coords = atlas->get_uv_coords(pixel_coords);

  for (int i = 0; i < 6; i++) {
    Vertices[vertices_arr_idx + 3] = uv_coords[indices[i]].x;
    Vertices[vertices_arr_idx + 4] = uv_coords[indices[i]].y;
    vertices_arr_idx += 5;
  }

  SPDLOG_DEBUG("Sampled front face texture.");

  // 3. Left
  indices = {2, 3, 0, 0, 1, 2};
  pixel_coords = atlas->get_pixel_coords(p_left.x, p_left.y);
  uv_coords = atlas->get_uv_coords(pixel_coords);

  for (int i = 0; i < 6; i++) {
    Vertices[vertices_arr_idx + 3] = uv_coords[indices[i]].x;
    Vertices[vertices_arr_idx + 4] = uv_coords[indices[i]].y;
    vertices_arr_idx += 5;
  }

  SPDLOG_DEBUG("Sampled left face texture.");

  // 4. Right
  pixel_coords = atlas->get_pixel_coords(p_right.x, p_right.y);
  uv_coords = atlas->get_uv_coords(pixel_coords);

  for (int i = 0; i < 6; i++) {
    Vertices[vertices_arr_idx + 3] = uv_coords[indices[i]].x;
    Vertices[vertices_arr_idx + 4] = uv_coords[indices[i]].y;
    vertices_arr_idx += 5;
  }

  SPDLOG_DEBUG("Sampled right face texture.");

  indices = {0, 1, 2, 2, 3, 0};

  // 5. Bottom
  pixel_coords = atlas->get_pixel_coords(p_bot.x, p_bot.y);
  uv_coords = atlas->get_uv_coords(pixel_coords);

  for (int i = 0; i < 6; i++) {
    Vertices[vertices_arr_idx + 3] = uv_coords[indices[i]].x;
    Vertices[vertices_arr_idx + 4] = uv_coords[indices[i]].y;
    vertices_arr_idx += 5;
  }

  SPDLOG_DEBUG("Sampled bottom face texture.");

  // 6. Top
  pixel_coords = atlas->get_pixel_coords(p_top.x, p_top.y);
  uv_coords = atlas->get_uv_coords(pixel_coords);

  for (int i = 0; i < 6; i++) {
    Vertices[vertices_arr_idx + 3] = uv_coords[indices[i]].x;
    Vertices[vertices_arr_idx + 4] = uv_coords[indices[i]].y;
    vertices_arr_idx += 5;
  }

  SPDLOG_DEBUG("Sampled top face texture.");

  return 0;
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
