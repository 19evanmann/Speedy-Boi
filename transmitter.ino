
/*   ~ Simple Arduino - xBee Transmitter sketch ~

  Read an analog value from potentiometer, then convert it to PWM and finally send it through serial port to xBee.
  The xBee serial module will send it to another xBee (resiver) and an Arduino will turn on (fade) an LED.
  The sending message starts with '<' and closes with '>' symbol. 
  
  Dev: Michalis Vasilakis // Date:2/3/2016 // Info: www.ardumotive.com // Licence: CC BY-NC-SA                    */
#include "SoftwareSerial.h"
//Constants: 
const int potPin = A0; //Pot at Arduino A0 pin 

//Variables:
int xvalue ; //Value from pot
int yvalue ;
SoftwareSerial Xbee(1, 0);
void setup() {
  //Start the serial communication
  Serial.begin(9600);
  Xbee.begin(9600); //Baud rate must be the same as is on xBee module
}

void loop() {
  //Read the analog value from pot and store it to "value" variable
  xvalue = analogRead(A0);
  yvalue = analogRead(A1);
  //Map the analog value to pwm value
  xvalue = map (xvalue, 0, 1023, -255, 255);
  yvalue = map (yvalue, 0, 1023, -255, 255);
  //Send the message:
  Serial.print("<");  //Starting symbol
  Serial.print(yvalue);//Value from 0 to 255
  Serial.println('>');
  
  Serial.print("<");  //Starting symbol
  Serial.print(xvalue);//Value from 0 to 255
  Serial.println('>');//Ending symbol

  delay(200);
}
