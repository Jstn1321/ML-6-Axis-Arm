#include <ezButton.h>
#include <AccelStepper.h>
#include <util/delay.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>

#define J1step 41
#define J1dir 42
#define J2step 43
#define J2dir 44
#define J3step 45
#define J3dir 46
#define J4step 47
#define J4dir 48
#define J5step 49
#define J5dir 50
#define J6step 51
#define J6dir 52
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

byte booger;
int16_t x,y;
uint16_t w,h;

bool manual = true;

String receivedData;

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

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

AccelStepper stepper6(1, 51, 52); // (Type of driver: with 2 pins, STEP, DIR)
AccelStepper stepper5(1, 49, 50); // (Type of driver: with 2 pins, STEP, DIR)
AccelStepper stepper4(1, 47, 48); // (Type of driver: with 2 pins, STEP, DIR)
AccelStepper stepper3(1, 45, 46); // (Type of driver: with 2 pins, STEP, DIR)
AccelStepper stepper2(1, 43, 44); // (Type of driver: with 2 pins, STEP, DIR)
AccelStepper stepper1(1, 41, 42); // (Type of driver: with 2 pins, STEP, DIR)

void setup() {
  pinMode(27, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial); 
  stepper1.setMaxSpeed(10000);
  stepper2.setMaxSpeed(10000);
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
}

void loop() {
  
  if (manual){
  if (Serial.available() > 0) {
    receivedData = Serial.readStringUntil('\n'); 
    if (receivedData.equals("a")){
      manual = false;
    }
  }
  rgbLed(0,255,0);
  changeStatus("Status: Idle");

  joy1x = analogRead(A0);
  joy1y = analogRead(A1);
  joy2x = analogRead(A2);
  joy2y = analogRead(A3);
  joy3x = analogRead(A4);
  joy3y = analogRead(A5);

  if (joy1x > 700){
    rgbLed(255,0,0);
    changeStatus("Status: Moving");
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
    rgbLed(255,0,0);
    changeStatus("Status: Moving");
    digitalWrite(J1dir, LOW);
  
    while (joy1x < 200){
      digitalWrite(J1step,HIGH); 
      __asm__("nop\n\t");    
      digitalWrite(J1step,LOW); 
      __asm__("nop\n\t");
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
      delayMicroseconds(100);  
      digitalWrite(J3step,LOW); 
      delayMicroseconds(100); 
      joy2x = analogRead(A2);
    }
  }
  else if (joy2x < 200){
    changeStatus("Status: Moving");
    rgbLed(255,0,0);
    digitalWrite(J3dir, LOW);

    while (joy2x < 200){
      digitalWrite(J3step,HIGH); 
      delayMicroseconds(100);     
      digitalWrite(J3step,LOW); 
      delayMicroseconds(100); 
      joy2x = analogRead(A2);
  }
}

  //ADJUST SPEED ACCORDINGLY I HAVENT DONE THAT YET
 if (joy2y > 700){
  digitalWrite(J4dir, HIGH);
  rgbLed(255,0,0);
  changeStatus("Status: Moving");

  while (joy2y > 700){
    digitalWrite(J4step,HIGH); 
    delayMicroseconds(600);     
    digitalWrite(J4step,LOW); 
    delayMicroseconds(600); 
    joy2y = analogRead(A3);
  }
 }
  else if (joy2y < 200) {
    digitalWrite(J4dir, LOW);
    rgbLed(255,0,0);
    changeStatus("Status: Moving");

    while (joy2y < 200){
      digitalWrite(J4step,HIGH); 
      delayMicroseconds(500);     
      digitalWrite(J4step,LOW); 
      delayMicroseconds(500); 
      joy2y = analogRead(A3);
    }
  }

  if (joy3x > 700){
  digitalWrite(J5dir, HIGH);
  rgbLed(255,0,0);
  changeStatus("Status: Moving");

  while (joy3x > 700){
    digitalWrite(J5step,HIGH); 
    delayMicroseconds(100);     
    digitalWrite(J5step,LOW); 
    delayMicroseconds(100); 
    joy3x = analogRead(A4);
  }
 }
  else if (joy3x < 200) {
    digitalWrite(J5dir, LOW);
    rgbLed(255,0,0);
    changeStatus("Status: Moving");

    while (joy3x < 200){
      digitalWrite(J5step,HIGH); 
      delayMicroseconds(100);     
      digitalWrite(J5step,LOW); 
      delayMicroseconds(100); 
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
  
  if (manual == false) {
  if (Serial.available() > 0) {
    receivedData = Serial.readStringUntil('\n'); 
    if (receivedData.length() == 1 && receivedData.equals("m")){
      manual = true;
    }
    rgbLed(0,0,255);
    changeMode("Sdrg");
    int startingPoint = 0;
    int commaPoint = 0;
    float itemInData = 0.0; 
    float jointAngles[8];  
    int jointAnglesIndex = 0;

    
  if (receivedData.length() > 1){
    for (int i = 0; i < receivedData.length(); i++) {
      if (receivedData[i] == ',') {
        commaPoint = i;
        String temp = receivedData.substring(startingPoint, commaPoint);
        temp.trim();
        itemInData = temp.toFloat(); 
        if (jointAnglesIndex < 8) {  
          jointAngles[jointAnglesIndex] = itemInData;
          jointAnglesIndex++;
        }
        startingPoint = commaPoint + 1;
      }
    }

    if (startingPoint < receivedData.length()) {
      String temp = receivedData.substring(startingPoint);
      temp.trim();
      itemInData = temp.toFloat();
      if (jointAnglesIndex < 8) { 
        jointAngles[jointAnglesIndex] = itemInData;
        jointAnglesIndex++;
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
//TO DO: MAKE A FUNCTION FOR MANUAL MOVEMENT OF THE MOTORS (maybe)

