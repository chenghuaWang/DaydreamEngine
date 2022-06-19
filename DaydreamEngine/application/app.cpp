#include "app.hpp"

App::App(): m_window_view("window-view") {
	m_action_show_log.m_name = "Show log.";
	m_action_show_log.m_accelerate_key = "ctrl+l";
	m_window_view.add_action(m_action_show_log);
	m_window_menu.add_sub_menu(m_window_view);

	auto menu_ui_layer = new ui::menu_layer();
	menu_ui_layer->register_menu(CREATE_REF(ui::menu)(m_window_menu));
	m_layers.add_layer(menu_ui_layer);
}

void App::flush_frame() {
	for (auto item : m_layers) {
		item->impl_imgui_render();
	}
}

