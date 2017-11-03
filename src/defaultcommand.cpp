#include "defaultcommand.h"
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <string>
#include <errno.h>
#include <boost/tokenizer.hpp>
using namespace std;

DefaultCommand::DefaultCommand() : Connector(), exec_command(0) {}

DefaultCommand::DefaultCommand(CommandLine* new_cmd) : Connector(), exec_command(new_cmd) {}

void DefaultCommand::execute() {
	if (checkExistence()) {
			// do the sys calls here, if succeed set cmdSuccess to true, else false
		pid_t child_pid;
		int child_status;
		
		int index = 0; // for argv
		int argument_size = 0;
		int i = 0; // find number of args
		
		char* cmd_to_execute = exec_command->getCommand();
		while (true) { // how many args
			if (cmd_to_execute[i] == ' ')
				++argument_size;
			else if (cmd_to_execute[i] == '#') // treat everything afterwards as a comment
				break;
			else if (cmd_to_execute[i] == '\0') {
				++argument_size;
				break;
			}
			++i;
		}
		string conv_to_str(cmd_to_execute);
		
		if (conv_to_str.find("#") != string::npos) // ignore everything to the right
			conv_to_str = conv_to_str.substr(0, conv_to_str.find("#") - 1); // keep everything to the left
		
		boost::char_separator<char> sep{" "};
		boost::tokenizer<boost::char_separator<char>> tok{conv_to_str, sep};
		char* argv[argument_size];
		
		for (boost::tokenizer<boost::char_separator<char>>::iterator itr = tok.begin(); itr != tok.end(); ++itr) { // build argv
			string temp_str = *itr;
			char* new_arg = new char[temp_str.size()];
			for (unsigned int i = 0; i < temp_str.size(); ++i)
				new_arg[i] = temp_str.at(i);
			argv[index] = new_arg;
			++index;
		}
		
		if (index > 0)
			argv[index] = NULL; // null term.
		else {
			cout << "Error in execute()" << endl;
			return;
		}
		//cout << argv[0] << endl;
		//cout << argv[1] << endl;
		return; // MAKE SURE SYS CALLS WORK
		
		child_pid = fork(); // create child process fork() returns an integer (0 == child)
		
		if (child_pid == 0) { // child will run cmd
			cmdSuccess = true;
			
			execvp(argv[0], argv); // returns a negative value if failed to execute
			
			// if continues, then failed (unknown cmd)
			
			cout << "Unknown command." << endl;
			
			cmdSuccess = false;
		}
		else if (child_pid == -1) // fork failed
			perror("Fork() failed");
		else { // parent has to wait for the child to be done
			pid_t check_pid = waitpid(child_pid, &child_status, 0);
			do {
				if (check_pid != child_pid) return; // need to fix
			} while(check_pid != child_pid);
			return; // return child_status;
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
