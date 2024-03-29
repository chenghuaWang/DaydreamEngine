#ifndef H_SCENE_SCENE2D
#define H_SCENE_SCENE2D

#if _MSC_VER > 1000
#pragma once
#pragma warnind(disable : 4251)
#endif  // _MSC_VER

#include "d_core/pch.hpp"
#include "d_render/core/ds.hpp"
#include "d_render/core/shader.hpp"
#include "d_render/core/command.hpp"
#include "d_render/utils/camera.hpp"

namespace daydream {
namespace scene {

// scene2d is just for shader test. No Component managment or Scene tree supoort
class D_API_EXPORT scene2d {
 public:
  scene2d(float w, float h);
  scene2d(const renderer::camera2d& camera);
  scene2d(const renderer::camera2d& camera, const renderer::FrameBuffer& frame_buffer);

  void Resize(float w, float h);
  void BeginRender();
  void EndRender();

  void setLineMode(bool enable);
  bool isLineMode();

  void setCurShader(REF(renderer::Shader) & shader);
  void setRunning(bool enable);

  uint32_t FrameIdx();

 public:
  bool m_running = true;
  bool m_LineMode = false;
  renderer::camera2d m_MainCamera;
  renderer::FrameBuffer m_FramBuffer;
  REF(renderer::Shader) m_MainShader = nullptr;
};

}  // namespace scene
}  // namespace daydream

#endif  // !H_SCENE_SCENE2D
