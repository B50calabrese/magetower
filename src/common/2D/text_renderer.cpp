#include "text_renderer.h"

#include <ft2build.h>

#include <iostream>
#include <sstream>
#include FT_FREETYPE_H

#include "common/utils/logger.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace common {
namespace twod {

TextRenderer::TextRenderer(common::resources::Shader shader,
                           glm::mat4 projection_matrix)
    : shader_(shader) {
  // Configure shaders
  shader_.activate();
  shader_.setMat4("projection", projection_matrix);
  init();
}

void TextRenderer::RenderText(const std::string& text, float x, float y,
                              float scale, glm::vec3 color, float rotate) {
  // activate corresponding render state
  shader_.activate();
  shader_.setVec3("textColor", color);

  glActiveTexture(GL_TEXTURE0);
  glBindVertexArray(vao_);

  // Set up initial values.
  float rotation_radians = glm::radians(rotate);
  glm::vec2 starting_position = glm::vec2(x, y);

  // iterate through all characters
  for (const char& c : text) {
    Character ch = characters_[c];

    starting_position =
        renderCharacter(c, starting_position.x, starting_position.y, scale);
  }
  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void TextRenderer::RenderTextInBoundingBox(
    const std::string& text, const common::utils::BoundingBox2D& bounding_box,
    float scale, glm::vec3 color, bool scale_to_fit) {
  float computed_scale =
      scale_to_fit ? computeOptimalScale(text, scale, bounding_box) : scale;

  // activate corresponding render state
  shader_.activate();
  shader_.setVec3("textColor", color);

  glActiveTexture(GL_TEXTURE0);
  glBindVertexArray(vao_);

  // Set up initial values.
  glm::vec2 starting_position =
      glm::vec2(bounding_box.bottom_left.x,
                bounding_box.bottom_left.y + bounding_box.size.y -
                    (line_height_ * computed_scale));

  // iterate through all characters
  std::stringstream potential_word;
  for (char c : text) {
    if (c == '\0') {
      break;
    } else if (c == ' ' || c == '\n') {
      // Render the word, advance the position, and clear the word.
      glm::vec2 potential_position =
          computeWordFinalPosition(potential_word.str(), starting_position.x,
                                   starting_position.y, computed_scale);

      // If we went beyond the bounds of the box, add a line.
      if (potential_position.x >
          (bounding_box.bottom_left.x + bounding_box.size.x)) {
        starting_position.x = bounding_box.bottom_left.x;
        starting_position.y -= line_height_ * computed_scale;
      }

      starting_position = renderWord(potential_word.str(), starting_position.x,
                                     starting_position.y, computed_scale);

      starting_position.x += (characters_[' '].advance_ >> 6) * computed_scale;
      potential_word.str("");

      if (c == '\n') {
        starting_position.y -= line_height_ * computed_scale;
        starting_position.x = bounding_box.bottom_left.x;
      }
    } else {
      potential_word << c;
    }
  }
  if (potential_word.str() != "") {
    // Render the word, advance the position, and clear the word.
    glm::vec2 potential_position =
        computeWordFinalPosition(potential_word.str(), starting_position.x,
                                 starting_position.y, computed_scale);

    // If we went beyond the bounds of the box, add a line.
    if (potential_position.x >
        (bounding_box.bottom_left.x + bounding_box.size.x)) {
      starting_position.x = bounding_box.bottom_left.x;
      starting_position.y -= line_height_ * computed_scale;
    }

    // Render the word, advance the position, and clear the word.
    starting_position = renderWord(potential_word.str(), starting_position.x,
                                   starting_position.y, computed_scale);
  }

  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}

// Private functions

void TextRenderer::init() {
  loadFreeType();
  reserveVaoVbo();
}

void TextRenderer::loadFreeType() {
  FT_Library ft;
  // All functions return a value different than 0 whenever an error occurred
  if (FT_Init_FreeType(&ft)) {
    utils::Logger::Error("FREETYPE: Could not init FreeType Library");
    return;
  }

  // load font as face
  FT_Face face;
  // TODO: Change what fonts we read.
  if (FT_New_Face(ft, "C:\\Windows\\fonts\\arial.ttf", 0, &face)) {
    utils::Logger::Error("FREETYPE: Failed to load font");
  } else {
    line_height_ = (face->height >> 6);

    // set size to load glyphs as
    FT_Set_Pixel_Sizes(face, 0, 48);

    // disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // load first 128 characters of ASCII set
    for (unsigned char c = 0; c < 128; c++) {
      // Load character glyph
      if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
        utils::Logger::Warning("FREETYTPE: Failed to load Glyph");
        continue;
      }
      // generate texture
      unsigned int texture;
      glGenTextures(1, &texture);
      glBindTexture(GL_TEXTURE_2D, texture);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width,
                   face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE,
                   face->glyph->bitmap.buffer);
      // set texture options
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      // now store character for later use
      Character character = {
          texture,
          glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
          glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
          static_cast<unsigned int>(face->glyph->advance.x)};
      characters_.insert(std::pair<char, Character>(c, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);
  }
  // destroy FreeType once we're finished
  FT_Done_Face(face);
}

void TextRenderer::reserveVaoVbo() {
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glBindVertexArray(vao_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

glm::vec2 TextRenderer::renderWord(const std::string& word, float x, float y,
                                   float scale) {
  glm::vec2 starting_position(x, y);
  for (char c2 : word) {
    Character ch = characters_[c2];

    starting_position =
        renderCharacter(c2, starting_position.x, starting_position.y, scale);
  }
  return starting_position;
}

glm::vec2 TextRenderer::renderCharacter(const char& c, float x, float y,
                                        float scale) {
  Character ch = characters_[c];

  float xpos = x + ch.bearing_.x * scale;
  float ypos = y - (ch.size_.y - ch.bearing_.y) * scale;

  float w = ch.size_.x * scale;
  float h = ch.size_.y * scale;

  float vertices[6][4] = {
      {0.0f, h, 0.0f, 0.0f}, {w, 0.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 1.0f},

      {0.0f, h, 0.0f, 0.0f}, {w, h, 1.0f, 0.0f},    {w, 0.0f, 1.0f, 1.0f}};

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(xpos, ypos, 0.0f));

  shader_.setMat4("model", model);

  // render glyph texture over quad
  glBindTexture(GL_TEXTURE_2D, ch.texture_id_);
  // update content of VBO memory
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  // render quad
  glDrawArrays(GL_TRIANGLES, 0, 6);

  // now advance cursors for next glyph (note that advance is number of 1/64
  // pixels)
  float advance_scaled = (ch.advance_ >> 6) * scale;
  return glm::vec2(x + advance_scaled, y);
}

glm::vec2 TextRenderer::computeWordFinalPosition(const std::string& word,
                                                 float x, float y,
                                                 float scale) {
  glm::vec2 final_position = glm::vec2(x, y);

  for (const char& c : word) {
    Character ch = characters_[c];
    float advance_scaled = (ch.advance_ >> 6) * scale;
    final_position += glm::vec2(advance_scaled, 0.0f);
  }

  return final_position;
}

float TextRenderer::computeOptimalScale(
    const std::string& word, float scale,
    const common::utils::BoundingBox2D& bounding_box) {
  float area_of_characters = 0.0f;
  float max_line_width = 0.0f;
  float current_line_width = 0.0f;
  int num_lines = 1;
  int num_spaces = 0;

  for (char c : word) {
    Character ch = characters_[c];
    // float w = (ch.advance >> 6) + ch.size.x;
    float w = (ch.advance_ >> 6);
    float h = ch.size_.y;

    if (c == '\n') {
      max_line_width = max_line_width < current_line_width ? current_line_width
                                                           : max_line_width;
      current_line_width = 0.0f;
      num_lines += 1;
    } else {
      if (c == ' ') {
        num_spaces++;
      }

      current_line_width += w;
    }
  }
  max_line_width =
      max_line_width < current_line_width ? current_line_width : max_line_width;
  int max_number_of_lines = std::ceil(bounding_box.size.y / line_height_);

  if (scale * max_line_width < bounding_box.size.x) {
    return scale;
  }

  for (int i = 2; i <= num_lines; i++) {
    if (scale * (max_line_width / 2) < bounding_box.size.x) {
      return scale;
    }
  }

  float scale_x = bounding_box.size.x / (max_line_width / num_lines);
  float scale_y = bounding_box.size.y / (line_height_ * num_lines);
  return std::min(scale_x, scale_y);
}

}  // namespace twod
}  // namespace common