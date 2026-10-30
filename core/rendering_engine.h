#include "cube.h"
#include "glad/glad.h"
#ifndef RENDERING_ENGINE_H
#define RENDERING_ENGINE_H

class RenderingEngine {
public:
  RenderingEngine() = delete;

  static int prepare_cube_for_render(Cube *p_object,
                                     GLuint *p_processed_texture_loc);
};

#endif // RENDERING_ENGINE_H
