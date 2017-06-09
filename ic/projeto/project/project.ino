/**
 * Authors: Ana Vitória, Bezaliel Silva, Caio M. Gomes, Fábio William, Jonathan Kilner. (Grupo PCBreakers)
 * License: Este projeto está sob a licensa Creative Commons - Atribuition, Share Alike and Non-commercial (CC BY-NC-SA)
 * Project: Esse projeto é o software para controle de um carrinho seguidor de linha que faz uso de sensores ultrassônico,
 * e óptico(binário) para seguir uma linha preta em um circuito, onde não existem curvas bruscas, porém, existem obstáculos
 * que o carrinho deverá desviar.
 * Place: CIn, UPFE - Recife, Brasil
 */

#include <Ultrasonic.h>

#define opticPin 11 //pino de entrada no sensor
#define readLine digitalRead(opticPin)	///< 0 -> dentro da linha
										///< 1 -> fora da linhas

#define INSIDE_LINE 0
#define OUTSIDE_LINE 1

// Definicoes pinos Galileo ligados a entrada da Ponte H (Half Bridge)
// Todos esses pinos são PWM para poder controlar a potência do motor. (poderia ser usada uma abordagem com
// manipulação de tensão para economizar os pinos PWM).
#define HB1  3
#define HB2  4
#define HB3  5
#define HB4  6 
#define SP1  9 
#define SP2  10 

#define ledVerde 12
#define ledVermelho 13

#define echo 8
#define trigger 9

#define N 10

int moveSide = 0; ///< 0 - move left.
                  ///< 1 - move right.

int lineState = INSIDE_LINE;
int oldState = INSIDE_LINE;
int stct = 0;

Ultrasonic ultrasonic(trigger, echo);

void setup() {
	Serial.begin(9600); //inicializando a porta serial
	pinMode(opticPin, INPUT); //colocando a porta 11 como entrada

	//Define os pinos do motor como saida
	pinMode(HB1, OUTPUT);
	pinMode(HB2, OUTPUT);
	pinMode(HB3, OUTPUT);
	pinMode(HB4, OUTPUT);

	pinMode(ledVerde, OUTPUT);	//verde
	pinMode(ledVermelho, OUTPUT);	//vermelho

	// Inicia o robô com ele virado para a direita da linha e gira para a esquerda até encontrar a linha.
	while(readLine == 0) {
		forwardSide(moveSide);
	}
	moveSide ^= 1;
	Serial.begin(9600);

}
 
void loop() {


	
	while(readLine == OUTSIDE_LINE) {
		// obstaculo();
		forwardSide(moveSide);
	}

	// Saiu da linha então inverte o sentido		
	// Continua nesse sentido até encontrar a linha
	while(readLine == INSIDE_LINE) {
		// obstaculo();
	    forwardSide(moveSide);
	}

	moveSide ^= 1;

	// Se estava na linha e saiu ele inverte o sentido
	// Se estava fora da linha e entrou só continua

	// if(oldState == INSIDE_LINE && readLine == OUTSIDE_LINE) {
	// 	moveSide ^= 1;
	// 	oldState = OUTSIDE_LINE;
	// }
	// if(oldState == OUTSIDE_LINE && readLine == INSIDE_LINE) {
	// 	oldState = INSIDE_LINE;
	// }

	// forwardSide(moveSide);

}

// TODO: mudar o nome da função.
void obstaculo() {
	int last_distance = ultrasonic.Ranging(CM);
	int diff = 0;
	int MAX_DIST = 4;

	if(last_distance < 20) {

		Serial.print("Distance: ");
		Serial.println(last_distance);
		while( diff < MAX_DIST ) {
			forwardSide(moveSide);
			diff = ultrasonic.Ranging(CM) - last_distance;
			Serial.print("Diff:");
			Serial.println(diff);

			last_distance = ultrasonic.Ranging(CM);
			Serial.print("last_distance: ");
			Serial.println(last_distance);
		}
		stop();
		Serial.print("STOP!!");
		delay(500);

		forwardPoweredSide(moveSide, 0.25, 0.4);
		delay(200);

		moveSide ^= 1;

		forwardPoweredSide(moveSide, 0.25, 0.4);
		delay(250);
		
		// while(readLine == OUTSIDE_LINE);

		// for (int i = 0; i < 5; ++i){
		// 	forwardSide(moveSide);
		// 	delay(50);
		// }

		// moveSide ^= 1;

		// for (int i = 0; i < 5; ++i){
		// 	forwardSide(moveSide);
		// 	delay(100);
		// }			

		// moveSide ^= 1;
	}

}

