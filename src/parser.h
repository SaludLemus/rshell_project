#ifndef parser_h_
#define parser_h_
#include <string>
#include "commandline.h"

using std::string;
class Parser {
	private:
		string str;
		unsigned position;
	
	public:
		Parser();
		Parser(const string & user_input);
		CommandLine* nextParse(); // permit access to command class
	private:
		void removeLastChar();
		int ifLast(size_t &, size_t &);
};

#endif
