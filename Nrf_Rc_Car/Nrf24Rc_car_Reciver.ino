
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

#define enA 6  
#define in1 7
#define in2 5
#define enB 3   
#define in3 4
#define in4 2

Servo myservo; 

RF24 radio(9,8); // CE, CSN
const byte address[6] = "00001";
char receivedData[32] = "";
int  xAxis, yAxis, Camservo;
int motorSpeedA = 0;
int motorSpeedB = 0;
int joystick[3]; 

void setup()
{
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  myservo.attach(10);
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
  
  digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
     
}
void loop() 
{

  if (radio.available()) 
  {   // If the NRF240L01 module received data
     
      radio.read( joystick, sizeof(joystick) );

    radio.read(&receivedData, sizeof(receivedData));
    yAxis = joystick[0];
    xAxis = joystick[1];
    Camservo = joystick[2];   
    
    int val  = map(Camservo, 0, 1023, 0, 255);
    myservo.write(val); 
    Serial.print(yAxis);
    Serial.print(" ");
    Serial.print(xAxis);
    Serial.print(" ");
    Serial.println(Camservo);
  }
  
  if (yAxis > 550 )   // Forward
  {

    digitalWrite(in1, 1);
    digitalWrite(in2, 0);

    digitalWrite(in3, 1);
    digitalWrite(in4, 0);
  }
  else if (yAxis < 470) // Reverse
  {

    digitalWrite(in1, 0);
    digitalWrite(in2, 1);

    digitalWrite(in3, 0);
    digitalWrite(in4, 1);
    

  }


  else if (xAxis < 470) // Left
  {
    
    digitalWrite(in1, 1);
    digitalWrite(in2, 0);

    digitalWrite(in3, 0);
    digitalWrite(in4, 1);

    }
  
  else if (xAxis > 550) // Right
  {
    
    digitalWrite(in1, 0);
    digitalWrite(in2, 1);

    digitalWrite(in3, 1);
    digitalWrite(in4, 0);

    }
 
    else    // Stop
  { 
    digitalWrite(in1, 0);
    digitalWrite(in2, 0);

    digitalWrite(in3, 0);
    digitalWrite(in4, 0);
   
  }


}
