#include "pipeline.hpp"
namespace daydream {
namespace renderer {
ForwardPipline::ForwardPipline()
    : m_main_shader(CREATE_REF(Shader)("../Asset/shader/StandardObj.glsl")) {}

void ForwardPipline::draw(const std::vector<_obj_light*>& Lights,
                          const std::vector<drawObject*>& Objects,
                          const REF(ProcedualSkySphare) & Sky, const Crates* RenderPayload,
                          PlaneObject* ReferencePlane) {
  // 1. Calculate the lights.
  for (auto __light__ : Lights) {
    m__runtimeLightsPortIndex__[__light__] = m__runtimeLightsNum__[__light__->Type()]++;
  }
  // 2. Bind Sky's Lights and Draw Sky Sphare first.
  Sky->draw();
  m__runtimeLightsPortIndex__[Sky->getLight().get()] =
      m__runtimeLightsNum__[Sky->getLight()->Type()]++;

  // 3. Draw the reference Plane. Without lights.
  if (ReferencePlane) { ReferencePlane->draw(); }

  // 4. Bind All Lights.
  for (auto __light__ : Lights) {
    __light__->Bind(m_main_shader, __light__->m_pos, m__runtimeLightsPortIndex__[__light__]);
  }
  m_main_shader->setInt("d_BasicNum", m__runtimeLightsNum__[LightType::Basic]);
  m_main_shader->setInt("d_DirLightNum", m__runtimeLightsNum__[LightType::Direct]);
  m_main_shader->setInt("d_PointLightNum", m__runtimeLightsNum__[LightType::Point]);
  m_main_shader->setInt("d_SpotLightNum", m__runtimeLightsNum__[LightType::Spot]);

  // 5. Draw all Objects
  m_main_shader->Bind();
  for (auto __obj__ : Objects) {
    // Pass the Shader to Material class.
    // Call the draw function in __obj__;
  }
  m_main_shader->UnBind();

  // [ Final ] Reset all Lights nums;
  for (auto __lights__ : m__runtimeLightsNum__) { __lights__.second = 0; }
  m__runtimeLightsPortIndex__.clear();
}
}  // namespace renderer
}  // namespace daydream
