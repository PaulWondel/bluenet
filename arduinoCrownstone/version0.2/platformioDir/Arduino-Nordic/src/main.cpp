#include <Arduino.h>

// Test version for changeing start address fro 0x00000000 to 0x00026000
// Test Write field:

#define ledPin (7) //PIN_A0
#define irPin PIN_A1
#define temPin PIN_AREF

int pwmPin = (2); // assigns pin 12 to variable pwm
int pot = A0; // assigns analog input A0 to variable pot
int c1 = 0;   // declares variable c1
int c2 = 0;   // declares variable c2


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(irPin, INPUT);
  pinMode(temPin, INPUT);
  pinMode(pwmPin, OUTPUT); 
  pinMode(pot, INPUT); 
}

void light(){
  int value = analogRead(pot);
  //Serial.println(value);
  c1= value; 
  c2= 500-c1;         // subtracts c2 from 1000 ans saves the result in c1
  
  if (value < 500)
  {
  digitalWrite(pwmPin, HIGH); 
  delayMicroseconds(c2);   
  digitalWrite(pwmPin, LOW);  
  delayMicroseconds(c1);   
  }
  if (value > 500)
  {
    digitalWrite(2,LOW);
  } 
}

void read(int reading){
  float voltage = reading * 5.0;
  voltage /= 1024.0; 
 
  // print out the voltage
  Serial.print(voltage); Serial.println(" volts");
 
  // now print out the temperature
  float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                               //to degrees ((voltage - 500mV) times 100)
  Serial.print(temperatureC); Serial.println(" degrees C");
 
  // now convert to Fahrenheit
  float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
  Serial.print(temperatureF); Serial.println(" degrees F");
}


void irSensing() {
  // Serial.println(analogRead(temPin));
  read(analogRead(temPin));
  light();
  // put your main code here, to run repeatedly:
  if(analogRead(irPin) < 600){
    digitalWrite(ledPin, HIGH); // set the LED on
    //Serial.println("Led On");
    }
  else {
    digitalWrite(ledPin, LOW); // set the LED off
    //Serial.println("Led Off");
    }
}


void loop(){
  light();
  irSensing();
}
