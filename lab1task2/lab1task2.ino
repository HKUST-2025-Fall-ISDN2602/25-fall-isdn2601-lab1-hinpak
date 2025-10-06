#include "Arduino.h"

#define Vin 12 //*** Define the GPIO pin 12 as Vin ***
#define Vout 27  //*** Define the GPIO pin 27 as Vout ***
#define Cal 14 //*** Define the GPIO pin 14 as the node for current calcultion ***

float R = 0.022; // *** Resistance in Mohm ***

float x;
float y;
float c1;
float c2;

void setup() {

  Serial.begin(115200); //*** Define the data rate as 115200 ***
  pinMode(Vin, OUTPUT); //*** Set Vin as OUTPUT ***
  pinMode(Vout, INPUT); //*** Set Vout as INPUT ***
  pinMode(Cal, INPUT); //*** Set Cal as INPUT ***
  
  delay(100);   //*** Set 100 ms delay ***
  //This task only needs to be done once, thus it is placed in setup().
  Serial.println("V_out(mV),I(uA)"); // display duty cycle,Vout for TASK 1 or I,Vout for Task 2 3 4
  
  for (int onPeriod = 0; onPeriod < 256; onPeriod++) 
    {
    analogWrite(Vin,onPeriod);// Output PWM at Vin      
    int Vout_value = analogRead(Vout); // read the voltage level at Vout 
    int c_value = analogRead(Cal); // read the voltage level at the node for current calcultion  
    c1 = float(Vout_value*3.3)/4095 ; // convert 12 bit binary number of Voltage level at Vout back to 0-3.3 V 
    c2 = float(c_value*3.3)/4095 ; // convert 12 bit binary number of Voltage level at D14 back to 0-3.3 V 
    x = c1*1000; // calculate the voltage at Vout in mV
    y = (c2-c1)/R; // calculate current in uA for Task 2 3 4 
    Serial.print(x,6); // print the voltage at Vout in mV
    Serial.print(","); 
    Serial.println(y,6);// print the current in uA (through DUT)
  }

  // Press reset button for a new sweep
}

void loop() {
  // Code for continuous operation can be added here
 
}