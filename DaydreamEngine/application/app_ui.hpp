#include "d_ui/widget/console.hpp"
#include "d_ui/widget/gl_content.hpp"

using namespace daydream;

struct uis {
	uis() {
		gl_graphic->set_scene2d();
	}

	~uis() {
		delete console_1;
		delete gl_graphic;
	}

	ui::console*		console_1 = new ui::console();
	ui::gl_content*		gl_graphic = new ui::gl_content();

};
