#include "gl_content.hpp"

namespace daydream {
namespace ui {
	void gl_content::on_attach() {
		renderer::GLCommand::init();
		switch (m_type)
		{
		case daydream::ui::gl_content_type::TwoD:
			if (m_scene2d == nullptr) {
				m_scene2d = CREATE_REF(scene::scene2d)(1.f, 1.f);
				LOG_WARN("The scene ptr is null. GL content can't ignore it.");
				exit(1);
			}
			break;
		case daydream::ui::gl_content_type::ThreeD:
			break;
		default:
			break;
		}
	}

	void gl_content::on_update() {
		switch (m_type)
		{
		case daydream::ui::gl_content_type::TwoD:
			m_scene2d->BeginRender();
			// Do something
			m_scene2d->EndRender();
			break;
		case daydream::ui::gl_content_type::ThreeD:
			break;
		default:
			break;
		}
	}

	void gl_content::update_event() {
	}

	void gl_content::impl_imgui_render() {
		m_panelsize_cur = ImGui::GetContentRegionAvail();
		switch (m_type)
		{
		case daydream::ui::gl_content_type::TwoD:
			m_scene2d->m_MainCamera.set_activited(ImGui::IsWindowFocused());
			if (m_panelsize_cur.x != m_panelsize_pre.x && m_panelsize_cur.y != m_panelsize_pre.y) {
				m_scene2d->Resize(m_panelsize_cur.x, m_panelsize_cur.y);
			}
			ImGui::Image((void*)m_scene2d->FrameIdx(), ImVec2(m_panelsize_pre.x, m_panelsize_pre.y), ImVec2(0, 1), ImVec2(1, 0));
			break;
		case daydream::ui::gl_content_type::ThreeD:
			break;
		default:
			break;
		}
	}

	void gl_content::set_scene2d() {
		m_type = gl_content_type::TwoD;
	}

}
}

