#ifndef H_CONSOLE
#define H_CONSOLE

#ifdef _MSC_VER > 1000
#pragma once
#endif // !_MSC_VER 

#include "_base.hpp"

namespace daydream {
namespace ui {
	
	class D_API_EXPORT console : public ui_object {
	public:
		console(const std::string &file_path="info.log");
		~console();

		void update_event() override;
		void impl_imgui_render() override;

		void setEnable(bool enable);
		void setVisible(bool enable);

	private:
		bool			m_enable;
		bool			m_visible;
		std::fstream	m_file;
		std::string		m_s_buffer;
		std::string		__tmp_a__;
	};

}
}

#endif // !H_CONSOLE
