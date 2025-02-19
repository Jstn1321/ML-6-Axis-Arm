#include <ezButton.h>
#include <AccelStepper.h>
#include <util/delay.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <MultiStepper.h>
#include <stdint.h>
#include <Servo.h>

#define J1step 41
#define J1dir 42
#define J2step 43
#define J2dir 44
#define J3step 45
#define J3dir 46
#define J4step 39
#define J4dir 48
#define J5step 49
#define J5dir 50
#define J6step 51
#define J6dir 52 

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define limitJ1 28
#define limitJ2 29
#define limitJ3 30
#define limitJ4 31
#define limitJ5 32
#define limitJ6 33

long J1pos;
long J2pos;
long J3pos;
long J4pos;
long J5pos;
long J6pos;

long home[6] = {0,0,0,0,0,0};

ezButton limJ1(limitJ1);
ezButton limJ2(limitJ2);
ezButton limJ3(limitJ3);
ezButton limJ4(limitJ4);
ezButton limJ5(limitJ5);
ezButton limJ6(limitJ6);

byte booger;
int16_t x,y;
uint16_t w,h;

bool manual = false;

int steps[6] = {0,0,0,0,0,0};

int joy1x;
int joy1y;
int joy2x;
int joy2y;
int joy3x;
int joy3y;
int joy4x;
int joy4y;
int joy5x;
int joy5y;
int joy6x;
int joy6y;

long blueSorted[6] = {-15640, 9000 - 1400, -32400 - (-10080), 0, -14933 - (-15306), 0};
long greenSorted[6] = {19720, 9000 - 1400, -32400 - (-10080), 0, -14933 - (-15306), 0};
long gotoposition[6];

bool firstRun = true;

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

AccelStepper stepper6(1, 51, 52); // (Type of driver: with 2 pins, STEP, DIR)
AccelStepper stepper5(1, 49, 50); // (Type of driver: with 2 pins, STEP, DIR)
AccelStepper stepper4(1, 39, 48); // (Type of driver: with 2 pins, STEP, DIR)
AccelStepper stepper3(1, 45, 46); // (Type of driver: with 2 pins, STEP, DIR)
AccelStepper stepper2(1, 43, 44); // (Type of driver: with 2 pins, STEP, DIR)
AccelStepper stepper1(1, 41, 42); // (Type of driver: with 2 pins, STEP, DIR)

Servo gripper;

MultiStepper steppersControl;

void setup() {
  gripper.attach(7);
  pinMode(27, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(limitJ1, INPUT_PULLUP);
  pinMode(limitJ2, INPUT_PULLUP);
  pinMode(limitJ3, INPUT_PULLUP);
  pinMode(limitJ4, INPUT_PULLUP);
  pinMode(limitJ5, INPUT_PULLUP);
  pinMode(limitJ6, INPUT_PULLUP);
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial); 
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.getTextBounds("JN V1", 0, 0, &x, &y, &w, &h);
  booger = (SCREEN_WIDTH - w)/2;
  display.setCursor(booger, 0);
  display.println("JN V1");
  display.setTextSize(1);
  display.setCursor(0, 30);
  display.println("Mode: Manual");
  display.setCursor(0, 50);
  display.println("Status: Idle");
  display.display(); 


  stepper1.setMaxSpeed(15000);
  stepper1.setAcceleration(5000);
  stepper2.setMaxSpeed(1000);
  stepper2.setAcceleration(700);
  stepper3.setMaxSpeed(10000);
  stepper3.setAcceleration(500);
  stepper4.setMaxSpeed(3000);
  stepper4.setAcceleration(1000);
  stepper5.setMaxSpeed(10000);
  stepper5.setAcceleration(1000);
  stepper6.setMaxSpeed(500);
  stepper6.setAcceleration(100);

  stepper1.setCurrentPosition(0);
  stepper2.setCurrentPosition(0);
  stepper3.setCurrentPosition(0);
  stepper4.setCurrentPosition(0);
  stepper5.setCurrentPosition(0);
  stepper6.setCurrentPosition(0);

  limJ1.setDebounceTime(50); 
  limJ2.setDebounceTime(50); 
  limJ3.setDebounceTime(50); 
  limJ4.setDebounceTime(50); 
  limJ5.setDebounceTime(50); 
  limJ6.setDebounceTime(50); 

  steppersControl.addStepper(stepper1);
  steppersControl.addStepper(stepper2);
  steppersControl.addStepper(stepper3);
  steppersControl.addStepper(stepper4);
  steppersControl.addStepper(stepper5);
  steppersControl.addStepper(stepper6);
}

