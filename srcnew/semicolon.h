#ifndef __SEMICOLON_H__
#define __SEMICOLON_H__

#include "connector.h"

class Semicolon: public Connector{
	
	public:
        Semicolon();
        Semicolon(Base*, Base*);
        ~Semicolon();
        bool execute();
        void display();
};

#endif

