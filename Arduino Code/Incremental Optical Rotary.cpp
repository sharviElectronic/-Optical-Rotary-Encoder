
#include <Arduino.h>

int encoder_Pin_1 = 2;
int encoder_Pin_2 = 3;

volatile int lastEncoded = 0;
volatile long encoderValue = 0;

long lastencoderValue = 0;

int lastMSB = 0;
int lastLSB = 0;

void setup()
{
  Serial.begin (9600);

  pinMode(encoder_Pin_1, INPUT); 
  pinMode(encoder_Pin_2, INPUT);

  digitalWrite(encoder_Pin_1, HIGH); //turn pullup resistor on
  digitalWrite(encoder_Pin_2, HIGH); //turn pullup resistor on

  //call updateEncoder() when any high/low changed seen
  //on interrupt 0 (pin 2), or interrupt 1 (pin 3) 
  attachInterrupt(0, updateEncoder, CHANGE); 
  attachInterrupt(1, updateEncoder, CHANGE);

}

void loop()
{ 
 
  Serial.println(encoderValue);
  delay(1000); //just here to slow down the output, and show it will work  even during a delay
}


void updateEncoder()
{
  int MSB = digitalRead(encoder_Pin_1); //MSB = most significant bit
  int LSB = digitalRead(encoder_Pin_2); //LSB = least significant bit

  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;

  lastEncoded = encoded; //store this value for next time
}
