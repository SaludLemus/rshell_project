#ifndef __PIPE_H__
#define __PIPE_H__

#include "connector.h"

class Pipe: public Connector{
    
	public:
        Pipe();
        Pipe(Base*, Base*);
        ~Pipe();
        bool execute();
        void display();
};

#endif