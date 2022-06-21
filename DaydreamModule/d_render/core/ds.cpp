#include "ds.hpp"

namespace daydream {
namespace renderer {
	
	FrameBuffer::FrameBuffer(float w, float h, float samples, bool swapChain):
		m_w(w), m_h(h), m_sampels(samples), m_swapChain(swapChain), m_idx(0) {
		Invalidate();
	}

	FrameBuffer::~FrameBuffer() {
		// Release memory from opengl state machine
		glDeleteFramebuffers(1, &m_idx);
		glDeleteTextures(1, &m_ColorAttach);
		glDeleteTextures(1, &m_DepthAttach);
	}

	void FrameBuffer::Invalidate() {
		// Delete current buffers if exists.
		if (m_idx) {
			glDeleteFramebuffers(1, &m_idx);
			glDeleteTextures(1, &m_ColorAttach);
			glDeleteTextures(1, &m_DepthAttach);
		}
		// For FrameBuffers.
		glCreateFramebuffers(1, &m_idx);
		glBindFramebuffer(GL_FRAMEBUFFER, m_idx);
		// Create Color Buffers
		glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttach);
		glBindTexture(GL_TEXTURE_2D, m_ColorAttach);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_w, m_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttach, 0);
		// Create Depth Buffers
		glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttach);
		glBindTexture(GL_TEXTURE_2D, m_DepthAttach);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_w, m_h);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttach, 0);
		// Unbind to 0.
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void FrameBuffer::Bind() {
		glBindFramebuffer(GL_FRAMEBUFFER, m_idx);
		glViewport(0, 0, m_w, m_h);
	}

	void FrameBuffer::UnBind() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void FrameBuffer::Resize(float w, float h) {
		m_w = w, m_h = h;
		Invalidate();
	}

	uint32_t FrameBuffer::FrameIdx() {
		return m_ColorAttach;
	}

}
}
