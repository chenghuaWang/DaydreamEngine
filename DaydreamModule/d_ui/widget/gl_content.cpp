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
			}

			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);
			// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
			glBindVertexArray(VAO);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);

			// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
			// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
			glBindVertexArray(0);
			break;
		case daydream::ui::gl_content_type::ThreeD:
			break;
		default:
			break;
		}
	}

	void gl_content::on_detach() {
		switch (m_type)
		{
		case daydream::ui::gl_content_type::TwoD:
			glDeleteVertexArrays(1, &VAO);
			glDeleteBuffers(1, &VBO);
			glDeleteBuffers(1, &EBO);
			break;
		case daydream::ui::gl_content_type::ThreeD:
			break;
		case daydream::ui::gl_content_type::None:
			break;
		default:
			break;
		}
	}

	void gl_content::on_update() {
		m_timer.OnUpdate();
		if (m_running) {
			switch (m_type)
			{
			case daydream::ui::gl_content_type::TwoD:
				m_scene2d->BeginRender();
				// below for shader bind
				m_scene2d->m_MainShader->setVec3("iResolution", m_panelsize_cur.x, m_panelsize_cur.y, 1.f);
				m_scene2d->m_MainShader->setFloat("iTime", m_timer.getGlobalTime()); //Time; TODO
				m_scene2d->m_MainShader->setFloat("iTimeDelta", m_timer.getTimeDelta()); //Time; TODO
				m_scene2d->m_MainShader->setInt("iFrame", 0); //Time; TODO
				m_scene2d->m_MainShader->setVec4("iMouse", m_cur_mouse_pos.x, m_cur_mouse_pos.y, m_cur_mouse_click.x, m_cur_mouse_click.y);

				glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
				//glDrawArrays(GL_TRIANGLES, 0, 6);
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
				m_scene2d->EndRender();
				break;
			case daydream::ui::gl_content_type::ThreeD:
				break;
			default:
				break;
			}
		}
	}

	void gl_content::update_event() {
		if (m_running) {
			if (ImGui::IsWindowFocused) {
				if (ImGui::IsMouseClicked) {
					m_cur_mouse_click = ImGui::GetMousePosOnOpeningCurrentPopup();
					// m_cur_mouse_pos = ImGui::GetMousePosOnOpeningCurrentPopup();
				}
			}
			// m_cur_mouse_pos = ImGui::GetMousePosOnOpeningCurrentPopup();
		}
	}

	void gl_content::impl_imgui_render() {
		m_panelsize_cur = ImGui::GetContentRegionAvail();
		uint32_t tmp_id = 0;
		switch (m_type)
		{
		case daydream::ui::gl_content_type::TwoD:
			m_scene2d->m_MainCamera.set_activited(ImGui::IsWindowFocused());
			if (m_panelsize_cur.x != m_panelsize_pre.x || m_panelsize_cur.y != m_panelsize_pre.y) {
				m_scene2d->Resize(m_panelsize_cur.x, m_panelsize_cur.y);
				m_panelsize_pre = m_panelsize_cur;
			}
			tmp_id = m_scene2d->FrameIdx();
			ImGui::Image((void*)tmp_id, ImVec2(m_panelsize_cur.x, m_panelsize_cur.y), ImVec2(0, 1), ImVec2(1, 0));
			break;
		case daydream::ui::gl_content_type::ThreeD:
			break;
		default:
			break;
		}
	}

	void gl_content::stop_render() {
		m_running = false;
		m_timer.stop();
		switch (m_type)
		{
		case daydream::ui::gl_content_type::TwoD:
			m_scene2d->setRunning(false);
			break;
		case daydream::ui::gl_content_type::ThreeD:
			break;
		case daydream::ui::gl_content_type::None:
			break;
		default:
			break;
		}
	}

	void gl_content::start_render() {
		m_running = true;
		m_timer.start();
		switch (m_type)
		{
		case daydream::ui::gl_content_type::TwoD:
			m_scene2d->setRunning(true);
			break;
		case daydream::ui::gl_content_type::ThreeD:
			break;
		case daydream::ui::gl_content_type::None:
			break;
		default:
			break;
		}
	}

	void gl_content::set_scene2d(REF(scene::scene2d)& sc) {
		m_scene2d = sc;
		m_type = gl_content_type::TwoD;
	}

}
}

