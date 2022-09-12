#ifndef H_CORE_OBJ_
#define H_CORE_OBJ_

#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER > 1000

#include "d_render/core/_gl_head.hpp"
#include "d_render/utils/crates.hpp"
#include "d_render/core/material.hpp"
#include "d_render/core/ds.hpp"
#include "d_render/utils/built_in_ds.hpp"

#define DRAW_DATA_INIT                                                                 \
  m_VAO->Bind();                                                                       \
  glDrawElements(GL_TRIANGLES, m_VAO->getIBO()->getCount(), GL_UNSIGNED_INT, nullptr); \
  glBindTexture(GL_TEXTURE_2D, 0);

namespace daydream {
namespace renderer {

class D_API_EXPORT drawObject;
class D_API_EXPORT _obj_material;

/*!
 *@brief The basic object for all object that needed to render.
 *
 * DLL EXpoRt: True
 *
 * @details actually draw() and update() function should be made pure
 * virtual functions, but for dll export purpose I set it to normal
 * virtual functions. But, to rememmber, every class that inherient
 * this class should implement those two functions.
 *
 * @note update() is not must to be implement. Only when draw() function
 * will changed with the event or other staff, update() will works. But,
 * you are also recommend to implement it, even leave it with an empty {}.
 */
class D_API_EXPORT drawObject {
 public:
  virtual void draw(){};    ///< defined the draw action in 3d space.
  virtual void update(){};  ///< If draw() will changed with the time. update() is needed.

  void __TransformUpdate__();
  glm::mat4& Transform();

  void genVertexArray();

 public:
  // Basic Material and Flags
  bool m_HasNormal = true;
  bool m_HasTexCoord = true;
  Crates* renderPayload = nullptr;
  REF(_obj_material) m_defualt_material = nullptr;

  // Actual Data in CPU Memory
  std::vector<Vertex> m_vertex;
  std::vector<Triangle> m_triangle;
  std::vector<uint32_t> m_Index;

  // Buffer in GPU Memory
  REF(VertexArray) m_VAO = nullptr;

  // The Modify materix attribute
  glm::vec3 m_Pos{0.f};
  glm::vec3 m_RelatePos{0.f};
  glm::vec3 m_Scale{1.f};
  glm::vec3 m_Rotate{0.f};
  glm::mat4 m_Trasnform{1.f};  // The M matrix in MVP transform.
};

}  // namespace renderer
}  // namespace daydream

#endif  // !H_CORE_OBJ_
