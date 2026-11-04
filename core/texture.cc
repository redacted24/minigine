#include "texture.h"
#include "glad/glad.h"
#include "spdlog/spdlog.h"
#include "stb_image/stb_image.h"
#include <filesystem>

/**
 * @brief For testing purposes
 */
Texture::Texture() {

};

Texture::Texture(std::filesystem::path p_texture_path) {
  if (!std::filesystem::exists(p_texture_path)) {
    SPDLOG_ERROR("Could not find texture at {}", p_texture_path.c_str());
  } else {
    SPDLOG_DEBUG("Successfully found texture at {}", p_texture_path.c_str());
    Path = p_texture_path;
  }
}

std::array<glm::vec2, 4> Texture::get_pixel_coords(int p_x, int p_y) {
  std::array<glm::vec2, 4> arr{};
  float real_cell_size = AtlasCellSize - 1;
  arr[0] = glm::vec2(p_x * AtlasCellSize, p_y * AtlasCellSize); // Bottom Left
  arr[1] = glm::vec2((AtlasCellSize - 1) + p_x * AtlasCellSize,
                     p_y * AtlasCellSize); // Bottom Right
  arr[2] = glm::vec2((AtlasCellSize - 1) + p_x * AtlasCellSize,
                     (AtlasCellSize - 1) + p_y * AtlasCellSize); // Top Right
  arr[3] = glm::vec2(p_x * AtlasCellSize,
                     (AtlasCellSize - 1) + p_y * AtlasCellSize); // Top Left
  return arr;
}

int Texture::load_texture() {
  Data = stbi_load(Path.c_str(), &Width, &Height, &NrChannels, 0);
  if (!Data) {
    SPDLOG_ERROR("Could not load texture at {}", Path.c_str());
    return 1;
  }

  SPDLOG_DEBUG("Loaded texture data at path {}", Path.c_str());
  glGenTextures(1, &GlTexture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, Data);

  /// NOTE: minecraft offers the actual mipmap pngs, in case this doesn't work
  /// well.
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(Data);
  Data = nullptr;

  return 0;
};
