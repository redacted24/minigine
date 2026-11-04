#ifndef TEXTURE_H
#define TEXTURE_H

#include <filesystem>
#include <glm/ext/vector_float2.hpp>
#include <string>

class Texture {
public:
  std::string Path;
  unsigned char *Data;
  int Width;
  int Height;
  int NrChannels;

  unsigned int GlTexture;

  Texture(std::filesystem::path p_texture_path);
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
