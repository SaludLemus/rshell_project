#ifndef parser_h_
#define parser_h_
#include <boost/tokenizer.hpp>
#include <string>
using namespace std;
class Parser {
	public:
		Parser();
		Parser(const string &);
		string nextParse();
		void removeLastChar();
		bool ifLast(const string&);
		string current_parse; // permit access to command class
	private:
		Tokenizer str;
};

#endif
