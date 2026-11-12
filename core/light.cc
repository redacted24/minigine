#include "light.h"
#include "glad/glad.h"

Light::Light() {
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  // we only need to bind to VBO
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // set the vertex attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                        (void *)nullptr);
  glEnableVertexAttribArray(0);
}
void Light::render() { return; }
