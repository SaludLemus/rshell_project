#ifndef __APPEND_H__
#define __APPEND_H__

#include "connector.h"

class Append: public Connector{
    char* file_name;
	public:
        Append();
        Append(Base*, Base*);
        ~Append();
        bool execute();
        void display();
        bool check_dup(int);
        bool check_close();
        bool change_output();
        bool restore_save1(int);
        bool execute(char**);
};

#endif
