#ifndef H_LAYER_STACK
#define H_LAYER_STACK

#ifdef _MSC_VER> 1000
#pragma once
#endif  // !_MSC_VER

#include "d_core/pch.hpp"
#include "d_ui/layers/layer.hpp"

namespace daydream {
namespace ui {
class D_API_EXPORT layer_stack {
 public:
  ~layer_stack();

  void add_layer(base_layer* rhs);
  void delete_layer(base_layer* rhs);

  std::vector<base_layer*>::const_iterator const_begin();
  std::vector<base_layer*>::const_iterator const_end();
  std::vector<base_layer*>::iterator begin();
  std::vector<base_layer*>::iterator end();

 private:
  std::vector<base_layer*> m_stack;
};
}  // namespace ui
}  // namespace daydream

#endif  // !H_LAYER_STACK
