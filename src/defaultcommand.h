#ifndef defaultcommand_h_
#define defaultcommand_h_

#include "connector.h"
#include "commandline.h"

class DefaultCommand : public Connector {
	public:
		DefaultCommand();
		DefaultCommand(CommandLine* new_cmd = 0);
		~DefaultCommand() {}
		void execute() = 0;
		bool checkExistence();
	private:
		CommandLine* exec_command; // single command (leaf node)
};

#endif
