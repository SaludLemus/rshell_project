#ifndef __CONNECTOR_H__
#define __CONNECTOR_H__

#include "base.h"

class Connector: public Base{
	protected:
		Base* leftNode;
		Base* rightNode;
	
	public:
        Connector();
        Connector(Base*, Base*);
        ~Connector();
        virtual bool execute() = 0;
        virtual void display() = 0;
        void setLeftNode(Base*);
        void setRightNode(Base*);
};

#endif