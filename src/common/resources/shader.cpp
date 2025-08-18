#include "shader.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>
#include <string>

#include "common/utils/logger.h"

namespace common {
namespace resources {

Shader::Shader(const char* vertex_data, const char* fragment_data) {
  GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &(vertex_data), 0);
  glCompileShader(vertex_shader);

  // print compile errors if any
  int success;
  char info_log[512];
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex_shader, 512, 0, info_log);
    utils::Logger::Error("SHADER: Vertex compilation failed: " +
                         std::string(info_log));
  };

  GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &(fragment_data), 0);
  glCompileShader(fragment_shader);

  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragment_shader, 512, 0, info_log);
    utils::Logger::Error("SHADER: Fragment compilation failed: " +
                         std::string(info_log));
  };

  id_ = glCreateProgram();
  glAttachShader(id_, vertex_shader);
  glAttachShader(id_, fragment_shader);
  glLinkProgram(id_);

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
}

void Shader::activate() const { glUseProgram(id_); }

void Shader::deactivate() const { glUseProgram(0); }

void Shader::setMat4(const std::string& uniform_name,
                     const glm::mat4& input) const {
  glUniformMatrix4fv(glGetUniformLocation(id_, uniform_name.c_str()), 1, false,
                     glm::value_ptr(input));
}

void Shader::setVec3(const std::string& uniform_name,
                     const glm::vec3& input) const {
  glUniform3f(glGetUniformLocation(id_, uniform_name.c_str()), input.x, input.y,
              input.z);
}

void Shader::setVec4(const std::string& uniform_name,
                     const glm::vec4& input) const {
  glUniform4f(glGetUniformLocation(id_, uniform_name.c_str()), input.x, input.y,
              input.z, input.a);
}

void Shader::setInteger(const std::string& uniform_name, const int input) const {
  glUniform1i(glGetUniformLocation(id_, uniform_name.c_str()), input);
}

}  // namespace resources
}  // namespace common