#ifndef RENDERING_ENGINE_H
#define RENDERING_ENGINE_H

template <typename T> class RenderingEngine {
public:
  RenderingEngine() = delete;
  int draw_object(T object);
};

#endif // RENDERING_ENGINE_H
