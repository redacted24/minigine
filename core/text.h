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
  int initialize_shaders(const char *p_vertex_path,
                         const char *p_fragment_path);
  int initialize_font(std::string p_font_path);
  void RenderText(std::string p_text, float p_x, float p_y, float p_scale,
                  glm::vec3 p_color);
};

#endif // TEXT_H
