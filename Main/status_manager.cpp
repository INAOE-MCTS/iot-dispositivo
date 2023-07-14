#include <SoftwareSerial.h>

const int ledYellow = D0;
const int ledGreen = D1;
const int ledRed = D2;
const int ledWhite = D3;
const int ledActuador = D4;

void setup_pines(){
  pinMode(ledYellow, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(ledWhite, OUTPUT);
  pinMode(ledActuador, OUTPUT);
}

void not_authenticated(){
  digitalWrite(ledRed, HIGH);
  delay(5000);
}

void authenticated(){
  digitalWrite(ledRed, LOW);
  delay(1000);
}

void actuador(int value){
  analogWrite(ledActuador, value);
  delay(3000);
  analogWrite(ledActuador, 0);
  delay(1000);
}

void red(){
  digitalWrite(ledRed, HIGH);
  delay(1000);
  digitalWrite(ledRed, LOW);
  delay(2000);
}

void green(){
  digitalWrite(ledGreen, HIGH);
  delay(1000);
  digitalWrite(ledGreen, LOW);
  delay(2000);
}

void yellow(){
  digitalWrite(ledYellow, HIGH);
  delay(1000);
  digitalWrite(ledYellow, LOW);
  delay(2000);
}

void white(){
  digitalWrite(ledWhite, HIGH);
  delay(1000);
  digitalWrite(ledWhite, LOW);
  delay(1000);
}