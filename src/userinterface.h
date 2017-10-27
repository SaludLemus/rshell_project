#ifndef USERINTERFACE_H_
#define USERINTERFACE_H_

class UserInterface {
   public:
      virtual void exit() = 0; // exit the rshell
      virtual void setCommand() = 0; // will set the parser's data member
};

#endif
