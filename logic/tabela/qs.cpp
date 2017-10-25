#include <bits/stdc++.h>

using namespace std;

void printv(std::vector<int> v){
	for (int i = 0; i < v.size(); ++i) {
		cout << v[i] << " ";
	}
	cout << endl;
}

bool fun(int a, int b){
	return a > b;
}

int sp(vector<int> &ls, int b, int e, bool (*f)(int, int));
void qs(vector<int> &ls, int b, int e, bool (*f)(int, int));

int main(int argc, char const *argv[]) {
	
	vector<int> v;
	v.push_back(11);
	v.push_back(1);
	v.push_back(14);
	v.push_back(31);
	v.push_back(22);
	v.push_back(-11);
	v.push_back(0);
	v.push_back(8);
	v.push_back(4);

	printv(v);
	qs(v, 0, v.size(), fun);
	printv(v);

	return 0;
}

int sp(vector<int> &ls, int b, int e, bool (*f)(int, int)) {
	int i = b + 1, j = e - 1;
	int pivot = b;

	while(i < j) {
		for (; i < e && f(ls[i], ls[pivot]); ++i);
		for (; j > i && !f(ls[j], ls[pivot]); --j);
		if(i < j) {
			swap(ls[i], ls[j]);
			i++;
			j--;
		}
	}

	if(!f(ls[pivot], ls[j])) {
		swap(ls[pivot], ls[j]);	
	}
	

	return j;
}

void qs(vector<int> &ls, int b, int e, bool (*f)(int, int)) {
	if(e <= b) {
		return;
	}

	printv(ls);

	int h = sp(ls, b, e, f);

	qs(ls, b, h - 1, f);
	qs(ls, h + 1, e, f);
}