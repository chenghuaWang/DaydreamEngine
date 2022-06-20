#include "app.hpp"

App::App(): m_window_view("window-view") {
	m_App_ui = new uis();

	m_action_show_log.m_name = "Show log.";
	m_action_show_log.m_accelerate_key = "ctrl+l";

	auto menu_ui_layer = new ui::menu_layer();
	auto console_ui_layer = new ui::obj_layer("console");

	console_ui_layer->add_obj(m_App_ui->console_1);

	m_layers.add_layer(menu_ui_layer);
	m_layers.add_layer(console_ui_layer);

	// signal and slots linking
	// !!! [TODO] bug. The action is not pass by ptr. So connect must before add_action.
	m_action_show_log.clicked.Connect(console_ui_layer, &ui::obj_layer::set_wopened);

	// init the main-menu
	m_window_view.add_action(m_action_show_log);
	m_window_menu.add_sub_menu(m_window_view);
	menu_ui_layer->register_menu(CREATE_REF(ui::menu)(m_window_menu));
}

App::~App() {
	delete m_App_ui;
}

void App::flush_frame() {
	for (auto item : m_layers) {
		item->impl_imgui_render();
	}
}

