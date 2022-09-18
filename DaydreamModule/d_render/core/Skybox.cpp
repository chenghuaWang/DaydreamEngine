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
  m_WorldLight->m_pos.x = 0;
  m_WorldLight->m_pos.y = m_r;
  m_WorldLight->m_pos.z = 0;
}

void ProcedualSkySphare::draw() {
  // Two pass.
  // Pass 1. Caculate Texture for Binding.
  // Pass 2. Bind the Texture to the sphare.
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

}  // namespace renderer
}  // namespace daydream