#ifndef LIGHT_H
#define LIGHT_H

#include "object.h"
#include "renderable.h"
#include <array>

class Light : public Object, public Renderable {
public:
  unsigned int VAO, VBO, TextureData;
  std::array<float, 108> Vertices = {
      -0.5f, -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, 0.5f,  0.5f,  -0.5f,
      0.5f,  0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, -0.5f, -0.5f,

      -0.5f, -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,  0.5f,  0.5f,
      0.5f,  0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,  -0.5f, -0.5f, 0.5f,

      -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  -0.5f, -0.5f, -0.5f, -0.5f,
      -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, 0.5f,  -0.5f, 0.5f,  0.5f,

      0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  -0.5f, 0.5f,  -0.5f, -0.5f,
      0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, 0.5f,  0.5f,  0.5f,  0.5f,

      -0.5f, -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, 0.5f,
      0.5f,  -0.5f, 0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, -0.5f,

      -0.5f, 0.5f,  -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,  0.5f,
      0.5f,  0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  -0.5f,
  };

  Light();

  // Renderable
  void render() override;
  int render_setup() override;
};

#endif // LIGHT_H
