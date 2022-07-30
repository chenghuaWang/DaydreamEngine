#ifndef H_RENDER_UTIlS_DS
#define H_RENDER_UTIlS_DS

#ifdef _MSC_VER > 1000
#pragma once
#endif

#include "d_core/pch.hpp"
#include "glm/glm.hpp"

namespace daydream {
	namespace renderer {

		struct D_API_EXPORT Vertex {
			glm::vec3	m_Position;
			glm::vec2	m_TexCoord;
			glm::vec3	m_Normal;
			glm::vec3	m_Tangent;

			bool operator == (const Vertex& v) const {
				return m_Position == v.m_Position &&
					m_TexCoord == v.m_TexCoord &&
					m_Normal == v.m_Normal;
			};
		};

		struct D_API_EXPORT Triangle {
			uint32_t	a;
			uint32_t	b;
			uint32_t	c;
		};

	}
}

#endif // !H_RENDER_UTIlS_DS
