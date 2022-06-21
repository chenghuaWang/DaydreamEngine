// DaydreamEngine.cpp: 定义应用程序的入口点。
//

#include "DaydreamEngine.h"
#include "application/app.hpp"
using namespace std;

int main() {
	App *main_app = new App();
	main_app->delay_init();
	main_app->exec();
	delete main_app;
}