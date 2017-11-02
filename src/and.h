#ifndef and_h_
#define and_h_

#include "connector.h"

class AndC : public Connector {
	public:
		AndC();
		AndC(Connector* left_child = 0, Connector* right_child = 0);
		~AndC() {deallocChildren();}
		void execute();
		bool checkExistence();
		void deallocChildren();
	private:
		Connector* left_child;
		Connector* right_child;
	
};

#endif
