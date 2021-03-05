
/*
 *
 *
 */

// Include libraries
#include <SPI.h>
#include <RF24.h>
#include <printf.h>
#include <RF24_config.h>
#include <nRF24L01.h>
#include <Servo.h>

// Initialize radio object
RF24 radio(49, 48); // pin for CE pin, pin  for CSN pin.

// Initialize servo object
Servo myservo;

// #define servoPin 13 // which one instead?
const int servoPin = 13; // servo pin
const byte address[6] = "00001";
int val_x, val_y;

void setup() {
  Serial.begin(115200);
  //while(!Serial){
  // 
  //}
  //
  //radio.begin();
  if (!radio.begin()){
    Serial.println("Wetin?");
  }

  radio.openReadingPipe(0, address); //
  radio.setPALevel(RF24_PA_LOW); //
  //radio.setDataRate(RF24_250KBPS);
  radio.startListening();
  myservo.attach(servoPin); // Attach the Servo variable to a pin
  myservo.write(90); // need to find the center

}

void loop() {
  /*
   * data[0] - left joystick x axis
   * data[1] - left joystick y axis
   * data[2] - right joystick x axis
   * data[3] - right joystick y axis
   */
  int data[4];
  if (radio.available()) {
    radio.read(&data, sizeof(data));
    Serial.print("Left horizontal: ");
    Serial.print(data[0]);
    Serial.print(" Left vertical: ");
    Serial.print(data[1]);
    Serial.print(" | Right horizontal: ");
    Serial.print(data[2]);
    Serial.print(" Right vertical: ");
    Serial.println(data[3]);

    // Servo control
    if (data[1] > 525){
      val_x = map(data[1], 530, 1023, 90, 180);
      myservo.write(val_x);   
    }

    else if (data[1] < 505){
      val_x = map(data[1], 500, 0, 90, 0);
      myservo.write(val_x); 
    }

    else {
      myservo.write(90);
    }
    
//    delay(300);

  }

}

// Need to show how to calibrate the servos
// check the sketch I wrote for calibration and the bookmarked page
// maybe we'll connect all the servos together and see run the
// the sketch
// seems like the servo calibrates itself ie returning to a
// starting position before the loop is started

// Understand the different lines and sections of the code, comment accordingly

// Play around with delay?
