#include "resource_manager.h"

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "common/resources/shader.h"
#include "common/resources/texture.h"
#include "common/utils/logger.h"
#include "stb_image.h"

namespace common {
namespace resources {

std::map<std::string, Texture> ResourceManager::textures;
std::map<std::string, Shader> ResourceManager::shaders;

Texture ResourceManager::LoadTexture(const char* file, std::string texture_name,
                                     bool alpha) {
  textures[texture_name] = loadTextureFromFile(file, alpha);
  return textures[texture_name];
}

Texture ResourceManager::LoadTextureRelative(const char* file,
                                             std::string texture_name,
                                             bool alpha) {
  return ResourceManager::LoadTexture(
      (ResourceManager::GetBaseFilePath() + file).data(), texture_name, alpha);
}

Shader ResourceManager::LoadShader(const char* vertexShaderFile,
                                   const char* fragmentShaderFile,
                                   std::string shader_name) {
  shaders[shader_name] =
      loadShaderFromFile(vertexShaderFile, fragmentShaderFile);
  return shaders[shader_name];
}

Shader ResourceManager::LoadShaderRelative(const char* vertexShaderFile,
                                           const char* fragmentShaderFile,
                                           std::string shader_name) {
  return ResourceManager::LoadShader(
      (ResourceManager::GetBaseFilePath() + vertexShaderFile).data(),
      (ResourceManager::GetBaseFilePath() + fragmentShaderFile).data(),
      shader_name);
}

Texture ResourceManager::GetTexture(std::string texture_name) {
  return textures[texture_name];
}

Shader ResourceManager::GetShader(std::string shader_name) {
  return shaders[shader_name];
}

Texture ResourceManager::loadTextureFromFile(const char* file, bool alpha) {
  Texture texture;
  int width, height, channels;
  unsigned char* data = stbi_load(file, &width, &height, &channels, 0);
  if (alpha) {
    texture.setImageFormat(GL_RGBA);
    texture.setInternalFormat(GL_RGBA);
  }

  if (data) {
    texture.generate(width, height, data);
  } else {
    const char* failureReason = stbi_failure_reason();
    std::string failure_reason_string = failureReason;
    std::string file_string = file;
    common::utils::Logger::Error("Failed to load image " + file_string + ": " +
                                 failure_reason_string + "\n");
  }
  stbi_image_free(data);
  return texture;
}

Shader ResourceManager::loadShaderFromFile(const char* vertexShader,
                                           const char* fragmentShader) {
  std::string vertexCode;
  std::string fragmentCode;
  std::ifstream vShaderFile;
  std::ifstream fShaderFile;

  try {
    vShaderFile.open(vertexShader);
    fShaderFile.open(fragmentShader);

    // Read the contents of the files.
    std::stringstream vShaderStream, fShaderStream;
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();

    // Close the files.
    vShaderFile.close();
    fShaderFile.close();

    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();
  } catch (std::ifstream::failure& e) {
    std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what()
              << std::endl;
  }

  Shader shader(vertexCode.c_str(), fragmentCode.c_str());
  return shader;
}

}  // namespace resources
}  // namespace common