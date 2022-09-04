#include "camera_ctrl.hpp"

#include "d_ui/window/window.hpp"
#include "d_core/include/input_sys.hpp"

#include "glm/glm.hpp"

namespace daydream {
namespace scene {
void camera3dController::OnEvent() {}

void camera3dController::OnUpdate(float ts) {
  // TODO Bug occaurs here.
  // Maybe the windowInstance handle is not good for use.
  // the ImGui it self can already process it. Try to remove
  // the glfw's overload and use imgui only.
  auto window_handle = ui::getWindowInstance();
  glm::vec3 position = m_camera3d.getPosition();
  if (isCameraActivated() || isMouseRightPress()) {
    /*InputSys::SetCursorHidden(window_handle, true);
    if (InputSys::isKeyPressed(window_handle, KeyCode::A)) {
      position -= ts * m_MovingSpeed * m_camera3d.getRightVector();
    }
    if (InputSys::isKeyPressed(window_handle, KeyCode::D)) {
      position += ts * m_MovingSpeed * m_camera3d.getRightVector();
    }
    if (InputSys::isKeyPressed(window_handle, KeyCode::W)) {
      position += ts * m_MovingSpeed * m_camera3d.getFrontVector();
    }
    if (InputSys::isKeyPressed(window_handle, KeyCode::S)) {
      position -= ts * m_MovingSpeed * m_camera3d.getFrontVector();
    }
    if (InputSys::isKeyPressed(window_handle, KeyCode::Q)) {
      position += ts * m_MovingSpeed * m_camera3d.getUpVector();
    }
    if (InputSys::isKeyPressed(window_handle, KeyCode::E)) {
      position -= ts * m_MovingSpeed * m_camera3d.getUpVector();
    }*/
  } else {
    /*InputSys::SetCursorHidden(window_handle, false);*/
  }
  m_camera3d.SetPosition(position);
}

bool camera3dController::isCameraActivated() {
  auto window_handle = ui::getWindowInstance();
  return InputSys::IsMouseButtonPressed(window_handle, MouseCode::ButtonRight) && m_Enable;
}

bool camera3dController::isMouseMiddlePress() {
  auto window_handle = ui::getWindowInstance();
  return InputSys::IsMouseButtonPressed(window_handle, MouseCode::ButtonMiddle) && m_Enable;
}

bool camera3dController::isMouseRightPress() {
  auto window_handle = ui::getWindowInstance();
  return InputSys::IsMouseButtonPressed(window_handle, MouseCode::ButtonRight) && m_Enable;
}
}  // namespace scene
}  // namespace daydream
