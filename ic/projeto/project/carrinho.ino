/**
 * Authors: Ana Vitória, Bezaliel Silva, Caio M. Gomes, Fábio William, Jonathan Kilner. (Grupo PCBreakers)
 * License: Este projeto está sob a licensa Creative Commons - Atribuition, Share Alike and Non-commercial (CC BY-NC-SA)
 * Project: Esse projeto é o software para controle de um carrinho seguidor de linha que faz uso de sensores ultrassônico,
 * e óptico(binário) para seguir uma linha preta em um circuito, onde não existem curvas bruscas, porém, existem obstáculos
 * que o carrinho deverá desviar.
 * Place: CIn, UPFE - Recife, Brasil
 */

#include <Ultrasonic.h>
// #include <NewPing.h> // Biblioteca de Ultrassom

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

#define ledVerde 12
#define ledVermelho 13

#define ECHO_PIN 10
#define TRIGGER_PIN 8
#define MAX_DISTANCE 200

#define MIN_DIST 20
#define MAX_DIFF 5

#define N 10

#define LEFT 0
#define RIGHT 1

#define NUMERO_LEITURAS 3

int moveSide = 0; ///< 0 - move left.
                  ///< 1 - move right.

int mstate = 0;

// Antigo desvio.
int lineState = INSIDE_LINE;
int oldState = INSIDE_LINE;
int stct = 0;
int cttogo = 0, oldct = 0, buff_diff = 0;

int lado_no_04;

int dist_array[NUMERO_LEITURAS];
int count_dist = 0;

int distancia_atual = 1000;

unsigned long old_time = 0;

void setup() {
	Serial.begin(9600); //inicializando a porta serial
	pinMode(opticPin, INPUT); //colocando a porta 11 como entrada

	//Define os pinos do motor como saida
	pinMode(HB1, OUTPUT);
	pinMode(HB2, OUTPUT);
	pinMode(HB3, OUTPUT);
	pinMode(HB4, OUTPUT);

	pinMode(TRIGGER_PIN, OUTPUT);
	pinMode(ECHO_PIN, INPUT);

	Serial.begin(115200);

	// Inicia o array de leituras de sensor
	for(int i = 0; i < NUMERO_LEITURAS; i++) {
		// dist_array[i] = sonar.ping_cm();
		// dist_array[i] = ultrasonic.Ranging(CM);
		dist_array[i] = pegaDistancia();
		delay(50);
	}

	old_time = millis();
}
 
void loop() {
	
	
	// Estado dentro da linha indo para a esquerda
	if(mstate == 0) {
		moveSide = LEFT;
		forwardSide(moveSide);
		
		if(readLine == OUTSIDE_LINE) {
			mstate = 1;
		}
		
		if(distancia_atual <= MIN_DIST) {
			mstate = 4;
		}
	}

	// Estado a esquerda da linha
	else if(mstate == 1) {
		moveSide = RIGHT;
		forwardSide(moveSide);
		
		if(readLine == INSIDE_LINE) {
			mstate = 2;
		}
		
		if(distancia_atual <= MIN_DIST) {
			mstate = 4;
		}
	}
	// Estado dentro da linha indo para a direita
	else if(mstate == 2) {
		moveSide = RIGHT;
		forwardSide(moveSide);
		
		if(readLine == OUTSIDE_LINE) {
			mstate = 3;
		}
		
		if(distancia_atual <= MIN_DIST) {
			mstate = 4;
		}
	}
	// Estado a direita da linha
	else if(mstate == 3) {
		moveSide = LEFT;
		forwardSide(moveSide);
		
		if(readLine == INSIDE_LINE) {
			mstate = 0;
		}
		
		if(distancia_atual <= MIN_DIST) {
			mstate = 4;
		}
	}
	// Acha limite do obstáculo
	else if(mstate == 4) {
		lado_no_04 = moveSide;
		acha_limite();
	}
	
	// Sai de perto do obstáculo
	else if(mstate == 5) {
		passa_obstaculo();
		mstate = 8;
	}
	
	// Reencontra o obstáculo
	else if(mstate == 6) {
		acha_obstaculo();		
	}
	
	// Sai de perto dele
	else if(mstate == 7) {
		sai_de_perto();
		
	}
	
	// Reencontra a linha
	else if(mstate == 8) {
		acha_linha();
	}

	// Delay mínimo para executar outra leitura do sensor
	if(millis() - old_time >= 30) {
		
		dist_array[count_dist] = pegaDistancia();

		Serial.println(distancia_atual);
	
		Serial.print("Estado: ");
		Serial.println(mstate);
	
		// Reseta o número de leituras.
		if(++count_dist == NUMERO_LEITURAS) {
			count_dist = 0;
		}	

		// pega a distancia atual com a média móvel
		distancia_atual = (int) getDistance();

		old_time = millis();
	}
	
}

unsigned long tempo_o = 0;

/**
 * @brief      Acha o limite do obstáculo e se move ao redor
 */
