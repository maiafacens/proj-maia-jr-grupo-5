#define TRIG_1 7 
#define ECHO_1 8   
#define TRIG_2 9 
#define ECHO_2 10    
#define TRIG_3 11 
#define ECHO_3 12 

#define distancia_max 400  
#define distancia_alerta 30 
#define velocidade_frente 90 
#define velocidade_tras 70 

#define ENA 2  //ENA
#define IN1 3 //IN1
#define IN2 4 //IN2

#define ENB 5  //ENB
#define IN3 6  //IN3
#define IN4 1  //IN4

// Funções
int medirDistancia1();
int medirDistancia2();
int medirDistancia3();
void controlarVelocidade();
void andarParaFrente();
void andarParaTras();
void parar();
void virarDireita();
void virarEsquerda();

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_1, OUTPUT);
  pinMode(ECHO_1, INPUT);
  pinMode(TRIG_2, OUTPUT);
  pinMode(ECHO_2, INPUT);
  pinMode(TRIG_3, OUTPUT);
  pinMode(ECHO_3, INPUT);
  
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  int distanciaSensor1 = medirDistancia1();
  int distanciaSensor2 = medirDistancia2();
  int distanciaSensor3 = medirDistancia3();

  Serial.print("Distancia Sensor 1: ");
  Serial.println(distanciaSensor1);
  Serial.print("Distancia Sensor 2: ");
  Serial.println(distanciaSensor2);
  Serial.print("Distancia Sensor 3: ");
  Serial.println(distanciaSensor3);

  // Lógica de controle
   if (distanciaSensor1 < 4 || distanciaSensor2 < 4 || distanciaSensor3 < 40) {
    andarParaTras(); 
  } else if (distanciaSensor2 < 300 && distanciaSensor3 < 300) {
    andarParaFrente();
  } else if (distanciaSensor1 < 250) {
    andarParaFrente(); 
  } else if (distanciaSensor2 < 250) {
    virarEsquerda(); 
  } else if (distanciaSensor3 < 250) {
    virarDireita(); 
  } else {
    parar();
  }
}


int medirDistancia1() {
  int distancia1, duracao1;
  
  digitalWrite(TRIG_1, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_1, LOW);
  duracao1 = pulseIn(ECHO_1, HIGH);
  distancia1 = duracao1 / 58.2;
  delay(10);
  return distancia1;
}

int medirDistancia2() {
  int distancia2, duracao2; 
  
  digitalWrite(TRIG_2, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_2, LOW);
  duracao2 = pulseIn(ECHO_2, HIGH);
  distancia2 = duracao2 / 58.2;
  delay(10);
  
  return distancia2;
}

int medirDistancia3() {
  int distancia3, duracao3;
  
  digitalWrite(TRIG_3, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_3, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_3, LOW);
  duracao3 = pulseIn(ECHO_3, HIGH);
  distancia3 = duracao3 / 58.2;
  delay(10);
  
  return distancia3;
}


void controlarVelocidade(int velA, int velB) {
  analogWrite(ENA, velA);
  analogWrite(ENB, velB);
}

void andarParaFrente() {
  controlarVelocidade(velocidade_frente, velocidade_frente);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void andarParaTras() {
  controlarVelocidade(velocidade_tras, velocidade_tras);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void parar() {
  controlarVelocidade(0, 0);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void virarDireita() {
  controlarVelocidade(velocidade_frente, velocidade_frente);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void virarEsquerda() {
  controlarVelocidade(velocidade_frente, velocidade_frente);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}