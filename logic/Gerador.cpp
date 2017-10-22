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
 * 
 * TODO: make an evaluation function which receives the operator as argument and
 * the expressions them it make the correct operation of evaluating the funcion.
 * 
 * TODO: make an evaluating function and iterate throught the 2^a, where a = number
 * of atomic expressions.
 *  - make a vector of evaluations and put all the evaluations into it in growing
 *  order, that means, in every expression the table should have an expression to
 *  the old expression, them we store everything and go consulting the table and
 *  comparing the strings to see if they match, and if they do, we should evaluate
 *  the parts of the expression as values.
 *  
 *  - go spliting the expressions untill find a atomic funcion, them we get the
 *  correct eval from the param (evals) which is an integer containing the correct
 *  number of evals
 *  x_eval = eval & 1
 *  y_eval = (eval << 1) & 1
 *  z_eval = (eval << 2) & 1
 *  t_eval = (eval << 3) & 1
 */

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
void sub_expr(string form, vector<string> &expr);
bool str_ord(string a, string b);
void printv(std::vector<string> v);
void printvec(std::vector<string> v, int b, int e);
void qs(vector<string> &ls, int b, int e, bool (*f)(string, string));

int main(int argc, char const *argv[]) {
	int n;
	string form;
	vector<string> expr;

	cin >> n;
	char dictionary[] = {'+', '.', '>', '-'};

	getline(cin, form); // clean \n buffer

	for (int i = 0; i < n; ++i) {
		getline(cin, form);
		// cout << form << endl;
		sub_expr(form, expr);
		/* code */
		for (int j = 0; j < expr.size(); ++j) {
			string buff = expr[j];
			// cout << buff << " | ";
		}
		// cout << endl;

		qs(expr, 0, expr.size(), str_ord);

		printv(expr);	

		expr.clear();
	}
	

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
			// cout << a[i] << " <-> " << b[i] << endl;
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
 * @brief      Swap two strings
 *
 * @param      a     First string to swap.
 * @param      b     Second string to swap.
 */
void swap_st(string &a, string &b){
	string t = a;
	a = b;
	b = t;
}

/**
 * @brief      Split the array to use quicksort in strings
 *
 * @param      ls    The list of strings reference
 * @param[in]  b     The begining point where to apply the function
 * @param[in]  e     The ending point where to apply the function
 * @param[in]  f     The function that controls the ">" evaluation
 *
 * @return     The element that already is in the correct order
 */
int sp(vector<string> &ls, int b, int e, bool (*f)(string, string)) {
	int i = b + 1, j = e - 1;
	int pivot = b;

	// printvec(ls, b, e);
	// cout << "pivot: " << ls[pivot] << endl;

	while(i < j) {
		for (; i < e && f(ls[i], ls[pivot]); ++i) {
			// cout << ls[pivot] << "|" << ls[pivot].size() << " : " << ls[i] << "|" << ls[i].size() << endl;
		}
		for (; j > i && !f(ls[j], ls[pivot]); --j) {
			// cout << ls[pivot] << "|" << ls[pivot].size() << " <> " << ls[j] << "|" << ls[j].size() << endl;
		}
		if(i <= j) {
			swap_st(ls[i], ls[j]);
			i++;
			j--;
		}
	}

	if(!f(ls[pivot], ls[j])) {
		swap_st(ls[pivot], ls[j]);	
		// cout << "swapped: " << ls[pivot] << " " << ls[j] << endl;
	}

	return j;
}

/**
 * @brief      A string array quicksort algorithm
 *
 * @param      ls    the array vector reference
 * @param[in]  b     The begining point where to apply the function
 * @param[in]  e     The ending point where to apply the function
 * @param[in]  f     The function that controls the ">" evaluation
 */
void qs(vector<string> &ls, int b, int e, bool (*f)(string, string)) {
	if(e <= b) {
		return;
	}
	// cout << "b: " << b << " e: " << e << endl;
	// printv(ls);

	int h = sp(ls, b, e, f);

	// qs(ls, b, h - 1, f);
	qs(ls, b, h, f);
	qs(ls, h + 1, e, f);
}

/**
 * @brief      Prints an entire vector.
 *
 * @param[in]  v     Vector to print.
 */
void printv(std::vector<string> v){
	for (int i = 0; i < v.size(); ++i) {
		cout << v[i] << " ";
	}
	cout << endl;
}

/**
 * @brief      Prints a vector from an element b to e.
 *
 * @param[in]  v     Vector to print.
 * @param[in]  b     Beginning element to print.
 * @param[in]  e     Ending element to print.
 */
void printvec(std::vector<string> v, int b, int e){
	for (int i = b; i < e && i < v.size(); ++i) {
		cout << v[i] << " ";
	}
	cout << endl;
}

// Receive the big expression, them go spliting it and evaluating it, them insert it
// into the pair that should be plotted in the end of the program.
void eval(vector<string> ls, ) {

}