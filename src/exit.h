#ifndef __EXIT_H__
#define __EXIT_H__

#include "command.h"

class Exit: public Command{
    
	public:
        Exit();
        ~Exit();
        bool execute();
        void display();
};

#endif