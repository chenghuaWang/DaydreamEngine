#ifndef H_RENDER_CORE_MATERIAL
#define H_RENDER_CORE_MATERIAL

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <glm/glm.hpp>

#include "d_core/pch.hpp"
#include "d_render/core/shader.hpp"
#include "d_render/core/texture.hpp"

namespace daydream {
namespace renderer {

	enum class D_API_EXPORT MaterialType {
		None = 0, ///< None for default
		Phong,
		BRDF_naive,
		Self_defined
	};

	/*!
	 * @brief Material is a top high-levle structure contain Texture and Shader
	 * 
	 * The _obj_material is the father class for all materials. Only one default
	 * shader is contained in this class by default. No default texture is contain
	 * in. Other class inherient from this class should manage all shader and tex-
	 * tures.
	 */
	class D_API_EXPORT _obj_material {
	public:
		_obj_material();
		_obj_material(REF(Shader)& shader);
		virtual ~_obj_material() = default;
		virtual void Bind(); //TODO pass the skybox to this fucntion.
		virtual void UnBind();

	protected:
		MaterialType	m_type;
		REF(Shader)		m_shader;
	};

	class D_API_EXPORT MaterialPhong :public _obj_material {
	public:
		MaterialPhong(); ///< phong GLSL is init in.
		~MaterialPhong();

		void Bind() override; //TODO pass the skybox to this fucntion.
		void UnBind() override;

		void resetDiffuseTexture(void* data, uint32_t size);
		void resetSpecularTexture(void* data, uint32_t size);
		void resetNormalTexture(void* data, uint32_t size);
		void resetDisplacementTexture(void* data, uint32_t size);


	private:
		float				m_HeightScale = 0;
		float				m_Shininess = 32;
		glm::vec3			m_Color{ 1.0f };
		REF(Texture2D)		m_DiffuseTexture = nullptr;
		REF(Texture2D)		m_SpecularTexture = nullptr;
		REF(Texture2D)		m_NormalTexture = nullptr;
		REF(Texture2D)		m_DisplacementTexture = nullptr;
	};

	class D_API_EXPORT MaterialBRDF :public _obj_material {
	public:

	private:

	};

	class D_API_EXPORT MaterialSelfDefined :public _obj_material {
	public:

	private:

	};

}
}

#endif // !H_RENDER_CORE_MATERIAL
