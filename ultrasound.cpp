#include <Arduino.h>

int pin = GPIO_NUM_32;
int pinEcho = GPIO_NUM_27;
int pinTrig = GPIO_NUM_25;

void setup() {      
  //Inicializando GPIO4 como saída    
  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);
  ledcAttachPin(pin, 0);
  ledcSetup(0, 1000, 10);
  Serial.begin(9600);
}     

void loop() {
  // Clears the trigPin
  digitalWrite(pinTrig, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  int duration = pulseIn(pinEcho, HIGH);
  int distance= duration*0.034/2;
  String text = "Distance: " + String(distance) + "\n";
  Serial.write(text.c_str());
  ledcWrite(0, duration/10);//Escrevemos valor no pino de saída  
  delay(20);
} 

