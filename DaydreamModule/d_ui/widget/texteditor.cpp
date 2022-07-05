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
		if (m_file_dialog.wait(m_file_dialog_value)) {
			switch (m_file_dialog_state) {
			case text_editor_cur_dialog_state::Open:
				open_file(m_file_dialog_value);
				break;
			case text_editor_cur_dialog_state::Save:
				break;
			case text_editor_cur_dialog_state::SaveAs:
				break;
			default:
				break;
			}
		}
	}

	void texteditor::signal_open_file() {
		m_file_dialog_state = text_editor_cur_dialog_state::Open;
		m_file_dialog.show("ChooseFileDlgKey", "Choose File", ".cpp,.h,.hpp,.shader,.glsl,.txt,.lua,.python", ".");
	}

	void texteditor::signal_set_lang_lua() {
		this->set_lang(lang::Lua);
	}
	
	void texteditor::signal_set_lang_glsl() {
		this->set_lang(lang::GLSL);
	}

	void texteditor::signal_compile_test() {

	}

	void texteditor::signal_link_prog() {

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
		std::string tmp_str = m_editor.GetText();
		std::ofstream t(m_file_dialog_value);
		if (t.good()) {
			t << tmp_str;
		}
		t.close();
	}

	void texteditor::backup_cur_file(const std::string& file_path) {

	}

	void texteditor::save_as_cur_file(const std::string& file_path) {

	}

	void texteditor::close_cur_file() {

	}

	void texteditor::set_lang(lang type) {
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

	void texteditor::set_color(texteditor_color color) {
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

	void texteditor::set_color_black() {
		set_color(texteditor_color::Dark);
	}

	void texteditor::set_color_white() {
		set_color(texteditor_color::Light);
	}

	void texteditor::set_color_blue() {
		set_color(texteditor_color::Blue);
	}

}
}