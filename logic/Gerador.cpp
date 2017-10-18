/**
 * @Author: Caio M. Gomes
 * @Description: Project presented to the discipline of Logic for Computer Sciences
 * @Place: Recife
 * @Year: 2017
 * 
 * Algorithm:
 * -> Read the Expression
 * -> Extract all subexpressions 
 * -> Order subexpression
 * -> Evaluate the subexpressions from atomic expressions untill the last one
 * 
 * Dictionary:
 * -> + or
 * -> . and
 * -> > so
 * -> - negate
 */

// #include <bits/stdc++.h> // TODO: modificar a biblioteca importada
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <vector> 
#include <cmath>

using namespace std;

// Prototypes
int detect_op(char ch);
void sub_expr(string form, vector<string> expr);

int main(int argc, char const *argv[]) {
	int n;
	string form;
	vector<string> expr;

	cin >> n;
	char dictionary[] = {'+', '.', '>', '-'};

	getline(cin, form); // clean \n buffer

	for (int i = 0; i < n; ++i) {
		getline(cin, form);
		cout << form << endl;
		sub_expr(form, expr);
		/* code */
	}
	

	return 0;
}


/**
 * @brief Find all subexpressions
 * @details Iters throught the string to find every single subexpression
 * that's insed of it
 * 
 * @param form the string expression to subexpress
 * @param expr The set of expressions that will beoutputed
 */
void sub_expr(string form, vector<string> expr) {
	
	int order = 0, op = 0, pos = -1, last_pos = 0;
	string str1, str2, *clone;
	cout << "-- expression : " << form << " --" << endl;

	// Adds the expression to the array
	expr.push_back(form);

	// If there aren't parenthesis it's atomic
	// And the system should stop
	if(form.find("(") == string::npos) {
		return;
	}

	// If the expression isn't atomic, need to find
	// the operator and the first order expressions
	// it means, get the value inside the parenthesis
	for (int i = 0; i < form.length(); ++i) {
		if(form[i] == '(') {
			order++;
			continue;
		}

		if(form[i] == ')') {
			order--;
			continue;
		}

		if(order == 1) {
			op = detect_op(form[i]);
			// find the expressions to evaluate 
			if(op != 0) {
				cout << "operator at: " << i << endl;
				pos = i;
				break;
			}
			
		}
	}

	// if the operator is negation, them, everything
	// after that is part of subexpression
	if(op == 4) { // op -> -
		// find the last ')'
		last_pos = form.find_last_of(")");
		str1 = form.substr(pos + 1, last_pos - 1); // ignore first and all last characters untill ignore all extra ')'
		sub_expr(str1, expr);
	}

	// if the operator isn't negation everything back him
	// and everything after him is part of the subexpression
	else { // TODO: make the last part become corret
		// save form string to don't lose it with substr
		str1 = form.substr(1, pos - 1); // ignore first and last character

		last_pos = form.find_last_of(")");

		str2 = form.substr(pos + 1, last_pos - 3); // ignore first and all last characters untill ignore all extra ')'
		// str2 = form.substr(pos, last_pos - 1);

		cout << "kuku " << str2 << endl;

		sub_expr(str1, expr);
		sub_expr(str2, expr);
	}
}

int detect_op(char ch) {
	int op = 0;
	char dictionary[] = {'+', '.', '>', '-'};

	for (int i = 0; i < 4; ++i) {
		if(ch == dictionary[i]) {
			op = i + 1;
			break;
		}
	}

	return op;
}