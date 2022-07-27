#include "scene3d.hpp"

namespace daydream {
	namespace scene {
		scene3d::scene3d(float w, float h) :m_camera_ctrl(camera3d(w, h, "dropped")) {
			std::cout << "[ Warn ]This class init method [float w, float h] is not support anymore.\n \
You should define Crates(in render lib) first, and pass it to this class \n \
Using scene3d::scene3drenderer::Crates& crates) function !" << std::endl;
			LOG_WARN("[ Warn ]This class init method [float w, float h] is not support anymore.\n \
You should define Crates(in render lib) first, and pass it to this class \n \
Using scene3d::scene3drenderer::Crates& crates) function !");
		}

		scene3d::scene3d(renderer::Crates& crates) :m_crates(crates), m_camera_ctrl(*crates.mainCamera) {
			std::cout << "[ INFO ] crates registered. " << std::endl;
			LOG_INFO("[ INFO ] crates registered. ");
		}

		void scene3d::Resize(float w, float h) {
			m_camera_ctrl.OnResize(w, h);
			m_crates.sceneFBO->Resize(w, h);
		}

		void scene3d::BeginRender() {
			m_crates.sceneFBO->Bind();
			renderer::GLCommand::setColor(0.f, 0.5f, 0.f, 1.f);
			renderer::GLCommand::clear();
			// TODO A drawable objs' table should be passed here.
		}

		void scene3d::EndRender() {
			renderer::GLCommand::setLineMode(m_LineMode);
			m_crates.sceneFBO->UnBind();
		}

		void scene3d::setLineMode(bool enable) {
			m_LineMode = enable;
		}

		bool scene3d::isLineMode() {
			return m_LineMode;
		}

		void scene3d::setRunning(bool enable) {
			m_running = enable;
		}

		uint32_t scene3d::FrameIdx() {
			return m_crates.sceneFBO->FrameIdx();
		}

		camera3dController& scene3d::getCameraCtrl() {
			return m_camera_ctrl;
		}

	}
}