#include "SkyBox.hpp"

namespace daydream {
namespace renderer {

ProcedualSkySphare::ProcedualSkySphare()
    : m_WorldLight(CREATE_REF(LightDirect)()), m__mesh__(CREATE_REF(SphareObject)()) {
  // Actual Data in CPU Memory
  m_vertex = m__mesh__->m_vertex;
  m_triangle = m__mesh__->m_triangle;
  m_Index = m__mesh__->m_Index;

  // Buffer in GPU Memory
  m_VAO = m__mesh__->m_VAO;

  // Change the m_scale to default.
  m_Scale.x = m_r;
  m_Scale.y = m_r;
  m_Scale.z = m_r;

  // init the basic shader.
}

void ProcedualSkySphare::draw() {}

void ProcedualSkySphare::update() {}

}  // namespace renderer
}  // namespace daydream