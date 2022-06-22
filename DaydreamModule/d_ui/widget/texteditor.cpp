#include "texteditor.hpp"

namespace daydream {
namespace ui {

	texteditor::texteditor() {
	}

	void texteditor::on_attach() {
		
	}

	void texteditor::on_detach() {

	}

	void texteditor::on_update() {

	}

	void texteditor::update_event() {

	}

	void texteditor::impl_imgui_render() {
		auto cpos = m_editor.GetCursorPosition();
		ImGui::Text("%6d/%-6d %6d lines  | %s | %s | %s | %s", cpos.mLine + 1, cpos.mColumn + 1, m_editor.GetTotalLines(),
			m_editor.IsOverwrite() ? "Ovr" : "Ins",
			m_editor.CanUndo() ? "*" : " ",
			m_editor.GetLanguageDefinition().mName.c_str(), m_file_buffers[m_cur_text_src_idx].file_path.c_str());

		m_editor.Render("TextEditor");
	}

	void texteditor::open_file(const std::string& file_path) {

		m_file_buffers[++m_cur_text_src_idx] = { m_cur_text_src_idx, file_path, "" };

		std::ifstream t(m_file_buffers[m_cur_text_src_idx].file_path);
		if (t.good()) {
			std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
			m_editor.SetText(str);
		}
		t.close();
	}

	void texteditor::save_cur_file() {

	}

	void texteditor::backup_cur_file(const std::string& file_path) {

	}

	void texteditor::save_as_cur_file(const std::string& file_path) {

	}

	void texteditor::close_cur_file() {

	}

	void texteditor::set_lang(lang& type) {
		switch (type)
		{
		case lang::GLSL:
			m_editor.SetLanguageDefinition(m_lang_glsl);
			break;
		case lang::Lua:
			m_editor.SetLanguageDefinition(m_lang_lua);
			break;
		default:
			break;
		}
	}

	void texteditor::set_color(texteditor_color &color) {
		switch (color)
		{
		case texteditor_color::Light:
			m_editor.SetPalette(TextEditor::GetLightPalette());
			break;
		case texteditor_color::Dark:
			m_editor.SetPalette(TextEditor::GetDarkPalette());
			break;
		case texteditor_color::Blue:
			m_editor.SetPalette(TextEditor::GetRetroBluePalette());
			break;
		default:
			break;
		}
	}



}
}