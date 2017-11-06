/**
 * Copyright (C) 2017  Caio Moreira Gomes
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @Author: Caio M. Gomes
 * @Project: Truth table
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

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <vector> 
#include <cmath>

#define WEIRD_CHAR 13

using namespace std;

void read_s(FILE* f, string &a) {
	char buff[100000];
	// fgets (buff, 100000, f);
	fscanf(f, " %[^\n]", &buff);
	a = buff;
}

// Prototypes
int detect_op(char ch);
void sub_expr(string form, vector<string> &expr);
bool str_ord(string a, string b);
void printv(std::vector<string> v, FILE* fw);
void correct_t(vector<string> &expr);
int atomic(vector<string> expr);
int find_in_expr(string form, vector<string> expr);
bool eval_expr(string form, vector<string> expr, vector<int> valoration[], int step);
int check_vals(vector<int> evals[], int sz);
void print_bottom_line(vector <string> expr, FILE* fw);
void bs(vector<string> &expr, bool (*f)(string, string));

int main(int argc, char const *argv[]) {
	int n, atom_num = 0, buff;
	string form;
	vector<string> expr;
	vector<int> *evals;

	FILE* fp = fopen("Expressoes.in", "r");
	FILE* fw = fopen("Expressoes.out", "w");

	char dictionary[] = {'+', '.', '>', '-'};

	// cin >> n;
	fscanf(fp ," %d", &n);

	// getline(cin, form); // clean \n buffer
	// read_s(fp, form);

	for (int i = 0; i < n; ++i) {
		// cout << "Tabela #" << i+1 << endl;
		fprintf(fw, "Tabela #%d\n", i+1);

		// getline(cin, form);
		read_s(fp, form);
		sub_expr(form, expr);
		
		// qs(expr, 0, expr.size(), str_ord);
		bs(expr, str_ord);
		correct_t(expr);
		
		print_bottom_line(expr, fw);
		printv(expr, fw);
		print_bottom_line(expr, fw);

		evals = new vector<int>[expr.size()];
		
		atom_num = atomic(expr);

		// obs: evals[j] -> subexpressão
		for (int j = 0; j < (1 << atom_num); ++j) {
			eval_expr(form, expr, evals, j);
		}

		for (int j = 0; j < (1 << atom_num); ++j) {
			// cout << "|";
			fprintf(fw, "|");
			for (int k = 0; k < expr.size(); ++k) { // iters thourght every subexpression
				for (int l = 1; l < expr[k].size(); ++l) {
					if(expr[k][l] == WEIRD_CHAR) continue;
					// cout << " ";
					fprintf(fw, " ");
				}
				// cout << evals[k][j] << "|";
				fprintf(fw, "%d|", evals[k][j]);
			}
			// cout << endl;
			fprintf(fw, "\n");
			print_bottom_line(expr, fw);
		}

		buff = check_vals(evals, expr.size());
		switch(buff) {
			case 0:
				// cout << "satisfativel e refutavel" << endl;
				fprintf(fw, "satisfativel e refutavel\n");
				break;
			case 1:
				// cout << "insatisfativel e refutavel" << endl;
				fprintf(fw, "insatisfativel e refutavel\n");
				break;
			case 2:
				// cout << "satisfativel e tautologia" << endl;
				fprintf(fw, "satisfativel e tautologia\n");
				break;
			default:
				break;
		}
		// cout << endl;
		fprintf(fw, "\n");

		expr.clear();
	}

	fclose(fw);
	fclose(fp);
	
	return 0;
}

/**
 * @brief      Find all subexpressions.
 * Iters throught the string to find every single subexpression inside it.
 *
 * @param[in]  form  The string expression to find subexpressions.
 * @param      expr  The set of expressions where we should insert the expressions.
 */
