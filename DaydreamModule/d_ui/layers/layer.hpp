#ifndef H_UI_LAYER
#define H_UI_LAYER

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "d_core/pch.hpp"

namespace daydream {
namespace ui {

	class D_API_EXPORT base_layer {
	public:
		base_layer(const std::string &name);

	public:
		virtual void update() {}; ///< for event
		virtual void impl_imgui_render() {}; ///< for imgui frame

	private:
		unsigned int	m_idx;
		std::string		m_name;
	};

} // !namespace daydream
} // !namespace daydream

#endif // H_UI_LAYER
