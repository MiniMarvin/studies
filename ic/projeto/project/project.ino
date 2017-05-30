/**
 * Authors: Ana Vitória, Bezaliel Silva, Caio M. Gomes, Fábio William, Jonathan Kilner. (Grupo PCBreakers)
 * License: Este projeto está sob a licensa Creative Commons - Atribuition, Share Alike and Non-commercial (CC BY-NC-SA)
 * Project: Esse projeto é o software para controle de um carrinho seguidor de linha que faz uso de sensores ultrassônico,
 * e óptico(binário) para seguir uma linha preta em um circuito, onde não existem curvas bruscas, porém, existem obstáculos
 * que o carrinho deverá desviar.
 * Place: CIn, UPFE - Recife, Brasil
 */

#define opticPin 11 //pino de entrada no sensor
#define readLine digitalRead(opticPin)

// Definicoes pinos Galileo ligados a entrada da Ponte H (Half Bridge)
// Todos esses pinos são PWM para poder controlar a potência do motor. (poderia ser usada uma abordagem com
// manipulação de tensão para economizar os pinos PWM).
#define HB1  3
#define HB2  4
#define HB3  5
#define HB4  6 
#define SP1  9 
#define SP2  10 

int moveSide = 0; ///< 0 - move left.
                  ///< 1 - move right.

void setup() {
	Serial.begin(9600); //inicializando a porta serial
	pinMode(opticPin, INPUT); //colocando a porta 11 como entrada

	//Define os pinos do motor como saida
	pinMode(HB1, OUTPUT);
	pinMode(HB2, OUTPUT);
	pinMode(HB3, OUTPUT);
	pinMode(HB4, OUTPUT);

	// Inicia o robô com ele virado para a direita da linha e gira para a esquerda até encontrar a linha.
	while(readLine == 0) {
		forwardSide(moveSide);
	}

}
 
void loop() {
	
	// Uma vez que a linha foi encontrada segue o fluxo para o sentido que estava indo 
	// anteriormente até sair da linha.
	while(readLine == 1) {
		forwardSide(moveSide);
	}

	// Saiu da linha então inverte o sentido
	moveSide ^= 1;

	// Continua nesse sentido até encontrar a linha
	while(readLine == 0) {
	    forwardSide(moveSide);
	}
}


void forwardSide(int side) {
	if(side == 1) 
		forwardRight();
	else if(side == 0)
		forwardLeft();
}

/**
 * @brief      Move o motor para frente porém desviando para a esquerda.
 */
void backwardLeft() {
	spinA_AH(255*0.5);
	spinB_H(255*0.1);
}

/**
 * @brief      Move o motor para frente porém desviando para a direita.
 */
void backwardRight() {
	spinA_H(255*0.1);
	spinB_AH(255*0.5);
}

/**
 * @brief      Move o motor para trás porém desviando para a esquerda.
 */
void forwardLeft() {
	spinA_AH(255*0.1);
	spinB_H(255*0.5);
}

/**
 * @brief      Move o motor para trás porém desviando para a direita.
 */
void forwardRight() {
	spinA_AH(255*0.5);
	spinB_H(255*0.1);
}

/**
 * @brief      Gira o Motor A no sentido horário
 *
 * @param[in]  eficiency  A eficiencia do motor, o quanto de potência que será recebido pelo motor. (0 - 255)
 */
void spinA_AH(int eficiency) {
	//Gira o Motor A no sentido horario
	analogWrite(SP1, eficiency);
	digitalWrite(HB1, HIGH);
	digitalWrite(HB2, LOW);
}

/**
 * @brief      Gira o Motor A no sentido anti-horário
 *
 * @param[in]  eficiency  A eficiencia do motor, o quanto de potência que será recebido pelo motor. (0 - 255)
 */
void spinA_H(int eficiency) {
	//Gira o Motor A no sentido anti-horario
	analogWrite(SP1, eficiency);
	digitalWrite(HB1, LOW);
	digitalWrite(HB2, HIGH);
}

/**
 * @brief      Gira o Motor B no sentido horário
 *
 * @param[in]  eficiency  A eficiencia do motor, o quanto de potência que será recebido pelo motor. (0 - 255)
 */
void spinB_AH(int eficiency) {
	analogWrite(SP2, eficiency);
	digitalWrite(HB3, HIGH);
	digitalWrite(HB4, LOW);
}

/**
 * @brief      Gira o Motor B no sentido anti-horário
 *
 * @param[in]  eficiency  A eficiencia do motor, o quanto de potência que será recebido pelo motor. (0 - 255)
 */
void spinB_H(int eficiency) {
	analogWrite(SP2, eficiency);
	digitalWrite(HB3, LOW);
	digitalWrite(HB4, HIGH);
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
