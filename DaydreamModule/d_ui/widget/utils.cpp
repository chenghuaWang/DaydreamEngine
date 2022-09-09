#include "utils.hpp"

namespace daydream {
namespace ui {

void line_continer::__same_line__() { ImGui::SameLine(); }

void line_continer::add_obj(ui_object* o) {
  //!!! Don't excute attach in this scope.
  //! The attach function will be used by line_container's on_attach func.
  m_contained_objs.emplace_back(o);
}

void line_continer::on_attach() {
  for (auto item : m_contained_objs) { item->on_attach(); }
  tmp_size = m_contained_objs.size();
}

void line_continer::on_detach() {
  for (auto item : m_contained_objs) { item->on_detach(); }
}

void line_continer::on_update(float ts) {
  for (auto item : m_contained_objs) { item->on_update(ts); }
}

void line_continer::update_event() {
  for (auto item : m_contained_objs) { item->update_event(); }
}

void line_continer::impl_imgui_render() {
  for (size_t i = 0; i < tmp_size - 1; ++i) {
    m_contained_objs[i]->impl_imgui_render();
    __same_line__();
  }
  m_contained_objs[tmp_size - 1]->impl_imgui_render();
}

void file_dialog::show(const std::string& a, const std::string& b, const std::string& c,
                       const std::string& d) {
  ImGuiFileDialog::Instance()->OpenDialog(a, b, c.c_str(), d);
}

bool file_dialog::wait(std::string& file_path) {
  bool a = false;
  if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) {
    // action if OK
    if (ImGuiFileDialog::Instance()->IsOk()) {
      file_path = ImGuiFileDialog::Instance()->GetFilePathName();
      a = true;
      // action
    }

    // close
    ImGuiFileDialog::Instance()->Close();
    return a;
  }
}

void SlideBar::impl_imgui_render() {
  if (ImGui::SliderFloat(m_Name.c_str(), &m_CurValue, m_MinValue, m_MaxValue)) {
    Changed.Emit(m_CurValue);
  }
}

}  // namespace ui
}  // namespace daydream
