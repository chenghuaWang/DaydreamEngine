#ifndef H_WINDOW
#define H_WINDOW

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "d_core/pch.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "GLFW/glfw3.h"

namespace daydream {
namespace ui {
	static void glfw_error_callback(int error, const char* description) {
		std::cerr << "GLFW Error " << error << ": " << description;
	}

	bool generate_glfw_context();
	void generate_imgui_context();
	void generate_gl_context();

	void collect_glfw_context();
	void collect_imgui_context();
	void collect_gl_context();

	void pass_glfw_context_to_gl();

	class base_window {
	public:
		base_window(size_t w, size_t h, const std::string &window_name);
		~base_window();

		virtual void update() = 0;
		virtual void flush();
		virtual void exec();

	protected:
		virtual void on_window_resize();
		virtual void on_window_hide();
		virtual void on_window_close();

	private:
		size_t		m_H, m_W;
		GLFWwindow* m_window_handle = nullptr;
		std::string	m_window_name;
	};

} // !namespace ui
} // !namespace daydream

#endif // !H_WINDOW
