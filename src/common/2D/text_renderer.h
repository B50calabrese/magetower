#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <ft2build.h>

#include <map>
#include FT_FREETYPE_H

#include "common/resources/shader.h"
#include "common/utils/bounding_box_2d.h"
#include "glm/glm.hpp"

namespace common {
namespace twod {

using common::resources::Shader;
using common::utils::BoundingBox2D;

class TextRenderer {
 public:
  TextRenderer(Shader& shader, glm::mat4 projection_matrix);

  struct Character {
    unsigned int textureId;  // ID handle of the glyph texture
    glm::ivec2 size;         // Size of the glyph
    glm::ivec2 bearing;      // Offset from baseline to left/top of glyph
    unsigned int advance;    // Offset to advance to next glyph.
  };

  std::map<char, Character> getCharacters() { return this->characters; }

  void RenderText(std::string text, float x, float y, float scale,
                  glm::vec3 color, float rotate = 0.0f);

  void RenderTextInBoundingBox(std::string text, BoundingBox2D bounding_box,
                               float scale, glm::vec3 color,
                               bool scale_to_fit = false);

 private:
  void init();

  void loadFreeType();

  void reserveVaoVbo();

  /*
   * Renders a word.
   * @returns the new position of the cursor
   */
  glm::vec2 renderWord(std::string word, float x, float y, float scale);

  /*
   * Renders the character at the position.
   * @returns the new position of the cursor
   */
  glm::vec2 renderCharacter(const char& c, float x, float y, float scale);

  glm::vec2 computeWordFinalPosition(std::string word, float x, float y,
                                     float scale);

  float computeOptimalScale(std::string word, float scale,
                            BoundingBox2D bounding_box);

  Shader shader;

  unsigned int VAO, VBO;

  std::map<char, Character> characters;

  float line_height;
};

}  // namespace twod
}  // namespace common

#endif  // TEXT_RENDERER