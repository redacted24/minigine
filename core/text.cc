#include "text.h"
#include "shader.h"
#include <ft2build.h>
#include <spdlog/spdlog.h>
#include <string>
#include FT_FREETYPE_H

TextRenderer::TextRenderer() {
  spdlog::warn("Initialized text renderer without a fragment/vertex shader.");
};

int TextRenderer::initialize_shaders(const char *p_vertex_path,
                                     const char *p_fragment_path) {
  TextShader = Shader(p_vertex_path, p_fragment_path);
  return 0;
}

int TextRenderer::initialize_font(std::string p_font_path) {
  FT_Library ft;
  if (FT_Init_FreeType(&ft)) {
    spdlog::error("Could not initialize Freetype library.");
    return -1;
  } else {
    spdlog::info("Initialized Freetype library");
  }

  FT_Face face;
  std::string font = "assets/fonts/arial.ttf";
  if (FT_New_Face(ft, font.c_str(), 0, &face)) {
    spdlog::error("Could not load font {}", font);
    return -1;
  } else {
    spdlog::debug("Loaded font {}", font);
  }

  FT_Set_Pixel_Sizes(face, 0, 48);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

  for (unsigned char c = 0; c < 128; c++) {
    // load character glyph
    if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
      spdlog::error("Freetype: failed to load glyph {}", c);
      continue;
    }

    // generate texture
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width,
                 face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE,
                 face->glyph->bitmap.buffer);

    // set texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // store char for later use
    Character character = {
        texture,
        glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
        glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
        (unsigned int)face->glyph->advance.x};
    Characters.insert(std::pair<char, Character>(c, character));
  }
  glBindTexture(GL_TEXTURE_2D, 0);

  spdlog::debug("Freetype: loaded 128 glyphs");

  FT_Done_Face(face);
  FT_Done_FreeType(ft);

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr,
               GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  return 0;
}

void TextRenderer::RenderText(std::string p_text, float p_x, float p_y,
                              float p_scale, glm::vec3 p_color) {
  // activate corresponding render state
  TextShader.use();
  glUniform3f(glGetUniformLocation(TextShader.ID, "textColor"), p_color.x,
              p_color.y, p_color.z);
  glActiveTexture(GL_TEXTURE0);
  glBindVertexArray(VAO);

  // iterate through all characters
  std::string::const_iterator c;
  for (c = p_text.begin(); c != p_text.end(); c++) {
    Character ch = Characters[*c];

    float xpos = p_x + ch.Bearing.x * p_scale;
    float ypos = p_y - (ch.Size.y - ch.Bearing.y) * p_scale;

    float w = ch.Size.x * p_scale;
    float h = ch.Size.y * p_scale;
    // update VBO for each character
    float vertices[6][4] = {
        {xpos, ypos + h, 0.0f, 0.0f},    {xpos, ypos, 0.0f, 1.0f},
        {xpos + w, ypos, 1.0f, 1.0f},

        {xpos, ypos + h, 0.0f, 0.0f},    {xpos + w, ypos, 1.0f, 1.0f},
        {xpos + w, ypos + h, 1.0f, 0.0f}};
    // render glyph texture over quad
    glBindTexture(GL_TEXTURE_2D, ch.TextureID);
    // update content of VBO memory
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // render quad
    glDrawArrays(GL_TRIANGLES, 0, 6);
    // now advance cursors for next glyph (note that advance is number of 1/64
    // pixels)
    p_x += (ch.Advance >> 6) *
           p_scale; // bitshift by 6 to get value in pixels (2^6 = 64)
  }
  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}
