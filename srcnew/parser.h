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

using namespace std;
class Parser {
	private:
		Base* root;
		string str;
		unsigned position;
	
	public:
		Parser();
		Parser(const string &);
		void setString(const string &);
		void createTree();
		Base* getRoot(); // permit access to command class
	private:
		Command* nextCommand();
		Connector* nextConnector();
		Command* returnSpecialCommand();
		bool checkCharSize(size_t &, size_t, int &);
		void returnEndForParameters(size_t &, size_t &);
		char* stringToCharStar(const string &);
};

#endif
