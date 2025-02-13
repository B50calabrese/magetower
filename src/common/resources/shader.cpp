#include "shader.h"

#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GL/GL.h>
#include <glm/gtc/type_ptr.hpp>

namespace common {
    namespace resources {

        Shader::Shader(const char* vertexData, const char* fragmentData) {
            GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertexShader, 1, &(vertexData), 0);
            glCompileShader(vertexShader);

            // print compile errors if any
            int success;
            char infoLog[512];
            glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(vertexShader, 512, 0, infoLog);
                std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
            };

            GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragmentShader, 1, &(fragmentData), 0);
            glCompileShader(fragmentShader);

            glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(fragmentShader, 512, 0, infoLog);
                std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
            };

            this->id = glCreateProgram();
            glAttachShader(this->id, vertexShader);
            glAttachShader(this->id, fragmentShader);
            glLinkProgram(this->id);

            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
        }

        void Shader::activate() {
            glUseProgram(this->id);
        }

        void Shader::setMat4(const std::string& uniformName, const glm::mat4& input) {
            glUniformMatrix4fv(glGetUniformLocation(this->id, uniformName.c_str()), 1, false, glm::value_ptr(input));
        }

        void Shader::setVec3(const std::string& uniformName, const glm::vec3 input) {
            glUniform3f(glGetUniformLocation(this->id, uniformName.c_str()), input.x, input.y, input.z);
        }

        void Shader::setVec4(const std::string& uniformName, const glm::vec4 input) {
            glUniform4f(glGetUniformLocation(this->id, uniformName.c_str()), input.x, input.y, input.z, input.a);
        }

        void Shader::setInteger(const std::string& uniformName, const int input) {
            glUniform1i(glGetUniformLocation(this->id, uniformName.c_str()), input);
        }

    } // namespace resources
} // namespace common