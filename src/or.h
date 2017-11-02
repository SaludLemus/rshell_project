#ifndef or_h_
#define or_h_

#include "connector.h"

class OrC : public Connector {
	public:
		OrC();
		OrC(Connector* left_child, Connector* right_child);
		~OrC() {}
		void execute() = 0;
		bool checkExistence();
	private:
		Connector* left_child;
		Connector* right_child;
};

#endif
