#include "d_ui/widget/console.hpp"
#include "d_ui/widget/gl_content.hpp"

using namespace daydream;

struct uis {
	uis() = default;

	~uis() {
		delete console_1;
		delete gl_graphic;
	}

	ui::console*			console_1 = new ui::console();
	ui::gl_content*			gl_graphic = new ui::gl_content();
	REF(scene::scene2d)		gl_scene = CREATE_REF(scene::scene2d)(100.f, 100.f);
	REF(renderer::Shader)	gl_scene_shader = renderer::Shader::create("../Asset/shader/twoD/default.glsl");
};
