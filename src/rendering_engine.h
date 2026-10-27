#include "cube.h"
#ifndef RENDERING_ENGINE_H
#define RENDERING_ENGINE_H

class RenderingEngine {
public:
  RenderingEngine() = delete;

  /**
   * @brief Draw the given object. (naive implementation)
   *
   * @param object The object to draw.
   * @return Nonzero on failure
   */
  static int prepare_cube_for_render(Cube *object);
};

#endif // RENDERING_ENGINE_H
