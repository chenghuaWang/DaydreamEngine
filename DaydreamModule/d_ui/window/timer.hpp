#ifndef H_RENDER_TIMER
#define H_RENDER_TIMER

#if _MSC_VER > 1000
#pragma once
#endif

#include "d_core/pch.hpp"

namespace daydream {
namespace ui {

	class D_API_EXPORT Timer {
	public:
		void OnUpdate();

		float getGlobalTime();
		float getTimeDelta();

		void stop();
		void start();
		void setRunning(bool enable);

	private:
		bool m_running = true;
		float m__cur_frame_time = 0.f;
		float m__pre_frame_time = 0.f;
		float m_GlobalTime = 0.f;
		float m_TimeDelta = 0.f;

		float stoppingPoint = 0.f;
		float stopTimeCnt = 0.f;
		float out_GloabalTime = 0.f;
	};

}
}

#endif // !H_RENDER_TIMER
