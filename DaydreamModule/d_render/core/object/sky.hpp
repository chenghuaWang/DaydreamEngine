#ifndef H_CORE_OBJECT_SKY
#define H_CORE_OBJECT_SKY

#if _MSC_VER > 1000
#pragma once
#pragma warnind(disable : 4251)  // For disable warning of template-class in dll export.
#endif                           // _MSC_VER > 1000

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "d_core/pch.hpp"
#include "d_render/core/ds.hpp"
#include "d_render/core/shader.hpp"
#include "d_render/core/object/drawObj.hpp"

namespace daydream {
namespace renderer {

struct D_API_EXPORT colorPreset {
  glm::vec3 cloudColorBottom, skyColorTop, skyColorBottom, lightColor, fogColor;
};

class D_API_EXPORT CloudsModel {};

class D_API_EXPORT VolumeClouds {
 public:
 private:
  REF(CloudsModel) m_cloudsModel;
};

/*!
 *@brief SkyBox for screen space only. It's not the normal
 * skybox, which just render on the screen space. No actual
 * box.
 */
class D_API_EXPORT ScreenSpaceSkyBox : public drawObject {
 public:
  ScreenSpaceSkyBox();
  ~ScreenSpaceSkyBox();
  friend class VolumeClouds;

  colorPreset defaultPreset();
  colorPreset sunsetPreset_1();
  colorPreset sunsetPreset_2();
  void mixPresets(float v, const colorPreset& p1, const colorPreset& p2);

  unsigned int getTextureID();

  void OnResize(float w, float h);

 public:  ///< override. from drawObject.
  void draw() override;
  void update() override;

 private:
  glm::vec3 m_skyColorTop;
  glm::vec3 m_skyColorBottom;
  REF(ScreenSpaceShader) m_spShader;  ///< screen sapce shader.
  REF(FrameBuffer) m_FBO;             ///< Frame buffer.
  colorPreset m_highSunPreset;
  colorPreset m_sunsetPreset;
};
}  // namespace renderer
}  // namespace daydream

#endif  // !H_CORE_OBJECT_SKY
