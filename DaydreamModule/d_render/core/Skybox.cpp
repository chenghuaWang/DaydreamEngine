#include "SkyBox.hpp"

namespace daydream {
namespace renderer {

ProcedualSkySphare::ProcedualSkySphare() : m_WorldLight(CREATE_REF(LightDirect)()) {
  // Init Meshes
  uint32_t real = 32 * 10;
  for (uint32_t i = 0; i <= real; i++)
    for (uint32_t j = 0; j <= real; j++) {
      Vertex v;
      v.m_Position = {(float)i / (float)real, 0.0f, (float)j / (float)real};
      v.m_Normal = {0.0f, 1.0f, 0.0f};
      v.m_TexCoord = {(float)i / (float)real, (float)j / (float)real};
      m_vertex.push_back(v);
    }
  uint32_t indices[6] = {0, real + 1, real + 2, 0, real + 2, 1};
  for (uint32_t k = 0; k < (real + 1) * real; k++)
    for (uint32_t i = 0; i < 6; i++)
      if ((k + 1) % (real + 1) > 0) m_Index.push_back(indices[i] + k);
  for (size_t i = 0; i < m_Index.size(); i += 3) {
    Triangle triangle = {m_Index[i], m_Index[i + 1ul], m_Index[i + 2ul]};
    m_triangle.push_back(triangle);
  }
  for (auto& p : m_vertex) {
    float phi = glm::radians(360.0f * p.m_Position.z);
    float theta = glm::radians(180.0f * p.m_Position.x - 90.0f);
    p.m_Position.x = p.m_Normal.x = cos(theta) * cos(phi);
    p.m_Position.y = p.m_Normal.y = sin(theta);
    p.m_Position.z = p.m_Normal.z = cos(theta) * sin(phi);
  }
  genVertexArray();
  // Change the m_scale to default.
  m_Scale.x = m_r;
  m_Scale.y = m_r;
  m_Scale.z = m_r;

  // Init the basic shader.

  // Init the Direct Light position.
  m_WorldLight->m_pos = {-0.5f, 0.3f, 0.5f};
  m_WorldLight->resetDirection({0.0, 0.0, 0.0});
  m_WorldLight->resetIntensity(128.f);
}

void ProcedualSkySphare::draw() {
  // Two pass.
  // Pass 1. Caculate Texture for Binding.
  // Pass 2. Bind the Texture to the sphare.
  // In Pass2. Disabel back face auto remove
  glDisable(GL_CULL_FACE);
  glDepthMask(GL_FALSE);
  m_shader_pass2->Bind();
  glm::mat4 view = glm::mat4(glm::mat3(renderPayload->mainCamera->getViewMatrix()));
  m_shader_pass2->setMat4("d_ViewProjection",
                          renderPayload->mainCamera->getProjectionMatrix() * view);
  m_shader_pass2->setMat4("d_Transform", Transform());
  DRAW_DATA_INIT;
  m_shader_pass2->UnBind();
  glDepthMask(GL_TRUE);
}

void ProcedualSkySphare::update() {}

REF(LightDirect) ProcedualSkySphare::getLight() const { return m_WorldLight; }

void ProcedualSkySphare::Bind(const REF(Shader) & shader) {}

StandardSkyBox::StandardSkyBox() : m_WorldLight(CREATE_REF(LightDirect)()) {
  m_WorldLight->m_pos = {0.0, 0.0, 0.0};
  m_WorldLight->resetDirection({0.0, 0.1, 0.0});
}

StandardSkyBox::~StandardSkyBox() {
  for (auto item : m_meshes) { delete item; }
}

void StandardSkyBox::Init(KVBase* db, const std::string& file_path) {
  __init_standard__(db, file_path);
}

void StandardSkyBox::draw() {
  for (auto mesh : m_meshes) {
    auto __shader__ = mesh->m_defualt_material->GetShader();
    auto __baseColor__ =
        static_cast<MaterialBRDF*>(mesh->m_defualt_material.get())->m_AlbedoTexture;
    glDisable(GL_CULL_FACE);
    glDepthMask(GL_FALSE);
    __shader__->Bind();
    __baseColor__->Bind(0);
    glm::mat4 view = glm::mat4(glm::mat3(renderPayload->mainCamera->getViewMatrix()));
    __shader__->setMat4("d_ViewProjection",
                        renderPayload->mainCamera->getProjectionMatrix() * view);
    __shader__->setMat4("d_Transform", mesh->Transform());
    __shader__->setInt("d_baseColor", 0);
    mesh->m_VAO->Bind();
    glDrawElements(GL_TRIANGLES, mesh->m_VAO->getIBO()->getCount(), GL_UNSIGNED_INT, nullptr);
    glBindTexture(GL_TEXTURE_2D, 0);
    __baseColor__->UnBind(0);
    __shader__->UnBind();
    glDepthMask(GL_TRUE);
  }
}

void StandardSkyBox::update() {}

REF(Texture2D) StandardSkyBox::getEnvMap() const {
  return static_cast<MaterialBRDF*>(m_defualt_material.get())->m_AlbedoTexture;
}

REF(LightDirect) StandardSkyBox::getLight() const { return m_WorldLight; }

void StandardSkyBox::Bind(const REF(Shader) & shader) const {
  auto __material__ = static_cast<MaterialBRDF*>(m_meshes[0]->m_defualt_material.get());
  __material__->m_AlbedoTexture->Bind(8);
  shader->Bind();
  shader->setInt("d_EnvMap", 8);
  shader->UnBind();
  __material__->m_AlbedoTexture->UnBind(8);
}

void StandardSkyBox::__init_standard__(KVBase* db, const std::string& file_path) {
  __load_binary_files__(file_path, m_meshes, db);
  auto SkyShader = CREATE_REF(Shader)("../Asset/SkyBox/StandardSphare.glsl");
  for (auto mesh : m_meshes) {
    mesh->m_defualt_material->SetShader(SkyShader);
    mesh->m_Scale = {0.2f, 0.2f, 0.2f};
    mesh->m_Pos = {0.f, 0.f, 0.f};
  }
}

void StandardSkyBox::__Cover2CubeMap__() {}

OctahedronSkyBox::OctahedronSkyBox() {}

void OctahedronSkyBox::draw() {}

void OctahedronSkyBox::update() {}

void OctahedronSkyBox::__init_octahedron__() {}

}  // namespace renderer
}  // namespace daydream