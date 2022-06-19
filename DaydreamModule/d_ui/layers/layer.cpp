#include "layer.hpp"

namespace daydream {
namespace ui {
	base_layer::base_layer(const std::string& name):m_idx(0), m_name(name) {
	}

	menu_layer::menu_layer(const std::string& name) :base_layer(name) {
		LOG_INFO("Imgui Window Menu layer init...done.")
	}

	void menu_layer::impl_imgui_render() {
		m_menu->impl_imgui_render();
	}

	void menu_layer::update() {
		m_menu->update();
	}

	void menu_layer::register_menu(const REF(menu)& rhs) {
		m_menu = rhs;
	}

	REF(menu)& menu_layer::get_menu() {
		return m_menu;
	}

} // !namespace ui
} // !namespace daydream