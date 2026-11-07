#include "stb_image/stb_image.h"
#include "texture.h"
#include <glm/ext/vector_double2.hpp>
#include <gtest/gtest.h>

class TextureClassTest : public testing::Test {
protected:
  TextureClassTest() {
    texture.AtlasCellSize = 16.0f;
    texture.Width = 2048.0f;
    texture.Height = 2048.0f;
  }

  Texture texture;
};

TEST(TextureClass, LoadValidTextureAtlas) {
  std::string path = "assets/textures/block_atlas.png";
  Texture texture = Texture(path);
  texture.Data = stbi_load(path.c_str(), &texture.Width, &texture.Height,
                           &texture.NrChannels, 0);
  ASSERT_TRUE(texture.Data) << stbi_failure_reason();
}

TEST(TextureClass, LoadInvalidTextureAtlas) {
  std::string path = "assets/textures/block_atlas";
  Texture texture = Texture(path);
  texture.Data = stbi_load(path.c_str(), &texture.Width, &texture.Height,
                           &texture.NrChannels, 0);
  ASSERT_FALSE(texture.Data) << stbi_failure_reason();
}

TEST_F(TextureClassTest, pixelCoordsCorrect) {
  std::array<glm::vec2, 4> arr{glm::vec2(0.0f, 0.0f), glm::vec2(15.0f, 0.0f),
                               glm::vec2(15.0f, 15.0f), glm::vec2(0.0f, 15.0f)};
  ASSERT_EQ(texture.get_pixel_coords(0, 0), arr);
}

TEST_F(TextureClassTest, pixelCoordsCorrect2) {
  std::array<glm::vec2, 4> arr{glm::vec2(48.0f, 48.0f), glm::vec2(63.0f, 48.0f),
                               glm::vec2(63.0f, 63.0f),
                               glm::vec2(48.0f, 63.0f)};
  ASSERT_EQ(texture.get_pixel_coords(3, 3), arr);
}

TEST_F(TextureClassTest, uvCoordsCorrect) {
  std::array<glm::vec2, 4> arr{glm::vec2(0.0f, 0.0f), glm::vec2(15.0f, 0.0f),
                               glm::vec2(15.0f, 15.0f), glm::vec2(0.0f, 15.0f)};
  std::array<glm::vec2, 4> exp_output{
      glm::vec2(0.0f, 0.0f), glm::vec2(15.0f / 2048.0f, 0.0f),
      glm::vec2(15.0f / 2048.0f, 15.0f / 2048.0f),
      glm::vec2(0.0f, 15.0f / 2048.0f)};

  ASSERT_EQ(texture.get_uv_coords(arr), exp_output);
}
