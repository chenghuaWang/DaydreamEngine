#include "camera.hpp"

namespace daydream {
namespace renderer {

	camera_obj::camera_obj(float w, float h):m_w(w), m_h(h), m_aspect((float)w/(float)h) {
	}

	void camera_obj::set_w(float a) {
		m_w = a;
		m_aspect = m_w / m_h;
	}

	void camera_obj::set_h(float a) {
		m_h = a;
		m_aspect = m_w / m_h;
	}

	float camera_obj::get_w() {
		return m_w;
	}

	float camera_obj::get_h() {
		return m_h;
	}

	float camera_obj::get_aspect() {
		return m_aspect;
	}

	bool camera_obj::is_activited() {
		return m_activated;
	}

	void camera_obj::set_activited(bool enable) {
		m_activated = enable;
	}

	camera2d::camera2d(float w, float h, const std::string& name):camera_obj(w, h), m_name(name), m_idx(0) {
	}

	void camera2d::set_idx(float a) {
		m_idx = a;
	}

	void camera2d::reset_name(const std::string& name) {
		m_name = name;
	}

	float camera2d::get_idx() const {
		return m_idx;
	}

	const std::string& camera2d::get_name() const {
		return m_name;
	}

}
}
