#include "defaultcommand.h"

DefaultCommand::DefaultCommand() : Connector(), exec_command(0) {}

DefaultCommand::DefaultCommand(CommandLine* new_cmd) : Connector(), exec_command(new_cmd) {}

void DefaultCommand::execute() {
	if (checkExistence()) {
			// do the sys calls here, if succeed set cmdSuccess to true, else false
		
	}
	return;
}

bool DefaultCommand::checkExistence() {
	if (exec_command) return true;
	return false;
}
