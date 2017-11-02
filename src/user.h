#ifndef user_h_
#define user_h_

#include "userinterface.h"
#include "command.h"
class User : public UserInterface{
   public:
      User();
      ~User(); // dealloc data member
      bool setCommand();
   private:
		Command* cmd_controller;
};

#endif
