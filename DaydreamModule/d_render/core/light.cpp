#include "light.hpp"

namespace daydream {
namespace renderer {
	
	_obj_light::_obj_light() {

	}

	_obj_light::_obj_light(glm::vec3& color, float intensity):
		m_color(color), m_intensity(intensity) {

	}

	void _obj_light::resetColor(glm::vec3& v) {
		m_color = v;
	}

	void _obj_light::resetIntensity(float v) {
		m_intensity = v;
	}

	void _obj_light::Bind(const REF(Shader)& shader, const glm::vec3& pos, const uint32_t port) {
		shader->Bind();
		shader->setVec3("d_Light[" + std::to_string(port) + "].Color", m_color);
		shader->setVec3("d_Light[" + std::to_string(port) + "].Position", pos);
		shader->setFloat("d_Light[" + std::to_string(port) + "].Intensity", m_intensity);
	}

	void _obj_light::UnBind(const REF(Shader)& shader) {
		shader->UnBind();
	}

	// -------------------------- Light Direction type ------------------------------

	LightDirect::LightDirect() {
		m_type = LightType::Direct;
	}

	LightDirect::LightDirect(const glm::vec3& direction):
		m_direction(direction) {
		m_type = LightType::Direct;
	}

	void LightDirect::resetDirection(const glm::vec3& v) {
		m_direction = v;
	}

	void LightDirect::Bind(const REF(Shader)& shader, const glm::vec3& pos, const uint32_t port) {
		shader->Bind();
		shader->setVec3("d_Light_direct[" + std::to_string(port) + "].Color", m_color);
		shader->setVec3("d_Light_direct[" + std::to_string(port) + "].Direction", m_direction);
		shader->setFloat("d_Light_direct[" + std::to_string(port) + "].Intensity", m_intensity);
	}

	// -------------------------- Light Point type ------------------------------

	LightPoint::LightPoint() {
		m_type = LightType::Point;
	}

	LightPoint::LightPoint(float constant, float linear, float quadratic):
		m_constant(constant), m_linear(linear), m_quadratic(quadratic) {
		m_type = LightType::Point;
	}

	void LightPoint::Bind(const REF(Shader)& shader, const glm::vec3& pos, const uint32_t port) {
		shader->Bind();
		shader->setVec3("d_Light_point[" + std::to_string(port) + "].Color", m_color);
		shader->setVec3("d_Light_point[" + std::to_string(port) + "].Position", pos);
		shader->setFloat("d_Light_point[" + std::to_string(port) + "].Intensity", m_intensity);
		shader->setFloat("d_Light_point[" + std::to_string(port) + "].Constant", m_constant);
		shader->setFloat("d_Light_point[" + std::to_string(port) + "].Linear", m_linear);
		shader->setFloat("d_Light_point[" + std::to_string(port) + "].Quadratic", m_quadratic);
	}

	void LightPoint::resetConstant(float v) {
		m_constant = v;
	}

	void LightPoint::resetLinear(float v) {
		m_linear = v;
	}

	void LightPoint::resetQuadratic(float v) {
		m_quadratic = v;
	}

	// -------------------------- Light Spot type ------------------------------

	LightSpot::LightSpot() {
		m_type = LightType::Spot;
	}

	LightSpot::LightSpot(float cutoff, float outcutoff, const glm::vec3& direction): 
		m_cutoff(cutoff), m_outCutoff(outcutoff), m_direction(direction) {
		m_type = LightType::Spot;
	}

	void LightSpot::Bind(const REF(Shader)& shader, const glm::vec3& pos, const uint32_t port) {
		shader->Bind();
		shader->setVec3("d_Light_spot[" + std::to_string(port) + "].Color", m_color);
		shader->setVec3("d_Light_spot[" + std::to_string(port) + "].Position", pos);
		shader->setVec3("d_Light_spot[" + std::to_string(port) + "].Direction", m_direction);
		shader->setFloat("d_Light_spot[" + std::to_string(port) + "].Intensity", m_intensity);
		shader->setFloat("d_Light_spot[" + std::to_string(port) + "].CutOff", m_cutoff);
		shader->setFloat("d_Light_spot[" + std::to_string(port) + "].OutCutOff", m_outCutoff);
	}

	void LightSpot::resetCutOff(float v) {
		m_cutoff = v;
	}

	void LightSpot::resetCutOff_radians(float v) {
		m_cutoff = glm::cos(glm::radians(v));
	}

	void LightSpot::resetOutCutOff(float v) {
		m_outCutoff = v;
	}

	void LightSpot::resetOutCutOff_radians(float v) {
		m_outCutoff = glm::cos(glm::radians(v));
	}

	void LightSpot::resetDirection(const glm::vec3& v) {
		m_direction = v;
	}

} //! namespace renderer
} //! namespace daydream
