#ifndef RENDERING_ENGINE_H
#define RENDERING_ENGINE_H

template <typename T> class RenderingEngine {
public:
  RenderingEngine() = delete;

  /**
   * @brief Draw the given object. (naive implementation)
   *
   * @param object The object to draw.
   * @return Nonzero on failure
   */
  int draw_object(T object);
};

#endif // RENDERING_ENGINE_H
