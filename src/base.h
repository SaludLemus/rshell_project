#ifndef __BASE_H__
#define __BASE_H__

class Base{
    public:
        virtual ~Base() {}
        virtual bool execute() = 0;
        virtual void display() = 0;
};

#endif