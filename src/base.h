#ifndef __BASE_H__
#define __BASE_H__

class Base{
    public:
        virtual ~Base() {}
        virtual bool execute() = 0;
        virtual void display() = 0;
        virtual char* getCommand() {return 0;}
        virtual char* currentCommand() {return 0;}
};

#endif
