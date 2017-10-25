/**
 * Truth table
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
 * @Description: Project presented to the discipline of Logic for Computer Sciences
 * @Place: Recife
 * @Year: 2017
 * 
 * Algorithm:
 * -> Read the Expression
 * -> Check if expressions are in FNC
 * -> Extract all clauses
 * -> Verify if all are horn clauses
 * -> Order descending order every clause
 * -> Find the first atomic clause "x" or "-x"
 * -> Iter untill the expr list
 * -> Go pushing back the results of supressions
 * untill find the end of the array or find the
 * a empty clause "()"
 * -> Print the sat result
 * 
 * 
 * Dictionary:
 * -> + or
 * -> . and
 * -> > so
 * -> - negate
 * 
 * 
 * 
 * TODO: CORRECT THE CLAUSE REMOTION
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
	fscanf(f, " %[^\n]", &buff);
	a = buff;
}

// Prototypes
int detect_op(char ch);
void sub_expr(string form, vector<string> &expr);
bool str_ord(string a, string b);
void printv(std::vector<string> v, FILE* fw);
void print_bottom_line(vector <string> expr, FILE* fw);
void bs(vector<string> &expr, bool (*f)(string, string));
int ex_clause(string form, vector<string> &expr);
bool check_horn(vector<string> &expr);
bool check_atomic(string form);
int eval_expr(vector<string> &expr);
void reduce_clauses(string c1, string c2, vector<string> &expr);

int main(int argc, char const *argv[]) {
	int n, atom_num = 0, buff, result;
	string form;
	vector<string> expr;

	FILE* fp = fopen("Expressoes.in", "r");
	FILE* fw = fopen("Expressoes.out", "w");

	char dictionary[] = {'+', '.', '>', '-'};

	fscanf(fp ," %d", &n);

	for (int i = 0; i < n; ++i) {
		
		fprintf(fw, "caso #%d\n", i+1);
		read_s(fp, form); // Read clause

		// extract every horn clause
		if(ex_clause(form, expr) == -1) {
			fprintf(fw, "nao esta na FNC\n");
		}

		else if(!check_horn(expr)){
			fprintf(fw, "nem todas as clausulas sao de horn\n");

		}

		else {
			// fprintf(fw, "?????\n");
			bs(expr, str_ord);
			printv(expr, fw);
			result = eval_expr(expr);
			printv(expr, fw);
		}

		

		expr.clear();
	}

	fclose(fw);
	fclose(fp);
	
	return 0;
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
		for (int i = 0; i > a.size(); ++i) {
			if(a[i] == b[i]) {
				continue;
			}
			else{
				return a[i] > b[i];
			}
		}
	}
	return a.size() > b.size();
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


/**
 * @brief      Extracts every horn clausule of the string expression.
 *
 * @param[in]  form  The formula.
 * @param      expr  The expressions list.
 *
 * @return     -1 if not in FNC.
 */
int ex_clause(string form, vector<string> &expr) {
	
	string buff = "";
	int st = 0;
	int max_ord = 0;

	for (int i = 0; i < form.size(); ++i) {
		if(form[i] == ' ') {
			continue;
		}

		if(form[i] == '(') {
			st++;
		}

		if(st > 0) {
			buff.push_back(form[i]);
		}

		if(form[i] == ')'&& st == 1) {
			st--;
			expr.push_back(buff);
			buff = "";
			continue;
		}

		if(st == 0 && detect_op(form[i]) != 2) { // other than the . operator
			return -1;
		}

		if(st > 1) {//  more than one subexpression by term
			return -1;	
		}

		if(st == 1 && detect_op(form[i]) > 1 && detect_op(form[i]) != 4) { // other than the + operator
			return -1;
		}
	}

	return 0;
}

bool check_horn(vector<string> &expr) {

	int atoms, m;

	for(int i = 0; i < expr.size(); i++) {
		
		atoms = 0;
		m = 0;
		
		// count atomics and '-' signals, if n(-) < n(atoms) - 1 -> not horn
		for (int j = 0; j < expr[i].size(); ++j) {
			if(expr[i][j] >= 'a' && expr[i][j] <= 'd') 
				atoms++;
			if(expr[i][j] == '-')
				m++;


			// check operators, if diff from '+' not horn
			if(detect_op(expr[i][j]) > 1 && detect_op(expr[i][j]) < 4) {
				return 0;
			}
		}
		if( m < atoms - 1)
			return 0;

	}

	return 1;
}

/**
 * @brief      Verify if a horn clause is "atomic" or not.
 *
 * @param[in]  form  The expression.
 *
 * @return     True if is horn clase and false in opposite.
 */
bool check_atomic(string form) {
	// for well formed clauses every atomic clause will be:
	// "()"
	// "(x)"
	// "(-x)"
	// and non atomic clauses will be at least:
	// "(a+b)"
	return form.size() <= 4; 
}

/**
 * @brief      Verify if the expression is sat or not.
 *
 * @param      expr  The expressions list.
 *
 * @return     0 if not sat and 1 if sat.
 */
int eval_expr(vector<string> &expr) {

	int i = 0, eval = 0;

	for (; i < expr.size(); ++i) {
		if(check_atomic(expr[i])) {
			break;
		}
	}

	if(i == expr.size()) { // no atomic clauses to verify
		return 0;
	}

	for (; i < expr.size(); ++i) {
		// verify if we are looking at some void clause
		if(expr[i].size() == 2) {
			eval = 1;
			break;
		}
		// search for the atomic representants in every string behind it
		for (int j = 0; j < i; ++j) {
			reduce_clauses(expr[i], expr[j], expr);
		}
	}

	return eval;
}

/**
 * @brief      Reduce two clauses of horn based on a atomic one.
 *
 * @param[in]  c1    The first clause.
 * @param[in]  c2    The second clause.
 * @param      expr  The expressions list.
 */
void reduce_clauses(string c1, string c2, vector<string> &expr) {
	
	char ch;
	string str, bf = "";
	int neg = 0, pos = 0;

	if(str_ord(c1, c2)) swap(c1, c2); // force the first one to be the lower

	for (int i = 1; i < c1.size(); ++i) {
		if(c1[i] >= 'a' && c1[i] <= 'd') {
			ch = c1[i];
			
			// verify if negated
			if(c1[i-1] == '-') {
				neg = 1;
			}

			break;
		}
	}

	// in the c2 we want to check if there is ch and -ch
	if(neg) {
		bf = "-";
	}
	bf.push_back(ch);

	pos = c2.find(bf);

	if(pos != string::npos) {
		c2.erase(pos, pos - neg); // remove the clause
		// remove the operator if exists
		if(c2[pos - 1] == '+') {
			c2.erase(pos - 1, 1);
		}
		expr.push_back(c2);
	}

}
