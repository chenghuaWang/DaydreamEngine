#ifndef H_UI_WIDGET_BASE
#define H_UI_WIDGET_BASE

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "imgui.h"
#include "d_core/pch.hpp"
#include "d_event/event.hpp"
#include "d_event/signal_slots/signal_slots.hpp"

#ifndef __gl_h_
#include "glad/glad.h"
#endif // !__gl

#include "stb_image.h"
// TODO add other stuff

namespace daydream {
namespace ui {
	class D_API_EXPORT ui_object {
	public:
		virtual void on_attach();
		virtual void on_detach();
		virtual void on_update();
		virtual void update_event();
		virtual void impl_imgui_render();
	};
}
}

#endif // !H_UI_WIDGET_BASE
