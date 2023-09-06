
 
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9,8); // CE, CSN
const byte address[6] = "00001";
char xyData[32] = "";
int joystick[3];
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
}
void loop() {
 
  joystick[0] = analogRead(A4);
  joystick[1] = analogRead(A3);
  joystick[2] = analogRead(A1);
  radio.write( joystick, sizeof(joystick) );
}
