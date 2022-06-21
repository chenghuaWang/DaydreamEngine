#ifndef H_DCORE_DS
#define H_DCORE_DS

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "_gl_head.hpp"

namespace daydream {
namespace renderer {

	class D_API_EXPORT FrameBuffer {
	public:
		FrameBuffer(float w, float h, float samples = 1, bool swapChain = false);
		~FrameBuffer();

		void Invalidate();
		void Bind();
		void UnBind();
		void Resize(float w, float h);

		uint32_t& FrameIdx();

	private:
		float	m_w, m_h;
		float	m_sampels = 1;
		bool	m_swapChain = false;

		uint32_t	m_idx = 0;
		uint32_t	m_ColorAttach = 0;
		uint32_t	m_DepthAttach = 0;
	};

}
}


#endif // !H_DCORE_DS
