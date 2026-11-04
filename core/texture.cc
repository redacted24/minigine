#include "texture.h"
#include "glad/glad.h"
#include "spdlog/spdlog.h"
#include "stb_image/stb_image.h"
#include <filesystem>

Texture::Texture(std::filesystem::path p_texture_path) {
  if (!std::filesystem::exists(p_texture_path)) {
    spdlog::error("Could not find texture at {}", p_texture_path.c_str());
  } else {
    spdlog::debug("Successfully found texture at {}", p_texture_path.c_str());
    Path = p_texture_path;
  }
}

int Texture::load_texture() {
  Data = stbi_load(Path.c_str(), &Width, &Height, &NrChannels, 0);
  if (!Data) {
    spdlog::error("Could not load texture at {}", Path.c_str());
    return 1;
  }

  spdlog::debug("Loaded texture data at path {}", Path.c_str());
  glGenTextures(1, &GlTexture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, Data);

  /// NOTE: minecraft offers the actual mipmap pngs, if this doesn't work well.
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(Data);
  Data = nullptr;

  return 0;
};
