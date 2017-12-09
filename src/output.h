#ifndef __OUTPUT_H__
#define __OUTPUT_H__

#include "connector.h"

class Output: public Connector{
    private:
    char* output_file;
	public:
        Output();
        Output(Base*, Base*);
        ~Output();
        bool execute();
        void display();
        bool check_dup(int);
        bool execute(char**);
};

#endif