void sub_expr(string form, vector<string> &expr) {
	
	int order = 0, op = 0, pos = -1, last_pos = 0;
	string str1, str2, *clone;

	// Adds the expression to the array if and only if the expression
	// isn't there yet.
	if(find_in_expr(form, expr) == -1){
		expr.push_back(form);
	}

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
				// cout << "operator at: " << i << endl;
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
		str1 = form.substr(pos + 1, last_pos - pos - 1); // ignore first and all last characters untill ignore all extra ')'
		sub_expr(str1, expr);
	}

	// if the operator isn't negation everything back him
	// and everything after him is part of the subexpression
	else { 
		
		last_pos = form.find_last_of(")");
		str2 = form.substr(pos + 1, last_pos - pos - 1); // ignore first and all last characters untill ignore all extra ')'

		// save form string to don't lose it with substr
		str1 = form.substr(1, pos - 1); // ignore first and last character

		sub_expr(str1, expr);
		sub_expr(str2, expr);
	}
}

/**
 * @brief      Defines which is the symbol operation in the propositional logic.
 *
 * @param[in]  ch    The symbol which we want to match with the logic operation.
 *
 * @return     A number representing the logic operation
 * 1 - disjunction (+)
 * 2 - conjunction (.)
 * 3 - implication (>)
 * 4 - negation (-)
 */
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

/**
 * @brief      Function that defines when a string is bigger than another one.
 * a is bigger than b if the size of a is bigger than the size of b, if the size
 * of the strings match, the string is ordered by lexicographic order, character
 * by character untill the first character not matching.
 *
 * @param[in]  a     The first string to compare.
 * @param[in]  b     The second string to compare.
 *
 * @return     1 if a < b and 0 if a > b
 */
bool str_ord(string a, string b) {
	if(a.size() == b.size()) {
		for (int i = 0; i < a.size(); ++i) {
			if(a[i] == b[i]) {
				continue;
			}
			else{
				return a[i] < b[i];
			}
		}
	}
	return a.size() < b.size();
}

/**
 * @brief      Prints an entire vector.
 *
 * @param[in]  v     Vector to print.
 */
void printv(std::vector<string> v, FILE* fw) {
	// cout << "|";
	fprintf(fw, "|");
	for (int i = 0; i < v.size(); ++i) {
		for (int j = 0; j < v[i].size(); ++j) {
			if(v[i][j] == WEIRD_CHAR) continue;
			// cout << v[i][j];
			fprintf(fw, "%c", v[i][j]);
		}
		// cout << "|";
		fprintf(fw, "|");
	}
	// cout << endl;
	fprintf(fw, "\n");
}

/**
 * @brief      Replace the t expression into the correct order.
 *
 * @param      expr  The expressions list.
 */
void correct_t(vector<string> &expr) {
	if(expr[0] == "t") {
		int pos = atomic(expr);
		for (int i = 1; i < pos; ++i) {
			swap(expr[i - 1], expr[i]);	
		}
	}
}

/**
  * @brief      Counts the number of atomic expressions inside the array.
  *
  * @param[in]  expr  The expression
  *
  * @return     The number of atomic expressions in expr list.
  */
int atomic(vector<string> expr) {
	int n = 0, sz = 0;
	for (int i = 0; i < expr.size(); ++i) {
		sz = 0;
		for (int j = 0; j < expr[i].size(); ++j) {
			if(expr[i][j] == WEIRD_CHAR) continue;
			sz++;
		}
		if(sz != 1) {
			break;
		}
		n++;
	}
	return n;
}

/**
 * @brief      Find the numeric position of a expression in the expr list.
 *
 * @param[in]  form  The expression.
 * @param[in]  expr  The expressions list.
 *
 * @return     The numeric position of the expression in expr list.
 * or -1 if didn't find the expression in the list.
 */
int find_in_expr(string form, vector<string> expr) {
	int ct = 0;

	// find the expression in the expr list
	for (int i = 0; i < expr.size(); ++i) {
		if(form == expr[i]) {
			break;
		}
		ct++;
	}

	if(ct == expr.size()) return -1;

	return ct;
}

