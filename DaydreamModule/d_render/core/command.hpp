#ifndef H_CORE_COMMAND
#define H_CORE_COMMAND

#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER > 1000

#include "_gl_head.hpp"

namespace daydream {
namespace renderer {

struct D_API_EXPORT GLCommand {
  static void init();
  static void setColor(float r, float g, float b, float a);
  static void setViewPortSize(size_t x, size_t y, size_t w, size_t h);
  static void clear();
  static void setLineMode(bool enable);
};

void D_API_EXPORT load_gl_context_from_dll();

}  // namespace renderer
}  // namespace daydream

#endif  // !H_CORE_COMMAND
