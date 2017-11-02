#ifndef exitc_h_
#define exitc_h_

#include "connector.h"

class ExitC : public Connector {
	public:
		ExitC();
		ExitC(Connector* left_child = 0);
		~ExitC() {
			if (single_command) delete single_command;
		}
		void execute() = 0;
		bool checkExistence();
	private:
		Connector* single_command;
		void exitProg();
};

#endif
