#include "sprite_renderer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>

#include "common/resources/shader.h"

namespace common {
namespace twod {

using common::resources::Shader;
using common::resources::Texture;

SpriteRenderer::SpriteRenderer(Shader& shader, glm::mat4 projection_matrix)
    : shader(shader), projection_matrix(projection_matrix) {
  this->init();
}

void SpriteRenderer::DrawSprite(Texture& texture, glm::vec2 position,
                                glm::vec2 size, float rotate, glm::vec4 color) {
  // prepare transformations
  glm::mat4 model = generateModelMatrix(position, size, rotate);

  this->DrawSprite(texture, model, color);
}

void SpriteRenderer::DrawSprite(Texture& texture, glm::mat4 model_matrix,
                                glm::vec4 color) {
  this->shader.activate();

  this->shader.setMat4("model", model_matrix);
  this->shader.setVec4("spriteColor", color);

  this->bindTextureAndDraw(texture);
}

// Private functions.

void SpriteRenderer::init() {
  // configure VAO/VBO
  unsigned int VBO;
  float vertices[] = {
      // pos      // tex
      0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,

      0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f};

  glGenVertexArrays(1, &this->VAO);
  glGenBuffers(1, &VBO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindVertexArray(this->VAO);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  // configure shaders
  this->shader.activate();
  this->shader.setMat4("projection", this->projection_matrix);
}

void SpriteRenderer::bindTextureAndDraw(Texture& texture) {
  glActiveTexture(GL_TEXTURE0);
  texture.bind();

  glBindVertexArray(this->VAO);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
}

glm::mat4 SpriteRenderer::generateModelMatrix(glm::vec2 position,
                                              glm::vec2 size, float rotate) {
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(
      model, glm::vec3(position,
                       0.0f));  // first translate (transformations are: scale
                                // happens first, then rotation, and then final
                                // translation happens; reversed order)

  model = glm::translate(
      model, glm::vec3(0.5f * size.x, 0.5f * size.y,
                       0.0f));  // move origin of rotation to center of quad
  model = glm::rotate(model, glm::radians(rotate),
                      glm::vec3(0.0f, 0.0f, 1.0f));  // then rotate
  model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y,
                                          0.0f));  // move origin back

  model = glm::scale(model, glm::vec3(size, 1.0f));  // last scale
  return model;
}

}  // namespace twod
}  // namespace common