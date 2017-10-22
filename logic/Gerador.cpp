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
 *  - make a vector of evaluations and put all the evaluations into it in growing
 *  order, that means, in every expression the table should have an expression to
 *  the old expression, them we store everything and go consulting the table and
 *  comparing the strings to see if they match, and if they do, we should evaluate
 *  the parts of the expression as values.
 *  
 *  - go spliting the expressions untill find a atomic funcion, them we get the
 *  correct eval from the param (evals) which is an integer containing the correct
 *  number of evals
 *  first_eval = eval & 1
 *  second_eval = (eval << 1) & 1
 *  third_eval = (eval << 2) & 1
 *  forth_eval = (eval << 3) & 1
 *  
 *  TODO: read from text file
 *  TODO: correct quicksort problem in the case:
 *  |x|y|z|t|(-x)|((-x)+t)|(y.(-x))|(-((-x)+t))|((-((-x)+t)).z)|((y.(-x)).((-x)+t))|((-x)>((-((-x)+t)).z))|(((-x)>((-((-x)+t)).z)).((y.(-x)).((-x)+t)))|((((-x)>((-((-x)+t)).z)).((y.(-x)).((-x)+t)))+(-((-x)+t)))|
 *  which is mismatching the (-x) and the z
 *  also: |x|y|z|(-x)|(-y)|(z.x)|(z>x)|((z>x)+z)|(z+(z>x))|(((z>x)+z)>(-y))|((z+(z>x)).(z.x))|((-x).((z+(z>x)).(z.x)))|(((-x).((z+(z>x)).(z.x)))+(((z>x)+z)>(-y)))|
 *  and: |x|y|z|(-y)|(-z)|(z.y)|((z.y)+z)|(((z.y)+z)+x)|((-y).((z.y)+z))|((((z.y)+z)+x)>z)|(((z.y)+z)>((((z.y)+z)+x)>z))|(-(((z.y)+z)>((((z.y)+z)+x)>z)))|((z.y)+(-(((z.y)+z)>((((z.y)+z)+x)>z))))|(((-y).((z.y)+z)).((z.y)+(-(((z.y)+z)>((((z.y)+z)+x)>z)))))|((-z).(((-y).((z.y)+z)).((z.y)+(-(((z.y)+z)>((((z.y)+z)+x)>z))))))|(((z.y)+(-(((z.y)+z)>((((z.y)+z)+x)>z))))>((z.y)+(-(((z.y)+z)>((((z.y)+z)+x)>z)))))|(-(((z.y)+(-(((z.y)+z)>((((z.y)+z)+x)>z))))>((z.y)+(-(((z.y)+z)>((((z.y)+z)+x)>z))))))|(((-z).(((-y).((z.y)+z)).((z.y)+(-(((z.y)+z)>((((z.y)+z)+x)>z)))))).(-(((z.y)+(-(((z.y)+z)>((((z.y)+z)+x)>z))))>((z.y)+(-(((z.y)+z)>((((z.y)+z)+x)>z)))))))|
 *  
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

// Prototypes
int detect_op(char ch);
void sub_expr(string form, vector<string> &expr);
bool str_ord(string a, string b);
void printv(std::vector<string> v);
void printvec(std::vector<string> v, int b, int e);
void qs(vector<string> &ls, int b, int e, bool (*f)(string, string));
void correct_t(vector<string> &expr);
int atomic(vector<string> expr);
int find_in_expr(string form, vector<string> expr);
bool eval_expr(string form, vector<string> expr, vector<int> valoration[], int step);
int check_vals(vector<int> evals[], int sz);
void print_bottom_line(vector <string> expr);
void bs(vector<string> &expr, bool (*f)(string, string));

int main(int argc, char const *argv[]) {
	int n, atom_num = 0, buff;
	string form;
	vector<string> expr;
	vector<int> *evals;

	cin >> n;
	char dictionary[] = {'+', '.', '>', '-'};

	getline(cin, form); // clean \n buffer

	for (int i = 0; i < n; ++i) {
		cout << "Tabela #" << i+1 << endl;

		getline(cin, form);
		sub_expr(form, expr);
		
		// qs(expr, 0, expr.size(), str_ord);
		bs(expr, str_ord);
		correct_t(expr);
		
		print_bottom_line(expr);
		printv(expr);
		print_bottom_line(expr);

		evals = new vector<int>[expr.size()];
		
		atom_num = atomic(expr);

		// obs: evals[j] -> subexpressão
		for (int j = 0; j < (1 << atom_num); ++j) {
			eval_expr(form, expr, evals, j);
		}

		for (int j = 0; j < (1 << atom_num); ++j) {
			cout << "|";
			for (int k = 0; k < expr.size(); ++k) { // iters thourght every subexpression
				for (int l = 1; l < expr[k].size(); ++l) {
					if(expr[k][l] == WEIRD_CHAR) continue;
					cout << " ";
				}
				cout << evals[k][j] << "|";
				// cout << "(" << j << "," << k << ") ";
			}
			cout << endl;
			print_bottom_line(expr);
		}

		buff = check_vals(evals, expr.size());
		switch(buff) {
			case 0:
				cout << "satisfativel e refutavel" << endl;
				break;
			case 1:
				cout << "insatisfativel e refutavel" << endl;
				break;
			case 2:
				cout << "satisfativel e tautologia" << endl;
				break;
			default:
				break;
		}
		cout << endl;

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
	cout << "|";
	for (int i = 0; i < v.size(); ++i) {
		// cout << v[i] << "|";
		// cout << "(" << v[i].size() << "-";
		for (int j = 0; j < v[i].size(); ++j) {
			if(v[i][j] == WEIRD_CHAR) continue;
			cout << v[i][j];
		}
		cout << "|";
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

/**
 * @brief      Replace the t expression into the correct order.
 *
 * @param      expr  The expressions list.
 */
void correct_t(vector<string> &expr) {
	// correct the (-x) and z case
	// which have been mismatching
	for (int i = 1; i < expr.size(); ++i) {
		if(expr[i - 1].size() > 1 && expr[i].size() == 1) {
			swap(expr[i - 1], expr[i]);
		}
	}
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

// Receive the big expression, them go spliting it and evaluating it, them insert it
// into the pair that should be plotted in the end of the program.
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

void print_bottom_line(vector <string> expr) {
	for (int j = 0; j < expr.size(); ++j) {
		for (int k = 0; k < expr[j].length(); ++k) {
			if(expr[j][k] == WEIRD_CHAR) continue;
			cout << "-";
		}
		cout << "-";
	}
	cout << "-" << endl;
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