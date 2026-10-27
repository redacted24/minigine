#include "cube.h"
#include "stb/stb_image.h"
#include <glm/glm.hpp>
#include <spdlog/spdlog.h>

Cube::Cube() : TexturePath("") {
  spdlog::warn("Cube does not have a texture path.");
}

Cube::Cube(std::string name, std::string texturePath) {
  Name = name;
  TexturePath = texturePath;
  load_texture_data(TexturePath);
};

int Cube::load_texture_data(std::string texturePath) {
  if (TexturePath == "") {
    spdlog::warn("No texture data for Cube {}", Name);
    return -1;
  }

  TextureData = stbi_load("assets/container.jpg", &TextureWidth, &TextureHeight,
                          &NrChannels, 0);

  if (!TextureData) {
    spdlog::error("Failed to lo texture {}", texturePath);
  } else {
    spdlog::debug("Loaded texture {} for node {}", texturePath, Name);
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
