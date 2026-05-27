// Defina os pinos dos motores (ajuste conforme a sua montagem)
const int motorEsqFrente = 5;
const int motorEsqTras = 6;
const int motorDirFrente = 9;
const int motorDirTras = 10;

void setup() {
  Serial.begin(9600);
  pinMode(motorEsqFrente, OUTPUT);
  pinMode(motorEsqTras, OUTPUT);
  pinMode(motorDirFrente, OUTPUT);
  pinMode(motorDirTras, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    char comando = Serial.read();

    if (comando == 'F') { // Frente
      digitalWrite(motorEsqFrente, HIGH);
      digitalWrite(motorDirFrente, HIGH);
      digitalWrite(motorEsqTras, LOW);
      digitalWrite(motorDirTras, LOW);
    } 
    else if (comando == 'P') { // Parar
      digitalWrite(motorEsqFrente, LOW);
      digitalWrite(motorDirFrente, LOW);
      digitalWrite(motorEsqTras, LOW);
      digitalWrite(motorDirTras, LOW);
    }
    else if (comando == 'D') { // Direita (roda esquerda gira, direita para)
      digitalWrite(motorEsqFrente, HIGH);
      digitalWrite(motorDirFrente, LOW);
    }
    else if (comando == 'E') { // Esquerda (roda direita gira, esquerda para)
      digitalWrite(motorEsqFrente, LOW);
      digitalWrite(motorDirFrente, HIGH);
    }
  }
}