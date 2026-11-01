#include "cube.h"
#include "glad/glad.h"
#include "stb_image/stb_image.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_transform.hpp>
#include <spdlog/spdlog.h>

Cube::Cube() : TexturePath("") {
  spdlog::warn("Cube does not have a texture path.");
}

Cube::Cube(std::string p_name, std::string p_texture_path,
           std::string p_top_texture_path) {
  Name = p_name;
  TexturePath = p_texture_path;
  RawTextureData = load_texture_data(p_texture_path);
  LocalRotationAxis = glm::vec3(1.0f, 0.0f, 0.0f);
  LocalRotationRadians = glm::radians(-90.0f);

  if (p_top_texture_path != "") {
    RawTopTextureData = load_texture_data(p_top_texture_path);
  }
};

unsigned char *Cube::load_texture_data(std::string p_texture_path) {
  unsigned char *data = stbi_load(p_texture_path.c_str(), &TextureWidth,
                                  &TextureHeight, &NrChannels, 0);

  if (!data) {
    spdlog::error("Failed to load texture {}", p_texture_path);
  } else {
    spdlog::debug("Loaded texture {} for node {}", p_texture_path, Name);
  }
  return data;
}

/**
 * @brief Function that checks the node integrity.
 *
 * @return 0 on success, nonzero if fail.
 */
int Cube::invariant() {
  if (Name == "") {
    spdlog::warn("Node has no name.");
  }
  return 0;
}
