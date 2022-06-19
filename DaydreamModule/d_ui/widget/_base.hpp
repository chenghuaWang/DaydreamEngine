#ifndef H_UI_WIDGET_BASE
#define H_UI_WIDGET_BASE

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "imgui.h"
#include "d_core/pch.hpp"
#include "d_event/event.hpp"
#include "d_event/signal_slots/signal_slots.hpp"
// TODO add other stuff

namespace daydream {
namespace ui {
	class ui_object {
	protected:
		virtual void update_event() = 0;
		virtual void impl_imgui_render() = 0;
	};
}
}

#endif // !H_UI_WIDGET_BASE
