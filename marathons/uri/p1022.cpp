#include <cstdio>

void simplify(int a, int b);

int main(int argc, char const *argv[]) {
	
	int in_num;
	int a, b, c, d, den, num;
	char symbol;

	scanf(" %d", &in_num);

	for (int i = 0; i < in_num; ++i) {
		
		scanf(" %d / %d %c %d / %d", &a, &b, &symbol, &c, &d);

		den = b*d;

		switch(symbol) {
			case '+':
				num = a*d + b*c;
				break;
			case '-':
				num = a*d - b*c;
				break;
			case '*':
				num = a*c;
				break;
			case '/':
				num = a*d;
				den = c*b;
				break;
		}

		printf("%d/%d = ", num, den);
		simplify(num, den);
		
	}

	

	return 0;
}

int abs(int x) {
	if(x > 0) 
		return x;
	return -x;
}

void simplify(int a, int b) {

	int lower, mmc, sign_ct = 0;
	
	if(a < 0) {
		sign_ct++;
		a = -a;
	}

	if(b < 0) {
		sign_ct++;
		b = -b;
	}

	lower = a;

	if(a > b) {
		lower = b;	
	}

	//printf("(%d/%d - low: %d) ", a, b, lower);

	// iters untill find some value that can be broken in two and start from beginning again
	for (int i = 1; i <= lower && (a != 1 && b != 1); ++i) {
		//printf("(%d/%d - low: %d) \n", a, b, lower);
		if(a%i == 0 && b%i == 0) {
			a /= i;
			b /= i;
			lower /= i;
			i = 1;

		}
	}
	if(sign_ct%2 == 0){
		printf("%d/%d\n", a, b);
	}
	else {
		printf("-%d/%d\n", a, b);
	}


	
}