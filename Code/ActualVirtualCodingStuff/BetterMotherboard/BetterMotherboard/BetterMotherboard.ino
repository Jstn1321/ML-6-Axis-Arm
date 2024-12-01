#include <ezButton.h>
#include <AccelStepper.h>
#include <util/delay.h>

#define J1step 41
#define J1dir 42
#define J2step 43
#define J2dir 44
#define J3step 45
#define J3dir 46

int joy1x;
int joy1y;
int joy2x;
int joy2y;
int joy3x;
int joy3y;

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
  joy1x = analogRead(A0);
  joy1y = analogRead(A1);
  joy2x = analogRead(A2);
  // put your main code here, to run repeatedly:
  if (joy1x > 700){
    digitalWrite(J1dir, HIGH);
    while (joy1x > 700){
      digitalWrite(J1step,HIGH); 
      __asm__("nop\n\t");
      digitalWrite(J1step,LOW); 
      __asm__("nop\n\t");
      joy1x = analogRead(A0);
    }
  } 
  else if (joy1x < 200) {
    digitalWrite(J1dir, LOW);
    while (joy1x < 200){
      digitalWrite(J1step,HIGH); 
      __asm__("nop\n\t");    // by changing this time delay between the steps we can change the rotation speed
      digitalWrite(J1step,LOW); 
      __asm__("nop\n\t");
      joy1x = analogRead(A0);
    }
  }
  if (joy1y > 700){
    digitalWrite(J2dir, HIGH);
    while (joy1y > 700){
      digitalWrite(J2step,HIGH); 
      delayMicroseconds(450);    // by changing this time delay between the steps we can change the rotation speed
      digitalWrite(J2step,LOW); 
      delayMicroseconds(450); 
      joy1y = analogRead(A1);
    }
  }
  else if (joy1y < 200){
    digitalWrite(J2dir, LOW);
    while (joy1y < 200){
      digitalWrite(J2step,HIGH); 
      delayMicroseconds(450);    // by changing this time delay between the steps we can change the rotation speed
      digitalWrite(J2step,LOW); 
      delayMicroseconds(450); 
      joy1y = analogRead(A1);
  }
}
  if (joy2x > 700){
    digitalWrite(J3dir, HIGH);
    while (joy2x > 700){
      digitalWrite(J3step,HIGH); 
      delayMicroseconds(100);    // by changing this time delay between the steps we can change the rotation speed
      digitalWrite(J3step,LOW); 
      delayMicroseconds(100); 
      joy2x = analogRead(A2);
    }
  }
  else if (joy2x < 200){
    digitalWrite(J3dir, LOW);
    while (joy2x < 200){
      digitalWrite(J3step,HIGH); 
      delayMicroseconds(100);     // by changing this time delay between the steps we can change the rotation speed
      digitalWrite(J3step,LOW); 
      delayMicroseconds(100); 
      joy2x = analogRead(A2);
  }
}
}