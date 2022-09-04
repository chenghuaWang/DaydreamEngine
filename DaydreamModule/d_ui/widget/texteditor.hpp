#ifndef H_UI_TEXTEDITOR
#define H_UI_TEXTEDITOR

#if _MSC_VER > 1000
#pragma once
#pragma warnind(disable : 4251)
#endif  // _MSC_VER > 1000

#include "_base.hpp"
#include "utils.hpp"
#include "TextEditor.h"

namespace daydream {
namespace ui {

enum class D_API_EXPORT lang {
  PureTxt = 0,
  GLSL = 1,
  Python = 2,
  Lua = 3,
  DSL = 4  // Domain special lang. Need LLVM backend.
};

enum class D_API_EXPORT texteditor_color { Dark = 0, Light = 1, Blue = 2 };

struct D_API_EXPORT text_src_payload {
  size_t idx;
  std::string file_path;
  std::string file_src;
};

enum class D_API_EXPORT text_editor_cur_dialog_state { Open = 0, Save = 1, SaveAs = 2, None = 3 };

class D_API_EXPORT texteditor : public ui_object {
 public:
  texteditor();

  void on_attach() override;
  void on_detach() override;
  void on_update(float ts) override;
  void update_event() override;
  void impl_imgui_render() override;

  void signal_open_file();
  void signal_set_lang_lua();
  void signal_set_lang_glsl();
  void signal_compile_test();
  void signal_link_prog();

  void open_file(const std::string& file_path);
  void save_cur_file();
  void backup_cur_file(const std::string& file_path);
  void save_as_cur_file(const std::string& file_path);
  void close_cur_file();
  void set_lang(lang type);
  void set_color(texteditor_color color);

  void set_color_black();
  void set_color_white();
  void set_color_blue();

 private:
  file_dialog m_file_dialog;
  std::string m_file_dialog_value;
  text_editor_cur_dialog_state m_file_dialog_state = text_editor_cur_dialog_state::None;

  TextEditor::LanguageDefinition m_lang_lua = TextEditor::LanguageDefinition::Lua();
  TextEditor::LanguageDefinition m_lang_glsl = TextEditor::LanguageDefinition::GLSL();
  TextEditor::ErrorMarkers m_err_markers;
  TextEditor m_editor;
  size_t m_cur_text_src_idx = 0;
  std::unordered_map<size_t, text_src_payload> m_file_buffers;
};

}  // namespace ui
}  // namespace daydream

#endif  // !H_UI_TEXTEDITOR
