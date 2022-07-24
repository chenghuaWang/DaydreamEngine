#ifndef H_RENDER_CORE_OBJECT_BASIC
#define H_RENDER_CORE_OBJECT_BASIC

#ifdef _MSC_VER > 1000
#pragma once
#endif

///< Shader has already include the drawObj.hpp
#include "d_render/core/shader.hpp"

namespace daydream {
	namespace renderer {

		/*!
		 *@brie The plane object is just a flat.
		 *
		 * DLL EXPORT: True
		 *
		 * @details This object will shown by default in every 3d scene.
		 * A speciall shader is working for it.
		 * Like Screen space shader. The shader is managed by this class it
		 * self, and this class will only has one instance in the scene. Note
		 * that, you are not recommand to use d_resource lib to manage the
		 * shader belong to this class.
		 */
		class D_API_EXPORT PlaneObject : public drawObject {
		public:
			PlaneObject();

			void draw() override;
			void update() override;

			static PlaneObject* getInstance();

		private:
			int					m_GridInternal;
			// TODO VAO, VBO.
			REF(Shader)			m_shader;
			static PlaneObject* m_instance;
		};
	}
}

#endif // !H_RENDER_CORE_OBJECT_BASIC
