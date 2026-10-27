#ifndef NODE_H
#define NODE_H

#include <glm/glm.hpp>

class Node {
  glm::vec3 Origin;
  glm::vec3 Position;

public:
  Node(glm::vec3 origin, glm::vec3 position);
  Node();
};

#endif // NODE_H
