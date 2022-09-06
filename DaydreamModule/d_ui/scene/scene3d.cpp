#include "scene3d.hpp"

namespace daydream {
namespace scene {
scene3d::scene3d(float w, float h) : m_camera_ctrl(new camera3d(w, h, "dropped")) {
  std::cout << "[ Warn ]This class init method [float w, float h] is not support anymore.\n \
You should define Crates(in render lib) first, and pass it to this class \n \
Using scene3d::scene3drenderer::Crates& crates) function !"
            << std::endl;
  LOG_WARN("[ Warn ]This class init method [float w, float h] is not support anymore.\n \
You should define Crates(in render lib) first, and pass it to this class \n \
Using scene3d::scene3drenderer::Crates& crates) function !");
  m__runtimeLightsPortIndex__[LightType::Basic] = 0;
  m__runtimeLightsPortIndex__[LightType::Direct] = 0;
  m__runtimeLightsPortIndex__[LightType::None] = 0;
  m__runtimeLightsPortIndex__[LightType::Point] = 0;
  m__runtimeLightsPortIndex__[LightType::Self_defined] = 0;
  m__runtimeLightsPortIndex__[LightType::Spot] = 0;
}

scene3d::scene3d(renderer::Crates crates) : m_crates(crates), m_camera_ctrl(crates.mainCamera) {
  std::cout << "[ INFO ] crates registered. " << std::endl;
  LOG_INFO("[ INFO ] crates registered. ");
  m__runtimeLightsPortIndex__[LightType::Basic] = 0;
  m__runtimeLightsPortIndex__[LightType::Direct] = 0;
  m__runtimeLightsPortIndex__[LightType::None] = 0;
  m__runtimeLightsPortIndex__[LightType::Point] = 0;
  m__runtimeLightsPortIndex__[LightType::Self_defined] = 0;
  m__runtimeLightsPortIndex__[LightType::Spot] = 0;
}

scene3d::~scene3d() {
  delete m_crates.mainCamera;
  delete m_crates.sceneFBO;
  delete m__ReferencePlaneObj__;
  for (auto item : m__DrawableClass__) { delete item; }
  for (auto item : m__lights__) { delete item; }
}

void scene3d::OnAttach() {}

void scene3d::OnDetach() {}

void scene3d::OnUpdate(float ts) { m_camera_ctrl.OnUpdate(ts); }

void scene3d::Resize(float w, float h) {
  m_camera_ctrl.OnResize(w, h);
  m_crates.sceneFBO->Resize(w, h);
}

void scene3d::BeginRender() {
  m_crates.sceneFBO->Bind();
  renderer::GLCommand::setColor(0.59765625, 0.59765625, 1.f, 1.f);
  renderer::GLCommand::clear();
  // pass light to all objs. include normal object(usr defined) and basic object(reference plane,
  // etc)
  for (auto light_it : m__lights__) {
    for (auto obj_item : m__DrawableClass__) {
      light_it->Bind(obj_item->m_defualt_material->GetShader(), obj_item->m_Pos,
                     m__runtimeLightsPortIndex__[light_it->Type()]++);
    }
  }
  // draw all element.
  if (m_ReferencePlane) { m__ReferencePlaneObj__->draw(); }
  for (auto item : m__DrawableClass__) { item->draw(); }
}

void scene3d::EndRender() {
  renderer::GLCommand::setLineMode(m_LineMode);
  m_crates.sceneFBO->UnBind();
  m__runtimeLightsPortIndex__[LightType::Basic] = 0;
  m__runtimeLightsPortIndex__[LightType::Direct] = 0;
  m__runtimeLightsPortIndex__[LightType::None] = 0;
  m__runtimeLightsPortIndex__[LightType::Point] = 0;
  m__runtimeLightsPortIndex__[LightType::Self_defined] = 0;
  m__runtimeLightsPortIndex__[LightType::Spot] = 0;
}

void scene3d::setLineMode(bool enable) { m_LineMode = enable; }

bool scene3d::isLineMode() { return m_LineMode; }

void scene3d::setRunning(bool enable) { m_running = enable; }

bool scene3d::isRunning() { return m_running; }

void scene3d::setReferencePlane(bool enable) { m_ReferencePlane = enable; }

bool scene3d::isReferencePlane() { return m_ReferencePlane; }

void scene3d::setReferencePlaneObj(PlaneObject* po) { m__ReferencePlaneObj__ = po; }

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

void scene3d::RegisterLight(_obj_light* ol) {
  m__lights__.push_back(ol);
  m__lightsPortIndex__[ol->Type()]++;
}

void scene3d::UnRegisterLight(_obj_light* ol) {
  for (std::vector<_obj_light*>::iterator i = m__lights__.begin(); i != m__lights__.end(); i++) {
    if (*i == ol) {
      m__lights__.erase(i);
      return;
    }
  }
  m__lightsPortIndex__[ol->Type()]--;
}

renderer::Crates* scene3d::getCratePtr() { return &m_crates; }

void scene3d::setCrate(renderer::Crates c) { m_crates = c; }

uint32_t scene3d::FrameIdx() { return m_crates.sceneFBO->FrameIdx(); }

void scene3d::setCamera2Ctrl(camera3d* c) { m_camera_ctrl = camera3dController(c); }

camera3dController& scene3d::getCameraCtrl() { return m_camera_ctrl; }

bool NewScene3D(int32_t sW, int32_t sH, const std::string& sName, REF(scene3d) & sS,
                bool sWireFrame, bool sReferencePlane) {
  // init the camera
  daydream::renderer::camera3d* __camera3d__ = new daydream::renderer::camera3d(sW, sH, sName);
  // init the framebuffer
  daydream::renderer::FrameBuffer* __framebuffer__ = new daydream::renderer::FrameBuffer(sW, sH);
  // init the crates.
  daydream::renderer::Crates __crates__;
  __crates__.mainCamera = __camera3d__;
  __crates__.sceneFBO = __framebuffer__;
  __crates__.wireframe = sWireFrame;
  sS->setCrate(__crates__);
  sS->setCamera2Ctrl(__crates__.mainCamera);
  // init the basic objs. Such as ReferencePlane, Sky, etc.
  auto __tmp_palne__ = new PlaneObject();
  __tmp_palne__->renderPayload = sS->getCratePtr();
  if (sReferencePlane) { sS->setReferencePlaneObj(__tmp_palne__); }
  // pass the scene;
  if (sS == nullptr || __camera3d__ == nullptr || __framebuffer__ == nullptr) { return false; }
  sS->setLineMode(sWireFrame);
  sS->setReferencePlane(sReferencePlane);
  return true;
}
bool D_API_EXPORT FreeScene3D(scene3d* sS) {
  if (sS != nullptr) {
    delete sS;
    return true;
  } else {
    return false;
  }
}
}  // namespace scene
}  // namespace daydream