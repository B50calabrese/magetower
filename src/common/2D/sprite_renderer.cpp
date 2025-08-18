#include "sprite_renderer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>

#include "common/resources/shader.h"

namespace common {
namespace twod {

SpriteRenderer::SpriteRenderer(common::resources::Shader shader,
                               glm::mat4 projection_matrix)
    : shader_(shader), projection_matrix_(projection_matrix) {
  init();
}

void SpriteRenderer::DrawSprite(const common::resources::Texture& texture,
                                glm::vec2 position, glm::vec2 size,
                                float rotate, glm::vec4 color) {
  // prepare transformations
  glm::mat4 model = generateModelMatrix(position, size, rotate);

  DrawSprite(texture, model, color);
}

void SpriteRenderer::DrawSprite(const common::resources::Texture& texture,
                                glm::mat4 model_matrix, glm::vec4 color) {
  shader_.activate();

  shader_.setMat4("model", model_matrix);
  shader_.setVec4("spriteColor", color);

  bindTextureAndDraw(texture);
}

// Private functions.

void SpriteRenderer::init() {
  // configure VAO/VBO
  unsigned int vbo;
  float vertices[] = {
      // pos      // tex
      0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,

      0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f};

  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindVertexArray(vao_);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  // configure shaders
  shader_.activate();
  shader_.setMat4("projection", projection_matrix_);
}

void SpriteRenderer::bindTextureAndDraw(
    const common::resources::Texture& texture) {
  glActiveTexture(GL_TEXTURE0);
  texture.bind();

  glBindVertexArray(vao_);
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