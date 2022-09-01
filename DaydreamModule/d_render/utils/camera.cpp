#include "camera.hpp"

#include <glm/gtc/quaternion.hpp>

namespace daydream {
namespace renderer {

camera_obj::camera_obj(float w, float h) : m_w(w), m_h(h), m_aspect((float)w / (float)h) {}

void camera_obj::set_w(float a) {
  m_w = a;
  m_aspect = m_w / m_h;
}

void camera_obj::set_h(float a) {
  m_h = a;
  m_aspect = m_w / m_h;
}

float camera_obj::get_w() { return m_w; }

float camera_obj::get_h() { return m_h; }

float camera_obj::get_aspect() { return m_aspect; }

bool camera_obj::is_activited() { return m_activated; }

void camera_obj::set_activited(bool enable) { m_activated = enable; }

camera2d::camera2d(float w, float h, const std::string& name)
    : camera_obj(w, h), m_name(name), m_idx(0) {}

void camera2d::set_idx(float a) { m_idx = a; }

void camera2d::reset_name(const std::string& name) { m_name = name; }

float camera2d::get_idx() const { return m_idx; }

const std::string& camera2d::get_name() const { return m_name; }

camera3d::camera3d(float w, float h, const std::string& name)
    : camera_obj(w, h), m_name(name), m_idx(0) {}

int camera3d::getIdx() const { return m_idx; }

const std::string& camera3d::getName() const { return m_name; }

void camera3d::UpdateViewMatrix() {
  glm::vec3 front = glm::vec3(1.0f);

  front.x = cos(glm::radians(m_Pitch)) * cos(glm::radians(m_Yaw));
  front.y = sin(glm::radians(m_Pitch));
  front.z = cos(glm::radians(m_Pitch)) * sin(glm::radians(m_Yaw));
  m_Front = glm::normalize(front);

  // right vector
  m_Right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));

  // up vector
  m_Up = glm::normalize(glm::cross(m_Right, m_Front));

  m_ViewMatrix = glm::lookAt(m_Position, m_Front + m_Position, m_Up);
  UpdateViewProjectionMatrix();
}

void camera3d::UpdateProjectionMatrix() {
  m_ProjectionMatrix = glm::perspective(glm::radians(m_Fov), m_aspect, m_ZNear, m_ZFar);
  UpdateViewProjectionMatrix();
}

void camera3dDispatcher::addCamera3d(camera3d& rhs) { m_data[rhs.getIdx()] = rhs; }

camera3d& camera3dDispatcher::getCamera3d(int a) {
  try {
    return m_data[a];
  } catch (char* n) {
    std::cout << n;
    return camera3d(0, 0, "wrong");
  }
}

void camera3dDispatcher::deleteCamera3d(int a) {
  try {
    m_data.erase(a);
  } catch (char* n) {
    std::cout << n;
    return;
  }
}

}  // namespace renderer
}  // namespace daydream
