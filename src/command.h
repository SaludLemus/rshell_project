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
      void init(const string &);
   private:
		Command();
		~Command();
      Parse* parse_cmd;
      List<CommandLine*> cmd_list;
      void commandIterator(); // will call exit() if "exit" exists or end of parse is reached
      void exit();
      void deallocParser();
      void deallocCMDList();
};

#endif
