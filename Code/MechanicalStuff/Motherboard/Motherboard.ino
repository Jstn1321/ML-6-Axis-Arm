#include <esp_now.h>
#include <WiFi.h>
#include <AccelStepper.h>
int speedX;
int speedY;
int manual = true;
int lastMessage;

/*

Input only pins

GPIOs 34 to 39 are GPIs – input only pins. These pins don’t have internal pull-up or pull-down resistors. They can’t be used as outputs, so use these pins only as inputs:

    GPIO 34
    GPIO 35
    GPIO 36
    GPIO 39

SPI flash integrated on the ESP-WROOM-32

GPIO 6 to GPIO 11 are exposed in some ESP32 development boards. However, these pins are connected to the integrated SPI flash on the ESP-WROOM-32 chip and are not recommended for other uses. So, don’t use these pins in your projects:

    GPIO 6 (SCK/CLK)
    GPIO 7 (SDO/SD0)
    GPIO 8 (SDI/SD1)
    GPIO 9 (SHD/SD2)
    GPIO 10 (SWP/SD3)
    GPIO 11 (CSC/CMD)

*/
//AccelStepper stepper6(1, 51, 52); // (Type of driver: with 2 pins, STEP, DIR)
//AccelStepper stepper5(1, 49, 50); // (Type of driver: with 2 pins, STEP, DIR)
//AccelStepper stepper4(1, 47, 48); // (Type of driver: with 2 pins, STEP, DIR)
//AccelStepper stepper3(1, 45, 46); // (Type of driver: with 2 pins, STEP, DIR)
AccelStepper stepper2(1, 0, 4); // (Type of driver: with 2 pins, STEP, DIR)
AccelStepper stepper1(1, 15, 2); // (Type of driver: with 2 pins, STEP, DIR)


typedef struct struct_message {
  int joy1x;
  int joy1y;
} struct_message;

struct_message myData;

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
}

void setup() {
  stepper1.setMaxSpeed(5000); // Set maximum speed value for the stepper
  stepper1.setAcceleration(1500); // Set acceleration value for the stepper
  stepper1.setCurrentPosition(0);
  stepper2.setMaxSpeed(45000);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  //Serial2.begin(2000000);
  
  // Initilize ESP-NOW
  
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
    esp_now_register_recv_cb(OnDataRecv);

}
//BASE ROT ONLY

void loop() {
  /* BASE ROT ALSO CHANGE THIS
  stepper1.moveTo(-60000);
  if (firstLoop == 1){
      while((stepper1.currentPosition() != -60000) && (touch == 1)){
        limitSwitch.loop();
        int state = limitSwitch.getState();
        if(state == HIGH){
          touch = 1;
          stepper1.run();
        } 
        else {
          touch = 0;
        }

      }
    delay(1000);
    stepper1.setCurrentPosition(0);
    stepper1.moveTo(15000);
    stepper1.runToPosition();
    stepper1.setCurrentPosition(0);
    firstLoop = 0;
 }*/
 /* SHOULDER MOTOR CHANGE THIS
  stepper2.moveTo(60000);
  if (firstLoop == 1){
      while((stepper2.currentPosition() != 60000) && (touch == 1)){
        limitSwitch.loop();
        int state = limitSwitch.getState();
        if(state == HIGH){
          touch = 1;
          stepper2.run();
        } 
        else {
          touch = 0;
        }
      }
    delay(1000);
    stepper2.setCurrentPosition(0);
    stepper2.moveTo(-15000);
    stepper2.runToPosition();
    stepper2.setCurrentPosition(0);
    firstLoop = 0;
 }
*/

  speedX = map(myData.joy1x, 0, 4095, -1000, 1000);
  speedY = map(myData.joy1y, 0, 4095, -1000, 1000);
  /*Serial.print(speedX);
  Serial.print(" , ");
  Serial.println(speedY);
*/
  manual = true;
  if (manual == true){
      if (speedX > 500){
        Serial.println("Spininng clockwise");
        stepper2.setSpeed(10000); // Forward
        stepper2.runSpeed();
      } 
      else if (speedX < -500) {
        Serial.println("Spininng counterclockwise");
        stepper2.setSpeed(-10000); // Reverse
        stepper2.runSpeed();
      }
      else if (speedX < 500 && speedX > -500){
        Serial.println("Doing Nothing");
      }
  }
}