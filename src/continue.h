#ifndef continue_h_
#define continue_h_

#include "connector.h"

class ContinueC : public Connector {
	public:
		ContinueC();
		~ContinueC();
		void execute() = 0;
		bool checkExistence();
	protected:
		bool cmdSuccess;
	private:
		Connector* default_command; // single command
};

#endif
