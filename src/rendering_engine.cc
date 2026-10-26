#include "rendering_engine.h"
#include "glad/glad.h"
#include <spdlog/spdlog.h>

template <typename T> int RenderingEngine<T>::draw_object(T object) {
  unsigned int texture1;
  glGenTextures(1, &texture1);
  glBindTexture(GL_TEXTURE_2D, texture1);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  if (!object.TextureWidth) {
    spdlog::debug("Node {} does not have a texture width.", object.Name);
  } else if (!object.TextureHeight) {
    spdlog::debug("Node {} does not have a texture height.", object.Name);
  }
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, object.TextureWidth,
               object.TextureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,
               object.TextureData);
  glGenerateMipmap(GL_TEXTURE_2D);
  return 0;
}
