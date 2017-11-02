#ifndef or_h_
#define or_h_

#include "connector.h"

class OrC : public Connector {
	public:
		OrC();
		OrC(Connector* left_child, Connector* right_child);
		~OrC() {deallocChildren();}
		void execute() = 0;
		bool checkExistence();
		void deallocChildren();
	private:
		Connector* left_child;
		Connector* right_child;
};

#endif
