#ifndef CUBE_H
#define CUBE_H

#include "object.h"
#include "renderable.h"
#include "texture.h"
#include <array>
#include <string>

class Cube : public Object, public Renderable {
public:
  unsigned int VAO, VBO, TextureData;
  Texture *atlas;
  std::array<float, 288> Vertices = {
      -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  0.0f,  0.0f,  -1.0f, 0.5f,  -0.5f,
      -0.5f, 0.0f,  0.0f,  0.0f,  0.0f,  -1.0f, 0.5f,  0.5f,  -0.5f, 0.0f,
      0.0f,  0.0f,  0.0f,  -1.0f, 0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  0.0f,
      0.0f,  -1.0f, -0.5f, 0.5f,  -0.5f, 0.0f,  0.0f,  0.0f,  0.0f,  -1.0f,
      -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  0.0f,  0.0f,  -1.0f,

      -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  0.0f,  0.0f,  1.0f,  0.5f,  -0.5f,
      0.5f,  0.0f,  0.0f,  0.0f,  0.0f,  1.0f,  0.5f,  0.5f,  0.5f,  0.0f,
      0.0f,  0.0f,  0.0f,  1.0f,  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  0.0f,
      0.0f,  1.0f,  -0.5f, 0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  0.0f,  1.0f,
      -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  0.0f,  0.0f,  1.0f,

      -0.5f, 0.5f,  0.5f,  0.0f,  0.0f,  -1.0f, 0.0f,  0.0f,  -0.5f, 0.5f,
      -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f,  0.0f,  -0.5f, -0.5f, -0.5f, 0.0f,
      0.0f,  -1.0f, 0.0f,  0.0f,  -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f,
      0.0f,  0.0f,  -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  -1.0f, 0.0f,  0.0f,
      -0.5f, 0.5f,  0.5f,  0.0f,  0.0f,  -1.0f, 0.0f,  0.0f,

      0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  0.5f,  0.5f,
      -0.5f, 0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  0.5f,  -0.5f, -0.5f, 0.0f,
      0.0f,  1.0f,  0.0f,  0.0f,  0.5f,  -0.5f, -0.5f, 0.0f,  0.0f,  1.0f,
      0.0f,  0.0f,  0.5f,  -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
      0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

      -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  0.0f,  -1.0f, 0.0f,  0.5f,  -0.5f,
      -0.5f, 0.0f,  0.0f,  0.0f,  -1.0f, 0.0f,  0.5f,  -0.5f, 0.5f,  0.0f,
      0.0f,  0.0f,  -1.0f, 0.0f,  0.5f,  -0.5f, 0.5f,  0.0f,  0.0f,  0.0f,
      -1.0f, 0.0f,  -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  0.0f,  -1.0f, 0.0f,
      -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  0.0f,  -1.0f, 0.0f,

      -0.5f, 0.5f,  -0.5f, 0.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.5f,  0.5f,
      -0.5f, 0.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.5f,  0.5f,  0.5f,  0.0f,
      0.0f,  0.0f,  1.0f,  0.0f,  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  0.0f,
      1.0f,  0.0f,  -0.5f, 0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f,
      -0.5f, 0.5f,  -0.5f, 0.0f,  0.0f,  0.0f,  1.0f,  0.0f};

  Cube(std::string p_blockname, Texture *p_atlas);

  /**
   * @brief Modifies the UV coordinates of the vertex array for a cube to match
   * the faces of the required block.
   *
   * @param p_top Top face
   * @param p_bot Bottom face
   * @param p_front Front face
   * @param p_left Left face
   * @param p_back Back face
   * @param p_right Right face
   * @return Zero on success, nonzero on fail.
   */
  int setup_vertices(glm::vec2 p_top, glm::vec2 p_bot, glm::vec2 p_front,
                     glm::vec2 p_left, glm::vec2 p_back, glm::vec2 p_right);

  /// ============ Overrides ==================

  // Renderable
  void render() override;
  int render_setup() override;
};

#endif // CUBE_H
