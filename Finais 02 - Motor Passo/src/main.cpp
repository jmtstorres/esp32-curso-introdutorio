#include <Arduino.h>
#include <Stepper.h>

const int stepsPerRevolution = 100; // change this to fit the number of steps per revolution

// initialize the stepper library on pins 15,2,0,4
Stepper myStepper(stepsPerRevolution, 15, 2, 4, 0);

int stepCount = 0; // number of steps the motor has taken

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  // step one step:
  myStepper.step(1);
  stepCount++;
  Serial.println(stepCount);
  delay(500);
}