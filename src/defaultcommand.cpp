#include "defaultcommand.h"
#include <unistd.h>
DefaultCommand::DefaultCommand() : Connector(), exec_command(0) {}

DefaultCommand::DefaultCommand(CommandLine* new_cmd) : Connector(), exec_command(new_cmd) {}

void DefaultCommand::execute() {
	if (checkExistence()) {
			// do the sys calls here, if succeed set cmdSuccess to true, else false
		pid_t child_pid;
		int child_status;
	}
	return;
}

bool DefaultCommand::checkExistence() {
	if (exec_command) return true;
	return false;
}

bool DefaultCommand::checkStatus() {
	return cmdSuccess;
}

CommandConnector DefaultCommand::getConnector() {
	if (checkExistence()) return exec_command->getConnector();
}
    
char* DefaultCommand::getCMD() {
	return exec_command->getCommand();	
}
