#include "scene3d.hpp"

namespace daydream {
namespace scene {
scene3d::scene3d(float w, float h) : m_camera_ctrl(camera3d(w, h, "dropped")) {
  std::cout << "[ Warn ]This class init method [float w, float h] is not support anymore.\n \
You should define Crates(in render lib) first, and pass it to this class \n \
Using scene3d::scene3drenderer::Crates& crates) function !"
            << std::endl;
  LOG_WARN("[ Warn ]This class init method [float w, float h] is not support anymore.\n \
You should define Crates(in render lib) first, and pass it to this class \n \
Using scene3d::scene3drenderer::Crates& crates) function !");
}

scene3d::scene3d(renderer::Crates& crates) : m_crates(crates), m_camera_ctrl(*crates.mainCamera) {
  std::cout << "[ INFO ] crates registered. " << std::endl;
  LOG_INFO("[ INFO ] crates registered. ");
}

void scene3d::Resize(float w, float h) {
  m_camera_ctrl.OnResize(w, h);
  m_crates.sceneFBO->Resize(w, h);
}

void scene3d::BeginRender() {
  m_crates.sceneFBO->Bind();
  renderer::GLCommand::setColor(0.f, 0.5f, 0.f, 1.f);
  renderer::GLCommand::clear();
  // TODO A drawable objs' table should be passed here.
  for (auto item : m__DrawableClass__) { item->draw(); }
}

void scene3d::EndRender() {
  renderer::GLCommand::setLineMode(m_LineMode);
  m_crates.sceneFBO->UnBind();
}

void scene3d::setLineMode(bool enable) { m_LineMode = enable; }

bool scene3d::isLineMode() { return m_LineMode; }

void scene3d::setRunning(bool enable) { m_running = enable; }

bool scene3d::isRunning() { return m_running; }

void scene3d::setReferencePlane(bool enable) { m_ReferencePlane = enable; }

bool scene3d::isReferencePlane() { return m_ReferencePlane; }

void scene3d::RegisterObj(drawObject* o) {
  m__DrawableClass__.push_back(o);
  o->renderPayload = &m_crates;
}

void scene3d::UnRegisterObj(drawObject* o) {
  for (std::vector<drawObject*>::iterator i = m__DrawableClass__.begin();
       i != m__DrawableClass__.end(); i++) {
    if (*i == o) {
      m__DrawableClass__.erase(i);
      return;
    }
  }
}

uint32_t scene3d::FrameIdx() { return m_crates.sceneFBO->FrameIdx(); }

camera3dController& scene3d::getCameraCtrl() { return m_camera_ctrl; }

bool NewScene3D(int32_t sW, int32_t sH, const std::string& sName, scene3d* sS, bool sWireFrame,
                bool sReferencePlane) {
  // init the camera
  daydream::renderer::camera3d* __camera3d__ = new daydream::renderer::camera3d(sW, sH, sName);
  // init the framebuffer
  daydream::renderer::FrameBuffer* __framebuffer__ = new daydream::renderer::FrameBuffer(sW, sH);
  // init the crates.
  daydream::renderer::Crates __crates__;
  __crates__.mainCamera = __camera3d__;
  __crates__.sceneFBO = __framebuffer__;
  __crates__.wireframe = sWireFrame;
  // init the basic objs. Such as ReferencePlane, Sky, etc.
  // pass the scene;
  sS = new scene3d(__crates__);
  if (sS != nullptr || __camera3d__ != nullptr || __framebuffer__ != nullptr) { return false; }
  sS->setLineMode(sWireFrame);
  sS->setReferencePlane(sReferencePlane);
  return true;
}
}  // namespace scene
}  // namespace daydream