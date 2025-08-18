#ifndef COMMON_RESOURCES_TEXTURE_H_
#define COMMON_RESOURCES_TEXTURE_H_

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
    internal_format_ = internal_format;
  }

  void setImageFormat(unsigned int image_format) {
    image_format_ = image_format;
  }

  unsigned int getId() const { return id_; }

  unsigned int getWidth() const { return width_; }

  unsigned int getHeight() const { return height_; }

  glm::vec2 getSizeVector() const { return glm::vec2(width_, height_); }

 private:
  unsigned int id_;
  unsigned int width_;
  unsigned int height_;
  unsigned int internal_format_;
  unsigned int image_format_;
  unsigned int wrap_s_;
  unsigned int wrap_t_;
  unsigned int filter_min_;
  unsigned int filter_max_;
};

}  // namespace resources
}  // namespace common

#endif  // COMMON_RESOURCES_TEXTURE_H_