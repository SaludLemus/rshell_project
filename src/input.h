#ifndef __INPUT_H__
#define __INPUT_H__

#include "connector.h"

class Input: public Connector{
    char* file_name;
	public:
        Input();
        Input(Base*, Base*);
        ~Input();
        bool execute();
        void display();
        bool check_dup(int);
        bool check_close();
        bool change_input();
        bool restore_save0(int);
};

#endif
