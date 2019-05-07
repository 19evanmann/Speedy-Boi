/*   ~ Simple Arduino - xBee Receiver sketch ~

  Read an PWM value from Arduino Transmitter to fade an LED
  The receiving message starts with '<' and closes with '>' symbol.
  
  Dev: Michalis Vasilakis // Date:2/3/2016 // Info: www.ardumotive.com // Licence: CC BY-NC-SA                    */
#include <SparkFun_TB6612.h>
#include "SoftwareSerial.h"

#define AIN1 2
#define BIN1 7
#define AIN2 4
#define BIN2 8
#define PWMA 5
#define PWMB 6
#define STBY 9

const int offsetA = 1;
const int offsetB = 1;

SoftwareSerial Xbee(7, 0);

Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);
//Constants
const int m1p = 3; //Led to Arduino pin 3 (PWM)
const int m2p = 4;
 int m1s = 0;
 int m2s = 0;
//Variables
bool started= false;//True: Message is strated
bool ended  = false;//True: Message is finished 
char incomingByte ; //Variable to store the incoming byte
char msg[3];    //Message - array from 0 to 2 (3 values - PWM - e.g. 240)
byte index;     //Index of array
int xvalue;
int yvalue;
void setup() {
  //Start the serial communication
  Serial.begin(9600);
  Xbee.begin(9600); //Baud rate must be the same as is on xBee module
  pinMode(m1p, OUTPUT);
  pinMode(m2p, OUTPUT);
}

void loop() {
  
  while (Xbee.available()>0){
    //Read the incoming byte
    incomingByte = Xbee.read();
    //Start the message when the '<' symbol is received
    if(incomingByte == '<')
    {
     started = true;
     index = 0;
     msg[index] = '\0'; // Throw away any incomplete packet
   }
   //End the message when the '>' symbol is received
   else if(incomingByte == '>')
   {
     ended = true;
     break; // Done reading - exit from while loop!
   }
   //Read the message!
   else
   {
     if(index < 4) // Make sure there is room
     {
       msg[index] = incomingByte; // Add char to array
       index++;
       msg[index] = '\0'; // Add NULL to end
     }
   }
 }
 
 if(started && ended)
 {
   int value = atoi(msg);
   analogWrite(m1p, value);
   analogWrite(m2p, value);

   if (xvalue >= 0){
    m2s = yvalue - xvalue;
    m1s = yvalue;
   }
   if(xvalue <= 0){
    m1s = yvalue - abs(xvalue);
    m2s = yvalue;
   }
   if(xvalue ==0){
    m1s = yvalue;
    m2s = yvalue;
   }
   motor1.drive(atoi(m1s), 1000);
   motor2.drive(atoi(m2s), 1000);
   
   //Serial.println(value); //Only for debugging
   index = 0;
   msg[index] = '\0';
   started = false;
   ended = false;
 }
}
