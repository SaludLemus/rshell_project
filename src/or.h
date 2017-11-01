#ifndef or_h_
#define or_h_

#include "connector.h"

class OrC : public Connector {
	public:
		OrC();
		~OrC();
		void execute() = 0;
		bool checkExistence();
	protected:
		bool cmdSuccess;
	private:
		Connector* left_child;
		Connector* right_child;
};

#endif
