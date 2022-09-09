#include "app.hpp"

App::App() : imgui_window(), m_window_view("window-view"), m_App_ui(nullptr) {}

App::~App() { delete m_App_ui; }

void App::flush_frame() {
  for (auto item : m_layers) {
    item->impl_imgui_render(m_App_ui->gl_graphic->m_timer.getTimeDelta());
  }
}

void App::update_event() {
  for (auto item : m_layers) { item->update(); }
  m_global_fps = 1 / m_App_ui->gl_graphic->m_timer.getTimeDelta();
  signal_fps_chaned.Emit(std::to_string(m_global_fps));

  // Fresh the Camera info
#if TEST3D == true
  {
    auto __tmp__ = m_App_ui->gl_scene->getCameraCtrl().getCamera();
    m_App_ui->camera_info_Aspect_label->set_value(std::to_string(__tmp__->getAspect()));
    m_App_ui->camera_info_Fov_label->set_value(std::to_string(__tmp__->getFov()));
    m_App_ui->camera_info_w_label->set_value(std::to_string(__tmp__->get_w()));
    m_App_ui->camera_info_h_label->set_value(std::to_string(__tmp__->get_h()));
    m_App_ui->camera_info_pitch_label->set_value(std::to_string(__tmp__->getPitch()));
    m_App_ui->camera_info_yaw_label->set_value(std::to_string(__tmp__->getYaw()));
    {
      auto pos = __tmp__->getPosition();
      m_App_ui->camera_info_pos_x->set_value(std::to_string(pos.x));
      m_App_ui->camera_info_pos_y->set_value(std::to_string(pos.y));
      m_App_ui->camera_info_pos_z->set_value(std::to_string(pos.z));
    }
  }
#endif
}

void App::delay_init() {
  // Init the widget
  m_App_ui = new uis();

  // Init the sub_menu's action attribute
  m_action_show_log.m_name = "Show log.";
  m_action_show_log.m_accelerate_key = "ctrl+l";
  m_action_open_model_files.m_name = "Open Modle";
  m_action_open_model_files.m_accelerate_key = "ctrl+o";

  auto menu_ui_layer = new ui::menu_layer();
  auto console_ui_layer = new ui::obj_layer("console");
  auto gl_ui_layer = new ui::obj_layer("Viewport");
  auto gl_ctrl_pannel_ui_layer = new ui::obj_layer("ctrl pannel");
  auto code_editor_ui_layer = new ui::obj_layer("Code Editor");
#if TEST3D == true
  auto camera_info_layer = new ui::obj_layer("Camera Atribute");
#endif

#if TEST2D == true
  m_App_ui->gl_scene->setCurShader(m_App_ui->gl_scene_shader);
  m_App_ui->gl_graphic->set_scene2d(m_App_ui->gl_scene);
#elif TEST3D == true:
  m_App_ui->gl_graphic->set_scene3d(m_App_ui->gl_scene);
#endif

  console_ui_layer->add_obj(m_App_ui->console_1);
  gl_ui_layer->add_obj(m_App_ui->gl_graphic);
  gl_ctrl_pannel_ui_layer->add_obj(m_App_ui->pannel_line_container);

  code_editor_ui_layer->set_flags(ImGuiWindowFlags_MenuBar);
  code_editor_ui_layer->add_obj(m_App_ui->text_editor_line_container);
  code_editor_ui_layer->add_obj(m_App_ui->text_editor_widget);
  code_editor_ui_layer->register_menu(m_App_ui->text_editor_menu);

#if TEST3D == true
  camera_info_layer->add_obj(m_App_ui->camera_info_h_label);
  camera_info_layer->add_obj(m_App_ui->camera_info_w_label);
  camera_info_layer->add_obj(m_App_ui->camera_info_Fov_label);
  camera_info_layer->add_obj(m_App_ui->camera_info_Aspect_label);
  camera_info_layer->add_obj(m_App_ui->camera_info_pitch_label);
  camera_info_layer->add_obj(m_App_ui->camera_info_yaw_label);
  camera_info_layer->add_obj(m_App_ui->camera_info_pos_x);
  camera_info_layer->add_obj(m_App_ui->camera_info_pos_y);
  camera_info_layer->add_obj(m_App_ui->camera_info_pos_z);
  camera_info_layer->add_obj(m_App_ui->camera_info_reset_button);
#endif

  m_layers.add_layer(menu_ui_layer);
  m_layers.add_layer(console_ui_layer);
  m_layers.add_layer(gl_ui_layer);
  m_layers.add_layer(gl_ctrl_pannel_ui_layer);
  m_layers.add_layer(code_editor_ui_layer);
#if TEST3D == true
  m_layers.add_layer(camera_info_layer);
#endif
  // signal and slots linking
  // !!! [TODO] bug. The action is not pass by ptr. So connect must before add_action.
  m_action_show_log.clicked.Connect(console_ui_layer, &ui::obj_layer::set_wopened);
  m_action_open_model_files.pressed.Connect(m_App_ui->gl_scene.get(),
                                            &scene::scene3d::slots_LoadFiles);

  // init the main-menu
  m_window_view.add_action(m_action_show_log);
  m_window_file.add_action(m_action_open_model_files);
  m_window_menu.add_sub_menu(m_window_view);
  m_window_menu.add_sub_menu(m_window_file);
  menu_ui_layer->register_menu(CREATE_REF(ui::menu)(m_window_menu));

  // Link all ptr based slots and slots
  this->signal_fps_chaned.Connect(m_App_ui->pannel_fps_label, &ui::label::set_value);
}
