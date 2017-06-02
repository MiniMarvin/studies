/**
 * Authors: Ana Vitória, Bezaliel Silva, Caio M. Gomes, Fábio William, Jonathan Kilner. (Grupo PCBreakers)
 * License: Este projeto está sob a licensa Creative Commons - Atribuition, Share Alike and Non-commercial (CC BY-NC-SA)
 * Project: Esse projeto é o software para controle de um carrinho seguidor de linha que faz uso de sensores ultrassônico,
 * e óptico(binário) para seguir uma linha preta em um circuito, onde não existem curvas bruscas, porém, existem obstáculos
 * que o carrinho deverá desviar.
 * Place: CIn, UPFE - Recife, Brasil
 */

#define opticPin 11 //pino de entrada no sensor
#define btn_Start 2

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

#define ledVerde 12
#define ledVermelho 13

int moveSide = 0; ///< 0 - move left.
                  ///< 1 - move right.

int start = 0;

unsigned long currentMillis;
unsigned long previousMillis = 0;
unsigned long delayMS = 75;

bool side = 0;

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
	
	// while(!checkButtonState(btn_Start));
	// start = 1;
	while(readLine == 0) {
		forwardSide(moveSide);
	}
	moveSide ^= 1;

}
 
void loop() {
	

	// if(checkButtonState(btn_Start)) {
	// 	start ^= start;
	// }

	// if(start) {
		// Uma vez que a linha foi encontrada segue o fluxo para o sentido que estava indo 
		// anteriormente até sair da linha.
		while(readLine == 1) {
			forwardSide(moveSide);
			currentMillis = millis();
		}

		// Saiu da linha então inverte o sentido
		

		

		// if((currentMillis - previousMillis) > delayMS) {
		// 	previousMillis = currentMillis;
		// 	moveSide ^= 1;	
		// }
		
		
		// Continua nesse sentido até encontrar a linha
		while(readLine == 0) {
		    forwardSide(moveSide);
		    currentMillis = millis();
		}

		moveSide ^= 1;	

		// if((currentMillis - previousMillis) > delayMS) {
		// 	previousMillis = currentMillis;
		// 	moveSide ^= 1;	
		// }
		
	// }
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

/**
 * @brief      Move o motor para frente porém desviando para a esquerda.
 */
void backwardLeft() {
	//0.27
	spinA_AH(255*0.4);
	spinB_H(255*0);
}

/**
 * @brief      Move25o motor para frente porém desviando para a direita.
 */
void backwardRight() {
	spinA_H(255*0);
	spinB_AH(255*0.4);
}

/**
 * @brief      Move o motor para trás porém desviando para a esquerda.
 */
void forwardLeft() {
	spinA_AH(255*0);
	spinB_H(255*0.4);
}

/**
 * @brief      Move o motor para trás porém desviando para a direita.
 */
void forwardRight() {
	spinA_AH(255*0.4);
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


int checkButtonState(int button){
  //Source: Arduino, modified by: KilnerJhow
  // read the state of the switch into a local variable:
  int reading = digitalRead(button);
  delay(50);
  reading = digitalRead(button);
  if(reading) {
    return 1;
  }
  return 0;
}