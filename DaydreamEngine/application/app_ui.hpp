#include "d_ui/widget/console.hpp"
#include "d_ui/widget/button.hpp"
#include "d_ui/widget/gl_content.hpp"
#include "d_ui/widget/utils.hpp"
#include "d_ui/widget/texteditor.hpp"

#define TEST2D false
#define TEST3D true

#define IMGS_PRE_LINE 6

using namespace daydream;

struct uis {
  uis() {
    // For console
    console_1 = new ui::console();

    // For gl content
    gl_graphic = new ui::gl_content();
#if TEST2D == true
    gl_scene = CREATE_REF(scene::scene2d)(100.f, 100.f);
    gl_scene_shader = renderer::Shader::create("../Asset/shader/twoD/circle.glsl");
#elif TEST3D == true
    gl_scene = CREATE_REF(scene::scene3d)(100.f, 100.f);
    if (!scene::NewScene3D(100, 100, "Scene3D", gl_scene, false)) {
      std::cout << "[ Err ] Failed to create scene\n";
      std::exit(1);
    }
#endif
    // For gl_content pannel
    pannel_line_container = new ui::line_continer();
    pannel_fps_label = new ui::label("FPS: ");
    pannel_stop_scene_button = new ui::button("Stop");
    pannel_start_scene_button = new ui::button("Start");
    pannel_line_container->add_obj(pannel_stop_scene_button);
    pannel_line_container->add_obj(pannel_start_scene_button);
    pannel_line_container->add_obj(pannel_fps_label);

    // Link all signal and slots. If both side is defined here.
    pannel_stop_scene_button->click.Connect(gl_graphic, &ui::gl_content::stop_render);
    pannel_start_scene_button->click.Connect(gl_graphic, &ui::gl_content::start_render);

    // Code Editor
    text_editor_widget = new ui::texteditor();
    text_editor_menu = CREATE_REF(ui::menu)();
    text_editor_theme_black_action.m_name = "Black";
    text_editor_theme_white_action.m_name = "White";
    text_editor_theme_blue_action.m_name = "Blue";
    text_editor_theme_black_action.pressed.Connect(text_editor_widget,
                                                   &ui::texteditor::set_color_black);
    text_editor_theme_white_action.pressed.Connect(text_editor_widget,
                                                   &ui::texteditor::set_color_white);
    text_editor_theme_blue_action.pressed.Connect(text_editor_widget,
                                                  &ui::texteditor::set_color_blue);
    text_editor_theme_submenu.add_action(text_editor_theme_black_action);
    text_editor_theme_submenu.add_action(text_editor_theme_white_action);
    text_editor_theme_submenu.add_action(text_editor_theme_blue_action);
    text_editor_menu->add_sub_menu(text_editor_theme_submenu);

    text_editor_file_close.m_name = "Close";
    text_editor_file_save.m_name = "Save";
    text_editor_file_save_as.m_name = "Save As";
    text_editor_file_open.m_name = "Open";

    text_editor_file_save.pressed.Connect(text_editor_widget, &ui::texteditor::save_cur_file);
    text_editor_file_open.pressed.Connect(text_editor_widget, &ui::texteditor::signal_open_file);
    text_editor_file_submenu.add_action(text_editor_file_close);
    text_editor_file_submenu.add_action(text_editor_file_save);
    text_editor_file_submenu.add_action(text_editor_file_save_as);
    text_editor_file_submenu.add_action(text_editor_file_open);
    text_editor_menu->add_sub_menu(text_editor_file_submenu);

    text_editor_lang_set_glsl.m_name = "Set GLSL";
    text_editor_lang_set_lua.m_name = "Set Lua";

    text_editor_lang_set_glsl.pressed.Connect(text_editor_widget,
                                              &ui::texteditor::signal_set_lang_glsl);
    text_editor_lang_set_lua.pressed.Connect(text_editor_widget,
                                             &ui::texteditor::signal_set_lang_lua);

    text_editor_lang_submenu.add_action(text_editor_lang_set_glsl);
    text_editor_lang_submenu.add_action(text_editor_lang_set_lua);
    text_editor_menu->add_sub_menu(text_editor_lang_submenu);

    text_editor_line_container = new ui::line_continer();
    text_editor_compile_test_button = new ui::button("Compile test");
    text_editor_link_button = new ui::button("Link");

    text_editor_compile_test_button->click.Connect(text_editor_widget,
                                                   &ui::texteditor::signal_compile_test);
    text_editor_link_button->click.Connect(text_editor_widget, &ui::texteditor::signal_link_prog);

    text_editor_line_container->add_obj(text_editor_compile_test_button);
    text_editor_line_container->add_obj(text_editor_link_button);
    // Camera info
#if TEST3D == true
    camera_info_Fov_label = new ui::label("Fov: ");
    camera_info_Aspect_label = new ui::label("Aspect: ");
    camera_info_w_label = new ui::label("Width: ");
    camera_info_h_label = new ui::label("Hight: ");
    camera_info_pitch_label = new ui::label("Pitch: ");
    camera_info_yaw_label = new ui::label("Yaw: ");
    camera_info_pos_x = new ui::label("Position X: ");
    camera_info_pos_y = new ui::label("Position Y: ");
    camera_info_pos_z = new ui::label("Position Z: ");
    camera_info_reset_button = new ui::button("Reset Camera");
    camera_info_reset_button->click.Connect(gl_scene->getCameraCtrl().getCamera(),
                                            &renderer::camera3d::slots_Reset);
    camera_info_speed_bar = new ui::SlideBar("Moving Speed");
    camera_info_speed_bar->Changed.Connect(&gl_scene->getCameraCtrl(),
                                           &scene::camera3dController::slots_setMovingSpeed);
#endif
    // Texture Pannel
    texture_pannel_imgae_gallary = new ui::ImageGallary();
    texture_pannel_imgae_gallary->register_render_func([=](void) -> void {
      auto DB = gl_scene->getDB();
      if (DB->TextureNum() != texture_pannel_imgae_gallary->_data_.size()) {
        texture_pannel_imgae_gallary->_data_.clear();
        for (uint32_t i = 0; i < DB->TextureNum(); ++i) {
          texture_pannel_imgae_gallary->_data_.push_back(DB->FindTexture(i));
        }
      }
    });
  }

