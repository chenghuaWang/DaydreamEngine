#ifndef H_SCENE_SCENE3D
#define H_SCENE_SCENE3D

#if _MSC_VER > 1000
#pragma once
#pragma warnind(disable : 4251)
#endif  // _MSC_VER

#include "camera_ctrl.hpp"
#include "d_core/pch.hpp"
#include "d_render/utils/crates.hpp"
#include "d_render/core/shader.hpp"
#include "d_render/core/command.hpp"
#include "d_render/utils/camera.hpp"
#include "d_render/core/object/drawObj.hpp"

namespace daydream {
namespace scene {

// TODO Should implement draobjs function, get data from resource_lib.

/*!
 *@brief A scene3d class for user interface to show.
 * You should pass this class to gl_content class in imgui widget.
 *
 * @detials The initialize of this class is quite different from sc-
 * ene2d. You can just init it from [w, h], and Crates. For more, [w,
 * h] actually is useless, you still ne to bind crates. We will not
 * create a Crates for you accroding to the [w, h]. Also, that is why
 * crates should contains all pointers while not actual instances.
 *
 * @Note You should note that, in scene2d there is just one shader( screen-
 * space shader), but in this scene3d class, multiple shaders will be used.
 * So, we just provide a vectors that contains all drawAble object, all
 * shaders should be contains in each drawable object as a pointer and ma-
 * naged in resource_lib. Further, each drawable object should not make
 * shader public to users or father classes. The father class drawObj are
 * not responsible to handle shader, the child inherented this class should
 * do this.
 */
class D_API_EXPORT scene3d {
 public:
  scene3d(float w, float h);
  scene3d(renderer::Crates& crates);

  void Resize(float w, float h);
  void BeginRender();
  void EndRender();

  void setLineMode(bool enable);
  bool isLineMode();

  void setRunning(bool enable);

  uint32_t FrameIdx();

  camera3dController& getCameraCtrl();

 private:
  renderer::Crates m_crates;
  camera3dController m_camera_ctrl;
  bool m_running = true;
  bool m_LineMode = false;
};

}  // namespace scene
}  // namespace daydream

#endif  // H_SCENE_SCENE3D
