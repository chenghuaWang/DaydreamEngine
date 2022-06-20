#ifndef H_UI_WIDGET_MENU
#define H_UI_WIDGET_MENU

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "_base.hpp"

using namespace kaleidoscope;

namespace daydream {
namespace ui {

	class D_API_EXPORT action {
	public:
		std::string		m_name;
		std::string		m_accelerate_key;

	public:
		Signal0<> clicked;
		void click(void) {
			clicked(); // Emitted.
		}
	};

	class D_API_EXPORT sub_menu {
	public:
		sub_menu(const std::string &name);

		const std::string& name() const { return m_name; }
		void add_action(const action& rhs);
	
	public:
		virtual void update() {};
		virtual void impl_imgui_render();

	private:
		std::string				m_name;
		std::vector<action>		m_actions;
	};

	class D_API_EXPORT menu {
	public:
		menu() {};
		~menu() {};

		void			add_sub_menu(sub_menu &rhs);
		void			add_sub_menu(size_t idx, sub_menu& rhs);
		void			remove_sub_menu(sub_menu& rhs);
		sub_menu&		get_sub_menu(size_t idx);

	public:
		virtual void	update() {};
		virtual void	impl_imgui_render();

	private:
		std::vector<sub_menu>	m_sub_menus;
	};

} //! namespace ui
} //! namespace daydream

#endif // !H_UI_WIDGET_MENU