void forwardSide(int side) {
	if(side == 1) {
		forwardRight();
		digitalWrite(ledVermelho, HIGH);
		digitalWrite(ledVerde, LOW);
	}
	else if(side == 0) {
		forwardLeft();
		digitalWrite(ledVerde, HIGH);
		digitalWrite(ledVermelho, LOW);
	}
}

//para obter um giro para esquerda eff_a > eff_b
void forwardPoweredSide(int side, float eff_a, float eff_b) {
	if(side == 1) {
		forwardPowered(eff_b, eff_a);
		digitalWrite(ledVermelho, HIGH);
		digitalWrite(ledVerde, LOW);
	}
	else if(side == 0) {
		forwardPowered(eff_a, eff_b);
		digitalWrite(ledVerde, HIGH);
		digitalWrite(ledVermelho, LOW);
	}

}

void forwardPowered(float eff1, float eff2) {
	spinA_AH(255*eff1);
	spinB_H(255*eff2);	
}

/**
 * @brief      Move o motor para trás porém desviando para a esquerda.
 */
void forwardLeft() {
	spinA_AH(255*0);
	spinB_H(255*0.3);
}

/**
 * @brief      Move o motor para trás porém desviando para a direita.
 */
void forwardRight() {
	spinA_AH(255*0.3);
	spinB_H(255*0);
}

/**
 * @brief      Gira o Motor A no sentido horário
 *
 * @param[in]  eficiency  A eficiencia do motor, o quanto de potência que será recebido pelo motor. (0 - 255)
 */
void spinA_AH(int eficiency) {
	//Gira o Motor A no sentido horario
	analogWrite(HB1, eficiency);
	// digitalWrite(HB1, HIGH);
	digitalWrite(HB2, LOW);
}

/**
 * @brief      Gira o Motor A no sentido anti-horário
 *
 * @param[in]  eficiency  A eficiencia do motor, o quanto de potência que será recebido pelo motor. (0 - 255)
 */
void spinA_H(int eficiency) {
	//Gira o Motor A no sentido anti-horario
	analogWrite(HB2, eficiency);
	digitalWrite(HB1, LOW);
	// digitalWrite(HB2, HIGH);
}

/**
 * @brief      Gira o Motor B no sentido horário
 *
 * @param[in]  eficiency  A eficiencia do motor, o quanto de potência que será recebido pelo motor. (0 - 255)
 */
void spinB_AH(int eficiency) {
	analogWrite(HB3, eficiency);
	// digitalWrite(HB3, HIGH);
	digitalWrite(HB4, LOW);
}

/**
 * @brief      Gira o Motor B no sentido anti-horário
 *
 * @param[in]  eficiency  A eficiencia do motor, o quanto de potência que será recebido pelo motor. (0 - 255)
 */
void spinB_H(int eficiency) {
	analogWrite(HB4, eficiency);
	digitalWrite(HB3, LOW);
	// digitalWrite(HB4, HIGH);
}

/**
 * @brief      Gera uma frenagem magnética nos motores.
 */
void stop() {
	// Para os motores A e B com uma frenagem eletromagnética.
	digitalWrite(HB1, HIGH);
	digitalWrite(HB2, HIGH);
	digitalWrite(HB3, HIGH);
	digitalWrite(HB4, HIGH);

	delay(10);

	// Libera a trava eletromagnética para evitar problemas com consumo de corrente.
	digitalWrite(HB1, LOW);
	digitalWrite(HB2, LOW);
	digitalWrite(HB3, LOW);
	digitalWrite(HB4, LOW);

	// Força velocidade 0 de chaveamento no motor.
	analogWrite(SP1, 0);
	analogWrite(SP2, 0);
}


long getDistance(){
  
  //get duration and distance
  long duration, distance;
  digitalWrite(trigger, LOW);
  delayMicroseconds(2); 
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigger, LOW);
  duration = pulseIn(echo, HIGH);
  distance = (duration/2) / 29.1;
  
  //filter
  
  return distance;
}
