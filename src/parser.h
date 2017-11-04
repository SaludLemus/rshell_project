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
		int checkConnectorForParameters(size_t &, size_t &, int &);
		void returnEndForParameters(size_t &, size_t &);
		int checkConnectorForCommand(size_t &, size_t &);
		char* stringToCharStar(const string &);
};

#endif
