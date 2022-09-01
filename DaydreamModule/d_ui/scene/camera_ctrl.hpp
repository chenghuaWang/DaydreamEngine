#ifndef H_SCENE_CAMERA_CTRL
#define H_SCENE_CAMERA_CTRL

#if _MSC_VER > 1000
#pragma once
#pragma warnind(disable : 4251)
#endif  // _MSC_VER

#include "d_render/utils/camera.hpp"

using namespace daydream::renderer;

namespace daydream {
namespace scene {

/*!
 *@brief The camera controller. It actually don't contain camera's infomation.
 * The camera need to be defined by users, and pass it to this clas by refer-
 * ence.
 *
 * @details When actually using this class, camera3dController can be just exits
 * once. May be you will create various cameras for some purpose, if you want to
 * control just one of them, you should pass this camera to this class.
 */
class D_API_EXPORT camera3dController {
 public:
  camera3dController(camera3d& camera) : m_camera3d(camera) {}

  camera3d& getCamera() { return m_camera3d; }
  float getMovingSpeed() { return m_MovingSpeed; }
  float getMousePosX() { return m_MouseLastPosX; }
  float getMousePosY() { return m_MouseLastPosY; }
  float getScensity() { return m_Scensity; }
  bool getEnable() { return m_Enable; }
  void setCamera(camera3d& camera) { m_camera3d = camera; }

 public:  ///< For Event pass and process.
  void OnEvent();
  void OnUpdate(float ts);
  void OnResize(float w, float h) { m_camera3d.SetAspect(w / h); }

 public:  // For Slots in event.
  void slots_setMovingSpeed(float speed) { m_MovingSpeed = speed; }
  void slots_setMousePos(float x, float y) { m_MouseLastPosX = x, m_MouseLastPosY = y; }
  void slots_setMousePosX(float x) { m_MouseLastPosX = x; }
  void slots_setMousePosY(float y) { m_MouseLastPosY = y; }
  void slots_setScensity(float s) { m_Scensity = s; }
  void slots_setEnable(bool e) { m_Enable = e; }

 protected:  // For activate Camera movable.
  bool isCameraActivated();
  bool isMouseMiddlePress();

 private:
  bool m_Enable = true;
  camera3d& m_camera3d;
  float m_MovingSpeed = 10.f;
  float m_MouseLastPosX = 0.f;
  float m_MouseLastPosY = 0.f;
  float m_Scensity = 0.1f;
};
}  // namespace scene
}  // namespace daydream

#endif  // !H_SCENE_CAMERA_CTRL
