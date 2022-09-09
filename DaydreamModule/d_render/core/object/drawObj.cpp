#include "drawObj.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

namespace daydream {
namespace renderer {
void drawObject::__TransformUpdate__() {
  glm::mat4 translation = glm::translate(glm::mat4(1.0f), m_Pos + m_RelatePos);
  glm::mat4 rotation = glm::mat4_cast(glm::qua<float>(glm::radians(m_Rotate)));
  m_Trasnform = glm::scale(translation * rotation, m_Scale);
}

glm::mat4& drawObject::Transform() {
  __TransformUpdate__();
  return m_Trasnform;
}
void drawObject::genVertexArray() {
  // Create VAO
  m_VAO = CREATE_REF(VertexArray)();

  // Create VBO using vertex data.
  REF(VertexBuffer)
  __VBO__ =
      CREATE_REF(VertexBuffer)((float*)(&*m_vertex.begin()), sizeof(Vertex) * m_vertex.size());

  // Bind layout to VBO
  BufferLayout __layout__ = {{ElementType::Vecf3, "a_Position"},
                             {ElementType::Vecf2, "a_TexCoord"},
                             {ElementType::Vecf3, "a_Normal"},
                             {ElementType::Vecf2, "a_Tengent"},
                             {ElementType::Vecf3, "a_Bitangent"}};
  __VBO__->setLayout(__layout__);

  // Bind VBO to VAO
  m_VAO->addVertexBuffer(__VBO__);

  // Create IDO
  REF(IndexBuffer)
  __IDO__ = CREATE_REF(IndexBuffer)((uint32_t*)(&*m_Index.begin()), m_Index.size());

  // Bind IDO to VAO
  m_VAO->addIndexBuffer(__IDO__);
}
}  // namespace renderer
}  // namespace daydream