  ~uis() {
    delete console_1;
    delete gl_graphic;
    delete pannel_fps_label;
    delete pannel_stop_scene_button;
    delete pannel_start_scene_button;
    delete pannel_line_container;
    delete text_editor_widget;
    delete text_editor_line_container;
    delete text_editor_compile_test_button;
    delete text_editor_link_button;
#if TEST3D == true
    delete camera_info_Fov_label;
    delete camera_info_Aspect_label;
    delete camera_info_w_label;
    delete camera_info_h_label;
    delete camera_info_pitch_label;
    delete camera_info_yaw_label;
    delete camera_info_pos_x;
    delete camera_info_pos_y;
    delete camera_info_pos_z;
    delete camera_info_reset_button;
    delete camera_info_speed_bar;
#endif
    delete texture_pannel_imgae_gallary;
  }

 public:
  // For console
  ui::console* console_1;
  // For gl content
  ui::gl_content* gl_graphic;
#if TEST2D == true
  REF(scene::scene2d) gl_scene;
  REF(renderer::Shader) gl_scene_shader;
#elif TEST3D == true
  REF(scene::scene3d) gl_scene;
#endif
  // For gl_content pannel
  ui::line_continer* pannel_line_container;
  ui::label* pannel_fps_label;
  ui::button* pannel_stop_scene_button;
  ui::button* pannel_start_scene_button;
  // For Code Editor
  ui::texteditor* text_editor_widget;
  REF(ui::menu) text_editor_menu;
  ui::sub_menu text_editor_theme_submenu = ui::sub_menu("Theme");
  ui::sub_menu text_editor_file_submenu = ui::sub_menu("File");
  ui::sub_menu text_editor_lang_submenu = ui::sub_menu("Lang");
  ui::action text_editor_file_open;
  ui::action text_editor_file_save;
  ui::action text_editor_file_save_as;
  ui::action text_editor_file_close;
  ui::action text_editor_theme_black_action;
  ui::action text_editor_theme_white_action;
  ui::action text_editor_theme_blue_action;
  ui::action text_editor_open_action;
  ui::action text_editor_lang_set_lua;
  ui::action text_editor_lang_set_glsl;
  ui::line_continer* text_editor_line_container;
  ui::button* text_editor_compile_test_button;
  ui::button* text_editor_link_button;
  // For Camera Attribute.
#if TEST3D == true
  ui::label* camera_info_Fov_label;
  ui::label* camera_info_Aspect_label;
  ui::label* camera_info_w_label;
  ui::label* camera_info_h_label;
  ui::label* camera_info_pitch_label;
  ui::label* camera_info_yaw_label;
  ui::label* camera_info_pos_x;
  ui::label* camera_info_pos_y;
  ui::label* camera_info_pos_z;
  ui::button* camera_info_reset_button;
  ui::SlideBar* camera_info_speed_bar;
#endif
  // For Texture Pannel
  ui::ImageGallary* texture_pannel_imgae_gallary;
  // For component pannel
};
