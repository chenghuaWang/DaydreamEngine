#include "console.hpp"

namespace daydream {
namespace ui {

	console::console(const std::string& file_path):m_enable(true), m_visible(true) {
		m_file.open(file_path, std::ios_base::in);
		if (!m_file.is_open()) {
			LOG_WARN("failed to load log files.")
			exit(1);
		}
	}

	console::~console() {
		m_file.close();
	}

	void console::update_event(){
	}

	void console::impl_imgui_render() {
		for (int i = 0; std::getline(m_file, __tmp_a__); ++i) {
			m_s_buffer += ( "\n" + __tmp_a__);
		}
		ImGui::Text(m_s_buffer.data());
		for (int i = 0; i < 4; i++) {
			ImGui::Text("");
		}
	}

	void console::setEnable(bool enable) {
		m_enable = enable;
	}

	void console::setVisible(bool enable) {
		m_visible = enable;
	}

}
}