void loop() {

  if (firstRun){
    caliJ1();
    caliJ2(); 
    caliJ3(); 
    caliJ4(); 
    caliJ5(); 
    caliJ6(); 
    firstRun = false;
    rgbLed(255,0,0);
  }
  if (Serial.available() > 0){
    char delimiter = Serial.read();
    if (delimiter == '$'){
      char letter = Serial.read();
      if (letter == 'a'){
        manual = false;
      }
      else if (letter == 'm'){
        manual = true;
      }

    }
  }
  while (manual){
  
  rgbLed(0,255,0);
  changeStatus("Status: Idle");

  joy1x = analogRead(A0);
  joy1y = analogRead(A1);
  joy2x = analogRead(A2);
  joy2y = analogRead(A3);
  joy3x = analogRead(A4);
  joy3y = analogRead(A5);

  if (Serial.available() > 0){
    char delimiter = Serial.read();
    if (delimiter == '$'){
      char letter = Serial.read();
      if (letter == 'a'){
        manual = false;
      }
    }
  }

  if (joy1x > 700){
    rgbLed(255,0,0);
    changeStatus("Status: Moving");
    digitalWrite(J1dir, HIGH);
    
    while (joy1x > 700){
      digitalWrite(J1step,HIGH); 
      //__asm__("nop\n\t");
      digitalWrite(J1step,LOW); 
      //__asm__("nop\n\t");
      joy1x = analogRead(A0);
    }
  } 
  else if (joy1x < 200) {
    rgbLed(255,0,0);
    changeStatus("Status: Moving");
    digitalWrite(J1dir, LOW);
  
    while (joy1x < 200){
      digitalWrite(J1step,HIGH); 
     // __asm__("nop\n\t");    
      digitalWrite(J1step,LOW); 
      //__asm__("nop\n\t");
      joy1x = analogRead(A0);
    }
  }
  if (joy1y > 700){
    rgbLed(255,0,0);
    changeStatus("Status: Moving");
    digitalWrite(J2dir, HIGH);

    while (joy1y > 700){
      digitalWrite(J2step,HIGH); 
      delayMicroseconds(450);   
      digitalWrite(J2step,LOW); 
      delayMicroseconds(450); 
      joy1y = analogRead(A1);
    }
  }
  else if (joy1y < 200){
    rgbLed(255,0,0);
    changeStatus("Status: Moving");
    digitalWrite(J2dir, LOW);
    
    while (joy1y < 200){
      digitalWrite(J2step,HIGH); 
      delayMicroseconds(450);   
      digitalWrite(J2step,LOW); 
      delayMicroseconds(450); 
      joy1y = analogRead(A1);
  }
}
  if (joy2x > 700){
    rgbLed(255,0,0);
    changeStatus("Status: Moving");
    digitalWrite(J3dir, HIGH);

    while (joy2x > 700){
      digitalWrite(J3step,HIGH); 
      delayMicroseconds(200);  
      digitalWrite(J3step,LOW); 
      delayMicroseconds(200); 
      joy2x = analogRead(A2);
    }
  }
  else if (joy2x < 200){
    changeStatus("Status: Moving");
    rgbLed(255,0,0);
    digitalWrite(J3dir, LOW);

    while (joy2x < 200){
      digitalWrite(J3step,HIGH); 
      delayMicroseconds(200);     
      digitalWrite(J3step,LOW); 
      delayMicroseconds(200); 
      joy2x = analogRead(A2);
  }
}

 if (joy2y > 700){
  digitalWrite(J4dir, HIGH);
  rgbLed(255,0,0);
  changeStatus("Status: Moving");

  while (joy2y > 700){
    digitalWrite(J4step,HIGH); 
    delayMicroseconds(200);     
    digitalWrite(J4step,LOW); 
    delayMicroseconds(200); 
    joy2y = analogRead(A3);
  }
 }
  else if (joy2y < 200) {
    digitalWrite(J4dir, LOW);
    rgbLed(255,0,0);
    changeStatus("Status: Moving");

    while (joy2y < 200){
      digitalWrite(J4step,HIGH); 
      delayMicroseconds(200);     
      digitalWrite(J4step,LOW); 
      delayMicroseconds(200); 
      joy2y = analogRead(A3);
    }
  }

  if (joy3x > 700){
  digitalWrite(J5dir, HIGH);
  rgbLed(255,0,0);
  changeStatus("Status: Moving");

  while (joy3x > 700){
    digitalWrite(J5step,HIGH); 
    delayMicroseconds(50);     
    digitalWrite(J5step,LOW); 
    delayMicroseconds(50); 
    joy3x = analogRead(A4);
  }
 }
  else if (joy3x < 200) {
    digitalWrite(J5dir, LOW);
    rgbLed(255,0,0);
    changeStatus("Status: Moving");

    while (joy3x < 200){
      digitalWrite(J5step,HIGH); 
      delayMicroseconds(50);     
      digitalWrite(J5step,LOW); 
      delayMicroseconds(50); 
      joy3x = analogRead(A4);
    }
  }

  if (joy3y > 700){
  digitalWrite(J6dir, HIGH);
  rgbLed(255,0,0);
  changeStatus("Status: Moving");

  while (joy3y > 700){
    digitalWrite(J6step,HIGH); 
    delayMicroseconds(1000);     
    digitalWrite(J6step,LOW); 
    delayMicroseconds(1000); 
    joy3y = analogRead(A5);
  }
 }
  else if (joy3y < 200) {
    digitalWrite(J6dir, LOW);
    rgbLed(255,0,0);
    changeStatus("Status: Moving");

    while (joy3y < 200){
      digitalWrite(J6step,HIGH); 
      delayMicroseconds(1000);     
      digitalWrite(J6step,LOW); 
      delayMicroseconds(1000); 
      joy3y = analogRead(A5);
    }
    }
  }
  
while (manual == false) {
    rgbLed(0,0,255);
    changeMode("Mode: Auto");
    if (Serial.available() > 0){

        char delimiter = Serial.read();
        
    if (delimiter == '$'){
      char letter = Serial.read();
      if (letter == 'm'){
        manual = true;
      }
     }

    if (delimiter == '#'){

    if (Serial.available() >= 9 * sizeof(int16_t)) {

        long jointAngles[9];
        byte buffer[9 * sizeof(int16_t)];
        Serial.readBytes(buffer, 9 * sizeof(int16_t));

        for (int i = 0; i < 9; i++) {
            jointAngles[i] = 0;
        for (int j = 0; j < sizeof(int16_t); j++) {
            jointAngles[i] |= buffer[i * sizeof(int16_t) + j] << (8 * j);
            }
        }

        jointAngles[1] = long((float(jointAngles[1]) / 360.0) * (51 * 1600 * 3));
        jointAngles[2] = long((float(jointAngles[2]) / 360.0) * (15 * 1600));
        jointAngles[4] = long((float(jointAngles[4]) / 360.0) * 27 * 1600 * 3);
        jointAngles[5] = long((float(jointAngles[5]) / 360.0) * (5 * 1600 * 3));
        jointAngles[6] = long((float(jointAngles[6]) / 360.0) * 14 * 1600 * 3);
        jointAngles[7] = long((float(jointAngles[7]) / 360.0) * (1600));

        gotoposition[0] = jointAngles[1];
        gotoposition[1] = J2pos - jointAngles[2];
        gotoposition[2] = J3pos - jointAngles[4];
        gotoposition[3] = jointAngles[5];
        gotoposition[4] = J5pos - jointAngles[6];
        gotoposition[5] = jointAngles[7];
        
        steppersControl.moveTo(gotoposition);
        steppersControl.runSpeedToPosition();
        J2pos = jointAngles[2];
        J3pos = jointAngles[4];
        J5pos = jointAngles[6];
        
        //Then bring to home position
        delay(2000);
        steppersControl.moveTo(home);
        steppersControl.runSpeedToPosition();
        J2pos = 9000;
        J3pos = -32400;
        J5pos = -14933;

        if (jointAngles[8] == 1){//Checks if it is blue
            steppersControl.moveTo(blueSorted);
            steppersControl.runSpeedToPosition();
            delay(2000);
            steppersControl.moveTo(home);
            steppersControl.runSpeedToPosition();
            J2pos = 9000;
            J3pos = -32400;
            J5pos = -14933;
        }
        else if (jointAngles[8] == 0){
            steppersControl.moveTo(greenSorted);
            steppersControl.runSpeedToPosition();
            delay(2000);
            steppersControl.moveTo(home);
            steppersControl.runSpeedToPosition();
            J2pos = 9000;
            J3pos = -32400;
            J5pos = -14933;
        }
   }
  }
 }
}
  
}
void rgbLed (int r, int g, int b){
  analogWrite(8, r);
  analogWrite(9, b);
  analogWrite(10, g);
}

