#ifndef H_RENDER_CORE_TEXTURE
#define H_RENDER_CORE_TEXTURE

#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER > 1000

#include "d_core/pch.hpp"
#include "_gl_head.hpp"

namespace daydream {
namespace renderer {

enum class D_API_EXPORT COLOR_SPACE { RGB = 0, RED, YCRCB, HSV, RGBA, HDR, None };

enum class D_API_EXPORT TEXTURE_TYPE {
  None = 0,
  Diffuse,
  Specular,
  Ambient,
  Normal,
  Metallic,
  Roughness,
  AOT,
  Displacement,
};

class D_API_EXPORT _obj_texture {
 public:
  _obj_texture() = default;
  _obj_texture(uint32_t w, uint32_t h, uint32_t c, COLOR_SPACE cs);
  virtual ~_obj_texture() = default;

  virtual void Bind(uint32_t b = 0) const = 0;
  virtual void UnBind(uint32_t b = 0) const = 0;

  virtual uint32_t Width() const { return m_w; }
  virtual uint32_t Height() const { return m_h; }
  virtual uint32_t Channel() const { return m_c; }
  virtual COLOR_SPACE ColorSpace() const { return m_type; }
  virtual uint32_t getIdx() const { return m_idx; }
  virtual const std::string& Name() const { return m_name; }
  virtual const std::string& FilePath() const { return m_path; }

  virtual void resetData(void* data, uint32_t size) = 0;

 protected:
  COLOR_SPACE m_type = COLOR_SPACE::None;
  uint32_t m_idx = 0;
  uint32_t m_w = 0, m_h = 0, m_c = 0;
  std::string m_name;
  std::string m_path;
};

class D_API_EXPORT Texture2D : public _obj_texture {
 public:
  Texture2D(uint32_t w, uint32_t h);
  Texture2D(const std::string& file_path, bool hdr = false);
  ~Texture2D();

  void Bind(uint32_t b = 0) const override;
  void UnBind(uint32_t b = 0) const override;

  void resetData(void* data, uint32_t size);

  bool isEmpty();

  static REF(Texture2D) create(uint32_t w, uint32_t h);
  static REF(Texture2D) create(const std::string& file_path, bool hdr = false);

 private:
  bool m_hasImage = false;
  GLenum m_format = 0;
};

}  // namespace renderer
}  // namespace daydream

#endif  // !H_RENDER_CORE_TEXTURE
