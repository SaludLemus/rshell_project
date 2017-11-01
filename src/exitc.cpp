#include "exitc.h"
#include <cstdlib>
using namespace std;

ExitC::ExitC() : Connector(), cmd_success(false), left_child(0) {}

ExitC::ExitC(bool cmd_success, Connector* left_child) : Connector(), cmd_success(cmd_success), left_child(left_child) {}

void ExitC::execute() {
	if (checkExistence()) {// valid
		left_child->execute(); // run command
		
		if (left_child->cmdSuccess) // sucessful run
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
	if (left_child && right_child) return true;
	return false;
}
