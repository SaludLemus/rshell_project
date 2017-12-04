#ifndef __PARSER_H__
#define __PARSER_H__
#include <string>
#include <cstring>
#include "base.h"
#include "and.h"
#include "or.h"
#include "semicolon.h"
#include "command.h"
#include "exit.h"
#include "test.h"
#include "pipe.h"
#include "input.h"
#include "output.h"
#include "append.h"

using namespace std;
class Parser {
	private:
		Base* root;
		string str;
		unsigned position;
	
	public:
		Parser();
		Parser(const string &);
		~Parser();
		void setString(const string &);
		void createTree();
		Base* getRoot(); // permit access to command class
	private:
		Base* nextCommand();
		Connector* nextConnector();
		Base* returnSpecialCommand();
		Base* returnTreeCommand();
		
		bool checkCharSize(size_t &, size_t, int &);
		void returnEndForParameters(size_t &, size_t &, size_t &);
		char* stringToCharStar(const string &);
};

#endif
