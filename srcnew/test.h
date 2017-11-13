#ifndef __TEST_H__
#define __TEST_H__

#include "command.h"


class Test : public Command {
	public:
		Test();
		~Test();
		bool execute();
		void display();
};


#endif
