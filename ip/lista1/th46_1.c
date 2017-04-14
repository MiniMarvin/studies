#include <stdio.h>
#include <stdlib.h>
int swap(int* a,int* b){ 
	int t = *a; 
	*a = *b; 
	*b = t;
}

int main() {
	
	int mbox[] = {31,28,31,30,31,30,31,31,30,31,30,31};
	int table1[] = {334, 306, 275, 245, 214, 184, 153, 122, 92, 61, 31, 0}; //number of days missing from january to december
	int table2[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334}; //number of days spent untill december to january

	int d1, m1, y1; //date 1
	int d2, m2, y2; //date 2
	int buff = 0, spent_days, missing_days;
	int days = 0;
	int bissexto = 0;
	int i = 0;
	
	// for(i = 0; i < 5000; i++) {
		scanf(" %d/%d/%d", &d1, &m1, &y1);
		scanf(" %d/%d/%d", &d2, &m2, &y2);

		if(y1 > y2) {
			swap(&y1,&y2);
			swap(&m1,&m2);
			swap(&d1,&d2);
		}else if( y1 == y2 && m1 > m2) {
			swap(&m1,&m2);
			swap(&d1,&d2);
		}else if( y1 == y2 && m1 > m2 && d1 > d2) {
			swap(&d1,&d2);
		}

		buff = y2 - y1 - 1;

		if(y1%4 == 0 && y1%100 != 0 || y1%400 == 0) mbox[1]++; //correction in bissext years
		missing_days = (mbox[m1 - 1] - d1) + table1[m1 - 1];
		spent_days = table2[m2 - 1] + d2;

		bissexto = y2/4 - (y1-1)/4 + y2/400 - (y1-1)/400 - (y2/100 - (y1-1)/100);

		if(buff < 0) {
			days = missing_days - (365 - spent_days);
			if(y1%4 == 0 && y1%100 != 0 || y1%400 == 0)
				if(m1 == 1 && m2 > 2) days += 1;
		}
		else if(buff == 0) {
			days = missing_days + spent_days;
			if(y1%4 == 0 && y1%100 != 0 || y1%400 == 0) 
				if(m1 == 1) days += 1;
			if(y2%4 == 0 && y2%100 != 0 || y2%400 == 0) 
				if(m2 > 2) days += 1;
		}
		else {
			
			days = missing_days + spent_days + bissexto + (buff)*365;

			if(y1%4 == 0 && y1%100 != 0 || y1%400 == 0) {
				if(m1 >= 2) days -= 1;
			}
			if(y2%4 == 0 && y2%100 != 0 || y2%400 == 0) {
				if(m2 <= 2) days -= 1;
			}

		}

		printf("%d\n", days);
	// }

	return EXIT_SUCCESS;
}