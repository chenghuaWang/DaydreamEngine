#include "basicObj.hpp"

namespace daydream {
namespace renderer {
PlaneObject* PlaneObject::m_instance = nullptr;

PlaneObject::PlaneObject() {
  m_shader = Shader::create("../Asset/shader/PlaneObj.glsl");
  uint32_t sample = 2;
  for (uint32_t i = 0; i <= sample; i++) {
    for (uint32_t j = 0; j <= sample; j++) {
      Vertex v;
      v.m_Position = {(float)i / (float)sample - 0.5f, 0.0f, (float)j / (float)sample - 0.5f};
      v.m_Normal = {0.0f, 1.0f, 0.0f};
      v.m_TexCoord = {(float)i / (float)sample, (float)j / (float)sample};
      m_vertex.push_back(v);
    }
  }
  uint32_t indices[6] = {0, sample + 1, sample + 2, 0, sample + 2, 1};

  for (int k = 0; k < (sample + 1) * sample; k++)
    for (int i = 0; i < 6; i++)
      if ((k + 1) % (sample + 1) > 0) m_Index.push_back(indices[i] + k);

  for (size_t i = 0; i < m_Index.size(); i += 3) {
    Triangle triangle = {m_Index[i], m_Index[i + 1ul], m_Index[i + 2ul]};
    m_triangle.push_back(triangle);
  }
  genVertexArray();
  m_instance = this;
}

void PlaneObject::draw() {
  m_shader->Bind();
  // TODO bind shader and bind data. sent data to shader.
  m_shader->UnBind();
}

void PlaneObject::update() {}

PlaneObject* PlaneObject::getInstance() { return m_instance; }

void PlaneObject::genVertexArray() {}

}  // namespace renderer
}  // namespace daydream