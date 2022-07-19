#ifndef H_CORE_OBJ_
#define H_CORE_OBJ_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "d_render/core/_gl_head.hpp"
#include "d_render/utils/crates.hpp"

namespace daydream {
	namespace renderer {


		class D_API_EXPORT drawObject {
		public:
			virtual void draw() {};
			virtual void update() {};

		public:
			static Crates	*renderPayload;
		};
	}
}

#endif // !H_CORE_OBJ_
