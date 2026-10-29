#ifndef TEXT_H
#define TEXT_H

#include "glad/glad.h"
#include "shader.h"
#include <glm/glm.hpp>
#include <map>
#include <string>

struct Character {
  /// ID handle of the glyph texture.
  unsigned int TextureID;
  /// Size of glyp
  glm::ivec2 Size;
  /// Offset from baseline to left/top of glyph
  glm::ivec2 Bearing;
  /// offset to advance to next glyph
  unsigned int Advance;
};

class TextRenderer {
public:
  std::map<GLchar, Character> Characters;
  unsigned int VBO, VAO;
  Shader TextShader;

  TextRenderer();
  int initialize_shaders(const char *vertexPath, const char *fragmentPath);
  int initialize_font(std::string fontPath);
  void RenderText(std::string text, float x, float y, float scale,
                  glm::vec3 color);
};

#endif // TEXT_H
