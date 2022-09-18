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

 private:
  float m_r = 100.f;  ///< the r of sphare. You should include all objects in the SkySphare.
  REF(LightDirect) m_WorldLight;
  REF(Shader) m_shader_pass2 = CREATE_REF(Shader)("../Asset/shader/SkyBox.glsl");
};

class D_API_EXPORT StandardSkyBox : public drawObject {
 public:
  StandardSkyBox();

  void draw() override final;
  void update() override final;

 private:
};

}  // namespace renderer
}  // namespace daydream

#endif  // !H_RENDER_CORE_SKYBOX_HPP_
