#ifndef NODE_H
#define NODE_H

#include <glm/glm.hpp>

class Node {
  glm::vec3 Origin;
  glm::vec3 Position;

public:
  Node(glm::vec3 p_origin, glm::vec3 p_position);
  Node();
};

#endif // NODE_H
