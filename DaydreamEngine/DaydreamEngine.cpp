// DaydreamEngine.cpp: 定义应用程序的入口点。
//

#include "DaydreamEngine.h"
#include "d_ui/window/window.hpp"

using namespace std;
using namespace daydream;

class main_window: public ui::base_window {
public:
	main_window(size_t w, size_t h, const std::string& name) : ui::base_window(w, h, name) {}

};

int main() {
	main_window app_window(1920, 1080, "DreamMaker");
	app_window.exec();
}
