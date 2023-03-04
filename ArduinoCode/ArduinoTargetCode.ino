#include <Wire.h>
#include <Servo.h>

#define PIN_ALVO 7
#define PIN_LED 8

int angulo = 0; 
int novoAngulo = 0;
Servo alvo;  
int sensorDoAlvo= A3;  // LDR Sensor
int pontuacao = 0; 
int leituraDoSensor;
int timer = 100; 
unsigned long intervalo = 100; 
unsigned long millisAnterior = 0;
int anguloAnterior = 0;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_LED, OUTPUT);
  alvo.attach(PIN_ALVO);
  alvo.write(0);
}

void loop() {
  
  unsigned long millisAtual = millis(); 

  
  if ((unsigned long)(millisAtual - millisAnterior) >= intervalo) {
      leituraDoSensor = analogRead(sensorDoAlvo);
    }
  millisAnterior = millis();

  fazLeitura();
  alvoVilao();
  alvoCaido();
  terminaJogo();
  contador();
  imprimePontuacao();   
}


void fazLeitura(){
  if (Serial.available()> 0) {
    angulo = Serial.parseInt();
        Serial.print("angulo: ");
    Serial.print(angulo);
    if (angulo == 0){
	 digitalWrite(PIN_LED, HIGH);
     
    }
    else if (angulo == 1){
    	digitalWrite(PIN_LED, LOW);
    }
    else if (angulo == 2){
      novoAngulo = 90;
    }
    else if (angulo == 3){
      novoAngulo = 135;
    }
    else if (angulo == 4){
      novoAngulo = 180;
    }
  }
}
  
void alvoVilao() {
    alvo.write(novoAngulo);
}

void alvoCaido() {
  if (leituraDoSensor > 200) {
    pontuacao++;
    Serial.print("Acertou o alvo! Nova pontuação: ");
    Serial.print(pontuacao);
    Serial.print("\n");
    alvo.write(0);
}
}

void imprimePontuacao(){
  if(timer % 5 == 0){
    Serial.print("Pontos: ");
    Serial.print(pontuacao);
    Serial.print("\n");
}
}

void contador() {
  timer--;
  delay(1000);
}

void terminaJogo() {
  if (timer == 0) {
    alvo.write(0);
    Serial.print("*****************\n");
    Serial.print(" SUA PONTUAÇÃO: ");
    Serial.print(pontuacao);
    Serial.print("*****************\n");
    delay(10000);
    pontuacao=0;
    timer = 100;
  }
}

