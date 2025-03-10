#include <iostream>
#include <crtdbg.h>
#include "Ui.h"
int main()
{
	{
		Ui ui;
		ui.start();
	}
	_CrtDumpMemoryLeaks();
	
	return 0;
}