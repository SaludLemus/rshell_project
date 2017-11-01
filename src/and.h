#ifndef and_h_
#define and_h_

#include "connector.h"

class AndC : public Connector {
	public:
		AndC();
		AndC(Connector* left_child = 0, Connector* right_child = 0);
		~AndC() {};
		void execute();
		bool checkExistence();
	protected:
		bool cmdSuccess;
	private:
		Connector* left_child;
		Connector* right_child;
	
};

#endif
