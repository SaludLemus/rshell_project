#include "defaultcommand.h"
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
using namespace std;
DefaultCommand::DefaultCommand() : Connector(), exec_command(0) {}

DefaultCommand::DefaultCommand(CommandLine* new_cmd) : Connector(), exec_command(new_cmd) {}

void DefaultCommand::execute() {
	if (checkExistence()) {
			// do the sys calls here, if succeed set cmdSuccess to true, else false
		pid_t child_pid;
		int child_status;
		
		// initiate arg list.
		// execvp(CMD, arg list) e.g. cd is CMD and backend is arg list; arg list must bell null term.
		char* argv[];
		int index = 0;
		
		char* cmd_to_execute = exec_command->getCommand();
		int argument_size = 0;
		
		int i = 0;
		
		while (true) {
			if (cmd_to_execute[i] == ' ')
				++argument_size;
			else if (cmd_to_execute[i] == '\0')
				++argument_size;
		}
		
		char* argv[argument_size];
		char* new_arg = new char[];
		argument_size = 0;
		int new_arg_index = 0;
		
		while (true) { // cd a
			if (cmd_to_execute[i] != ' ') {
				new_arg[new_arg_index] = cmd_to_execute[i];
				++new_arg_index;
			}
			else if (cmd_to_execute[i] == ' ') {
				argv[index] = new_arg; // add to argument list for execvp
				++index;
			
				new_arg_index = 0; // start over
				if (cmd_to_execute[i + 1] != '\0')
					new_arg = new char[];
			}
			else if (cmd_to_execute[i] == '\0') {
				argv[index] = new_arg;
				++index;
				break;
			}
			++i;
		}
		
		if (index > 0)
			argv[index] = NULL; // null term.
		else {
			cout << "Error in execute()" << endl;
			return;
		}
		
		child_pid = fork(); // create child process
		
		if (child_pid == 0) { // child will run cmd
			cmdSuccess = true;
			
			execvp(argv[0], argv);
			
			// if continues, then failed (unknown cmd)
			
			cout << "Unknown command." << endl;
			
			cmdSuccess = false;
			
		}
		else { // parent has to wait for child to be done
			pid_t check_pid = waitpid(child_pid, &child_status);
			do {
				if (check_pid != child_pid) return; // need to fix
			} while(check_pid != child_pid);
			return child_status;
		}
			
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
