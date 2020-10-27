#include "markovRule.h"

markovRule::markovRule() {
	ruleNum = -1;
	leftSide = "";
	rightSide = "";
	nextRule = -1;
} // constructor (default)

markovRule::markovRule(int newRuleNum, string newLeftSide, string newRightSide, int newNextRule) {
	ruleNum = newRuleNum;
	leftSide = newLeftSide;
	rightSide = newRightSide;
	nextRule = newNextRule;
} // overloaded constructor

int markovRule::getRuleNum(){
	return ruleNum;
}

string markovRule::getLeftSide(){
	return leftSide;
}

string markovRule::getRightSide(){
	return rightSide;
}

int markovRule::getNextRule(){
	return nextRule;
}