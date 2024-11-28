#include <ezButton.h>
#include <AccelStepper.h>
#define ENABLE_PIN 26
int touch = 1;
#include <Wire.h>
int firstLoop = 1;
int potValueX;
int speedX;
int potValueY;
int speedY;
int sped;
int manual = true;
int message = 0;
int tempMessage = 0;
AccelStepper stepper6(1, 51, 52); // (Type of driver: with 2 pins, STEP, DIR)
AccelStepper stepper5(1, 49, 50); // (Type of driver: with 2 pins, STEP, DIR)
AccelStepper stepper4(1, 47, 48); // (Type of driver: with 2 pins, STEP, DIR)
AccelStepper stepper3(1, 45, 46); // (Type of driver: with 2 pins, STEP, DIR)
AccelStepper stepper2(1, 43, 44); // (Type of driver: with 2 pins, STEP, DIR)
AccelStepper stepper1(1, 41, 42); // (Type of driver: with 2 pins, STEP, DIR)

ezButton limitSwitch1(40);
ezButton limitSwitch2(39);
ezButton limitSwitch3(38);
ezButton limitSwitch4(37);
ezButton limitSwitch5(36);
ezButton limitSwitch6(35);

void setup() {
  stepper1.setMaxSpeed(5000); // Set maximum speed value for the stepper
  stepper1.setAcceleration(1500); // Set acceleration value for the stepper
  stepper5.setMaxSpeed(1000); // Set maximum speed value for the stepper
  stepper5.setAcceleration(500); // Set acceleration value for the stepper
  stepper6.setMaxSpeed(1000); // Set maximum speed value for the stepper
  stepper6.setAcceleration(500); // Set acceleration value for the stepper
  stepper1.setCurrentPosition(0);
  stepper1.setSpeed(45000);
  stepper2.setSpeed(15000);
  stepper2.setMaxSpeed(45000);
   // Set maximum speed value for the stepper
  limitSwitch1.setDebounceTime(0); // set debounce time to 50 milliseconds
  limitSwitch2.setDebounceTime(0); // set debounce time to 50 milliseconds
  limitSwitch3.setDebounceTime(0); // set debounce time to 50 milliseconds
  limitSwitch4.setDebounceTime(0); // set debounce time to 50 milliseconds
  limitSwitch5.setDebounceTime(0); // set debounce time to 50 milliseconds
  limitSwitch6.setDebounceTime(0); // set debounce time to 50 milliseconds
  Serial.begin(2000000);  // Debugging on Serial Monitor
  Serial1.begin(2000000);
  Serial1.setTimeout(0.0000000000000000000000000000000000000000000000000000000000000000000000001);
}

void loop() {
    tempMessage = Serial1.parseInt();
    if (tempMessage != 0){
      message = tempMessage;
    }
    Serial.print(message);  // Print message to Serial Monitor
    Serial.print(", ");  // Print message to Serial Monitor
    Serial.println(tempMessage);  // Print message to Serial Monitor
    if (message == -2162) {
    Serial.print("Spininng clockwise");
    stepper2.setSpeed(10000); // Forward
    stepper2.runSpeed();
  } if (message == -2163) {
    Serial.print("Spininng counterclockwise");
    stepper2.setSpeed(-10000); // Reverse
    stepper2.runSpeed();
  } if (message == -2160) {
    Serial.print("Doing nothing");
  }
/*
    if (message == -2162){
      stepper2.setSpeed(15000);
      while (message == -2162){
        stepper2.runSpeed();
        message = Serial1.parseInt();
        Serial.println(message);  // Print message to Serial Monitor
    }
  }
    if (message == -2163){
    //stepper5.moveTo(-100000);
      stepper2.setSpeed(-15000);
      while (message == -2163){
        stepper2.runSpeed();
        message = Serial1.parseInt();
        Serial.println(message);  // Print message to Serial Monitor
    }
  }
/*
  if (message == -2161){
    //stepper5.moveTo(100000);
    stepper6.setSpeed(1000);
    while (message == -2161){
      stepper6.runSpeed();
      message = Serial1.parseInt();
    Serial.println(message);  // Print message to Serial Monitor
    }
  }
  if (message == -2160){
    //stepper5.moveTo(-100000);
    stepper6.setSpeed(-1000);
    while (message == -2160){
      stepper6.runSpeed();
      message = Serial1.parseInt();
    Serial.println(message);  // Print message to Serial Monitor
    }
  }
  */
/*
  if (message == -2165){
    while (message == -2165) {
      message = Serial1.parseInt();
    Serial.println(message + "Staying Still");  // Print message to Serial Monitor
  }
  }
  */

}