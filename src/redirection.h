#ifndef __REDIRECTION_H__
#define __REDIRECTION_H__

#include "connector.h"

class Redirection: public Connector{
	protected:
		Base* leftNode;
		Base* rightNode;
	
	public:
        Redirection();
        Redirection(Base*, Base*);
        ~Redirection();
        virtual bool execute() = 0;
        virtual void display() = 0;
        void setLeftNode(Base*);
        void setRightNode(Base*);
};

#endif