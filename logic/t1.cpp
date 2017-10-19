#include <bits/stdc++.h>

using namespace std;

int swap(int &a, int &b) {
	int t = a;
	a = b;
	b = t;
}

void printv(vector<int> &lst){
	for (int i = 0; i < lst.size(); ++i) {
		cout << lst[i] << " ";
	}
	cout << endl;
}

int split(vector<int> &lst, int b, int e, bool (*f)(int,int)) {
	int i = b + 1, j = e;
	int pivot = b;

	while(i < j) {
		for(; (*f)(lst[i], lst[pivot]) && i < e; i++);
		for(; !(*f)(lst[j], lst[pivot]) && j >= b; j--);
        if(i < j) {
            swap(lst[i], lst[j]);
            i++;
            j--;
        }
	}
	
	if(!(*f)(lst[pivot], lst[j]))
		swap(lst[pivot], lst[j]);

	return j;
}



void qs(vector<int> &lst, int b, int e, bool (*f)(int, int)) {
	int pivot = b;
	int i = b + 1, j = e;

	// cout << "b: " << b << " e: " << e << endl;

	if(b >= e) return;

	j = split(lst, b, e, f);

	qs(lst, b, j - 1, f);
	qs(lst, j + 1, e, f);
}

bool m(int a , int b) {
	return a < b;
}

int main(int argc, char const *argv[]) {
	
	vector<int> a;

	a.push_back(11);
	a.push_back(8);
	a.push_back(4);
	a.push_back(21);
	a.push_back(13);
	a.push_back(10);
	a.push_back(44);
	a.push_back(18);
	a.push_back(40);
	a.push_back(51);
	a.push_back(-2);
	a.push_back(17);
	a.push_back(-7);
	a.push_back(0);

	qs(a, 0, a.size() - 1, m);

	printv(a);


	return 0;
}

