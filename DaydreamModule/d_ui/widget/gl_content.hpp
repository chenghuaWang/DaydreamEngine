#ifndef H_GL_CONTENT
#define H_GL_CONTEMT

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER

#include "_base.hpp"
#include "d_scene/scene/scene2d.hpp"
#include "d_scene/scene/scene3d.hpp"

namespace daydream {
namespace ui {

	enum class D_API_EXPORT gl_content_type {
		TwoD = 0,
		ThreeD = 1
	};
	
	class D_API_EXPORT gl_content : public ui_object {
	public:
		void on_attach() override;
		void on_update() override;
		void update_event() override;
		void impl_imgui_render() override;

		void set_scene2d();
		// void set_scene3d(REF(scene::scene3d)& sc);

	private:
		ImVec2				m_panelsize_cur{0.f, 0.f};
		ImVec2				m_panelsize_pre{0.f, 0.f};
		gl_content_type		m_type;
		REF(scene::scene2d)	m_scene2d = nullptr;
		// TODO REF(scene::scene3d)	m_scene3d;
	};

}
}

#endif // !H_GL_CONTENT
