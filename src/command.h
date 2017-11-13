#ifndef __COMMAND_H__
#define __COMMAND_H__

#include "base.h"

class Command: public Base{
	protected:
		char** commandArray;
	
	public:
        Command();
        Command(char**);
        ~Command();
        bool execute();
        void display();
};

#endif