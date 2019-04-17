
#include "SoftwareSerial.h"

SoftwareSerial XBee(2, 3);
void setup() {
  
  XBee.begin(9600);
  // put your setup code here, to run once:
pinMode(A0, INPUT);
pinMode(7, OUTPUT);
pinMode(A1, INPUT);
pinMode(A2, INPUT);
}

void loop() {
  if (analogRead(A0) == HIGH){
    digitalWrite(7, HIGH);
  }
  Serial.write("X=");
  Serial.println(analogRead(A0));
  Serial.write("Y=");
  Serial.println(analogRead(A1));
  delay(500);

}
