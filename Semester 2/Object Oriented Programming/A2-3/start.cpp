#include "Ui.h"
#include <crtdbg.h>
int main()
{
	Repository* repo = create_repository();
	OperationsStack* undos = createStack();
	OperationsStack* redos = createStack();
	Service* ctrl = create_service(repo ,undos,redos);
	//test_repo();
	//test_service();
	//Test_dynamic_array();
	initial_input(repo);
	Ui* ui = createUi(ctrl);
	start(ui);
	destroyUi(ui);
	_CrtDumpMemoryLeaks();
	 
	return 0;
}
