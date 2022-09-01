#include "scene2d.hpp"

namespace daydream {
namespace scene {

scene2d::scene2d(float w, float h) : m_MainCamera(w, h, "MainCam2D-Scene"), m_FramBuffer(w, h) {}

scene2d::scene2d(const renderer::camera2d& camera)
    : m_MainCamera(camera), m_FramBuffer(camera.m_w, camera.m_h) {}

scene2d::scene2d(const renderer::camera2d& camera, const renderer::FrameBuffer& frame_buffer)
    : m_MainCamera(camera), m_FramBuffer(frame_buffer) {}

void scene2d::Resize(float w, float h) {
  m_MainCamera.set_w(w);
  m_MainCamera.set_h(h);

  m_FramBuffer.Resize(w, h);
}

void scene2d::BeginRender() {
  m_FramBuffer.Bind();
  renderer::GLCommand::setColor(0.f, 0.5f, 0.f, 1.f);
  renderer::GLCommand::clear();
  m_MainShader->Bind();
}

void scene2d::EndRender() {
  renderer::GLCommand::setLineMode(m_LineMode);
  m_FramBuffer.UnBind();
  m_MainShader->UnBind();
}

void scene2d::setLineMode(bool enable) { m_LineMode = enable; }

bool scene2d::isLineMode() { return m_LineMode; }

void scene2d::setCurShader(REF(renderer::Shader) & shader) { m_MainShader = shader; }

void scene2d::setRunning(bool enable) { m_running = enable; }

uint32_t scene2d::FrameIdx() { return m_FramBuffer.FrameIdx(); }

}  // namespace scene
}  // namespace daydream
