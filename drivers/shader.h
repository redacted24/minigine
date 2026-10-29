#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <spdlog/spdlog.h>
#include <string>

class Shader {
public:
  unsigned int ID;

  Shader();
  Shader(const char *p_vertex_path, const char *p_fragment_path);

  void use();

  void setBool(const std::string &p_name, bool p_value) const;
  void setInt(const std::string &p_name, int p_value) const;
  void setFloat(const std::string &p_name, float p_value) const;
  void setMat2(const std::string &p_name, const glm::mat2 &p_mat) const;
  void setMat3(const std::string &p_name, const glm::mat3 &p_mat) const;
  void setMat4(const std::string &p_name, const glm::mat4 &p_mat) const;
  void setVec2(const std::string &p_name, const glm::vec2 &p_value) const;
  void setVec2(const std::string &p_name, float p_x, float p_y) const;
  void setVec3(const std::string &p_name, const glm::vec3 &p_value) const;
  void setVec3(const std::string &p_name, float p_x, float p_y,
               float p_z) const;
  void setVec4(const std::string &p_name, const glm::vec4 &p_value) const;
  void setVec4(const std::string &p_name, float p_x, float p_y, float p_z,
               float p_w) const;

private:
  void checkCompileErrors(unsigned int p_shader, std::string p_type);
};

#endif // SHADER_H
