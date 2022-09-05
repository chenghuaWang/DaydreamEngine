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
  // Camera Position update.
  if (ImGui::IsWindowFocused() && ImGui::IsMouseDown(1)) {
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
  // Camera Direction update.
  if (ImGui::IsWindowFocused() && ImGui::IsMouseDragging(ImGuiMouseButton_Right)) {
    // TODO m_MousePos is not updateed yet, or not check.
    float yaw = m_camera3d.getYaw(), pitch = m_camera3d.getPitch();
    yaw += (ImGui::GetMousePos().x - m_MouseLastPosX) * m_Scensity;
    pitch -= ((m_camera3d.get_w() - ImGui::GetMousePos().y) - m_MouseLastPosY) * m_Scensity;
    if (pitch > 89.0f) {
      pitch = 89.0f;
    } else if (pitch < -89.0f) {
      pitch = -89.0f;
    }
    m_camera3d.SetPitch(pitch);
    m_camera3d.SetYaw(yaw);
    // Update the last Mouse Position in this scope. For next scope-update to use.
    // The last position should in the right-click is dragged.
    m_MouseLastPosX = ImGui::GetMousePos().x;
    m_MouseLastPosY = m_camera3d.get_w() - ImGui::GetMousePos().y;
  } else if (ImGui::IsWindowFocused() && ImGui::IsMouseDragging(ImGuiMouseButton_Middle)) {
  }
  // Set the Position.
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
