#ifndef H_APP
#define H_APP

#ifdef _MSC_VER> 1000
#pragma once
#endif  // _MSC_VER > 1000

#include "d_ui/window/window.hpp"
#include "d_ui/layers/layer.hpp"
#include "d_ui/layers/layer_stack.hpp"

#include "app_ui.hpp"

using namespace daydream;

class App : public ui::imgui_window {
 public:
  App();
  ~App();

  void flush_frame() override;
  void update_event() override;
  void delay_init();

 public:
  Signal1<const std::string&> signal_fps_chaned;

 private:
  // Record the global FPS.
  float m_global_fps = 0;
  // Defined all widget that need to be used.
  uis* m_App_ui;
  // Sub menu. Need to be registered to Main Menu.
  ui::sub_menu m_window_view;
  ui::sub_menu m_window_file = ui::sub_menu("Files");
  // The action in each sub menu.
  ui::action m_action_show_log = ui::action_type::MainTain;
  ui::action m_action_open_model_files = ui::action_type::Normal;
  // The window main menu.
  ui::menu m_window_menu;
  // Manage all layers in the application.
  ui::layer_stack m_layers;
};

#endif  // !H_APP
