#ifndef H_CAMERA
#define H_CAMERA

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "d_core/pch.hpp"

namespace daydream {
namespace renderer {

	class D_API_EXPORT camera_obj {
	public:
		camera_obj(float w, float h);

		void set_w(float a);
		void set_h(float a);
		float get_w();
		float get_h();

		float get_aspect();

		bool is_activited();
		void set_activited(bool enable);

	public:
		bool	m_activated;
		float	m_w, m_h;
		float	m_aspect;
	};

	class D_API_EXPORT camera2d :public camera_obj {
	public:
		camera2d(float w, float h, const std::string& name);

		void set_idx(float a);
		void reset_name(const std::string &name);

		float get_idx() const;
		const std::string& get_name() const;

	private:
		float		m_idx;
		std::string m_name;
	};

	class D_API_EXPORT camera3d :public camera_obj {
		// TODO. Also for 2d, no ctrl needed. But 3d camera need a event aware contoler.
	};

}
}

#endif // !H_CAMERA