void changeStatus (String message){
  display.setCursor(0, 50);
  for (y=50; y<=57; y++)
      {
       for (x=0; x<127; x++)
       {
        display.drawPixel(x, y, BLACK); 
       }
      }
  display.println(message);
  display.display(); 
}

void changeMode (String message){
  display.setCursor(0, 30);
  for (y=30; y<=57; y++)
      {
       for (x=0; x<127; x++)
       {
        display.drawPixel(x, y, BLACK); 
       }
      }
  display.println(message);
  display.display(); 
}

void caliJ1(){
  stepper1.moveTo(250000);
  while (true){
      limJ1.loop();
      int state = limJ1.getState();
      stepper1.run();
      if (state == LOW){
        break;
      }
    }
  stepper1.setCurrentPosition(0);
  stepper1.moveTo(-1600*0.4*51*3);
  stepper1.runToPosition();
  stepper1.setCurrentPosition(0);
}

void caliJ2(){
  stepper2.moveTo(-60000);
  int state = limJ2.getState();
  if (state == HIGH){
  while (true){
      limJ2.loop();
      stepper2.run();
      state = limJ2.getState();
      if (state == LOW){
        break;
      }
    }
  }
  stepper2.setCurrentPosition(0);
  stepper2.moveTo(1600*0.05*15); //moves roughly 15 degrees
  stepper2.runToPosition();
  stepper2.setCurrentPosition(0);
  J2pos = 9000;
}

