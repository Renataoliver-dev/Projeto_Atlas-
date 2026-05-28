#include <SoftwareSerial.h>

SoftwareSerial bluetooth(2, 3);

// Motores
const int motorA1 = 5;
const int motorA2 = 6;
const int motorB1 = 9;
const int motorB2 = 10;

char comando;

void setup() {
  bluetooth.begin(9600);

  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);

  parar();
}

void loop() {

  if (bluetooth.available()) {

    comando = bluetooth.read();

    switch (comando) {

      case 'F': frente();   break;
      case 'B': tras();     break;
      case 'L': esquerda(); break;
      case 'R': direita();  break;
      case 'S': parar();    break;
    }
  }
}

// =========================
// MOVIMENTOS
// =========================

void frente() {
  digitalWrite(motorA1, HIGH); digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH); digitalWrite(motorB2, LOW);
}

void tras() {
  digitalWrite(motorA1, LOW); digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, LOW); digitalWrite(motorB2, HIGH);
}

void esquerda() {
  digitalWrite(motorA1, LOW);  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, HIGH); digitalWrite(motorB2, LOW);
}

void direita() {
  digitalWrite(motorA1, HIGH); digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);  digitalWrite(motorB2, HIGH);
}

void parar() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
}
