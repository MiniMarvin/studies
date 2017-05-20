#include <stdlib.h>

#define qtdLeds 4

int** p;
int rodada = 1, aux = 4, count = 4;

void setup() {
	// put your setup code here, to run once:
	
	//Aloca 2 linhas 
	p = (int**) malloc( sizeof(int*)*2 );

	//Aloca 20 colunas
	for(int i = 0 ; i < 2; ++i) {
		*(p + i) = (int*) malloc(sizeof(int)*20);
	}

	//Pega uma seed aletória para a função rand
	randomSeed(analogRead(0));
	/*
	for (int i = 4; i < 12; ++i)	{
		if(i < 8) pinMode(i, INPUT);
		if(i >= 8) pinMode(i, OUTPUT);
	}*/
  
  	pinMode(4, INPUT);
  	pinMode(5, INPUT);
  	pinMode(6, INPUT);
  	pinMode(7, INPUT);
  
  	pinMode(0, OUTPUT);
  	pinMode(1, OUTPUT);
  	pinMode(2, OUTPUT);
  	pinMode(3, OUTPUT);
  	pinMode(13, OUTPUT);

	//Leds
	p[0][0] = 2; //vermelho
	p[0][1] = 3; //verde
	p[0][2] = 4; // amarelo;
	p[0][3] = 5;
	
	//Botões							
	p[1][0] = 6;	//btn 1
	p[1][1] = 7;	//btn2
	p[1][2] = 8;	//btn3
	p[1][3] = 9;            	
	
	//Realoca para 24 colunas
	for(int i = 0 ; i < 2; ++i) {
		*(p + i) = (int*) realloc(*(p + i),sizeof(int)*24);
	}

	Serial.begin(9600);
}

void loop() {
	
	if(rodada < 20){

		ligaLED();
	
		pegaBotaoApertado();

		if(!compara()) {
			acendePerdeu();
			rodada = 1;
			count = qtdLeds;
		}else{
			count++;
			rodada++;
		}

		
	} else {
		piscaPadrao();
		count = qtdLeds;
		rodada = 1;
	}
	delay(2000);
	
}

void piscaPadrao() {

	for (int i = 0; i < qtdLeds; ++i)	{
		if(!(i%2)) {
			digitalWrite(p[0][i], HIGH);
			digitalWrite(p[0][(i+2)%qtdLeds], HIGH);
			delay(1000);
			digitalWrite(p[0][i], LOW);
			digitalWrite(p[0][(i+2)%qtdLeds], LOW);
		} else {
			digitalWrite(p[0][i], HIGH);
			digitalWrite(p[0][(i+2)%qtdLeds], HIGH);
			delay(1000);
			digitalWrite(p[0][i], LOW);
			digitalWrite(p[0][(i+2)%qtdLeds], LOW);
		}
	}

}

void acendePerdeu() {
	for (int i = 0; i < qtdLeds; ++i) {
		digitalWrite(p[0][i], HIGH);
	}
	delay(4000);
	for (int i = 0; i < qtdLeds; ++i) {
		digitalWrite(p[0][i], LOW);
	}

}

void ligaLED() {

	p[0][count] = random(2, 5);
	for (int i = qtdLeds; i <= count; ++i) {

		digitalWrite(p[0][i], HIGH);
		Serial.print("Led Ligado: ");
		Serial.println(p[0][i]);
		delay(1000);

      	Serial.print("Led desligado: ");
		Serial.println(p[0][i]);
		digitalWrite(p[0][i], LOW);
		delay(1000);
	}
}

void pegaBotaoApertado() {
	int x = qtdLeds;
	while(x <= count) {

		if(checkButtonState(p[1][0])) {
			p[1][x] = 2;
			Serial.println("Botao Apertado:");
			digitalWrite(p[1][x], checkButtonState(p[1][0]));
			Serial.println(p[1][x]);
			while(checkButtonState(p[1][0]));
			digitalWrite(p[1][x++], LOW);
		}
		if(checkButtonState(p[1][1])) {
			p[1][x] = 3;
			Serial.println("Botao Apertado:");
			Serial.println(p[1][x]);
			digitalWrite(p[1][x], HIGH);
			while(checkButtonState(p[1][1]));
			digitalWrite(p[1][x++], LOW);
		}
		if(checkButtonState(p[1][2])) {
			p[1][x] = 4;
			digitalWrite(p[1][x], HIGH);
			Serial.println("Botao Apertado:");

			Serial.println(p[1][x]);
			while(checkButtonState(p[1][2]));
			digitalWrite(p[1][x++], LOW);
		}
		if(checkButtonState(p[1][3])) {
			p[1][x] = 5;
			digitalWrite(p[1][x], HIGH);
			Serial.println("Botao Apertado:");
			Serial.println(p[1][x]);
			while(checkButtonState(p[1][3]));
			digitalWrite(p[1][x++], LOW);
		}
	}
}

int compara() {
	int ok = 1;
	Serial.println("Comparado: ");
	for (int i = qtdLeds; i <= count; ++i) {
		if(p[0][i] == p[1][i]) {
			Serial.print(p[0][i]);
			Serial.print(" = ");
			Serial.println(p[1][i]);
			continue;
		}
		else { 
			Serial.print(p[0][i]);
			Serial.print(" != ");
			Serial.println(p[1][i]);
			ok = 0;
		}
	}

	return ok;

}

int checkButtonState(int button){

	int reading = digitalRead(button);
	delay(100);
	reading = digitalRead(button);
	if(reading) {
		return 1;
	}
	return 0;
}

