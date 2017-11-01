#ifndef exitc_h_
#define exitc_h_

#include "connector.h"

class ExitC : public Connector {
	public:
		ExitC();
		~ExitC();
		void execute() = 0;
		bool checkExistence();
	protected:
		bool cmdSuccess;
	private:
		Connector* left_child;
		Connector* right_child;
};

#endif
