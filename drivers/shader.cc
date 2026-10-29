#include "shader.h"
#include "spdlog/spdlog.h"
#include <fstream>
#include <glm/glm.hpp>
#include <iostream>
#include <sstream>

Shader::Shader() {};

Shader::Shader(const char *p_vertex_path, const char *p_fragment_path) {
  spdlog::debug("Initializing vertex shader {} and fragment shader {}",
                p_vertex_path, p_fragment_path);
  std::string vertexCode;
  std::string fragmentCode;
  std::ifstream vShaderFile;
  std::ifstream fShaderFile;

  vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    // open files
    vShaderFile.open(p_vertex_path);
    std::stringstream vShaderStream, fShaderStream;
    // read file's buffer contents into stream
    vShaderStream << vShaderFile.rdbuf();
    // close file handlers
    vShaderFile.close();
    // convert stream into string
    vertexCode = vShaderStream.str();
  }

  catch (std::ifstream::failure e) {
    spdlog::error("Vertex shader file {} not successfully read.",
                  p_vertex_path);
  }

  try {
    fShaderFile.open(p_fragment_path);
    std::stringstream fShaderStream;
    fShaderStream << fShaderFile.rdbuf();
    fShaderFile.close();
    fragmentCode = fShaderStream.str();
  }

  catch (std::ifstream::failure e) {
    spdlog::error("Fragment shader file {} not successfully read.",
                  p_fragment_path);
  }

  spdlog::debug("Read vs {} and fs {}", p_vertex_path, p_fragment_path);
  const char *vShaderCode = vertexCode.c_str();
  const char *fShaderCode = fragmentCode.c_str();

  // 2. Compile shaders
  unsigned int vertex, fragment;
  int success;
  char infoLog[52];

  // vertex shader
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, nullptr);
  glCompileShader(vertex);
  // print compile errors if any
  checkCompileErrors(vertex, "VERTEX");
  spdlog::debug("vertex shader {} compiled", p_vertex_path);

  // fragment shader
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, nullptr);
  glCompileShader(fragment);
  checkCompileErrors(fragment, "FRAGMENT");
  spdlog::debug("fragment shader {} compiled", p_fragment_path);

  // shaderProgram
  ID = glCreateProgram();
  glAttachShader(ID, vertex);
  glAttachShader(ID, fragment);
  glLinkProgram(ID);
  glGetProgramiv(ID, GL_LINK_STATUS, &success);
  checkCompileErrors(ID, "PROGRAM");
  spdlog::debug("shader program (ID:3) created", ID);

  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

void Shader::use() { glUseProgram(ID); }

void Shader::setBool(const std::string &p_name, bool p_value) const {
  glUniform1i(glGetUniformLocation(ID, p_name.c_str()), (int)p_value);
}

void Shader::setInt(const std::string &p_name, int p_value) const {
  glUniform1i(glGetUniformLocation(ID, p_name.c_str()), p_value);
}

void Shader::setFloat(const std::string &p_name, float p_value) const {
  glUniform1f(glGetUniformLocation(ID, p_name.c_str()), p_value);
}

void Shader::setVec2(const std::string &p_name,
                     const glm::vec2 &p_value) const {
  glUniform2fv(glGetUniformLocation(ID, p_name.c_str()), 1, &p_value[0]);
}

void Shader::setVec2(const std::string &p_name, float p_x, float p_y) const {
  glUniform2f(glGetUniformLocation(ID, p_name.c_str()), p_x, p_y);
}

void Shader::setVec3(const std::string &p_name,
                     const glm::vec3 &p_value) const {
  glUniform3fv(glGetUniformLocation(ID, p_name.c_str()), 1, &p_value[0]);
}

void Shader::setVec3(const std::string &p_name, float p_x, float p_y,
                     float p_z) const {
  glUniform3f(glGetUniformLocation(ID, p_name.c_str()), p_x, p_y, p_z);
}

void Shader::setVec4(const std::string &p_name,
                     const glm::vec4 &p_value) const {
  glUniform4fv(glGetUniformLocation(ID, p_name.c_str()), 1, &p_value[0]);
}

void Shader::setVec4(const std::string &p_name, float p_x, float p_y, float p_z,
                     float p_w) const {
  glUniform4f(glGetUniformLocation(ID, p_name.c_str()), p_x, p_y, p_z, p_w);
}

void Shader::setMat2(const std::string &p_name, const glm::mat2 &p_mat) const {
  glUniformMatrix2fv(glGetUniformLocation(ID, p_name.c_str()), 1, GL_FALSE,
                     &p_mat[0][0]);
}

void Shader::setMat3(const std::string &p_name, const glm::mat3 &p_mat) const {
  glUniformMatrix3fv(glGetUniformLocation(ID, p_name.c_str()), 1, GL_FALSE,
                     &p_mat[0][0]);
}

void Shader::setMat4(const std::string &p_name, const glm::mat4 &p_mat) const {
  glUniformMatrix4fv(glGetUniformLocation(ID, p_name.c_str()), 1, GL_FALSE,
                     &p_mat[0][0]);
}

void Shader::checkCompileErrors(unsigned int p_shader, std::string p_type) {
  int success;
  char infoLog[1024];
  if (p_type != "PROGRAM") {
    glGetShaderiv(p_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(p_shader, 1024, nullptr, infoLog);
      spdlog::error("Shader compilation error of type {}. {}", p_type, infoLog);
    }
  } else {
    glGetProgramiv(p_shader, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(p_shader, 1024, nullptr, infoLog);
      spdlog::error("Shader linking error of type {}. {}", p_type, infoLog);
    }
  }
}
