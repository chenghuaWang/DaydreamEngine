#ifndef H_UI_UTILS
#define H_UI_UTILS

#if _MSC_VER > 1000
#pragma once
#pragma warnind(disable : 4251)
#endif  // _MSC_VER > 1000

#include "_base.hpp"
#include "ImGuiFileDialog.h"

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

}  // namespace ui
}  // namespace daydream

#endif  // !H_UI_UTILS
