#ifndef USERINTERFACE_H_
#define USERINTERFACE_H_

class UserInterface {
   public:
      virtual void exit(); // exit the rshell
      virtual void setCommand(); // will set the parser's data member
};

#endif
