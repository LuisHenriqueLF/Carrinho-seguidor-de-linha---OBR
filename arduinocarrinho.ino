const int in1 = 4; 
const int in2 = 5; 
const int in3 = 6; 
const int in4 = 7; 
const int ena = 3; 
const int enb = 9; 

const int triggerPin = 2;
const int echoPin = 11;

long readUltrasonicDistance(int triggerPin, int echoPin) {
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(10, INPUT);
  pinMode(8, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);
  Serial.begin(9600);
}

void frente() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  
  for (int velo = 255; velo >= 150; velo -= 5) {
    analogWrite(ena, velo);
    analogWrite(enb, velo);
    delay(10);
  }
}

void atras() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  
  for (int velo = 255; velo >= 150; velo -= 5) {
    analogWrite(ena, velo);
    analogWrite(enb, velo);
  }
}

void direita() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  
  for (int velo = 255; velo >= 150; velo -= 5) {
    analogWrite(ena, velo);
  }
  analogWrite(enb, 0);
}

void esquerda() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  
  for (int velo = 255; velo >= 150; velo -= 5) {
    analogWrite(enb, velo);
  }
  analogWrite(ena, 0);
}

void parar() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  
  analogWrite(ena, 0);
  analogWrite(enb, 0);
}

void desviar() {
  parar();
  delay(500);
  
  atras(); 
  delay(500);
  
  esquerda();  
  delay(700);
  
  frente();  
  delay(1000);
  
  direita(); 
  delay(700);
  
  frente(); 
}

void loop() {
  int distanciaCm = 0.01723 * readUltrasonicDistance(triggerPin, echoPin);
  Serial.println(distanciaCm);

  if (distanciaCm > 0 && distanciaCm < 15) {  
    desviar();
  } else {
    int sensormDire = digitalRead(10);
    int sensormEsq = digitalRead(8);
    int sensorEsq = digitalRead(12);
    int sensorDire = digitalRead(13);
    
    if (sensormDire == 0 && sensormEsq == 0 && sensorEsq == 0 && sensorDire == 0) {
      frente();
    } else if (sensormEsq == 1 && sensormDire == 1) {
      frente();
    } else if (sensormDire == 1) {
      direita();
    } else if (sensormEsq == 1) {
      esquerda();
    } else if (sensorEsq == 1) {
      esquerda();
    } else if (sensorDire == 1) {
      direita();
    }
  }
}
