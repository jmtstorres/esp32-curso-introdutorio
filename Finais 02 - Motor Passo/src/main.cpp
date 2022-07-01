#include <Arduino.h>
#include <Stepper.h>

const int stepsPerRevolution = 100; // Passos por revolução

// Inicializa o objeto do motor nos pinos 15,2,0,4
Stepper myStepper(stepsPerRevolution, 15, 2, 4, 0);

int stepCount = 0; // numero de passos já dados

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  // Um passo a cada loop:
  myStepper.step(1);
  stepCount++;
  Serial.println(stepCount);
  delay(500);
}