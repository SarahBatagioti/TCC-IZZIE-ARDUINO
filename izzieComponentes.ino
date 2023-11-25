//Fotossensível e buzzer
const int ldr_pin = 13;
const int buzzer = 12;
unsigned long lastDetectionTime = 0;
const unsigned long detectionDelay = 7000; // 7 segundos em milissegundos

// Ultrassônico e ponte H
const int leftTriggerPin = 2; // Pino de trigger do sensor esquerdo
const int leftEchoPin = 3; // Pino de eco do sensor esquerdo
const int centerTriggerPin = 4; // Pino de trigger do sensor central
const int centerEchoPin = 5; // Pino de eco do sensor central
const int rightTriggerPin = 6; // Pino de trigger do sensor direito
const int rightEchoPin = 7; // Pino de trigger do sensor direito
const int motorVibratorPin = LED_BUILTIN; //sensor vibratório

void setup() {

  //Fotossensível e buzzer
  pinMode(ldr_pin, INPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);

  // Ultrassônico e ponte H
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(leftTriggerPin, OUTPUT);
  pinMode(centerTriggerPin, OUTPUT);
  pinMode(rightTriggerPin, OUTPUT);
  pinMode(leftEchoPin, INPUT);
  pinMode(centerEchoPin, INPUT);
  pinMode(rightEchoPin, INPUT);
  pinMode(motorVibratorPin, OUTPUT); // Configura o pino do motor vibratório

}

void loop() {

  //Fotossensível e buzzer
  int ldrValue = digitalRead(ldr_pin);
  if (ldrValue == 1) {
    lastDetectionTime = millis();
    digitalWrite(buzzer, LOW);
  } else {
    if (millis() - lastDetectionTime >= detectionDelay) {
      digitalWrite(buzzer, HIGH);
    }
  }
  Serial.println(ldrValue);
  delay(100);

  // Ultrassônico e ponte H
  int leftDistance = getDistance(leftTriggerPin, leftEchoPin);
  int centerDistance = getDistance(centerTriggerPin, centerEchoPin);
  int rightDistance = getDistance(rightTriggerPin, rightEchoPin);
  if (leftDistance <= 40) {
    // Gire para a direita
    analogWrite(10, 255);
    digitalWrite(9, HIGH); // Sentido horário
    digitalWrite(8, LOW);  // Sentido horário
  } else if (centerDistance <= 40) {
    // Gire para a esquerda
    analogWrite(10, 255);
    digitalWrite(9, LOW);  // Sentido anti-horário
    digitalWrite(8, HIGH); // Sentido anti-horário
  } else if (rightDistance <= 40) {
    // Gire para a esquerda
    analogWrite(10, 255);
    digitalWrite(9, LOW);  // Sentido anti-horário
    digitalWrite(8, HIGH); // Sentido anti-horário
  } else {
     analogWrite(10, 255);
  	digitalWrite(9, LOW);  // Desligado
    digitalWrite(8, LOW);
  }
  delay(100);

  // Motor Vibratório
  if (leftDistance <= 30 || centerDistance <= 30 || rightDistance <= 30) {
    digitalWrite(motorVibratorPin, HIGH); // Liga o motor vibratório
    delay(5000); // Mantém ligado por 5 segundos
    digitalWrite(motorVibratorPin, LOW); // Desliga o motor vibratório
  }

}

// Ultrassônico e ponte H
int getDistance(int triggerPin, int echoPin) {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(8);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  return pulseIn(echoPin, HIGH) / 58; // Calcula a distância em centímetros
}