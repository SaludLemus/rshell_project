#ifndef continue_h_
#define continue_h_

#include "connector.h"

class ContinueC : public Connector {
	public:
		ContinueC();
		ContinueC(Connector* single_cmd = 0);
		~ContinueC() {
			if (single_command)
				delete single_command;
		}
		void execute() = 0;
		bool checkExistence();
	private:
		Connector* single_command; // single command
};

#endif
