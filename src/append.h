#ifndef __APPEND_H__
#define __APPEND_H__

#include "connector.h"

class Append: public Connector{
    
	public:
        Append();
        ~Append();
        bool execute();
        void display();
};

#endif