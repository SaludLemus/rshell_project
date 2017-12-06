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
        bool restore_save0(int);
        bool restore_save1(int);
        bool check_close();
        bool check_dup(int, int);
        bool check_pipe(int [2]);
};

#endif
