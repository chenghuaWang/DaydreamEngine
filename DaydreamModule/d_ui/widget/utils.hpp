#ifndef H_UI_UTILS
#define H_UI_UTILS

#if _MSC_VER > 1000
#pragma once
#pragma warnind(disable : 4251)
#endif  // _MSC_VER > 1000

#include "_base.hpp"
#include "ImGuiFileDialog.h"

using namespace kaleidoscope;

namespace daydream {
namespace ui {

class D_API_EXPORT line_continer : public ui_object {
 public:
  inline void __same_line__();
  void add_obj(ui_object* o);

  void on_attach() override;
  void on_detach() override;
  void on_update(float ts) override;
  void update_event() override;
  void impl_imgui_render() override;

 private:
  size_t tmp_size = 0;
  std::vector<ui_object*> m_contained_objs;
};

class D_API_EXPORT file_dialog {
 public:
  void show(const std::string& a, const std::string& b, const std::string& c, const std::string& d);
  bool wait(std::string& file_path);
};

class D_API_EXPORT SlideBar : public ui_object {
 public:
  SlideBar(const std::string& name) : m_Name(name) {}

  void on_attach() override{};
  void on_detach() override{};
  void on_update(float ts) override{};
  void update_event() override{};
  void impl_imgui_render() override;

  std::string m_Name;
  float m_MinValue = 0.1f;
  float m_MaxValue = 100.f;
  float m_CurValue = 0.1;
  Signal1<float> Changed;
};

}  // namespace ui
}  // namespace daydream

#endif  // !H_UI_UTILS
