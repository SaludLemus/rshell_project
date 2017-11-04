#ifndef Command_h_
#define Command_h_

#include "parser.h"
#include "commandline.h"
#include "connector.h"
#include "defaultcommand.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Command {
   public:
		Command();
		~Command();
      void init(const string &);
   private:
      Parser* parse_cmd;
      vector<Connector*> cmd_list;
      void commandIterator(); // will call exit() if "exit" exists or end of parse is reached
      void deallocParser();
      void deallocCMDList();
      void exitProg();
};

#endif
