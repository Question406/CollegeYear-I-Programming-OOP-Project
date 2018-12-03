/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include <string>
#include <algorithm>
#include <iterator>
#include "program.h"
#include "statement.h"
using namespace std;

Program::Program() {
    // Replace this stub with your own code
}

Program::~Program() {
    // Replace this stub with your own code
	Linenumber.clear();
	program.clear();
}

void Program::clear() {
    // Replace this stub with your own code
	Linenumber.clear();
	program.clear();
}

void Program::addSourceLine(int lineNumber, string line) {
	
    // Replace this stub with your own code
	int t = lower_bound(Linenumber.begin(), Linenumber.end(), lineNumber) - Linenumber.begin();

	if (t == Linenumber.size()){
		Linenumber.push_back(lineNumber);
		program.insert(pair<int, string> (lineNumber, line));
		return;
	}

	if (Linenumber[t] == lineNumber){
		program[lineNumber] = line;
		return;
	}
	int p = Linenumber.size() - 1;
	Linenumber.push_back(Linenumber[p]);
	for (int i = p; p > t; --i)
		Linenumber[i] = Linenumber[i + 1];
	Linenumber[t] = lineNumber;
	program.insert(pair<int, string>(lineNumber, line));
}

void Program::removeSourceLine(int lineNumber) {
	map<int, string>::iterator iter = program.find(lineNumber);
	program.erase(iter);
	int tmp = lower_bound(Linenumber.begin(), Linenumber.end(), lineNumber) - Linenumber.begin();
	Linenumber.erase(Linenumber.begin() + tmp);
    // Replace this stub with your own code
}

string Program::getSourceLine(int lineNumber) {
	return program[lineNumber];
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
    // Replace this stub with your own code
}

Statement *Program::getParsedStatement(int lineNumber) {
    return NULL;  // Replace this stub with your own code
}

int Program::getFirstLineNumber() {
	if (Linenumber.size() != 0) 
		return Linenumber[0];     // Replace this stub with your own code
}

int Program::getNextLineNumber(int lineNumber) {
	for (int i = 0; i < Linenumber.size(); ++i)
		if (Linenumber[i] == lineNumber) return i;
    return 0;     // Replace this stub with your own code
}

void Program::printProgram() {
	for (int i = 0; i < Linenumber.size(); ++i)
		cout << program[i] << endl;
	return;
}
