#ifndef COMMON_RESOURCES_SHADER_H_
#define COMMON_RESOURCES_SHADER_H_

#include <string>

#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace common {
namespace resources {

class Shader {
 public:
  Shader() = default;

  Shader(const char* vertex_data, const char* fragment_data);

  void setMat4(const std::string& uniform_name, const glm::mat4& input) const;

  void setVec3(const std::string& uniform_name, const glm::vec3& input) const;

  void setVec4(const std::string& uniform_name, const glm::vec4& input) const;

  void setInteger(const std::string& uniform_name, int input) const;

  // Enable the shader
  void activate() const;

  // Disable the shader
  void deactivate() const;

 private:
  GLuint id_ = 0;
};

}  // namespace resources
}  // namespace common

#endif  // COMMON_RESOURCES_SHADER_H_