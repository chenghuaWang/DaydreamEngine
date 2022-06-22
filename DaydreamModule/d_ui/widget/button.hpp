#ifndef H_UI_BUTTON
#define H_UI_BUTTON

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "_base.hpp"

using namespace kaleidoscope;

namespace daydream {
namespace ui {

	class D_API_EXPORT button :public ui_object {
	public:
		button(const std::string &name);

		void on_attach() override {};
		void on_detach() override {};
		void on_update() override {};
		void update_event() override {};
		void impl_imgui_render() override;

		Signal0<>	click;
	
	protected:
		std::string m_name;
	};

	class D_API_EXPORT label :public button {
	public:
		label(const std::string& name);
		void impl_imgui_render();
		void set_value(const std::string& v);

	public:
		std::string m_value;
	};

	class D_API_EXPORT image_button :public button {
	public:
		image_button(const std::string& name);
		~image_button();

		void impl_imgui_render() override;
		void set_image(const std::string &path, float size_w, float size_h);

	private:
		unsigned char*	result;
		uint32_t		m_image_idx;
		ImVec2			m_image_size;
	};

}
}

#endif // !H_UI_BUTTON
