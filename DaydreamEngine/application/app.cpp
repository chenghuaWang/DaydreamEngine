#include "app.hpp"

App::App(): m_window_view("window-view") {
	m_App_ui = new uis();

	m_action_show_log.m_name = "Show log.";
	m_action_show_log.m_accelerate_key = "ctrl+l";
	m_window_view.add_action(m_action_show_log);
	m_window_menu.add_sub_menu(m_window_view);

	auto menu_ui_layer = new ui::menu_layer();
	auto console_ui_layer = new ui::obj_layer("console");

	menu_ui_layer->register_menu(CREATE_REF(ui::menu)(m_window_menu));
	console_ui_layer->add_obj(m_App_ui->console_1);

	m_layers.add_layer(menu_ui_layer);
	m_layers.add_layer(console_ui_layer);
}

App::~App() {
	delete m_App_ui;
}

void App::flush_frame() {
	for (auto item : m_layers) {
		item->impl_imgui_render();
	}
}

