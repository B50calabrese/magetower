#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include "shader.h"
#include "texture.h"

namespace common {
    namespace resources {

        class ResourceManager {
        public:
            static std::map<std::string, Texture> textures;
            static std::map<std::string, Shader> shaders;

            static Texture LoadTexture(const char* file, std::string texture_name, bool alpha);

            static Texture LoadTextureRelative(const char* file, std::string texture_name, bool alpha);

            static Shader LoadShader(const char* vertexShaderFile, const char* fragmentShaderFile, std::string shader_name);

            static Shader LoadShaderRelative(const char* vertexShaderFile, const char* fragmentShaderFile, std::string shader_name);

            static Texture GetTexture(std::string texture_name);

            static Shader GetShader(std::string shader_name);

            static std::string GetBaseFilePath() {
                return "C:/code/cardrogue/";
            }

        private:
            ResourceManager() {}

            static Texture loadTextureFromFile(const char* file, bool alpha);

            static Shader loadShaderFromFile(const char* vertexShader, const char* fragmentShader);
        };

    } // namespace resources
} // namespace common

#endif // RESOURCE_MANAGER_H