#include "HelloWindow.h"

int HelloWindow::start()
{
	Program* base = new Program();
	int result = base->run();

	delete(base);
	return result;
}
