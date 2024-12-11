#include <ezButton.h>
#include <AccelStepper.h>
#include <util/delay.h>

#define J1step 41
#define J1dir 42
#define J2step 43
#define J2dir 44
#define J3step 45
#define J3dir 46
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

byte booger;
int16_t x,y;
uint16_t w,h;

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


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
  // Display static text
  display.println("JN V1");
  display.setTextSize(1);
  display.setCursor(0, 30);
  display.println("Mode: Manual");
  display.setCursor(0, 50);
  display.println("Status: Idle");
  display.display(); 
}

void loop() {
  rgbLed(0,255,0);
  joy1x = analogRead(A0);
  joy1y = analogRead(A1);
  joy2x = analogRead(A2);
  // put your main code here, to run repeatedly:
  if (joy1x > 700){
    rgbLed(255,0,0);
    digitalWrite(J1dir, HIGH);
    display.setCursor(0, 50);
    for (y=50; y<=57; y++)
      {
       for (x=0; x<127; x++)
       {
        display.drawPixel(x, y, BLACK); 
       }
      }
    display.println("Status: Moving");
    display.display(); 
    while (joy1x > 700){
      digitalWrite(J1step,HIGH); 
      __asm__("nop\n\t");
      digitalWrite(J1step,LOW); 
      __asm__("nop\n\t");
      joy1x = analogRead(A0);
    }
    display.setCursor(0, 50);
  for (y=50; y<=57; y++)
      {
       for (x=0; x<127; x++)
       {
        display.drawPixel(x, y, BLACK); 
       }
      }
  display.println("Status: Idle");
  display.display(); 
  } 
  else if (joy1x < 200) {
    rgbLed(255,0,0);
    digitalWrite(J1dir, LOW);
    display.setCursor(0, 50);
    for (y=50; y<=57; y++)
      {
       for (x=0; x<127; x++)
       {
        display.drawPixel(x, y, BLACK); 
       }
      }
    display.println("Status: Moving");
    display.display(); 
    while (joy1x < 200){
      digitalWrite(J1step,HIGH); 
      __asm__("nop\n\t");    // by changing this time delay between the steps we can change the rotation speed
      digitalWrite(J1step,LOW); 
      __asm__("nop\n\t");
      joy1x = analogRead(A0);
    }
    display.setCursor(0, 50);
    for (y=50; y<=57; y++)
      {
       for (x=0; x<127; x++)
       {
        display.drawPixel(x, y, BLACK); 
       }
      }
  display.println("Status: Idle");
  display.display(); 
  }
  if (joy1y > 700){
    rgbLed(255,0,0);
    digitalWrite(J2dir, HIGH);
    display.setCursor(0, 50);
    for (y=50; y<=57; y++)
      {
       for (x=0; x<127; x++)
       {
        display.drawPixel(x, y, BLACK); 
       }
      }
    display.println("Status: Moving");
    display.display(); 
    while (joy1y > 700){
      digitalWrite(J2step,HIGH); 
      delayMicroseconds(450);    // by changing this time delay between the steps we can change the rotation speed
      digitalWrite(J2step,LOW); 
      delayMicroseconds(450); 
      joy1y = analogRead(A1);
    }
    display.setCursor(0, 50);
    for (y=50; y<=57; y++)
      {
       for (x=0; x<127; x++)
       {
        display.drawPixel(x, y, BLACK); 
       }
      }
  display.println("Status: Idle");
  display.display(); 
  }
  else if (joy1y < 200){
    rgbLed(255,0,0);
    digitalWrite(J2dir, LOW);
    display.setCursor(0, 50);
    for (y=50; y<=57; y++)
      {
       for (x=0; x<127; x++)
       {
        display.drawPixel(x, y, BLACK); 
       }
      }
    display.println("Status: Moving");
    display.display(); 
    while (joy1y < 200){
      digitalWrite(J2step,HIGH); 
      delayMicroseconds(450);    // by changing this time delay between the steps we can change the rotation speed
      digitalWrite(J2step,LOW); 
      delayMicroseconds(450); 
      joy1y = analogRead(A1);
  }
  display.setCursor(0, 50);
  for (y=50; y<=57; y++)
      {
       for (x=0; x<127; x++)
       {
        display.drawPixel(x, y, BLACK); 
       }
      }
  display.println("Status: Idle");
  display.display(); 
}
  if (joy2x > 700){
    rgbLed(255,0,0);
    digitalWrite(J3dir, HIGH);
    display.setCursor(0, 50);
    for (y=50; y<=57; y++)
      {
       for (x=0; x<127; x++)
       {
        display.drawPixel(x, y, BLACK); 
       }
      }
    display.println("Status: Moving");
    display.display(); 
    while (joy2x > 700){
      digitalWrite(J3step,HIGH); 
      delayMicroseconds(100);    // by changing this time delay between the steps we can change the rotation speed
      digitalWrite(J3step,LOW); 
      delayMicroseconds(100); 
      joy2x = analogRead(A2);
    }
    display.setCursor(0, 50);
    for (y=50; y<=57; y++)
      {
       for (x=0; x<127; x++)
       {
        display.drawPixel(x, y, BLACK); 
       }
      }
  display.println("Status: Idle");
  display.display(); 
  }
  else if (joy2x < 200){
    rgbLed(255,0,0);
    digitalWrite(J3dir, LOW);
    display.setCursor(0, 50);
    for (y=50; y<=57; y++)
      {
       for (x=0; x<127; x++)
       {
        display.drawPixel(x, y, BLACK); 
       }
      }
    display.println("Status: Moving");
    display.display(); 
    while (joy2x < 200){
      digitalWrite(J3step,HIGH); 
      delayMicroseconds(100);     // by changing this time delay between the steps we can change the rotation speed
      digitalWrite(J3step,LOW); 
      delayMicroseconds(100); 
      joy2x = analogRead(A2);
  }
  display.setCursor(0, 50);
  for (y=50; y<=57; y++)
      {
       for (x=0; x<127; x++)
       {
        display.drawPixel(x, y, BLACK); 
       }
      }
  display.println("Status: Idle");
  display.display(); 
}
}

void rgbLed (int r, int g, int b){
  analogWrite(8, r);
  analogWrite(9, b);
  analogWrite(10, g);
}