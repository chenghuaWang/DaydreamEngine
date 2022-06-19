#include "console.hpp"

namespace daydream {
namespace ui {

	console::console(const std::string& file_path):m_enable(true), m_visible(true) {
		m_file.open(file_path);
	}

	console::~console() {
		m_file.close();
	}

	void console::update_event(){
	}

	void console::impl_imgui_render() {
		ImGui::Begin("console", &m_visible);
		for (int i = 0; std::getline(m_file, m_s_buffer); ++i) {
			if (i >= 4) ImGui::Text(m_s_buffer.data());
		}
		for (int i = 0; i < 4; i++) {
			ImGui::Text("");
		}
		ImGui::End();
	}

	void console::setEnable(bool enable) {
		m_enable = enable;
	}

	void console::setVisible(bool enable) {
		m_visible = enable;
	}

}
}
