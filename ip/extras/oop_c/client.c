#include <stdio.h>
#include <stdlib.h>

#define CLIENT_NUM 3

typedef struct {
   char name[100]; 
   char cpf[11];
   double money;
} Client;

void addClient(Client *a);
void printClient(Client a);
void findClient(Client a, char* cpf);

int main () {
    int i = 0;
    Client *a = (Client*) malloc(sizeof(Client) * CLIENT_NUM);
    for (i = 0; i < CLIENT_NUM; i++) {
        addClient( &a[i] );
        printClient(a[i]);
    }
    
    free(a);
    
    return 0;
}


void addClient(Client *a) {
    
    //printf("Digit the client name: ");
    scanf(" %[^\n]", a->name );
    //printf("Digit the client CPF: ");
    scanf(" %s", a->cpf );
    //printf("Digit the client's Money: ");
    scanf(" %lf", &a->money );
}

void printClient(Client a) {
    printf("Name: %s\n", a.name);
    printf("CPF: %s\n", a.cpf);
    printf("Money: %lf\n", a.money);
}

void findClient(Client *a, char *cpf, clientNum) {
    
    int found = 1, i = 0;

    for (j = 0; j < clientNum; j++) {
        for (i = 0; cpf[i] != '\0'; i++) {
            if(cpf[i] != a[j].cpf[i]) {
                found = 0;
                break;
            }
        }
    }
    
    if(found == 1) {
        printClient(a);
    }
    
}