#ifndef H_REDNERER_CORE_PIPELINE_HPP_
#define H_REDNERER_CORE_PIPELINE_HPP_

#if _MSC_VER > 1000
#pragma once
#endif

#include "d_core/pch.hpp"
#include "d_render/core/shader.hpp"
#include "d_render/core/light.hpp"
#include "d_render/core/SkyBox.hpp"
#include "d_render/core/object/drawObj.hpp"
#include "d_render/utils/crates.hpp"

namespace daydream {
namespace renderer {
class D_API_EXPORT ForwardPipline {
 public:
  ForwardPipline();
  void draw(const std::vector<_obj_light*>& Lights, const std::vector<drawObject*>& Objects,
            const REF(ProcedualSkySphare) & Sky, const Crates* RenderPayload,
            PlaneObject* ReferencePlane = nullptr);

 private:
  REF(Shader) m_main_shader = nullptr;
  std::unordered_map<LightType, uint32_t> m__runtimeLightsNum__;
  std::unordered_map<_obj_light*, uint32_t> m__runtimeLightsPortIndex__;
};
}  // namespace renderer
}  // namespace daydream

#endif  // !H_REDNERER_CORE_PIPELINE_HPP_
