// DaydreamEngine.cpp: 定义应用程序的入口点。
//

#include "DaydreamEngine.h"
#include "application/app.hpp"
using namespace std;

int main() {
	App *main_app = new App();

	daydream::renderer::load_gl_context_from_dll(); // Need to pass the context to exe and other dll.
	
	main_app->delay_init();
	main_app->exec();
	delete main_app;
}