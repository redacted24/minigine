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
  glm::vec3 get_local_position();
  glm::vec3 get_global_position();
  glm::vec3 get_rotation_axis();
  float get_rotation_radians();
};

#endif // OBJECT_H
