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
  float m_global_fps = 0;
  uis* m_App_ui;
  ui::sub_menu m_window_view;
  ui::action m_action_show_log = ui::action_type::MainTain;
  ui::menu m_window_menu;
  ui::layer_stack m_layers;
};

#endif  // !H_APP
