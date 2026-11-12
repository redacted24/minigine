#include "light.h"
#include "glad/glad.h"
#include "spdlog/spdlog.h"

Light::Light() {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices.data(),
               GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                        (void *)nullptr);
  glEnableVertexAttribArray(0);

  SPDLOG_DEBUG("Finalized light source cube for rendering.");
}

void Light::render() { return; }

int Light::render_setup() { return 0; }
