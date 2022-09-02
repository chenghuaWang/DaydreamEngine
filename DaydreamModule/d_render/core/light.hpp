#ifndef H_RENDER_CORE_LIGHT
#define H_RENDER_CORE_LIGHT

#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER > 1000

#include <glm/glm.hpp>

#include "d_core/pch.hpp"
#include "d_render/core/shader.hpp"

namespace daydream {
namespace renderer {

enum class D_API_EXPORT LightType { None = 0, Direct, Point, Spot, Basic, Self_defined };

/*!
 * @brief light is an attribute of a Drawable Model.
 * So, light don't need to contain the position info-
 * mation.
 */
class D_API_EXPORT _obj_light {
 public:
  _obj_light();
  _obj_light(glm::vec3& color, float intensity = 1.f);

  void resetColor(glm::vec3& v);
  void resetIntensity(float v);
  LightType Type() const;

  virtual void Bind(const REF(Shader) & shader, const glm::vec3& pos, const uint32_t port);
  virtual void UnBind(const REF(Shader) & shader);

 protected:
  float m_intensity = 1.f;
  LightType m_type = LightType::None;
  glm::vec3 m_color{1.f};
};

class LightDirect : public _obj_light {
 public:
  LightDirect();
  LightDirect(const glm::vec3& direction);

  void resetDirection(const glm::vec3& v);

  void Bind(const REF(Shader) & shader, const glm::vec3& pos, const uint32_t port) override;

 private:
  glm::vec3 m_direction{0.f, 0.f, 1.f};
};

class LightPoint : public _obj_light {
 public:
  LightPoint();
  LightPoint(float constant, float linear, float quadratic);

  void Bind(const REF(Shader) & shader, const glm::vec3& pos, const uint32_t port) override;

  void resetConstant(float v);
  void resetLinear(float v);
  void resetQuadratic(float v);

 private:
  ///< The parameters of qX^2 + lX + c for mixing spot light.
  float m_constant = 1.0f;
  float m_linear = 0.09f;
  float m_quadratic = 0.032f;
};

class LightSpot : public _obj_light {
 public:
  LightSpot();
  LightSpot(float cutoff, float outcutoff, const glm::vec3& direction);

  void Bind(const REF(Shader) & shader, const glm::vec3& pos, const uint32_t port) override;

  void resetCutOff(float v);
  void resetCutOff_radians(float v);

  void resetOutCutOff(float v);
  void resetOutCutOff_radians(float v);

  void resetDirection(const glm::vec3& v);

 private:
  float m_cutoff = glm::cos(glm::radians(12.5f));
  float m_outCutoff = glm::cos(glm::radians(17.5f));
  glm::vec3 m_direction{0.f, 0.f, 1.f};
};

class LightBasic : public _obj_light {
  // Basic is defualt behavior in _obj_light;
};

class LightSelfDefined : public _obj_light {
 public:
 private:
};

}  // namespace renderer
}  // namespace daydream

#endif  // !H_RENDER_CORE_LIGHT
