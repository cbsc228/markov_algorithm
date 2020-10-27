#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include "markovRule.h"

using namespace std;

//used as the size of the array that stores the markovRules
const int MAX_NUM_RULES = 1000;

//gets the user input file
string getInputFile(){
	string inputFile;
	cout << "Input file: ";
	cin >> inputFile;
	cout << endl;
	return inputFile;
}

//reads the user provided .txt file and stores the data in the markovRule class
int readFile(markovRule ruleList[]){
	ifstream inFile;
	inFile.open(getInputFile());
	if(inFile.fail()){
		cout << "Error: could not open requested .txt file" << endl;
		return 0;
	}
	string stringTotalNumRules = "";
	int totalNumRules;
	string leftSide = "";
	string rightSide = "";
	string stringRuleNum = "";
	int ruleNum;
	string inputString;
	inFile >> inputString;
	int index = 0;
	//gets the total number of rules to expect
	while(inputString[index] != '\''){
		stringTotalNumRules += inputString[index];
		index += 1;
	}
	//converts the string to an int
	stringstream convertTotal(stringTotalNumRules);
	convertTotal >> totalNumRules;
	if(totalNumRules > MAX_NUM_RULES){
		cout << "Error: Maximum number of rules exceeded" << endl;
		return -1;
	}
	//gets the rest of the rules
	int count = 0;
	while(count < totalNumRules){
		leftSide = "";
		rightSide = "";
		stringRuleNum = "";
		//gets leftSide
		index += 1;
		while(inputString[index] != '\''){
			leftSide += inputString[index];
			index += 1;
		}
		index += 2;
		//get rightSide
		while(inputString[index] != '\''){
			rightSide += inputString[index];
			index += 1;
		}
		index += 1;
		//get nextRuleNum
		while(inputString[index] != '\'' && inputString[index] != '\000'){
			stringRuleNum += inputString[index];
			index += 1;
		}
		//convert string to int
		stringstream convertRuleNum(stringRuleNum);
		convertRuleNum >> ruleNum;
		//add the new rule to the list of rules
		markovRule* newRule = new markovRule(count, leftSide, rightSide, ruleNum);
		ruleList[count] = *newRule;
		count += 1;
	}
	//close the .txt file
	inFile.close();
	return totalNumRules;
}

//lists the rules imported from the user provided .txt file
void printRulesTable(markovRule ruleList[], int numRules){
	cout << "Num     Left     Right     NextRule" << endl;
	for(int i = 0; i < numRules; i++){
		int ruleNum = ruleList[i].getRuleNum();
		string stringRuleNum = to_string(ruleNum);
		int ruleNumLength = stringRuleNum.length();
		string leftSide = ruleList[i].getLeftSide();
		int leftSideLength = leftSide.length();
		string rightSide = ruleList[i].getRightSide();
		int rightSideLength = rightSide.length();
		int nextRule = ruleList[i].getNextRule();
		string stringNextRule = to_string(nextRule);
		int nextRuleLength = stringNextRule.length();
		cout << stringRuleNum << " " << setw(10 - ruleNumLength)
			 << leftSide << " " << setw(10)
			 << rightSide << " " << setw(12)
			 << stringNextRule << endl;
	}
}

//checks if a given string exists in the main string,
//if there is a match returns the index of the beginning of the match
//if there is no match returns -1
//method utilized: Boyer-Moore Method (Backward search)
int matchSubstring(string currentString, string leftSide){
	if(currentString == leftSide){//base case for if strings are entierly identical
		return 0;
	}
	int currentStringLength = currentString.length();
	int leftSideLength = leftSide.length();
	int currentIndex = 0;
	while(currentIndex+leftSideLength <= currentStringLength){
		int leftIndex = leftSideLength - 1;
		while(currentString[currentIndex+leftIndex] == leftSide[leftIndex]){
			leftIndex -= 1;
			if(leftIndex < 0){
				return currentIndex;//match found, returning index of where the match starts
			}
		}
		currentIndex += 1;
	}
	return -1;//no match found
}

//calls matchSubstring to check if the currentString has a match to the currentRule
//if there is a match, does the substring replacement and returns the next rule stored in the currentRule
//if there is no match, does no replacement and returns the numerically next rule
int performRule(markovRule currentRule, string &currentString){
	int nextRule;
	string leftSide = currentRule.getLeftSide();
	int leftSideLength = leftSide.length();
	string rightSide = currentRule.getRightSide();
	int rightSideLength = rightSide.length();
	int stringMatchIndex;
	int rightIndex = 0;
	stringMatchIndex = matchSubstring(currentString, leftSide);
	if(stringMatchIndex != -1){//rule was a match, return the rule num stored as the next rule in the current rule
		string leftPart = "";
		string middlePart = "";
		string rightPart = "";
		for(int i = 0; i < stringMatchIndex; i++){
			leftPart += currentString[i];
		}
		middlePart = rightSide;
		for(int j = stringMatchIndex + leftSideLength; j< currentString.length(); j++){
			rightPart += currentString[j];
		}
		currentString = leftPart + middlePart + rightPart;
		return currentRule.getNextRule();
	}
	else{//rule was not a match, return the numerically next rule num
		int currentRuleNum = currentRule.getRuleNum();
		currentRuleNum += 1;
		return currentRuleNum;
	}
}

//starts the Markov Algorithm
void markovAlgorithm(markovRule ruleList[], int numRules){
	int nextRule = 0;
	string currentString = "";
	//output top of output table
	cout << "Rule" << "       " << "Mainstring (after the rule)" << endl;
	//starting at the first rule, complete them until the last one has been completed.
	//change the iterator either to the (n+1) where n is the current rule number in the case
	//that the next rule is not a match, or change the iterator to the next rule stored in 
	//the current rule being processed
	for(int currentRule = 0; currentRule < numRules; currentRule = nextRule){
		//currentString is passed by reference
		nextRule = performRule(ruleList[currentRule], currentString);
		//output processed info
		int nextRuleLength = to_string(nextRule).length();
		string currentRuleNum = to_string(ruleList[currentRule].getRuleNum());
		cout << currentRuleNum << " " << setw(20-nextRuleLength) << currentString << endl;
	}
}

int main(){
	int numRules;
	//defines the array to hold the markov rules in numerical order
	markovRule ruleList[MAX_NUM_RULES];
	//reads in data
	numRules = readFile(ruleList);
	if(numRules == -1){
		return -1;
	}
	//prints table of rules
	printRulesTable(ruleList, numRules);
	//performs the markov algorithm according to the provided rules
	markovAlgorithm(ruleList, numRules);
	return 0;
}