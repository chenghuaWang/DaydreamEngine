#include "layer_stack.hpp"

namespace daydream {
namespace ui {
	layer_stack::~layer_stack() {
		for (auto item : m_stack) {
			delete item;
		}
	}

	void layer_stack::add_layer(base_layer* rhs) {
		m_stack.push_back(rhs);
	}

	void layer_stack::delete_layer(base_layer* rhs) {
		for (auto it = m_stack.begin(); it != m_stack.end(); ) {
			if ((* it) == rhs) {
				it = m_stack.erase(it);
			} else {
				++it;
			}
		}
	}

	std::vector<base_layer*>::const_iterator layer_stack::const_begin() { return m_stack.cbegin(); }
	std::vector<base_layer*>::const_iterator layer_stack::const_end() { return m_stack.cend(); }
	std::vector<base_layer*>::iterator layer_stack::begin() { return m_stack.begin(); }
	std::vector<base_layer*>::iterator layer_stack::end() { return m_stack.end(); }

}
}