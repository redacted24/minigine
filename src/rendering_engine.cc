#include "rendering_engine.h"
#include "cube.h"
#include <glad/glad.h>
#include <spdlog/spdlog.h>

int RenderingEngine::prepare_cube_for_render(Cube *object) {
  // Check that object has required fields
  unsigned int texture1;
  glGenTextures(1, &texture1);
  glBindTexture(GL_TEXTURE_2D, texture1);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  if (!object->TextureWidth) {
    spdlog::debug("Node {} does not have a texture width.", object->Name);
  } else if (!object->TextureHeight) {
    spdlog::debug("Node {} does not have a texture height.", object->Name);
  }
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, object->TextureWidth,
               object->TextureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,
               object->TextureData);
  glGenerateMipmap(GL_TEXTURE_2D);
  spdlog::debug("Prepared cube {} for render", object->Name);
  return 0;
}
