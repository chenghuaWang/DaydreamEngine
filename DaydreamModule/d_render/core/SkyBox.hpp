#ifndef H_RENDER_CORE_SKYBOX_HPP_
#define H_RENDER_CORE_SKYBOX_HPP_

#if _MSC_VER > 1000
#pragma once
#endif

#include "d_core/pch.hpp"
#include "d_render/core/light.hpp"
#include "d_render/core/object/basicObj.hpp"

namespace daydream {
namespace renderer {

class D_API_EXPORT ProcedualSkySphare : public drawObject {
 public:
  ProcedualSkySphare();

  void draw() override final;
  void update() override final;

  REF(LightDirect) getLight() const;
  void Bind(const REF(Shader) & shader);

 private:
  float m_r = 100.f;  ///< the r of sphare. You should include all objects in the SkySphare.
  REF(LightDirect) m_WorldLight;
  REF(Shader) m_shader_pass2 = CREATE_REF(Shader)("../Asset/shader/SkyBox.glsl");
};

class D_API_EXPORT OctahedronSkyBox : public drawObject {
 public:
  OctahedronSkyBox();

  void draw() override final;
  void update() override final;

 private:
  void __init_octahedron__();
};

class D_API_EXPORT StandardSkyBox : public drawObject {
 public:
  StandardSkyBox();
  ~StandardSkyBox();

  void Init(KVBase* db, const std::string& file_path);
  void draw() override final;
  void update() override final;

  REF(Texture2D) getEnvMap() const;
  REF(LightDirect) getLight() const;
  void Bind(const REF(Shader) & shader) const;

 private:
  REF(LightDirect) m_WorldLight;
  std::vector<ModelObject*> m_meshes;
  void __init_standard__(KVBase* db, const std::string& file_path);
  void __Cover2CubeMap__();
};

}  // namespace renderer
}  // namespace daydream

#endif  // !H_RENDER_CORE_SKYBOX_HPP_
