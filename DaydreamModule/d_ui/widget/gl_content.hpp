#ifndef H_GL_CONTENT
#define H_GL_CONTEMT

#if _MSC_VER > 1000
#pragma once
#pragma warnind( disable: 4251 )
#endif // _MSC_VER

#include "_base.hpp"
#include "d_ui/window/timer.hpp"
#include "d_ui/scene/scene2d.hpp"
#include "d_ui/scene/scene3d.hpp"

namespace daydream {
namespace ui {

	enum class D_API_EXPORT gl_content_type {
		TwoD = 0,
		ThreeD = 1,
		None = 2
	};
	
	class D_API_EXPORT gl_content : public ui_object {
	public:
		void on_attach() override;
		void on_detach() override;
		void on_update() override;
		void update_event() override;
		void impl_imgui_render() override;

		void stop_render();
		void start_render();

		void set_scene2d(REF(scene::scene2d)& sc);
		 void set_scene3d(REF(scene::scene3d)& sc);

		Timer m_timer;

	private:
		bool				m_running = true;

		ImVec2				m_panelsize_cur{0.f, 0.f};
		ImVec2				m_panelsize_pre{0.f, 0.f};
		ImVec2				m_cur_mouse_pos;
		ImVec2				m_cur_mouse_click;
		gl_content_type		m_type = gl_content_type::None;
		REF(scene::scene2d)	m_scene2d = nullptr;
		REF(scene::scene3d) m_scene3d = nullptr;
		// TODO REF(scene::scene3d)	m_scene3d;

	private:
		float vertices[12] = {
		 1.0f,  1.0f, 0.0f,  // top right
		 1.0f, -1.0f, 0.0f,  // bottom right
		-1.0f, -1.0f, 0.0f,  // bottom left
		-1.0f,  1.0f, 0.0f   // top left 
		};

		unsigned int indices[6] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
		};
		unsigned int VBO, VAO, EBO;
	};

}
}

#endif // !H_GL_CONTENT
