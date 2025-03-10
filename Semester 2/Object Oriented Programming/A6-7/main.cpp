#include <crtdbg.h>
#include <iostream>
#include "Ui.h"
#include <iostream>
#include "Tests.h"
using namespace std;
int main()
{
	{
		//TestRepository();
		//TestService();
		Ui ui;
		ui.run();
	}
	_CrtDumpMemoryLeaks();
	

    return 0;
}
