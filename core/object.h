#ifndef OBJECT_H
#define OBJECT_H

#include <glm/ext/vector_float3.hpp>
#include <string>

class Object {
public:
  std::string Name;
  glm::vec3 LocalPosition;
  glm::vec3 GlobalPosition;
  glm::vec3 RotationAxis;
  float RotationRadians;
  virtual glm::vec3 get_local_position() = 0;
  virtual glm::vec3 get_global_position() = 0;
  virtual glm::vec3 get_rotation_axis() = 0;
  virtual float get_rotation_radians() = 0;
};

#endif // OBJECT_H
