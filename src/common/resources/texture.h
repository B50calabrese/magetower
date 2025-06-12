#ifndef TEXTURE_H
#define TEXTURE_H

#include "glm/vec2.hpp"

namespace common {
namespace resources {

/*
 * Utility class for holding texture information, and applying textures.
 */
class Texture {
 public:
  Texture();

  void generate(unsigned int width, unsigned int height, unsigned char* data);

  void bind() const;

  void setInternalFormat(unsigned int internal_format) {
    this->internal_format = internal_format;
  }

  void setImageFormat(unsigned int image_format) {
    this->image_format = image_format;
  }

  unsigned int getId() { return this->id; }

  unsigned int getWidth() { return this->width; }

  unsigned int getHeight() { return this->height; }

  glm::vec2 getSizeVector() { return glm::vec2(this->width, this->height); }

 private:
  unsigned int id, width, height, internal_format, image_format;
  unsigned int wrap_s, wrap_t, filter_min, filter_max;
};

}  // namespace resources
}  // namespace common

#endif  // TEXTURE_H