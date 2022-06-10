#ifndef H_WINDOW
#define H_WINDOW

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "d_core/pch.hpp"

namespace daydream {
namespace ui {
	void generate_glfw_context();
	void generate_imgui_context();
	void generate_gl_context();

	void collect_glfw_context();
	void collect_imgui_context();
	void collect_gl_context();

	void pass_glfw_context_to_gl();

	class base_window {

	};

} // !namespace ui
} // !namespace daydream

#endif // !H_WINDOW
