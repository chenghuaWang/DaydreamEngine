#ifndef H_RENDER_CORE_MATERIAL
#define H_RENDER_CORE_MATERIAL

#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER > 1000

#include <glm/glm.hpp>

#include "d_core/pch.hpp"
#include "d_render/core/shader.hpp"
#include "d_render/core/texture.hpp"

namespace daydream {
namespace renderer {

enum class D_API_EXPORT MaterialType {
  None = 0,  ///< None for default
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
  _obj_material(const REF(Shader) & shader);
  virtual ~_obj_material() = default;
  virtual void Bind();  // TODO pass the skybox to this fucntion.
  virtual void UnBind();

  void SetShader(const REF(Shader) & s);
  REF(Shader) GetShader();

 protected:
  void _resetTexture(REF(Texture2D) & t, const std::string& p = std::string());

  MaterialType m_type;
  REF(Shader) m_shader;
};

class D_API_EXPORT MaterialPhong : public _obj_material {
 public:
  MaterialPhong();  ///< phong GLSL is init in.
  MaterialPhong(REF(Texture2D) & diffuse, REF(Texture2D) & specular, REF(Texture2D) & Normal,
                REF(Texture2D) & displacement, float height = 0, float shine = 32,
                glm::vec3& color = glm::vec3{1.0f});
  MaterialPhong(const std::string& diffuse_p, const std::string& specular_p,
                const std::string& normal_p, const std::string& displacement_p, float height = 0,
                float shine = 32, glm::vec3& color = glm::vec3{1.0f});

  ~MaterialPhong();

  void Bind() override;  // TODO pass the skybox to this fucntion. For env specular.
  void UnBind() override;

  void resetDiffuseTexture(const std::string& p);
  void resetDiffuseTexture(void* data, uint32_t size);
  void resetDiffuseTexture(const REF(Texture2D) & a);

  void resetSpecularTexture(const std::string& p);
  void resetSpecularTexture(void* data, uint32_t size);
  void resetSpecularTexture(const REF(Texture2D) & a);

  void resetNormalTexture(const std::string& p);
  void resetNormalTexture(void* data, uint32_t size);
  void resetNormalTexture(const REF(Texture2D) & a);

  void resetDisplacementTexture(const std::string& p);
  void resetDisplacementTexture(void* data, uint32_t size);
  void resetDisplacementTexture(const REF(Texture2D) & a);

  void resetHeightScale(float v);
  void rsetShiness(float v);
  void resetColor(const glm::vec3& v);

 private:
  float m_HeightScale = 0;
  float m_Shininess = 32;
  glm::vec3 m_Color{1.0f};
  REF(Texture2D) m_DiffuseTexture = nullptr;
  REF(Texture2D) m_SpecularTexture = nullptr;
  REF(Texture2D) m_NormalTexture = nullptr;
  REF(Texture2D) m_DisplacementTexture = nullptr;
};

class D_API_EXPORT MaterialBRDF : public _obj_material {
 public:
  MaterialBRDF();
  MaterialBRDF(REF(Texture2D) albedo, REF(Texture2D) noraml, REF(Texture2D) roughness,
               REF(Texture2D) metallic, REF(Texture2D) ao, REF(Texture2D) displament,
               float height_f = 0.f, float metallic_f = 1.f, float rough_f = 1.f);
  MaterialBRDF(const std::string& albedo_p, const std::string& noraml_p,
               const std::string& roughness_p, const std::string& metallic_p,
               const std::string& ao_p, const std::string& displament_p, float height_f = 0.f,
               float metallic_f = 1.f, float rough_f = 1.f);

  ~MaterialBRDF();

  void Bind() override;  // TODO pass the skybox to this fucntion. For env specular.
  void UnBind() override;

  void resetHeightScale(float v);
  void resetMetallic(float v);
  void resetRoughness(float v);
  void resetColor(const glm::vec3& v);

  void restAlbedoTexture(const std::string& p);
  void resetAlbedoTexture(void* data, uint32_t size);
  void resetAlbedoTexture(const REF(Texture2D) & a);

  void restNormalTexture(const std::string& p);
  void resetNormalTexture(void* data, uint32_t size);
  void resetNormalTexture(const REF(Texture2D) & a);

  void restMetallicTexture(const std::string& p);
  void resetMetallicTexture(void* data, uint32_t size);
  void resetMetallicTexture(const REF(Texture2D) & a);

  void restRoughnessTexture(const std::string& p);
  void restRoughnessTexture(void* data, uint32_t size);
  void resetRoughnessTexture(const REF(Texture2D) & a);

  void restAOTexture(const std::string& p);
  void resetAOTexture(void* data, uint32_t size);
  void resetAOTexture(const REF(Texture2D) & a);

  void restDisplacementTexture(const std::string& p);
  void restDisplacementTexture(void* data, uint32_t size);
  void resetDisplacementTexture(const REF(Texture2D) & a);

 private:
  float m_HeightScale = 0.0f;
  float m_Metallic = 1.0f;
  float m_Roughness = 1.0f;
  glm::vec3 m_Color{1.0f};
  REF(Texture2D) m_AlbedoTexture = CREATE_REF(Texture2D)(1.f, 1.f);
  REF(Texture2D) m_NormalTexture = CREATE_REF(Texture2D)(1.f, 1.f);
  REF(Texture2D) m_MetallicTexture = CREATE_REF(Texture2D)(1.f, 1.f);
  REF(Texture2D) m_RoughnessTexture = CREATE_REF(Texture2D)(1.f, 1.f);
  REF(Texture2D) m_AOTexture = CREATE_REF(Texture2D)(1.f, 1.f);  ///< Ambient Occlusion
  REF(Texture2D) m_DisplacementTexture = CREATE_REF(Texture2D)(1.f, 1.f);
};

class D_API_EXPORT MaterialSelfDefined : public _obj_material {
 public:
  MaterialSelfDefined();
  ~MaterialSelfDefined();

  virtual void Bind() override{};
  virtual void UnBind() override{};

  void addValue(const std::string& key, float value);
  void addShader(const std::string& key, REF(Shader) & value);
  void addTexture(const std::string& key, REF(Texture2D) & value);

  void deleteValue(const std::string& key);
  void deleteShader(const std::string& key);
  void deleteTexture(const std::string& key);

  void resetValue(const std::string& key, float value);
  void resetShader(const std::string& key, REF(Shader) & value);
  void resetTexture(const std::string& key, REF(Texture2D) & value);

 private:
  std::unordered_map<std::string, float> m_values;
  std::unordered_map<std::string, REF(Shader)> m_shaders;
  std::unordered_map<std::string, REF(Texture2D)> m_textures;
};

}  // namespace renderer
}  // namespace daydream

#endif  // !H_RENDER_CORE_MATERIAL
