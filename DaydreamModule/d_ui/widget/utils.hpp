#ifndef H_UI_UTILS
#define H_UI_UTILS

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "_base.hpp"

namespace daydream {
namespace ui {
	
	class D_API_EXPORT line_continer : public ui_object {
	public:
		inline void __same_line__();
		void add_obj(ui_object* o);

		void on_attach();
		void on_detach();
		void on_update();
		void update_event();
		void impl_imgui_render();

	private:
		size_t						tmp_size = 0;
		std::vector<ui_object*>		m_contained_objs;
	};

}
}


#endif // !H_UI_UTILS