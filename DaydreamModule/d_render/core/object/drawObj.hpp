#ifndef H_CORE_OBJ_
#define H_CORE_OBJ_

#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER > 1000

#include "d_render/core/_gl_head.hpp"
#include "d_render/utils/crates.hpp"

namespace daydream {
namespace renderer {

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

 public:
  bool m_HasNormal = true;
  bool m_HasTexCoord = true;
  Crates* renderPayload;
};

}  // namespace renderer
}  // namespace daydream

#endif  // !H_CORE_OBJ_
