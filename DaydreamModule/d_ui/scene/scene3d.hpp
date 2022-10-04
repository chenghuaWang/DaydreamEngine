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
#include "d_render/core/light.hpp"
#include "d_render/core/command.hpp"
#include "d_render/utils/camera.hpp"
#include "d_render/core/SkyBox.hpp"
#include "d_render/core/object/basicObj.hpp"
#include "d_ui/widget/utils.hpp"

#include "ImGuizmo.h"
#include <glm/gtc/type_ptr.hpp>

namespace daydream {
namespace scene {

/*!
 *@brief A scene3d class for user interface to show.
 * You should pass this class to gl_content class in imgui widget.
 *
 * @detials The initialize of this class is quite different from sc-
 * ene2d. You can just init it from [w, h], and Crates. For more, [w,
 * h] actually is useless, you still ne to bind crates. I will not
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
  explicit scene3d(renderer::Crates crates);
  ~scene3d();

  void OnAttach();
  void OnDetach();
  void OnUpdate(float ts);

  void Resize(float w, float h);
  void BeginRender();
  void EndRender();

  void setLineMode(bool enable);
  bool isLineMode();

  void setRunning(bool enable);
  bool isRunning();

  void setReferencePlane(bool enable);
  bool isReferencePlane();
  void setReferencePlaneObj(PlaneObject* po);

  void RegisterObj(drawObject* o);
  void UnRegisterObj(drawObject* o);

  void RegisterLight(_obj_light* ol);
  void UnRegisterLight(_obj_light* ol);

  void setChoosedObj(uint32_t index) { m_ChoosedObj = m__DrawableClass__[index]; }
  std::vector<drawObject*> getAllDrawableObj() { return m__DrawableClass__; }

  renderer::Crates* getCratePtr();
  ::daydream::renderer::KVBase* getDB();

  void setCrate(renderer::Crates c);

  uint32_t FrameIdx();

  void setCamera2Ctrl(camera3d* c);
  camera3dController& getCameraCtrl();

 public:
  std::function<void(glm::vec2)> m_GuizmoFunc = [&](glm::vec2 viewportSize) {
    ImVec2 size = ImGui::GetContentRegionAvail();
    ImVec2 cursorPos = ImGui::GetCursorScreenPos();
    ImGuizmo::SetRect(cursorPos.x, cursorPos.y, size.x, size.y);
    ImGuizmo::Manipulate(
        glm::value_ptr(m_ChoosedObj->renderPayload->mainCamera->getViewMatrix()),
        glm::value_ptr(m_ChoosedObj->renderPayload->mainCamera->getProjectionMatrix()),
        ImGuizmo::OPERATION::ROTATE, ImGuizmo::MODE::WORLD, &m_ChoosedObj->m_Trasnform[0][0]);
    ImGuizmo::DecomposeMatrixToComponents(&m_ChoosedObj->m_Trasnform[0][0], &m_ChoosedObj->m_Pos[0],
                                          &m_ChoosedObj->m_Rotate[0], &m_ChoosedObj->m_Scale[0]);
  };

 public:
  void slots_LoadFiles();

 private:
  drawObject* m_ChoosedObj = nullptr;
  std::string __tmp_str__;
  ::daydream::ui::file_dialog __tmp_dialog__;
  bool m__file_dialog_opened__ = false;

  ::daydream::renderer::KVBase* m__DataBase = new ::daydream::renderer::KVBase();
  ::daydream::renderer::StandardSkyBox* m__sky = new ::daydream::renderer::StandardSkyBox();

  renderer::Crates m_crates;
  camera3dController m_camera_ctrl;
  bool m_running = true;
  bool m_LineMode = false;
  bool m_ReferencePlane = true;

  REF(_obj_material) m__default_material = CREATE_REF(_obj_material)();

  std::vector<drawObject*> m__DrawableClass__;
  std::vector<drawObject*> m__DrawableLines__;
  std::vector<_obj_light*> m__lights__;
  PlaneObject* m__ReferencePlaneObj__ = nullptr;

  std::unordered_map<LightType, uint32_t> m__runtimeLightsPortIndex__;
  std::unordered_map<LightType, uint32_t> m__lightsPortIndex__;
};

bool D_API_EXPORT NewScene3D(int32_t sW, int32_t sH, const std::string& sName, REF(scene3d) & sS,
                             bool sWireFrame = false, bool sReferencePlane = true);

bool D_API_EXPORT FreeScene3D(scene3d* sS);

}  // namespace scene

namespace ui {

class D_API_EXPORT PopItems : public ui_object {
 public:
  void on_attach() override{};
  void on_detach() override{};
  void on_update(float ts) override{};
  void update_event() override{};
  void impl_imgui_render() override {
    for (uint32_t i = 0; i < m__data->getAllDrawableObj().size(); ++i) {
      ImGui::LabelText("New Object", nullptr);
      ImGui::SameLine();
      if (ImGui::Button("Choose")) {
        item_cur = i;
        m__data->setChoosedObj(i);
      }
    }
  };

 public:
  uint32_t item_cur = 0;
  scene::scene3d* m__data;
};

}  // namespace ui
}  // namespace daydream

#endif  // H_SCENE_SCENE3D
