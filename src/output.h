#ifndef __OUTPUT_H__
#define __OUTPUT_H__

#include "connector.h"

class Output: public Connector{
    
	public:
        Output();
        Output(Base*, Base*);
        ~Output();
        bool execute();
        void display();
};

#endif