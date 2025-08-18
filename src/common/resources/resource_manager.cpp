#include "resource_manager.h"

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "common/resources/shader.h"
#include "common/resources/texture.h"
#include "common/utils/logger.h"

namespace common {
namespace resources {

std::map<std::string, Texture> ResourceManager::textures_;
std::map<std::string, Shader> ResourceManager::shaders_;

Texture& ResourceManager::LoadTexture(const std::string& file,
                                      const std::string& texture_name,
                                      bool alpha) {
  textures_[texture_name] = loadTextureFromFile(file, alpha);
  return textures_[texture_name];
}

Shader& ResourceManager::LoadShader(const std::string& vertex_shader_file,
                                    const std::string& fragment_shader_file,
                                    const std::string& shader_name) {
  shaders_[shader_name] =
      loadShaderFromFile(vertex_shader_file, fragment_shader_file);
  return shaders_[shader_name];
}

Texture& ResourceManager::GetTexture(const std::string& texture_name) {
  return textures_[texture_name];
}

Shader& ResourceManager::GetShader(const std::string& shader_name) {
  return shaders_[shader_name];
}

Texture ResourceManager::loadTextureFromFile(const std::string& file,
                                              bool alpha) {
  Texture texture;
  int width, height, channels;
  unsigned char* data =
      stbi_load(file.c_str(), &width, &height, &channels, 0);
  if (alpha) {
    texture.setImageFormat(GL_RGBA);
    texture.setInternalFormat(GL_RGBA);
  }

  if (data) {
    texture.generate(width, height, data);
  } else {
    const char* failure_reason = stbi_failure_reason();
    utils::Logger::Error("Failed to load image " + file + ": " +
                         failure_reason + "\n");
  }
  stbi_image_free(data);
  return texture;
}

Shader ResourceManager::loadShaderFromFile(const std::string& vertex_shader,
                                           const std::string& fragment_shader) {
  std::string vertex_code;
  std::string fragment_code;
  std::ifstream v_shader_file;
  std::ifstream f_shader_file;

  v_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  f_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try {
    v_shader_file.open(vertex_shader);
    f_shader_file.open(fragment_shader);

    std::stringstream v_shader_stream, f_shader_stream;
    v_shader_stream << v_shader_file.rdbuf();
    f_shader_stream << f_shader_file.rdbuf();

    v_shader_file.close();
    f_shader_file.close();

    vertex_code = v_shader_stream.str();
    fragment_code = f_shader_stream.str();
  } catch (std::ifstream::failure& e) {
    utils::Logger::Error("SHADER: Failed to read file: " +
                         std::string(e.what()));
  }

  Shader shader(vertex_code.c_str(), fragment_code.c_str());
  return shader;
}

}  // namespace resources
}  // namespace common