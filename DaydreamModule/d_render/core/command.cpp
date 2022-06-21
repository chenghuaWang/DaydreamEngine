#include "command.hpp"

namespace daydream {
namespace renderer {

	void GLCommand::init() {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	}

	void GLCommand::setColor(float r, float g, float b, float a) {
		glClearColor(r, g, b, a);
	}

	void GLCommand::setViewPortSize(size_t x, size_t y, size_t w, size_t h) {
		glViewport(x, y, w, h);
	}

	void GLCommand::clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void GLCommand::setLineMode(bool enable) {
		if (enable) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}

}
}