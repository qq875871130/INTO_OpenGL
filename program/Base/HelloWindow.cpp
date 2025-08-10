#include "HelloWindow.h"
#include "GLBase.h"

int HelloWindow::Start()
{
	RenderProgram* base = new RenderProgram();
	int result = base->Run();

	return result;
}
