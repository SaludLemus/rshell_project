#ifndef USERINTERFACE_H_
#define USERINTERFACE_H_

class UserInterface {
   public:
      UserInterface() {}
      virtual ~UserInterface() {}
      virtual bool setCommand() = 0; // will set the parser's data member
};

#endif
