#include "material.hpp"

namespace daydream {
namespace renderer {

	// -------------------- BELOW FOR BASIC MATERIAL --------------------------

	_obj_material::_obj_material():
		m_shader(Shader::create("../Asset/shader/defaultObj.glsl")),
		m_type(MaterialType::None) {
	}

	_obj_material::_obj_material(REF(Shader)& shader):
		m_shader(shader),
		m_type(MaterialType::None) {
	}

	void _obj_material::Bind() {
		m_shader->Bind();
	}

	void _obj_material::UnBind() {
		m_shader->UnBind();
	}

	// -------------------- BELOW FOR PHONG MATERIAL --------------------------

	MaterialPhong::MaterialPhong():
		_obj_material(Shader::create("../Asset/shader/phongObj.glsl")) {
		m_type = MaterialType::Phong;
	}

	MaterialPhong::~MaterialPhong() {
		// TODO
	}

	void MaterialPhong::Bind() {
		// TODO
	}

	void MaterialPhong::UnBind() {
		// TODO
		m_shader->UnBind();
	}

	void MaterialPhong::resetDiffuseTexture(void* data, uint32_t size) {
		// TODO The image size shoulf first be set to (1.0, 1.0)
		m_DiffuseTexture->resetData(data, size);
	}

	void MaterialPhong::resetSpecularTexture(void* data, uint32_t size) {
		// TODO The image size shoulf first be set to (1.0, 1.0)
		m_SpecularTexture->resetData(data, size);
	}

	void MaterialPhong::resetNormalTexture(void* data, uint32_t size) {
		// TODO The image size shoulf first be set to (1.0, 1.0)
		m_NormalTexture->resetData(data, size);
	}

	void MaterialPhong::resetDisplacementTexture(void* data, uint32_t size) {
		// TODO The image size shoulf first be set to (1.0, 1.0)
		m_DisplacementTexture->resetData(data, size);
	}

	// -------------------- BELOW FOR BRDF-NAIVE MATERIAL ---------------------

} //! namespace daydream
} //! namespace renderer
