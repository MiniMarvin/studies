#include <bits/stdc++.h>

using namespace std;

typedef struct app{
	int num;
	int status; // 1 - unread/ 2 - read
	int *parent;
} app;

int main() {

	int apps, events, buff, unread = 0, ct = 0;
	app chron[300000];
	int unread[300000] = {0};

	cin >> apps;
	cin >> events;

	for (int i = 0; i < events; ++i) {
		cin >> buff;
		if(buff == 1) {
			unread++;
			chron[ct].status = 1;
			cin >> chron[ct].num;
			unread[chron[ct].num]++;
			ct++;
		}
		else if (buff == 2) {
			cin >> buff;

			for (int j = 0; j < ct; ++j) {
				if(chron[j].num == buff){
					if(chron[j].status == 1) {
						chron[j].status = 2;
						unread--;
					}
				}
			}
		}
		else if(buff == 3) {
			cin >> buff;
			for (int j = 0; j < buff; ++j) {
				if(chron[j].status == 1) {
					chron[j].status = 2;
					unread--;
				}
			}
		}

		cout << unread << endl;
	}

	return 0;
}