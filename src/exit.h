#ifndef __EXIT_H__
#define __EXIT_H__

#include "command.h"

class Exit: public Base{
    
	public:
        Exit();
        ~Exit();
        bool execute();
        void display();
};

#endif