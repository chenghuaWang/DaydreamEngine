#include "layer.hpp"

namespace daydream {
namespace ui {
	base_layer::base_layer(const std::string& name):m_idx(0), m_name(name) {
	}

	obj_layer::obj_layer(const std::string& name) :base_layer(name), p_open(true) {
	}

	obj_layer::~obj_layer() {
		for (auto item : m_objs) {
			delete item;
		}
	}

	void obj_layer::update() {
		for (auto item : m_objs) {
			item->update_event();
		}
	}

	void obj_layer::impl_imgui_render() {
		ImGui::Begin(m_name.c_str(), &p_open);
		for (auto item : m_objs) {
			item->impl_imgui_render();
		}
		ImGui::End();
	}

	void obj_layer::add_obj(ui_object* o) {
		m_objs.emplace_back(o);
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