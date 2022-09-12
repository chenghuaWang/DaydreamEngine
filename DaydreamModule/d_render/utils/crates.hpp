#ifndef H_CORE_UTILS_CRATES
#define H_CORE_UTILS_CRATES

#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER > 1000

#include "d_render/core/ds.hpp"
#include "d_render/utils/camera.hpp"

namespace daydream {
namespace renderer {

/*!
 *@brief Crates works like a minimal scene. It manages some basic components
 * needed for rendering. But it don't contain any data(such as texture, model,
 * shaders, etc).
 *
 * DLL EXPORT: True
 *
 * @details What Crates contains are VP Matrix from MVP transformation; The
 * Frame buffer of one 3d scene; Main camera infomation; Global light( such as
 * Fog-color, Atmosphere light color, sun-position, etc) if sky need to be
 * rendered; Some basic settings (wireframe-mode, depth-enable, etc).
 *
 * ---------------------------------------------------------------------------
 *                       How to work with this class ?
 * ---------------------------------------------------------------------------
 * In brief, this class is just a compose of some necessary data. It should not
 * hold any runtime data. If you want to modify it, make sure that this class
 * holds only pointers to some most vital objects needed all over the time when
 * renderer is running. For convience, all members in this class should be decl-
 * ared in public scope. KEY: do not delete data from this class, it's dangerous.
 * You can free all data manualy out of this class or pass this class to ui's wid-
 * get scene3d witch will be sent to gl_content to show on ui. The delete func
 * should be implemented in scene3d class to free the basic objects memory.
 *
 * Other classed can hold the pointer of this Crates to obtain basic infomation for
 * convenient purpose.
 *
 * It works like this:
 *
 * Crates--------->scene3d-->gl_content(3d)-->ui_layer-->window-->Application
 *			   |
 * drawObject--|
 *
 * @note If you want to inherient this class in your program. It's ok, but, you
 * are not recommend to use smart-ptr in this class. This class should works
 * like a payload just compose all basic data together. Adding too much trade-
 * off in this class is not a good ideal, dut to it is used almost everywhere.
 */
class D_API_EXPORT Crates {
 public:
  bool wireframe = false;
  camera3d* mainCamera = nullptr;
  FrameBuffer* sceneFBO = nullptr;
};
}  // namespace renderer
}  // namespace daydream

#endif  // !H_CORE_UTILS_CRATES