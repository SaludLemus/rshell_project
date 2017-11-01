#ifndef defaultcommand_h_
#define defaultcommand_h_

#include "connector.h"
#include "commandline.h"

class DefaultCommand : public Connector {
	public:
		DefaultCommand();
		~DefaultCommand();
		void execute() = 0;
		bool checkExistence();
	protected:
		bool cmdSuccess;
	private:
		CommandLine* exec_command; // single command (leaf node)
};

#endif
