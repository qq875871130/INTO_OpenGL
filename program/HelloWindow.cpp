#include "HelloWindow.h"

int HelloWindow::Start()
{
	Program* base = new Program();
	int result = base->Run();

	return result;
}
