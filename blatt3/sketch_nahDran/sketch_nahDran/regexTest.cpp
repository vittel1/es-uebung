//Example 1
//#include <iostream>

#include <regex>
//#include <string>
#include "regexTest.h"
using namespace std;



bool testFormat(string input)
{
	regex format("^setRGB\\([[:digit:]]\\.[[:digit:]]\\, [[:space:][:digit:]]\\.[[:digit:]]\\, [[:space:][:digit:]]\\.[[:digit:]]\\)");
	return regex_match(input, format);
}

/*int main()
{
	bool input;
 	regex integer("^setRGB\\([[:digit:]]\\.[[:digit:]]\\, [[:space:][:digit:]]\\.[[:digit:]]\\, [[:space:][:digit:]]\\.[[:digit:]]\\)");
	//As long as the input is correct ask for another number
 
	input = testFormat("setRGB(1.0, 1.0, 1.0)");
	cout<<input<<endl;

	input = testFormat("skjbvksb");
	cout<<input<<endl;

	input = testFormat("setRGB(0.0, 0.2, 0.3)");
	cout<<input<<endl;

	input = testFormat("setRGB(-1.0, 0.0, 0.0)");
	cout<<input<<endl;
}*/
