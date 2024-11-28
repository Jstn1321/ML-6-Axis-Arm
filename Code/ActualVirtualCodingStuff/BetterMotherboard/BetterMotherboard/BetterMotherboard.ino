#include <ezButton.h>
#include <AccelStepper.h>

int joy1x;
int joy1y;

//AccelStepper stepper6(1, 51, 52); // (Type of driver: with 2 pins, STEP, DIR)
//AccelStepper stepper5(1, 49, 50); // (Type of driver: with 2 pins, STEP, DIR)
//AccelStepper stepper4(1, 47, 48); // (Type of driver: with 2 pins, STEP, DIR)
AccelStepper stepper3(1, 45, 46); // (Type of driver: with 2 pins, STEP, DIR)
AccelStepper stepper2(1, 43, 44); // (Type of driver: with 2 pins, STEP, DIR)
AccelStepper stepper1(1, 41, 42); // (Type of driver: with 2 pins, STEP, DIR)



void setup() {
  pinMode(27, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  // put your setup code here, to run once:
  Serial.begin(9600);
  stepper1.setMaxSpeed(10000);
  stepper2.setMaxSpeed(10000);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  joy1x = (analogRead(A0));
  joy1y = (analogRead(A1));

  //joy1y = map(analogRead(A1), 0, 1023, -1000, 1000);
  if (joy1x > 700){
    stepper2.setSpeed(5000); // Forward
    stepper2.runSpeed();
  } 
  else if (joy1x < 200) {
    stepper2.setSpeed(-5000); // Reverse
    stepper2.runSpeed();
  }
  if (joy1y > 700){
    stepper1.setSpeed(10000);
    stepper1.runSpeed();
  }
  else if (joy1y < 200){
    stepper1.setSpeed(-10000);
    stepper1.runSpeed();
  }
}