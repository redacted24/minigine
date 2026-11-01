#include "rendering_engine.h"
#include "cube.h"
#include <glad/glad.h>
#include <spdlog/spdlog.h>

int RenderingEngine::prepare_cube_for_render(Cube *p_object,
                                             GLuint *p_processed_texture_loc,
                                             unsigned int *p_vao,
                                             unsigned int *p_vbo) {

  glGenVertexArrays(1, p_vao);
  glGenBuffers(1, p_vbo);

  glBindVertexArray(*p_vao);
  glBindBuffer(GL_ARRAY_BUFFER, *p_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Cube::Vertices), Cube::Vertices,
               GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void *)nullptr);
  glEnableVertexAttribArray(0);
  // texture attribute
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // Check that object has required fields
  glGenTextures(1, p_processed_texture_loc);
  glBindTexture(GL_TEXTURE_2D, *p_processed_texture_loc);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  if (!p_object->TextureWidth) {
    spdlog::debug("Node {} does not have a texture width.", p_object->Name);
  } else if (!p_object->TextureHeight) {
    spdlog::debug("Node {} does not have a texture height.", p_object->Name);
  }
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, p_object->TextureWidth,
               p_object->TextureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,
               p_object->RawTextureData);
  glGenerateMipmap(GL_TEXTURE_2D);
  spdlog::debug("Prepared cube {} for render", p_object->Name);
  return 0;
}
