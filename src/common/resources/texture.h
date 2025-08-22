#ifndef MAGETOWER_SRC_COMMON_RESOURCES_TEXTURE_H_
#define MAGETOWER_SRC_COMMON_RESOURCES_TEXTURE_H_

#include "glm/vec2.hpp"

namespace common {
namespace resources {

// Utility class for holding texture information, and applying textures.
class Texture {
 public:
  Texture();

  void Generate(unsigned int width, unsigned int height, unsigned char* data);

  void Bind() const;

  void set_internal_format(unsigned int internal_format) {
    internal_format_ = internal_format;
  }

  void set_image_format(unsigned int image_format) {
    image_format_ = image_format;
  }

  unsigned int id() const { return id_; }

  unsigned int width() const { return width_; }

  unsigned int height() const { return height_; }

  glm::vec2 size_vector() const { return glm::vec2(width_, height_); }

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

#endif  // MAGETOWER_SRC_COMMON_RESOURCES_TEXTURE_H_