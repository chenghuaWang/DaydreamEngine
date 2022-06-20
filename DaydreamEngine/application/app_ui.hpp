#include "d_ui/widget/console.hpp"

using namespace daydream;

struct uis {
	uis() = default;
	~uis() {
		delete console_1;
	}

	ui::console* console_1 = new ui::console();
};
