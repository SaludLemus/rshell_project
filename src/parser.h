#ifndef parser_h_
#define parser_h_
#include <string>
#include "commandline.h"

using namespace std;
class Parser {
	private:
		string str;
		size_t position;
	
	public:
		Parser();
		Parser(const string & user_input);
		CommandLine nextParse(); // permit access to command class
	private:

		void removeLastChar();
		bool ifLast();
};

#endif
