#ifndef H_RENDER_RESOURCE_KVBASE_HPP_
#define H_RENDER_RESOURCE_KVBASE_HPP_

#if MSC_VER > 1000
#pragma once
#endif

#include "d_core/pch.hpp"
#include "d_render/core/material.hpp"

using namespace ::daydream::renderer;

namespace daydream {
namespace resource {

enum class D_API_EXPORT ComponentType : uint8_t {
  None = 0,
  Texture_t,
  Material_t,
  Shader_t,
};

struct Component {
 protected:
  uint32_t __magic__;
  ComponentType __type__ = ComponentType::None;
};

struct TextureComponent : public Component {
  explicit TextureComponent(REF(Texture2D) & a, const std::string& n, const std::string& f)
      : __this__(a), __name__(n), __file_path__(f) {
    __type__ = ComponentType::Texture_t;
  }

  const std::string& Name() const { return __name__; }
  const REF(Texture2D) Item() const { return __this__; }

 private:
  std::string __name__;
  std::string __file_path__;
  REF(Texture2D) __this__;
};

struct MaterialComponent : public Component {
  explicit MaterialComponent(REF(_obj_material) & a, const std::string& n)
      : __this__(a), __name__(n) {
    __type__ = ComponentType::Material_t;
  }

  const std::string& Name() const { return __name__; }
  const REF(_obj_material) Item() const { return __this__; }

 private:
  std::string __name__;
  REF(_obj_material) __this__;
};

struct ShaderComponent : public Component {
  explicit ShaderComponent(REF(Shader) & a, const std::string& n, const std::string& f)
      : __this__(a), __name__(n), __file_path__(f) {
    __type__ = ComponentType::Shader_t;
  }

  const std::string& Name() const { return __name__; }
  const REF(Shader) Item() const { return __this__; }

 private:
  std::string __name__;
  std::string __file_path__;
  REF(Shader) __this__;
};

class D_API_EXPORT KVBase {
 public:
  ~KVBase();
  bool FindByPath(const std::string& f);
  REF(Texture2D) FindTexture(const std::string& f);

 private:
  uint32_t Hashing(const std::string& n);

  std::unordered_map<uint32_t, Component*> m_data;
};

}  // namespace resource
}  // namespace daydream

#endif  //! H_RENDER_RESOURCE_KVBASE_HPP_