void acha_limite() {
	// achou os limites do obstáculo
	if(distancia_atual > (MIN_DIST + MAX_DIFF)) {
		mstate = 5;
		delay(150);
		// inverte 90º
		moveSide ^= 1;
		forwardSide(moveSide);
		delay(150);
		// stop();
		tempo_o = millis();
	}
	
	else {
		forwardSide(moveSide);
	}
}
/**
 * @brief      Faz a rotina de desvio do obstáculo
 */
void passa_obstaculo() {

	delay(50);

	// Move no sentido da borda encontrada do obstáculo.
	forwardPoweredSide(moveSide, 0.43, 0.45);

	delay(300);
	mstate = 6;
}

/**
 * @brief      Encontra o obstáculo e avança a máquina de estados
 */
void acha_obstaculo() {
	
	if(lado_no_04 == 0) {
		moveSide = 1;
	}
	else {
		moveSide = 0;
	}

	forwardPoweredSide(moveSide, 0, 0.3);
	if(distancia_atual <= (MIN_DIST + 10)) {
		mstate = 7;
		// stop();
	}
}

/**
 * @brief      Sai de perto do obstáculo
 */
void sai_de_perto() {
	
	moveSide = lado_no_04;
	
	forwardSide(moveSide);
	
	if(distancia_atual >= (MIN_DIST + MAX_DIFF) ) {
		mstate = 8;
		// moveSide = lado_no_04;
		delay(200); // Vai um pouco mais
		// stop(); // Para o carrinho
	}
}

/**
 * @brief      Procura a linha depois de sair da rotina de desvio
 */
void acha_linha() {
	// Inverte o lado de movimentação
	// moveSide = lado_no_04;
	if(lado_no_04 == 0) {
		moveSide = 1;
	}
	else {
		moveSide = 0;
	}


	forwardPoweredSide(moveSide, 0.25, 0.40);
	
	if(readLine == INSIDE_LINE) {
		// mstate = 0;
		if(lado_no_04 == RIGHT) {
			mstate = 0;
		}
		else {
			mstate = 2;
		}
	}
	
}

/**
 * @brief      Move o carrinho de acordo com o estado atual
 *
 * @param[in]  side  Estado para mover o carrinho 
 */
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


/**
 * @brief      Move o motor para a frente de acordo com a eficiencia recebida
 *
 * @param[in]  eff1  A eficiencia do motor A
 * @param[in]  eff2  A eficiencia do motor B
 */
void forwardPowered(float eff1, float eff2) {
	spinA_AH(255*eff1);
	spinB_H(255*eff2);	
}

/**
 * @brief      Move o motor para frente porém desviando para a esquerda.
 */
void forwardLeft() {
	spinA_AH(255*0);
	spinB_H(255*0.3);
}

/**
 * @brief      Move o motor para frente porém desviando para a direita.
 */
void forwardRight() {
	spinA_AH(255*0.3);
	spinB_H(255*0);
}

/**
 * @brief      Gira o Motor A no sentido anti-horário
 *
 * @param[in]  eficiency  A eficiencia do motor, o quanto de potência que será recebido pelo motor. (0 - 255)
 */
void spinA_AH(int eficiency) {
	analogWrite(HB1, eficiency);
	digitalWrite(HB2, LOW);
}

/**
 * @brief      Gira o Motor A no sentido horário
 *
 * @param[in]  eficiency  A eficiencia do motor, o quanto de potência que será recebido pelo motor. (0 - 255)
 */
void spinA_H(int eficiency) {
	analogWrite(HB2, eficiency);
	digitalWrite(HB1, LOW);
}

/**
 * @brief      Gira o Motor B no sentido anti-horário
 *
 * @param[in]  eficiency  A eficiencia do motor, o quanto de potência que será recebido pelo motor. (0 - 255)
 */
void spinB_AH(int eficiency) {
	analogWrite(HB3, eficiency);
	digitalWrite(HB4, LOW);
}

/**
 * @brief      Gira o Motor B no sentido horário
 *
 * @param[in]  eficiency  A eficiencia do motor, o quanto de potência que será recebido pelo motor. (0 - 255)
 */
void spinB_H(int eficiency) {
	analogWrite(HB4, eficiency);
	digitalWrite(HB3, LOW);
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
}

// Tira a média das leituras realizadas.
int getDistance(){
  
  int distance = 0;
  
  for (int i = 0; i < NUMERO_LEITURAS; i++) {
  	distance += dist_array[i];
  }
  distance /= NUMERO_LEITURAS;
  
  return distance;
}

// Pega a distancia do sensor ultrassonico
long pegaDistancia() {

	long duration, cm;

	digitalWrite(TRIGGER_PIN, LOW);
	delayMicroseconds(2);
	digitalWrite(TRIGGER_PIN, HIGH);
	delayMicroseconds(10);
	digitalWrite(TRIGGER_PIN, LOW);
	
	duration = pulseIn(ECHO_PIN, HIGH);

	cm = microsecondsToCentimeters(duration);
  
  	return cm;
}

//Converte o tempo em distancia
long microsecondsToCentimeters(long microseconds) {
	
	return microseconds / 29 / 2;
}