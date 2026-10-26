#include "node.h"

Node::Node()
    : Origin(glm::vec3(0.0f, 0.0f, 0.0f)),
      Position(glm::vec3(0.0f, 0.0f, 0.0f)) {};

Node::Node(glm::vec3 origin, glm::vec3 position) {
  Origin = origin;
  Position = position;
}
