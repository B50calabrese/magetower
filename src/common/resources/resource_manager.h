#ifndef COMMON_RESOURCES_RESOURCE_MANAGER_H_
#define COMMON_RESOURCES_RESOURCE_MANAGER_H_

#include <map>
#include <string>

#include "shader.h"
#include "texture.h"

namespace common {
namespace resources {

class ResourceManager {
 public:
  ResourceManager() = delete;

  static Texture& LoadTexture(const std::string& file,
                              const std::string& texture_name, bool alpha);

  static Shader& LoadShader(const std::string& vertex_shader_file,
                            const std::string& fragment_shader_file,
                            const std::string& shader_name);

  static Texture& GetTexture(const std::string& texture_name);

  static Shader& GetShader(const std::string& shader_name);

 private:
  static Texture loadTextureFromFile(const std::string& file, bool alpha);

  static Shader loadShaderFromFile(const std::string& vertex_shader,
                                   const std::string& fragment_shader);

  static std::map<std::string, Texture> textures_;
  static std::map<std::string, Shader> shaders_;
};

}  // namespace resources
}  // namespace common

#endif  // COMMON_RESOURCES_RESOURCE_MANAGER_H_