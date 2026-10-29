#include "cube.h"
#include "stb_image/stb_image.h"
#include <glm/glm.hpp>
#include <spdlog/spdlog.h>

Cube::Cube() : TexturePath("") {
  spdlog::warn("Cube does not have a texture path.");
}

Cube::Cube(std::string p_name, std::string p_texture_path) {
  Name = p_name;
  TexturePath = p_texture_path;
  load_texture_data(TexturePath);
};

int Cube::load_texture_data(std::string p_texture_path) {
  if (TexturePath == "") {
    spdlog::warn("No texture data for Cube {}", Name);
    return -1;
  }

  TextureData = stbi_load("assets/container.jpg", &TextureWidth, &TextureHeight,
                          &NrChannels, 0);

  if (!TextureData) {
    spdlog::error("Failed to lo texture {}", p_texture_path);
  } else {
    spdlog::debug("Loaded texture {} for node {}", p_texture_path, Name);
  }
  return 0;
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
