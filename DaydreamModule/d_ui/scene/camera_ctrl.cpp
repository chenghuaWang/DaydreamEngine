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
  if (ImGui::IsMouseDown(1)) {
    ImGui::SetMouseCursor(ImGuiMouseCursor_None);
    if (ImGui::IsKeyPressed(ImGuiKey_A)) {
      position -= ts * m_MovingSpeed * m_camera3d.getRightVector();
    }
    if (ImGui::IsKeyPressed(ImGuiKey_D)) {
      position += ts * m_MovingSpeed * m_camera3d.getRightVector();
    }
    if (ImGui::IsKeyPressed(ImGuiKey_W)) {
      position += ts * m_MovingSpeed * m_camera3d.getFrontVector();
    }
    if (ImGui::IsKeyPressed(ImGuiKey_S)) {
      position -= ts * m_MovingSpeed * m_camera3d.getFrontVector();
    }
    if (ImGui::IsKeyPressed(ImGuiKey_Q)) {
      position += ts * m_MovingSpeed * m_camera3d.getUpVector();
    }
    if (ImGui::IsKeyPressed(ImGuiKey_E)) {
      position -= ts * m_MovingSpeed * m_camera3d.getUpVector();
    }
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
