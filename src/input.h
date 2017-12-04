#ifndef __INPUT_H__
#define __INPUT_H__

#include "connector.h"

class Input: public Connector{
    
	public:
        Input();
        ~Input();
        bool execute();
        void display();
};

#endif