const byte seteSegmentos[16][7] = { { 1,1,1,1,1,1,0 },  // = Digito 0
                                 { 0,1,1,0,0,0,0 },  // = Digito 1
                                 { 1,1,0,1,1,0,1 },  // = Digito 2
                                 { 1,1,1,1,0,0,1 },  // = Digito 3
                                 { 0,1,1,0,0,1,1 },  // = Digito 4
                                 { 1,0,1,1,0,1,1 },  // = Digito 5
                                 { 1,0,1,1,1,1,1 },  // = Digito 6
                                 { 1,1,1,0,0,0,0 },  // = Digito 7
                                 { 1,1,1,1,1,1,1 },  // = Digito 8
                                 { 1,1,1,0,0,1,1 },  // = Digito 9
                                 { 1,1,1,0,1,1,1 },  // = Digito A
                                 { 0,0,1,1,1,1,1 },  // = Digito B
                                 { 1,0,0,1,1,1,0 },  // = Digito C
                                 { 0,1,1,1,1,0,1 },  // = Digito D
                                 { 1,0,0,1,1,1,1 },  // = Digito E
                                 { 1,0,0,0,1,1,1 }   // = Digito F
                                 };

int arr[5];
int i = 0;
int j = 0;
int senha = 0;

#define led1 12
#define led2 13

void setup() {
  pinMode(2, OUTPUT); //Pino 2 do Arduino ligado ao segmento A  
  pinMode(3, OUTPUT); //Pino 3 do Arduino ligado ao segmento B
  pinMode(4, OUTPUT); //Pino 4 do Arduino ligado ao segmento C
  pinMode(5, OUTPUT); //Pino 5 do Arduino ligado ao segmento D
  pinMode(6, OUTPUT); //Pino 6 do Arduino ligado ao segmento E
  pinMode(7, OUTPUT); //Pino 7 do Arduino ligado ao segmento F
  pinMode(8, OUTPUT); //Pino 8 do Arduino ligado ao segmento G
  pinMode(9, OUTPUT); //Pino 9 do Arduino ligado ao segmento PONTO
  pinMode(10, INPUT); //Botão salva
  pinMode(11, INPUT); //Botão incrementa
  pinMode(12, OUTPUT); //Led Vermelho
  pinMode(13, OUTPUT);  //Led Verde
}


void loop() {
  // put your main code here, to run repeatedly:
  if(checkButtonState(10)) {
    delay(20);
    while(checkButtonState(10));
    Serial.println(i);
    Serial.println(j);
    arr[j] = i;
    j++; 
  }

  if(checkButtonState(11)) {
    delay(20);
    while(checkButtonState(11));
    Serial.print("11 - I:" + i);
    i++;
    if(i == 16) i = 0; 
  }

  liga7Seg(i);

  if(j == 4) {
    if(compara(achanum(arr, j), senha)) {
      digitalWrite(led1, HIGH);
      Serial.println("Igual");
    }
    else {
      Serial.println("Diferente");
      digitalWrite(led2, HIGH);
    }
    delay(1000);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    j = 0;
  }
}

int achanum(int vect[], int size) {
  int numero = 0, i;
  for (i = 0; i < size; ++i) {
    numero *= 10;
    numero += vect[i];
  }
  return numero;
}

int compara(int a, int b) {
  if(a == b) return 1;
  return 0;
}

void liga7Seg(int digit) {
  byte pin = 2;
  for (byte segCount = 0; segCount < 7; ++segCount)  { 
    digitalWrite(pin, seteSegmentos[digit][segCount]);
    pin++;
  }
}

int checkButtonState(int button){
  //Source: Arduino, modified by: KilnerJhow
  // read the state of the switch into a local variable:
  int reading = digitalRead(button);
  delay(100);
  reading = digitalRead(button);
  if(reading) {
    return 1;
  }
  return 0;
}