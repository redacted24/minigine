#ifndef CUBE_H
#define CUBE_H

#include "object.h"
#include "renderable.h"
#include "texture.h"
#include <string>

class Cube : public Object, public Renderable {
public:
  std::string Name;
  glm::vec3 LocalPosition;
  glm::vec3 GlobalPosition;
  glm::vec3 RotationAxis;
  float RotationRadians;
  Cube(glm::vec2 p_top, glm::vec2 p_bot, glm::vec2 p_front, glm::vec2 p_left,
       glm::vec2 p_back, glm::vec2 p_right, Texture *p_atlas);
  unsigned int VAO, VBO, TextureData;
  Texture *atlas;
  std::array<float, 180> Vertices;

  void render() override;
  int render_setup() override;
  virtual glm::vec3 get_local_position() override;
  virtual glm::vec3 get_global_position() override;
  virtual glm::vec3 get_rotation_axis() override;
  virtual float get_rotation_radians() override;
};

#endif // CUBE_H
