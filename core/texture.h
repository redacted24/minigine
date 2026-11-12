#ifndef TEXTURE_H
#define TEXTURE_H

#include "glm/ext/vector_float2.hpp"
#include <filesystem>
#include <string>

class Texture {
public:
  std::string Path;
  unsigned char *Data;
  int Width;
  int Height;
  int NrChannels;
  float AtlasCellSize = 16.0f;

  unsigned int GlTextureData;

  Texture();
  Texture(std::filesystem::path p_texture_path);
  std::array<glm::vec2, 4> get_pixel_coords(int p_x, int p_y);
  std::array<glm::vec2, 4> get_uv_coords(std::array<glm::vec2, 4> p_arr);
  int load_texture();
};

typedef struct {
  std::string name;
  glm::vec2 front_uvcoords[4];
  glm::vec2 left_uvcoords[4];
  glm::vec2 right_uvcoords[4];
  glm::vec2 back_uvcoords[4];
  glm::vec2 top_uvcoords[4];
  glm::vec2 bottom_uvcoords[4];
} Block;

#endif // TEXTURE_H
