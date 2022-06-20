#include "menu.hpp"

namespace daydream {
namespace ui {

	sub_menu::sub_menu(const std::string& name) :m_name(name) {
	}

	void sub_menu::add_action(const action& rhs) {
		m_actions.push_back(rhs);
	}

	void sub_menu::impl_imgui_render() {
		if (ImGui::BeginMenu(m_name.c_str()))
		{
			for (auto& item : m_actions) {
				if (ImGui::MenuItem(item.m_name.c_str(), item.m_accelerate_key.c_str())) {
					item.click();
				}
			}
			ImGui::EndMenu();
		}
	}

	sub_menu& menu::get_sub_menu(size_t idx) {
		if (idx > m_sub_menus.size()) {
			std::cout << "[Err]: Indexing sub menu from main menu, error, out of range.";
			std::cout << "Find size() is " << m_sub_menus.size() << ". But indexing size is " << idx << ".\n";
			exit(1);
		}

		return m_sub_menus[idx];
	}

	void menu::add_sub_menu(sub_menu& rhs) {
		m_sub_menus.push_back(rhs);
	}

	void menu::add_sub_menu(size_t idx, sub_menu& rhs) {
		m_sub_menus.insert(m_sub_menus.begin() + idx, rhs);
	}

	void menu::remove_sub_menu(sub_menu& rhs) {
		for (auto it = m_sub_menus.begin(); it != m_sub_menus.end(); ) {
			if (it->name() == rhs.name()) {
				m_sub_menus.erase(it);
			}
			++ it;
		}
	}

	void menu::impl_imgui_render() {
		if (ImGui::BeginMenuBar())
		{
			for (auto& item : m_sub_menus) {
				item.impl_imgui_render();
			}
			ImGui::EndMenuBar();
		}
	}

} //! namesapce daydream
} //! namespace daydream