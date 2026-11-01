#ifndef CUBE_H
#define CUBE_H

#include "node.h"
#include <string>

class Cube : public Node {
public:
  // 1. bottom face
  // 2. top face
  // 3. left
  // 4. right
  // 5. front
  // 6. back
  static constexpr float Vertices[] = {
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.5f,
      0.5f, -0.5f, 1.0f, 1.0f, 0.5f, 0.5f, -0.5f, 1.0f, 1.0f, -0.5f, 0.5f,
      -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

      // -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
      // 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
      // -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,

      -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, -0.5f,
      -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f,
      0.5f, 0.0f, 0.0f, -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

      0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.5f, -0.5f,
      -0.5f, 0.0f, 1.0f, 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f, -0.5f, 0.5f,
      0.0f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.5f,
      -0.5f, 0.5f, 1.0f, 0.0f, 0.5f, -0.5f, 0.5f, 1.0f, 0.0f, -0.5f, -0.5f,
      0.5f, 0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.5f, 0.5f,
      0.5f, 1.0f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f, 0.0f, -0.5f, 0.5f, 0.5f, 0.0f,
      0.0f, -0.5f, 0.5f, -0.5f, 0.0f, 1.0f};

  static constexpr float TopFaceVertices[] = {
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.5f,  -0.5f, 0.5f, 1.0f, 0.0f,
      0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
      -0.5f, 0.5f,  0.5f, 0.0f, 1.0f, -0.5f, -0.5f, 0.5f, 0.0f, 0.0f};

  std::string Name;
  std::string TexturePath;
  std::string TopTexturePath;
  unsigned char *RawTextureData;
  unsigned char *RawTopTextureData;
  // TODO: convert to a texture class maybe
  int TextureWidth;
  int TextureHeight;
  int NrChannels;

  float LocalRotationRadians;
  glm::vec3 LocalRotationAxis;

  /**
   * @brief Create a cube
   *
   * @param p_name Name of node
   * @param p_texture_path Path of textures of all faces except top face of cube
   * @param p_top_texture_path Path of texture for top face of cube
   */
  Cube(std::string p_name, std::string p_texture_path,
       std::string p_top_texture_path);
  Cube();

private:
  unsigned char *load_texture_data(std::string p_texture_path);
  int invariant();
};

#endif // CUBE_H
