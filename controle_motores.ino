#include <SoftwareSerial.h>

// Ajuste: Comentário corrigido para Arduino Uno
SoftwareSerial bluetooth(2, 3); 

// Definição dos pinos
const int motorA1 = 5; 
const int motorA2 = 6; 
const int motorB1 = 9; 
const int motorB2 = 10; 

char comando;

void setup() {
  Serial.begin(9600);
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
    
    // Ajuste: Mostra o comando recebido no monitor serial do PC
    Serial.println(comando); 
    
    switch (comando) {
      case 'F': case 'f': frente();    break;
      case 'B': case 'b': tras();      break;
      case 'L': case 'l': esquerda();  break;
      case 'R': case 'r': direita();   break;
      case 'S': case 's': parar();     break;
    }
  }
}

void frente() {
  // Lado A e Lado B para frente
  digitalWrite(motorA1, HIGH); digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH); digitalWrite(motorB2, LOW);
}

void tras() {
  // Lado A e Lado B para trás
  digitalWrite(motorA1, LOW);  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, LOW);  digitalWrite(motorB2, HIGH);
}

void esquerda() {
  // Para virar à esquerda:
  // Lado Direito (B) vai para FRENTE, Lado Esquerdo (A) vai para TRÁS
  digitalWrite(motorA1, LOW);  digitalWrite(motorA2, HIGH); // A Trás
  digitalWrite(motorB1, HIGH); digitalWrite(motorB2, LOW);  // B Frente
}

void direita() {
  // Para virar à direita:
  // Lado Esquerdo (A) vai para FRENTE, Lado Direito (B) vai para TRÁS
  digitalWrite(motorA1, HIGH); digitalWrite(motorA2, LOW);  // A Frente
  digitalWrite(motorB1, LOW);  digitalWrite(motorB2, HIGH); // B Trás
}

void parar() {
  digitalWrite(motorA1, LOW);  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);  digitalWrite(motorB2, LOW);
}
