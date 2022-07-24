#include "sky.hpp"

namespace daydream {
	namespace renderer {
		ScreenSpaceSkyBox::ScreenSpaceSkyBox():
			m_skyColorBottom(0.9, 0.9, 0.95),
			m_skyColorTop(0.525, 0.735, 0.9975) {
			m_spShader = CREATE_REF(ScreenSpaceShader)("../Asset/shader/sky.frag");
			m_FBO = CREATE_REF(FrameBuffer)(100.f, 100.f);
			sunsetPreset_1();
			defaultPreset();
		}

		ScreenSpaceSkyBox::~ScreenSpaceSkyBox() {

		}

		colorPreset ScreenSpaceSkyBox::defaultPreset() {
			return colorPreset();
		}

		colorPreset ScreenSpaceSkyBox::sunsetPreset_1() {
			return colorPreset();
		}

		colorPreset ScreenSpaceSkyBox::sunsetPreset_2() {
			return colorPreset();
		}

		void ScreenSpaceSkyBox::mixPresets(float v, const colorPreset& p1, const colorPreset& p2) {

		}

		unsigned int ScreenSpaceSkyBox::getTextureID() {
			return m_FBO->FrameIdx();
		}

		void ScreenSpaceSkyBox::OnResize(float w, float h) {
			m_FBO->Resize(w, h);
		}

		void ScreenSpaceSkyBox::draw() {

		}

		void ScreenSpaceSkyBox::update() {
		}

	}
}
