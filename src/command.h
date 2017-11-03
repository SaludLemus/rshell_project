#ifndef Command_h_
#define Command_h_

#include "parser.h"
#include "commandline.h"
#include <iostream>
#include <string>
#include <list>
using namespace std;

class Command {
   public:
      Command();
		~Command();
      void init(const string &);
   private:
      Parser* parse_cmd;
      list<CommandLine*> cmd_list;
      void commandIterator(); // will call exit() if "exit" exists or end of parse is reached
      void exit();
      void deallocParser();
      void deallocCMDList();
};

#endif
