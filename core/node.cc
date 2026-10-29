#include "node.h"

Node::Node()
    : Origin(glm::vec3(0.0f, 0.0f, 0.0f)),
      Position(glm::vec3(0.0f, 0.0f, 0.0f)) {};

Node::Node(glm::vec3 p_origin, glm::vec3 p_position) {
  Origin = p_origin;
  Position = p_position;
}