/**
 * @brief      Evaluate all subexpressions in some specific expression.
 * Goes recursively find all the subexpressions untill the atomic ones,
 * them it gives to every atomic function the bit which it should receive,
 * them it goes returning the valorations and the upper expression gets
 * the received values to evaluate the high order expression untill the
 * original expression gets valorated.
 *
 * @param[in]  form        The expression to valorate.
 * @param[in]  expr        The expressions list.
 * @param      valoration  The valorations list.
 * @param[in]  step        The number with the binary representation to every atomic expression.
 *
 * @return     The boolean value of the expression received.
 */
bool eval_expr(string form, vector<string> expr, vector<int> valoration[], int step) {
	int order = 0, op = 0, pos = -1, last_pos = 0, ct = 0;
	bool eval, val1, val2;
	string str1, str2, *clone;

	ct = find_in_expr(form, expr);

	// If there aren't parenthesis it's atomic
	// And the system should stop
	if(form.find("(") == string::npos) {
		// eval the atomic exp	ression
		eval = (bool) ((step >> (atomic(expr) - ct - 1)) & 1); // just the bit wich belongs to the expression
		
		if(valoration[ct].size() == step) { // just add the expression value if didn't added yet
			valoration[ct].push_back(eval);
		}
		
		return eval;
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
				// cout << "operator at: " << i << endl;
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
		str1 = form.substr(pos + 1, last_pos - pos - 1); // ignore first and all last characters untill ignore all extra ')'
		eval = !eval_expr(str1, expr, valoration, step);
	}

	// if the operator isn't negation everything back him
	// and everything after him is part of the subexpression
	else { 
		
		last_pos = form.find_last_of(")");
		str2 = form.substr(pos + 1, last_pos - pos - 1); // ignore first and all last characters untill ignore all extra ')'
		str1 = form.substr(1, pos - 1); // ignore first and last character

		val1 = eval_expr(str1, expr, valoration, step);
		val2 = eval_expr(str2, expr, valoration, step);
	}


	switch(op) {
		case 1:
			eval = val1|val2;
			break;
		case 2:
			eval = val1&val2;
			break;
		case 3:
			eval = (!val1)|(val2);
			break;
		default:
			break;
	}

	if(valoration[ct].size() == step) { // just add the expression value if didn't added yet
		valoration[ct].push_back(eval); // add to the valorations list
	}	

	return eval;
}


/**
 * @brief      Check whether the expression is sat, insat, tautology or refutable
 *
 * @param      evals  The evals list.
 * @param[in]  sz     The number of subexpressions.
 *
 * @return     0 - (sat|ref)
 *             1 - (insat|ref)
 *             2 - (sat|taut).
 */
int check_vals(vector<int> evals[], int sz) {
	int z = 0, u = 0, st = 0;
	
	for (int i = 0; i < evals[sz - 1].size(); ++i) {
		if(evals[sz - 1][i]) {
			u++;
		}
		else {
			z++;
		}
	}

	if( z == evals[sz - 1].size() ) { // insat
		st = 1;
	}
	if( u == evals[sz - 1].size() ) { // insat
		st = 2;
	}

	return st;
}

/**
 * @brief      Prints a number of "-" equivalent to the size of the expressions list.
 *
 * @param[in]  expr  The expressions list.
 */
void print_bottom_line(vector <string> expr, FILE* fw) {
	for (int j = 0; j < expr.size(); ++j) {
		for (int k = 0; k < expr[j].length(); ++k) {
			if(expr[j][k] == WEIRD_CHAR) continue;
			// cout << "-";
			fprintf(fw, "-");
		}
		// cout << "-";
		fprintf(fw, "-");
	}
	// cout << "-" << endl;
	fprintf(fw, "-\n");
}

/**
 * @brief      Bubble sort for a vector of strings.
 *
 * @param      expr  The expressions list.
 * @param[in]  f     The function that defines lower element.
 */
void bs(vector<string> &expr, bool (*f)(string, string)) {
	for (int i = 0; i < expr.size(); ++i) {
		for (int j = 1; j < expr.size(); ++j) {
			if(f(expr[j], expr[j - 1])) swap(expr[j], expr[j - 1]);
		}
	}
}