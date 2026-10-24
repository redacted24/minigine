#ifndef INCLUDE_SHADER_H
#define INCLUDE_SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <spdlog/spdlog.h>
#include <string>

class Shader {
public:
  /**
   * @brief Program ID, used for many important things.
   */
  unsigned int ID;

  /**
   * @brief Constructor for the Shader class.
   *
   * @param vertexPath path to vertex shader
   * @param fragmentPath path to fragment shader
   */
  Shader(const char *vertexPath, const char *fragmentPath);

  /**
   * @brief Use or active shader.
   */
  void use();

  // utility uniform functions
  /**
   * @brief Set boolean value for shader.
   *
   * @param name
   * @param value
   */
  void setBool(const std::string &name, bool value) const;

  /**
   * @brief Set int value
   *
   * @param name
   * @param value
   */
  void setInt(const std::string &name, int value) const;

  /**
   * @brief Set float value
   *
   * @param name
   * @param value
   */
  void setFloat(const std::string &name, float value) const;

  /**
   * @brief Set 2d matrix.
   *
   * @param name
   * @param mat
   */
  void setMat2(const std::string &name, const glm::mat2 &mat) const;

  /**
   * @brief Set 3d matrix.
   *
   * @param name
   * @param mat
   */
  void setMat3(const std::string &name, const glm::mat3 &mat) const;

  /**
   * @brief Set 4d matrix.
   *
   * @param name
   * @param mat
   */
  void setMat4(const std::string &name, const glm::mat4 &mat) const;

  /**
   * @brief Set 2d vector, using a glm::vec2 object.
   *
   * @param name
   * @param value
   */
  void setVec2(const std::string &name, const glm::vec2 &value) const;

  /**
   * @brief Set a 2d vector using x and y values.
   *
   * @param name
   * @param x
   * @param y
   */
  void setVec2(const std::string &name, float x, float y) const;

  /**
   * @brief Set 3d vector, using a glm::vec3 object.
   *
   * @param name
   * @param value
   */
  void setVec3(const std::string &name, const glm::vec3 &value) const;

  /**
   * @brief Set a 3d vector using x and y values.
   *
   * @param name
   * @param x
   * @param y
   */
  void setVec3(const std::string &name, float x, float y, float z) const;

  /**
   * @brief Set 4d vector, using a glm::vec4 object.
   *
   * @param name
   * @param value
   */
  void setVec4(const std::string &name, const glm::vec4 &value) const;

  /**
   * @brief Set a 4d vector using x and y values.
   *
   * @param name
   * @param x
   * @param y
   */
  void setVec4(const std::string &name, float x, float y, float z,
               float w) const;

private:
  void checkCompileErrors(unsigned int shader, std::string type);
};

#endif // INCLUDE_SHADER_H
