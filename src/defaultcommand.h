#ifndef defaultcommand_h_
#define defaultcommand_h_

#include "connector.h"
#include "commandline.h"

class DefaultCommand : public Connector {
	public:
		DefaultCommand();
		DefaultCommand(CommandLine* new_cmd = 0);
		~DefaultCommand() {
			if (exec_command)
				delete exec_command;
		}
		void execute();
		bool checkExistence();
		CommandConnector getConnector();
		bool checkStatus();
		const char* getCMD();
	private:
		CommandLine* exec_command; // single command (leaf node)
};

#endif