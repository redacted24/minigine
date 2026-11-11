#ifndef CUBE_H
#define CUBE_H

#include "object.h"
#include "renderable.h"
#include "texture.h"
#include <array>
#include <string>

class Cube : public Object, public Renderable {
public:
  std::string Name;
  glm::vec3 LocalPosition;
  glm::vec3 GlobalPosition;
  glm::vec3 RotationAxis;
  float RotationRadians;
  unsigned int VAO, VBO, TextureData;
  Texture *atlas;
  std::array<float, 180> Vertices;

  Cube(std::string p_blockname, Texture *p_atlas);

  // WARNING\: deprecated. Use Cube with block name constructor instead.
  Cube(glm::vec2 p_top, glm::vec2 p_bot, glm::vec2 p_front, glm::vec2 p_left,
       glm::vec2 p_back, glm::vec2 p_right, Texture *p_atlas);

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

  // Object
  virtual glm::vec3 get_local_position() override;
  virtual glm::vec3 get_global_position() override;
  virtual glm::vec3 get_rotation_axis() override;
  virtual float get_rotation_radians() override;
  // Renderable
  void render() override;
  int render_setup() override;
};

#endif // CUBE_H
