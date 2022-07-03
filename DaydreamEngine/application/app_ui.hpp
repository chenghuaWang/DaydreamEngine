#include "d_ui/widget/console.hpp"
#include "d_ui/widget/button.hpp"
#include "d_ui/widget/gl_content.hpp"
#include "d_ui/widget/utils.hpp"
#include "d_ui/widget/texteditor.hpp"

using namespace daydream;

struct uis {
	uis() {
		// For console
		console_1 = new ui::console();

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
		pannel_stop_scene_button->click.Connect(gl_graphic, &ui::gl_content::stop_render);
		pannel_start_scene_button->click.Connect(gl_graphic, &ui::gl_content::start_render);

		// Code Editor
		text_editor_widget = new ui::texteditor();
	}

	~uis() {
		delete console_1;
		delete gl_graphic;
		delete pannel_fps_label;
		delete pannel_stop_scene_button;
		delete pannel_start_scene_button;
		delete pannel_line_container;
		delete text_editor_widget;
	}

public:
	// For console
	ui::console*			console_1;
	// For gl content
	ui::gl_content*			gl_graphic;
	REF(scene::scene2d)		gl_scene;
	REF(renderer::Shader)	gl_scene_shader;
	// For gl_content pannel
	ui::line_continer*		pannel_line_container;
	ui::label*				pannel_fps_label;
	ui::button*				pannel_stop_scene_button;
	ui::button*				pannel_start_scene_button;
	// For Code Editor
	ui::texteditor*			text_editor_widget;
};
