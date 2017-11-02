#include "exitc.h"
#include <cstdlib>
using namespace std;

ExitC::ExitC() : Connector(), single_command(0) {}

ExitC::ExitC(Connector* left_child) : Connector(), single_command(left_child) {}

void ExitC::execute() {
	if (checkExistence()) {// valid
		single_command->execute(); // run command
		
		if (single_command->cmdSuccess) // sucessful run
			cmdSuccess = true;
	}
	exitProg(); // quit program since end is reached (quits despite command succeeds or not)
	return;
}

void ExitC::exitProg() {
	exit(0);
	return;
}

bool ExitC::checkExistence() { // no seg. fault
	if (single_command) return true;
	return false;
}
