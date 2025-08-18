#ifndef COMMON_2D_TEXT_RENDERER_H_
#define COMMON_2D_TEXT_RENDERER_H_

#include <ft2build.h>

#include <map>
#include <string>
#include FT_FREETYPE_H

#include "common/resources/shader.h"
#include "common/utils/bounding_box_2d.h"
#include "glm/glm.hpp"

namespace common {
namespace twod {

class TextRenderer {
 public:
  TextRenderer(common::resources::Shader shader, glm::mat4 projection_matrix);

  struct Character {
    unsigned int texture_id_;  // ID handle of the glyph texture
    glm::ivec2 size_;          // Size of the glyph
    glm::ivec2 bearing_;       // Offset from baseline to left/top of glyph
    unsigned int advance_;     // Offset to advance to next glyph.
  };

  const std::map<char, Character>& getCharacters() const {
    return characters_;
  }

  void RenderText(const std::string& text, float x, float y, float scale,
                  glm::vec3 color, float rotate = 0.0f);

  void RenderTextInBoundingBox(const std::string& text,
                               const common::utils::BoundingBox2D& bounding_box,
                               float scale, glm::vec3 color,
                               bool scale_to_fit = false);

 private:
  void init();

  void loadFreeType();

  void reserveVaoVbo();

  /**
   * Renders a word.
   * @return the new position of the cursor
   */
  glm::vec2 renderWord(const std::string& word, float x, float y, float scale);

  /**
   * Renders the character at the position.
   * @return the new position of the cursor
   */
  glm::vec2 renderCharacter(const char& c, float x, float y, float scale);

  glm::vec2 computeWordFinalPosition(const std::string& word, float x, float y,
                                     float scale);

  float computeOptimalScale(const std::string& word, float scale,
                            const common::utils::BoundingBox2D& bounding_box);

  common::resources::Shader shader_;

  unsigned int vao_, vbo_;

  std::map<char, Character> characters_;

  float line_height_;
};

}  // namespace twod
}  // namespace common

#endif  // COMMON_2D_TEXT_RENDERER_H_