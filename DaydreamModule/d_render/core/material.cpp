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
		// Vertex data should not passed here.
		// start pass Fragment data
	}

	void _obj_material::UnBind() {
		m_shader->UnBind();
	}

	void _obj_material::_resetTexture(REF(Texture2D)& t, const std::string& p) {
		if (p.empty()) {
			///< When empty, create a black Texture.
			t.reset();
			t = Texture2D::create(1, 1);
			uint32_t data = 0xffffffff;
			t->resetData(&data, sizeof(uint32_t));
		}
		else {
			t.reset();
			t = Texture2D::create(p);
		}
		return;
	}

	// -------------------- BELOW FOR PHONG MATERIAL --------------------------

	MaterialPhong::MaterialPhong():
		_obj_material(Shader::create("../Asset/shader/phongObj.glsl")) {
		m_type = MaterialType::Phong;
	}

	MaterialPhong::MaterialPhong(
		REF(Texture2D)& diffuse, 
		REF(Texture2D)& specular, 
		REF(Texture2D)& Normal, 
		REF(Texture2D)& displacement, 
		float height, // defualt = 0
		float shine, // default = 32
		glm::vec3& color): // default = { 1.0f }
		m_DiffuseTexture(diffuse), m_SpecularTexture(specular), m_NormalTexture(Normal),
		m_DisplacementTexture(displacement), m_HeightScale(height), m_Shininess(shine),
		m_Color(color),
		_obj_material(Shader::create("../Asset/shader/phongObj.glsl")){
		m_type = MaterialType::Phong;
	}

	MaterialPhong::MaterialPhong(
		const std::string& diffuse_p, 
		const std::string& specular_p, 
		const std::string& normal_p, 
		const std::string& displacement_p, 
		float height, // defualt = 0
		float shine, // default = 32
		glm::vec3& color): // default = { 1.0f }
		m_DiffuseTexture(Texture2D::create(diffuse_p)),
		m_SpecularTexture(Texture2D::create(specular_p)),
		m_NormalTexture(Texture2D::create(normal_p)),
		m_DisplacementTexture(Texture2D::create(displacement_p)),
		m_Color(color),
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

	void MaterialPhong::resetDiffuseTexture(const std::string& p) {
		this->_resetTexture(m_DiffuseTexture, p);
	}

	void MaterialPhong::resetDiffuseTexture(void* data, uint32_t size) {
		// TODO The image size shoulf first be set to (1.0, 1.0)
		m_DiffuseTexture->resetData(data, size);
	}

	void MaterialPhong::resetSpecularTexture(const std::string& p) {
		this->_resetTexture(m_SpecularTexture, p);
	}

	void MaterialPhong::resetSpecularTexture(void* data, uint32_t size) {
		// TODO The image size shoulf first be set to (1.0, 1.0)
		m_SpecularTexture->resetData(data, size);
	}

	void MaterialPhong::resetNormalTexture(const std::string& p) {
		this->_resetTexture(m_NormalTexture, p);
	}

	void MaterialPhong::resetNormalTexture(void* data, uint32_t size) {
		// TODO The image size shoulf first be set to (1.0, 1.0)
		m_NormalTexture->resetData(data, size);
	}

	void MaterialPhong::resetDisplacementTexture(const std::string& p) {
		this->_resetTexture(m_DisplacementTexture, p);
	}

	void MaterialPhong::resetDisplacementTexture(void* data, uint32_t size) {
		// TODO The image size shoulf first be set to (1.0, 1.0)
		m_DisplacementTexture->resetData(data, size);
	}

	void MaterialPhong::resetHeightScale(float v) {
		m_HeightScale = v;
	}

	void MaterialPhong::rsetShiness(float v) {
		m_Shininess = v;
	}

	void MaterialPhong::resetColor(const glm::vec3& v) {
		m_Color = v;
	}

	// -------------------- BELOW FOR BRDF-NAIVE MATERIAL ---------------------

	MaterialBRDF::MaterialBRDF():
		_obj_material(Shader::create("../Asset/shader/pbrObj.glsl")) {
		m_type = MaterialType::BRDF_naive;
	}

	MaterialBRDF::MaterialBRDF(
		REF(Texture2D) albedo, 
		REF(Texture2D) noraml, 
		REF(Texture2D) roughness, 
		REF(Texture2D) metallic, 
		REF(Texture2D) ao, 
		REF(Texture2D) displament, 
		float height_f, 
		float metallic_f, 
		float rough_f): 
		m_AlbedoTexture(albedo), m_NormalTexture(noraml), m_RoughnessTexture(roughness),
		m_MetallicTexture(metallic), m_AOTexture(ao), m_DisplacementTexture(displament),
		m_HeightScale(height_f), m_Metallic(metallic_f), m_Roughness(rough_f),
		_obj_material(Shader::create("../Asset/shader/pbrObj.glsl")) {
		m_type = MaterialType::BRDF_naive;
	}

	MaterialBRDF::MaterialBRDF(
		const std::string& albedo_p, 
		const std::string& noraml_p, 
		const std::string& roughness_p, 
		const std::string& metallic_p, 
		const std::string& ao_p, 
		const std::string& displament_p, 
		float height_f, 
		float metallic_f, 
		float rough_f):
		m_AlbedoTexture(Texture2D::create(albedo_p)),
		m_NormalTexture(Texture2D::create(noraml_p)),
		m_RoughnessTexture(Texture2D::create(roughness_p)),
		m_MetallicTexture(Texture2D::create(metallic_p)),
		m_AOTexture(Texture2D::create(ao_p)),
		m_DisplacementTexture(Texture2D::create(displament_p)),
		m_HeightScale(height_f), m_Metallic(metallic_f), m_Roughness(rough_f),
		_obj_material(Shader::create("../Asset/shader/pbrObj.glsl")) {
		m_type = MaterialType::BRDF_naive;
	}

	MaterialBRDF::~MaterialBRDF() {
		// TODO
	}

	void MaterialBRDF::Bind() {
		m_shader->Bind();
		// TODO pass the value to shader.
	}

	void MaterialBRDF::UnBind() {
		m_shader->UnBind();
		// TODO other clean stuff.
	}

	void MaterialBRDF::resetHeightScale(float v) {
		m_HeightScale = v;
	}

	void MaterialBRDF::resetMetallic(float v) {
		m_Metallic = v;
	}

	void MaterialBRDF::resetRoughness(float v) {
		m_Roughness = v;
	}

	void MaterialBRDF::resetColor(const glm::vec3& v) {
		m_Color = v;
	}

	void MaterialBRDF::restAlbedoTexture(const std::string& p) {
		this->_resetTexture(m_AlbedoTexture, p);
	}

	void MaterialBRDF::resetAlbedoTexture(void* data, uint32_t size) {
		// TODO make sure image data size is same.
		m_AlbedoTexture->resetData(data, size);
	}

	void MaterialBRDF::restNormalTexture(const std::string& p) {
		this->_resetTexture(m_NormalTexture, p);
	}

	void MaterialBRDF::resetNormalTexture(void* data, uint32_t size) {
		// TODO make sure image data size is same.
		m_NormalTexture->resetData(data, size);
	}

	void MaterialBRDF::restMetallicTexture(const std::string& p) {
		this->_resetTexture(m_MetallicTexture, p);
	}

	void MaterialBRDF::resetMetallicTexture(void* data, uint32_t size) {
		// TODO make sure image data size is same.
		m_MetallicTexture->resetData(data, size);
	}

	void MaterialBRDF::restRoughnessTexture(const std::string& p) {
		this->_resetTexture(m_RoughnessTexture, p);
	}

	void MaterialBRDF::restRoughnessTexture(void* data, uint32_t size) {
		// TODO make sure image data size is same.
		m_RoughnessTexture->resetData(data, size);
	}

	void MaterialBRDF::restAOTexture(const std::string& p) {
		this->_resetTexture(m_AOTexture, p);
	}

	void MaterialBRDF::resetAOTexture(void* data, uint32_t size) {
		// TODO make sure image data size is same.
		m_AOTexture->resetData(data, size);
	}

	void MaterialBRDF::restDisplacementTexture(const std::string& p) {
		this->_resetTexture(m_DisplacementTexture, p);
	}

	void MaterialBRDF::restDisplacementTexture(void* data, uint32_t size) {
		// TODO make sure image data size is same.
		m_DisplacementTexture->resetData(data, size);
	}

	// -------------------- BELOW FOR SELF DEFINED MATERIAL ---------------------

	MaterialSelfDefined::MaterialSelfDefined():
		_obj_material() {
		m_type = MaterialType::Self_defined;
	}

	MaterialSelfDefined::~MaterialSelfDefined() {
		// TODO
	}

	void MaterialSelfDefined::addValue(const std::string& key, float value) {
		m_values[key] = value;
	}

	void MaterialSelfDefined::addShader(const std::string& key, REF(Shader)& value) {
		m_shaders[key] = value;
	}

	void MaterialSelfDefined::addTexture(const std::string& key, REF(Texture2D)& value) {
		m_textures[key] = value;
	}

	void MaterialSelfDefined::deleteValue(const std::string& key) {
		m_values.erase(key);
	}

	void MaterialSelfDefined::deleteShader(const std::string& key) {
		m_shaders.erase(key);
	}

	void MaterialSelfDefined::deleteTexture(const std::string& key) {
		m_textures.erase(key);
	}

	void MaterialSelfDefined::resetValue(const std::string& key, float value) {
		m_values[key] = value;
	}

	void MaterialSelfDefined::resetShader(const std::string& key, REF(Shader)& value) {
		m_shaders[key] = value;
	}

	void MaterialSelfDefined::resetTexture(const std::string& key, REF(Texture2D)& value) {
		m_textures[key] = value;
	}


} //! namespace daydream
} //! namespace renderer
