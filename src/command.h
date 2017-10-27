#ifndef Command_h_
#define Command_h_

#include "parse.h"
#include "commandline.h"
#include <iostream>
#include <string>
using namespace std;

class Command {
   public:
      void init(const string &);
   private:
      Parse* parse_cmd;
      List<CommandLine*> cmd_list;
      void commandIterator();
      void exit();
};

#endif
