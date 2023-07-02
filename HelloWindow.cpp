#include "HelloWindow.h"

int HelloWindow::start()
{
	GLBaseProgram* base = new GLBaseProgram();
	int result = base->run();

	delete(base);
	return result;
}
