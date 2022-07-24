#include "basicObj.hpp"

namespace daydream {
	namespace renderer {
		PlaneObject* PlaneObject::m_instance = nullptr;

		PlaneObject::PlaneObject() {
			m_shader = Shader::create("../Asset/shader/PlaneObj.glsl");
		}

		void PlaneObject::draw() {
			m_shader->Bind();
			// TODO bind shader and bind data.
			m_shader->UnBind();
		}

		void PlaneObject::update() {

		}

		PlaneObject* PlaneObject::getInstance() {
			return m_instance;
		}

	}
}