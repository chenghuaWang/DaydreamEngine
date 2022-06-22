#include "d_ui/widget/console.hpp"
#include "d_ui/widget/button.hpp"
#include "d_ui/widget/gl_content.hpp"
#include "d_ui/widget/utils.hpp"

using namespace daydream;

struct uis {
	uis() {
		// For console
		console_1 = new ui::console();
		console_clear_button = new ui::button("Clear");
		// For gl content
		gl_graphic = new ui::gl_content();
		gl_scene = CREATE_REF(scene::scene2d)(100.f, 100.f);
		gl_scene_shader = renderer::Shader::create("../Asset/shader/twoD/default.glsl");
		// For gl_content pannel
		pannel_line_container = new ui::line_continer();
		pannel_fps_label = new ui::label("FPS: ");
		pannel_stop_scene_button = new ui::button("Stop");
		pannel_start_scene_button = new ui::button("Start");
		pannel_line_container->add_obj(pannel_stop_scene_button);
		pannel_line_container->add_obj(pannel_start_scene_button);
		pannel_line_container->add_obj(pannel_fps_label);

		// Link all signal and slots. If both side is defined here.
		console_clear_button->click.Connect(console_1, &ui::console::clear);
		pannel_stop_scene_button->click.Connect(gl_graphic, &ui::gl_content::stop_render);
		pannel_start_scene_button->click.Connect(gl_graphic, &ui::gl_content::start_render);
	}

	~uis() {
		delete console_1;
		delete console_clear_button;
		delete gl_graphic;
		delete pannel_fps_label;
		delete pannel_stop_scene_button;
		delete pannel_start_scene_button;
		delete pannel_line_container;
	}

public:
	// For console
	ui::console*			console_1;
	ui::button*				console_clear_button;
	// For gl content
	ui::gl_content*			gl_graphic;
	REF(scene::scene2d)		gl_scene;
	REF(renderer::Shader)	gl_scene_shader;
	// For gl_content pannel
	ui::line_continer*		pannel_line_container;
	ui::label*				pannel_fps_label;
	ui::button*				pannel_stop_scene_button;
	ui::button*				pannel_start_scene_button;
};
