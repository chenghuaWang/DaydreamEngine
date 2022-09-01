#ifndef H_RENDER_CORE_PIPELINE
#define H_RENDER_CORE_PIPELINE

#ifdef _MSC_VER> 1000
#pragma once
#endif  // _MSC_VER > 1000

#include "d_core/pch.hpp"

namespace daydream {
namespace renderer {

void D_API_EXPORT StartPipline();
void D_API_EXPORT ShutdownPipline();

}  // namespace renderer
}  // namespace daydream

#endif  // !H_RENDER_CORE_PIPELINE
