/**
 * Authors: Ana Vitória, Bezaliel Silva, Caio M. Gomes, Fábio William, Jonathan Kilner. (Grupo PCBreakers)
 * License: Este projeto está sob a licensa Creative Commons - Atribuition, Share Alike and Non-commercial (CC BY-NC-SA)
 * Project: Esse projeto é o software para controle de um carrinho seguidor de linha que faz uso de sensores ultrassônico,
 * e óptico(binário) para seguir uma linha preta em um circuito, onde não existem curvas bruscas, porém, existem obstáculos
 * que o carrinho deverá desviar.
 * Place: CIn, UPFE - Recife, Brasil
 */

// #include <Ultrasonic.h>
#include <NewPing.h> // Biblioteca de Ultrassom

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

#define ECHO_PIN 9
#define TRIGGER_PIN 10
#define MAX_DISTANCE 200

#define MIN_DIST 20
#define MAX_DIFF

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

// Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

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

	Serial.begin(9600);

	// Inicia o array de leituras de sensor
	for(i = 0; i < NUMERO_LEITURAS; i++) {
		dist_array[i] = sonar.ping_cm();
		delay(50);
	}
}
 
void loop() {
	
	// pega a distancia atual com a média móvel
	distancia_atual =(int) getDistance();
	
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
			lado_no_04 = mstate;
		}
	}
	// Acha limite do obstáculo
	else if(mstate == 4) {
		acha_limite();
	}
	
	// Sai de perto do obstáculo
	else if(mstate == 5) {
		passa_obstaculo();
		mstate = 6
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
	
	// Lê o sonar
	dist_array[count_dist++] = sonar.ping_cm();
	
	// Reseta o número de leituras.
	if(count_dist == NUMERO_LEITURAS) {
		count_dist = 0;
	}
	
	delay(29);
	
}


void acha_limite() {
	// achou os limites do obstáculo
	if(distancia_atual > MIN_DIST + MAX_DIFF) {
		mstate = 5;
		stop();
	}
	
	else {
		forwardSide(moveSide);
	}
}


void passa_obstaculo() {
	// Inverte o lado de movimentação
	moveSide = (lado_no_04 == 0 ) ? 1 : 0;

	// Move no sentido da borda encontrada do obstáculo.
	forwardPoweredSide(moveSide, 0.45, 0.35);
	// delay(350);
	delay(400);
}

void acha_obstaculo() {
	forwardSide();
	if(distancia_atual <= MIN_DIST) {
		mstate = 7;
		stop();
	}
}

void sai_de_perto() {
	
	moveSide = lado_no_04;
	
	forwardSide();
	
	if(distancia_atual >= MIN_DIST + MAX_DIFF) {
		mstate = 8;
		delay(100); // Vai um pouco mais
		stop(); // Para o carrinho
	}
}

void acha_linha() {
	// Inverte o lado de movimentação
	moveSide = (lado_no_04 == 0 ) ? 1 : 0;
	
	forwardPoweredSide(moveSide, 0.35, 0.45);
	
	// Volta a sair de perto do obstáculo
	if(distancia_atual <= MIN_DIST) {
		mstate = 7;
	}
	
	if(readLine == INSIDE_LINE) {
		mstate = 0;
	}
	
}


// TODO: mudar o nome da função.
void obstaculo() {
	int last_distance = ultrasonic.Ranging(CM);
	// int last_distance = getDistance();
	int diff = 0;
	int MAX_DIST = 4;

	Serial.println(last_distance);
	if(last_distance < 20) {
		cttogo++;
	}
	else {
		cttogo = 0;
	}
	// if(last_distance < 20) {
	if(cttogo == 4){

		int spinct = 0;

		// Gira até encontrar o fim do obstáculo.
		Serial.print("Distance: ");
		Serial.println(last_distance);
		while( diff < MAX_DIST ) {
			forwardSide(moveSide);
			diff = getDistance() - last_distance;
			Serial.print("Diff:");
			Serial.println(diff);

			last_distance = ultrasonic.Ranging(CM);
			Serial.print("last_distance: ");
			Serial.println(last_distance);
			spinct++;
		}

		// Gira um pouco mais para garantir que não vai bater no obstáculo.
		forwardSide(moveSide);
		delay(100);

		// Para para indicar o fim do bloco de processamento.
		stop();
		Serial.print("STOP!!");
		delay(1000);

		// Move no sentido da borda encontrada do obstáculo.
		forwardPoweredSide(moveSide, 0.45, 0.35);
		// delay(350);
		delay(400);

		// Move no sentido da borda encontrada do obstáculo.
		forwardPoweredSide(moveSide, 0.45, 0.35);
		// delay(350);
		delay(100);

		// Para para indicar o fim do bloco de processamento.
		stop();
		Serial.print("STOP!!");
		delay(1000);

		// Indica que agora ele precisa girar no sentido oposto.
		moveSide ^= 1;

		// // gira de volta.
		// forwardPoweredSide(moveSide, 0, 0.7);
		// delay(300);

		// stop();
		// Serial.print("STOP!!");
		// delay(1000);		

		// Reencontra o objeto
		while( ultrasonic.Ranging(CM) > 25 ) {
		// while( getDistance() > 25 ) {
			forwardSide(moveSide);
		}

		// Para para indicar o fim do bloco de processamento.
		stop();
		Serial.print("STOP!!");
		delay(1000);

		// Inverte novamente o sentido de rotação
		moveSide ^= 1;

		// gira de volta.
		// sai de perto do objeto
		while( ultrasonic.Ranging(CM) < 25 ) {
		// while( getDistance() < 25 ) {
			forwardSide(moveSide);
		}

		// vai um pouco mais por precaução
		forwardSide(moveSide);
		delay(300);

		// Para para indicar o fim do bloco de processamento.
		stop();
		Serial.print("STOP!!");
		delay(1000);

		// Gira até reencontrar a pista
		while(readLine != INSIDE_LINE) {
			forwardPoweredSide(moveSide, 0.6, 0.3);
		}

		//encontrou a pista então para.
		stop();
		Serial.print("STOP!!");
		delay(500);

		// TODO: modificar isso para fazer uma máquina de estados real
		// e não uma adaptação técnica da relação com whiles
		// pois se mstate for 1 ele vai girar o sentido quando voltar
		// para o loop principal, então inverte logo para quando chegar
		// lá voltar ao normal.
		if(mstate == 1) {
			moveSide ^= 1;
		}
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

// Tira a média das leituras realizadas.
float getDistance(){
  
  float distance = 0;
  
  for (int i = 0; i < NUMERO_LEITURAS; i++) {
  	distance += dist_array[i];
  }
  distance /= NUMERO_LEITURAS;
  
  return distance;
}