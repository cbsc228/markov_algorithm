//------------------------------------------
//              class markovRule
//------------------------------------------
// Describes a Markov Rule for a string input
//------------------------------------------
#include <string>
using namespace std;

class markovRule {
public:
	//default constructor
	markovRule(); 
	//overloaded constructor
	markovRule(int newRuleNum, string newLeftSide, string newRightSide, int newNextRule);
	//gets current rule int
	int getRuleNum();
	//gets current rule left string
	string getLeftSide();
	//gets current rule right string
	string getRightSide();
	//gets next rule int
	int getNextRule();
private:
	//which rule this one is
	int ruleNum;
	//describes the part of the string to check
	string leftSide;
	//describes the string to replace the matched leftSide
	string rightSide;
	//describes the next rule to move to
	int nextRule;
};