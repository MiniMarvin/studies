#include <stdio.h>
#include <stdlib.h>
int swap(int* a,int* b){ 
	int t = *a; 
	*a = *b; 
	*b = t;
}

int main() {
	
	int mbox[] = {31,28,31,30,31,30,31,31,30,31,30,31};
	int usum[] = {334, 306, 275, 245, 214, 184, 153, 122, 92, 61, 31, 0}; //number of days missing from january to december
	int dsum[] = {334, 304, 273, 243, 212, 181, 151, 120, 90, 59, 31, 0}; //number of days spent untill december to january

	int d1, m1, y1; //date 1
	int d2, m2, y2; //date 2
	int buff = 0, spent1, spent2, miss1, miss2;
	int days = 0;
	int bissexto = 0;
	int i = 0;
	
	for(i = 0; i < 5000; i++) {
		scanf(" %d/%d/%d", &d1, &m1, &y1);
		scanf(" %d/%d/%d", &d2, &m2, &y2);
		if(y1 > y2) {
			swap(&y1,&y2);
			swap(&m1,&m2);
			swap(&d1,&d2);
		}else if(m1 > m2) {
			swap(&m1,&m2);
			swap(&d1,&d2);
		}else if(d1 > d2) {
			swap(&d1,&d2);
		}

		bissexto = (y2/4 - (y1-1)/4) + (y2/400 - (y1-1)/400) - (y2/100 - (y1-1)/100);
		if(bissexto > 0 && y2 -y1 > 4) bissexto -= 1;
		if(bissexto < 0) bissexto = 0;

		spent1 = usum[m1 - 1];
		spent2 = dsum[12 - m2];

		miss1 = mbox[m1 - 1] - d1;
		//if(miss1 < 0) miss1 = 0;
		miss2 = d2;

		buff = y2 - y1 - 1;
		if(buff < 0 ){
			days = spent1 - (365 - spent2) + miss1 + miss2;
			if(y1%4 == 0 && y1%100 != 0 || y1%400 == 0) 
				if(m1 <= 2) {
					days += 1;
				}
		}
		else if(buff == 0) {
			days = spent1 + miss1 + spent2 + miss2;
			if(y1%4 == 0 && y1%100 != 0 || y1%400 == 0) 
				if(m1 <= 2) {
					days += 1;
				}
			if(y1%4 == 0 && y1%100 != 0 || y1%400 == 0) 				
				if(y2%4 == 0 && m2 >= 2) {
					days += 1;
				}
		}
		else{
			days = buff*365 + spent1 + spent2 + miss1 + miss2 + bissexto;
			if(y1%4 == 0 && y1%100 != 0 || y1%400 == 0) 
				if(m1 <= 2) {
					days += 1;
				}
			if(y1%4 == 0 && y1%100 != 0 || y1%400 == 0) 
				if(m2 >= 2) {
					days += 1;
				}
		}

		
		printf("%d\n", days);
	}

	return EXIT_SUCCESS;
}