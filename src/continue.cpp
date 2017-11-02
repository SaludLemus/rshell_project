#include "continue.h"

ContinueC::ContinueC() : Connector(), single_command(0) {}

ContinueC::ContinueC(Connector* new_cmd) : Connector(), single_command(new_cmd) {}

void ContinueC::execute() {
	if (checkExistence()) {
		single_command->execute(); // execute cmd
		
		if (single_command->cmdSuccess)
			cmdSuccess = true;
	}
	return;
}

bool ContinueC::checkExistence() {
	if (single_command) return true;
	return false;
}
