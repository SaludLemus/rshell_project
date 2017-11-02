#ifndef Command_h_
#define Command_h_

#include "parse.h"
#include "commandline.h"
#include "connector.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Command {
   public:
      void init(const string &);
   private:
		Command();
		~Command();
      Parse* parse_cmd;
      vector<Connector*> cmd_list;
      void commandIterator(); // will call exit() if "exit" exists or end of parse is reached
      void deallocParser();
      void deallocCMDList();
      void exitProg();
};

#endif
