#include "timer.hpp"
#include "GLFW/glfw3.h"
namespace daydream {
namespace ui {

	void Timer::OnUpdate() {
		m__cur_frame_time = (float)glfwGetTime();
		m_GlobalTime = m__cur_frame_time;
		m_TimeDelta = m__cur_frame_time - m__pre_frame_time;
		m__pre_frame_time = m__cur_frame_time;

		if (m_running) {
			out_GloabalTime = m_GlobalTime - stopTimeCnt;
		}
		else {
			out_GloabalTime = stoppingPoint;
		}
	}

	float Timer::getGlobalTime() {
		return out_GloabalTime;
	}

	float Timer::getTimeDelta() {
		return m_TimeDelta;
	}

	void Timer::stop() {
		if (m_running != false) {
			setRunning(false);
			stoppingPoint = m_GlobalTime;
		}
	}

	void Timer::start() {
		if (m_running != true) {
			setRunning(true);
			stopTimeCnt += (m_GlobalTime - stoppingPoint);
		}
	}

	void Timer::setRunning(bool enable) {
		m_running = enable;
	}

}
}

