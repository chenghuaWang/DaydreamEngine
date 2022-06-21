/*!
 * @author	chenghua.wang
 * @brief	Where the basic window and imgui window defined.
 * @file	DaydreamModule/d_ui/window/window.hpp
 * @version	v0.0.1-beta
 */
#ifndef H_WINDOW
#define H_WINDOW

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "d_core/pch.hpp"
//#include "d_event/signal_slots/signal_slots.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "ImGuizmo.h"

#include "d_render/core/_gl_head.hpp"
#include "GLFW/glfw3.h"

namespace daydream {
namespace ui {

	/*!
	 * @brief	This fucntion is a callback for opengl error thrower. 
	 */
	static void glfw_error_callback(int error, const char* description) {
		std::cerr << "GLFW Error " << error << ": " << description;
	}

	bool generate_glfw_context();
	void generate_imgui_context();
	//void generate_gl_context(); TODO

	void collect_glfw_context();
	void collect_imgui_context();
	//void collect_gl_context(); TODO
	void pass_glfw_context_to_gl();

	class D_API_EXPORT gl_context {
	public:
		gl_context(GLFWwindow* windowHandle);

		void Init();
		void SwapBuffers();

	private:
		GLFWwindow* m_WindowHandle;
	};

	/*!
	 * @brief	This class is the basic and necessary class for all render.
	 *			It's responsible for [OpenGL Context & glfw-Window]
	 * 
	 * @detail	All other self-defined window should inherient from this window.
	 *			This basic window class provide event transfer and flush_frame
	 *			for all component in this class. If you want to make a window that
	 *			behave in other ways, you can just override the flush_frame and
	 *			event update functions.
	 * 
	 * For more, This window basic class provide a context of opengl for render.
	 * So, don't need to re-init a opengl context. Just use the context in this
	 * window class will make things easier, also, this class are responsed to de-
	 * stroy this context.
	 * 
	 * You should note that, this class is just for 2 things [OpenGL context, window].
	 * So, if you want to build fancy ui on it. You should use other class, such as
	 * imgui_window, or write a brand new one by you own.
	 */
	class D_API_EXPORT window_base {
	public:
		window_base(size_t w = 1920, size_t h = 1080, const std::string& window_name = "window");
		~window_base();

		virtual void hook_glfw_callback();
		static void on_window_resize(GLFWwindow* window, int width, int height);
		static void on_window_close(GLFWwindow* window);

		virtual void exec();
		virtual void flush_frame();
		virtual void update_event();

	public:
		size_t			getW();
		size_t			getH();
	
	protected:
		gl_context*		m_context;
		size_t			m_H, m_W;
		GLFWwindow*		m_window_handle = nullptr;
		std::string		m_window_name;
		REF(p_logger)	m_logger;
	};

	/*!
	 * @brief	A enum for windows flags. Only imgui based window support this flag.
	 * 
	 * NONE model / Docking / Multi-window / Auto_api is support now. In the imgui 
	 * window, those flags is all set to true.
	 */
	enum D_API_EXPORT imgui_window_flags {
		NONE = 0,
		DOCKING = 1,
		MULTI_WINDOW = 1 << 1,
		AUTO_DPI = 1 << 2,
	};

	/*!
	 * @brief	A enum for color style choose. For now, there r just 3 flavors for you. 
	 */
	enum class D_API_EXPORT imgui_color_style {
		NONE = 0,
		CLASSIC_DARK = 1,
		CLASSIC_WHITE = 2,
	};

	/*!
	 * @brief	Imgui window class. Inherented from window_base class.
	 *			You need to use window-flags to init this window class first when you want to
	 *			start a thread with imgui window.
	 * 
	 * For Auto DPI, check the https://github.com/ocornut/imgui/issues/2442.
	 */
	class D_API_EXPORT imgui_window : public window_base {
	public:
		imgui_window(
			size_t w = 1920, 
			size_t h = 1080, 
			uint16_t flags = imgui_window_flags::AUTO_DPI | imgui_window_flags::DOCKING | imgui_window_flags::MULTI_WINDOW, 
			const std::string& window_name = "imgui window");
		~imgui_window();

		virtual void _imgui_start_();
		virtual void _imgui_end_();
		virtual void _imgui_auto_dpi_();
		virtual void set_imgui_style(imgui_color_style style);

		static void on_window_resize_dpi_aware(GLFWwindow* window, int width, int height);

	public:
		void exec()			override;
		void flush_frame()	override;
		void update_event() override;

	private:
		uint16_t	m_window_flags;
	};

} // !namespace ui
} // !namespace daydream

#endif // !H_WINDOW