void caliJ3(){
  int state = limJ3.getState();
  if (state == HIGH){
  stepper3.moveTo(-130000);
  while (true){
      limJ3.loop();
      stepper3.run();
      state = limJ3.getState();
      if (state == LOW){
        break;
      }
    }
  }
  stepper3.setCurrentPosition(0);
  stepper3.moveTo(1600*0.065*27*3); // MAKE IT SO THAT IT GOES TO 90 DEGREES
  stepper3.runToPosition();
  stepper3.setCurrentPosition(0);
  J3pos = -32400;
}

void caliJ4(){
  int state = limJ4.getState();
  if (state == HIGH){
  stepper4.moveTo(60000);
  while (true){
      limJ4.loop();  
      stepper4.run();
      state = limJ4.getState();
      if (state == LOW){
        break;
      }
    }
  }
  stepper4.setCurrentPosition(0);
  stepper4.moveTo(-1600*0.65*5);
  stepper4.runToPosition();
  stepper4.setCurrentPosition(0);
}

void caliJ5(){
  stepper5.moveTo(-80000);
  while (true){
      limJ5.loop();
      stepper5.run();
      int state = limJ5.getState();
      if (state == LOW){
        break;
      }
    }
  stepper5.setCurrentPosition(0);
  stepper5.moveTo(0.4 * 1600 * 3 * 14);
  stepper5.runToPosition();
  stepper5.setCurrentPosition(0);
  J5pos = -14933;
}

void caliJ6(){
  int state = limJ6.getState();
  if (state == HIGH){
  stepper6.moveTo(60000);
  while (true){
      limJ6.loop(); 
      stepper6.run();
      state = limJ6.getState();
      if (state == LOW){
        break;
      }
    }
  }
  stepper6.setCurrentPosition(0);
  stepper6.moveTo(-730);
  stepper6.runToPosition();
  stepper6.setCurrentPosition(0);
}