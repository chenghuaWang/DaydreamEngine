#ifndef H_UI_LAYER
#define H_UI_LAYER

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "d_core/pch.hpp"
#include "d_ui/widget/menu.hpp"

namespace daydream {
namespace ui {

	class D_API_EXPORT base_layer {
	public:
		base_layer(const std::string &name);

		virtual void update() {}; ///< for event
		virtual void impl_imgui_render() {}; ///< for imgui frame

	private:
		unsigned int	m_idx;
		std::string		m_name;
	};

	class D_API_EXPORT menu_layer : public base_layer {
	public:
		menu_layer(const std::string& name = "menu");

		void update() override;
		void impl_imgui_render() override;

		void register_menu(const REF(menu)& rhs);
		REF(menu)& get_menu();

	private:
		REF(menu)	m_menu;
	};

} // !namespace daydream
} // !namespace daydream

#endif // H_UI_LAYER
