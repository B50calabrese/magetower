#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <glm/mat4x4.hpp>
#include <string>

namespace common {
namespace resources {

class Shader {
 public:
  Shader() {}

  Shader(const char* vertexData, const char* fragmentData);

  void setMat4(const std::string& uniformName, const glm::mat4& input);

  void setVec3(const std::string& uniformName, const glm::vec3 input);

  void setVec4(const std::string& uniformName, const glm::vec4 input);

  void setInteger(const std::string& uniformName, const int input);

  // Enable the shader
  void activate();

  // Disable the shader
  void deactivate();

 private:
  GLuint id = 0;
};

}  // namespace resources
}  // namespace common

#endif  // SHADER_H