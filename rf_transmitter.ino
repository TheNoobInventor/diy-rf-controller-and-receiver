/*

  Reference the libraries I used herein

*/

// Include libraries
#include <SPI.h>
#include <RF24.h>
#include <printf.h>
#include <RF24_config.h>
#include <nRF24L01.h>
#include <Joystick.h>
#include <XYReplacerJoystick.h>
#include <AxisJoystick.h>
#include <DelegateJoystick.h>

// instantiate an object for the nRF24L01 transceiver
RF24 radio(7, 8); // Pin 7 for CE pin, pin 8 for CSN pin
const byte address[6] = "00001"; // Address, might change this later

#define VRX1_PIN A1
#define VRY1_PIN A0
#define VRX2_PIN A5
#define VRY2_PIN A6
#define SW_PIN 1 // need to handle this better
#define LOW_END 0
#define HIGH_END 1023 
#define DEVIATION 100

Joystick* joystickL;
Joystick* joystickR;
int data[4]; // rename variable later

//
void setup() {
  Serial.begin(115200);
  //radio.begin();
  if (!radio.begin()){
    Serial.println("Wetin?");
  }
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  //radio.setDataRate(RF24_250KBPS);
  radio.stopListening();

  joystickL = new AxisJoystick(SW_PIN, VRX1_PIN, VRY1_PIN); //
  joystickR = new AxisJoystick(SW_PIN, VRX2_PIN, VRY2_PIN);

  // this or below?
//  joystickL->calibrate(LOW_END, HIGH_END);
//  joystickR->calibrate(LOW_END, HIGH_END);

  joystickL->calibrate(LOW_END, HIGH_END, DEVIATION);
  joystickR->calibrate(LOW_END, HIGH_END, DEVIATION);
}

void loop() {

  /*
   * data[0] - left joystick x axis
   * data[1] - left joystick y axis
   * data[2] - right joystick x axis
   * data[3] - right joystick y axis
   */
   
  int data[4] = {joystickL->readVRx(), joystickL->readVRy(),
                  joystickR->readVRx(), joystickR->readVRy()};

  radio.write(&data, sizeof(data));

//  delay(500);

}


//Look up powering up and down the radio on receiver side as well
//  radio.powerDown();
//avr_enter_sleep_mode(); // Custom function to sleep the device
//radio.powerUp();

// Check docs for stuff about channels and anything we might need
// check examples too

// what should be the delay between packets??
// Sort out cabling for vx and vy later
// We might have to tune the range of values of the joystick. But that will come later
