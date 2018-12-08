/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <string>
#include "statement.h"
#include "program.h"

#include "../StanfordCPPLib/tokenscanner.h"
#include "parser.h"
using namespace std;

/* Implementation of the Statement class */

Statement::Statement() {
   /* Empty */
}

Statement::~Statement() {
   /* Empty */
}

/*-----------------------------------------------------*/
/*-----------------------------------------------------*/
/*-----------------------------------------------------*/
/*-----------------------------------------------------*/
/*-----------------------------------------------------*/
/*-----------------------------------------------------*/

void Let::execute(EvalState & state)
{
	if (run)
		state.setValue(var, value);
}

bool Let::is_statement(EvalState & state) {
	string _line = line.substr(line.find("LET"));
	TokenScanner scanner;
	scanner.ignoreWhitespace();
	scanner.scanNumbers();
	scanner.setInput(_line);
	string head = scanner.nextToken();
	string _var;
	_var = scanner.nextToken();
	string op = scanner.nextToken();
	if (op != "=") return false;
	Expression *exp = parseExp(scanner);
	int _value = exp->eval(state, run);
	var = _var;
	value = _value;
	return true;
}

/*-----------------------------------------------------*/
/*-----------------------------------------------------*/
/*-----------------------------------------------------*/
/*-----------------------------------------------------*/
/*-----------------------------------------------------*/
/*-----------------------------------------------------*/

void Input::getvar()
{
	string _line = line.substr(line.find("INPUT") + 5);
	TokenScanner scanner;
	scanner.ignoreWhitespace();
	scanner.scanNumbers();
	scanner.setInput(_line);
	var = scanner.nextToken();
}

bool Input::is_statement(EvalState & state) {
	TokenScanner scanner;
	scanner.ignoreWhitespace();
	scanner.scanNumbers();
	scanner.setInput(line);
	string head = scanner.nextToken();
	string var = scanner.nextToken();
	if (var == "" || scanner.hasMoreTokens() || !((isupper(var[0]) || islower(var[0])))) return false;
	return true;
}

void Input::execute(EvalState & state)
{
	getvar();
	string _value;
	TokenScanner scanner;
	scanner.ignoreWhitespace();
	scanner.scanNumbers();
	while (1) {
		cout << " ? ";
		
		_value.clear();
		char ch = getchar();
		while (ch != '\n')
			_value.push_back(ch), ch = getchar();

		bool f = true;
		for (int i = 0; i < _value.length(); ++i) {
			if (i == 0 && _value[i] == '-') continue;
			if (!isdigit(_value[i])) {
				f = false;
				cout << "INVALID NUMBER" << endl;
				break;
			}
		}
		if (f) {
			int value;
			value = stringToInteger(_value);
			state.setValue(var, value);
			break;
		}
	}
}

/*-----------------------------------------------------*/
/*-----------------------------------------------------*/
/*-----------------------------------------------------*/
/*-----------------------------------------------------*/
/*-----------------------------------------------------*/
/*-----------------------------------------------------*/
void If::execute(EvalState & state)
{
	gotolinenum = -1;
	switch (if_op) {
	case '=': if (value1 == value2) gotolinenum = linenum; break;
	case '>': if (value1 >  value2) gotolinenum = linenum; break;
	case '<': if (value1 <  value2) gotolinenum = linenum; break;
	}
}

bool If::is_statement(EvalState & state) 
{
	char op = '0';
	if (line.find("=") != string::npos) op = '=';
	if (line.find("<") != string::npos) {
		if (op != '0') return  false;
		op = '<';
	}
	if (line.find(">") != string::npos) {
		if (op != '0') return false;
		op = '>';
	}
	if (line.find("THEN") == string::npos || !(line.find(op) < line.find("THEN")))	return false;
	if_op = op;

	auto pos_if = line.find("IF"), pos_op = line.find(op), pos_then = line.find("THEN");
	exp1 = line.substr(pos_if + 2, pos_op - pos_if - 2); 
	exp2 = line.substr(pos_op + 1, pos_then - pos_op - 1);
	TokenScanner expscanner;
	expscanner.ignoreWhitespace();
	expscanner.scanNumbers();
	expscanner.setInput(exp1);
	Expression *exp = parseExp(expscanner);
	value1 = exp->eval(state, run);

	expscanner.setInput(exp2);
	exp = parseExp(expscanner);
	value2 = exp->eval(state, run);
	
	string tlinenum = line.substr(pos_then + 4);
	expscanner.setInput(tlinenum);
	tlinenum = expscanner.nextToken();
	if (expscanner.hasMoreTokens() || !(isdigit(tlinenum[0]))) return false;
	linenum = stringToInteger(tlinenum);
	return true;
}

int If::getlinenum() {
	return gotolinenum;
}
/*-----------------------------------------------------*/
/*-----------------------------------------------------*/
/*-----------------------------------------------------*/
/*-----------------------------------------------------*/
/*-----------------------------------------------------*/
/*-----------------------------------------------------*/
bool Goto::is_statement(EvalState & state)
{
	string _line = line.substr(line.find("GOTO") + 4);
	TokenScanner scanner;
	scanner.ignoreWhitespace();
	scanner.scanNumbers();
	scanner.setInput(_line);
	string num = scanner.nextToken();
	if (scanner.hasMoreTokens() || !(isdigit(num[0]))) return false;
	linenum = stringToInteger(num);
	return true;
}

/*-----------------------------------------------------*/
/*-----------------------------------------------------*/
/*-----------------------------------------------------*/
/*-----------------------------------------------------*/
/*-----------------------------------------------------*/
/*-----------------------------------------------------*/
void Print::execute(EvalState & state)
{
	string _line = line.substr(line.find("PRINT") + 5);
	TokenScanner scanner;
	scanner.ignoreWhitespace();
	scanner.scanNumbers();
	scanner.setInput(_line);
	Expression *exp = parseExp(scanner);
	int value = exp->eval(state, run);
	if (run) cout << value << endl;
}
