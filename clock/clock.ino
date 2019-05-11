/*
   Project:     Clock
   Hardware:    Arduino Nano - 8 Dig x 7 Seg LED Display - RTC DHT22
   Revision:    1.0
   Date:    2019-05-10
   Author:  LeoBasil
   License:     CC BY-NC-ND 4.0
        (Attribution-NonCommercial-NoDerivatives 4.0 International)
*/

#include <LedControl.h>   // Library for LED control with MAX72XX
#include <Wire.h>  //SDA = A4; SCL = A5
#include "DS3231.h" // Real Time Clock (RTC) library

// LedControl(int dataPin, int clkPin, int csPin, int numDevices)
LedControl lc = LedControl(11, 13, 10, 1);
RTClib RTC;
DateTime now;
DS3231 Clock;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  lc.shutdown(0, false);  // The MAX72XX is in power-saving mode on startup, we have to do a wakeup call
  lc.setIntensity(0, 5);  // Set the brightness of display between 0 and 15

}


void loop() {
  
  now = RTC.now();
  if (now.second()%6<3){
    display_time();
  }
  else{
    display_temperature();
  }
  
  

  delay(1000);

}

void display_temperature(){
  lc.clearDisplay(0);
  display_number(Clock.getTemperature(), 0, 2, true);
  display_number(int((Clock.getTemperature()*10))%10, 0, 1, false);
  //lc.setChar(0,0,'c', false);
  lc.setRow(0,0,B1100011);
}

void display_time(){
  lc.clearDisplay(0);
  display_number(now.month(), 0, 4, true);
  display_number(now.day(), 0, 6, true);
  display_number(now.hour(), 0, 2, true);
  display_number(now.minute(), 0 , 0, is_even(now.second()));
}

void display_number(int number_to_display, int device, int start_position, boolean dp){
  
  //Serial.print((int)floor(log10(number_to_display)));
  int number_of_digits = (int)floor(log10(number_to_display))+1;

  for (int i =0; i<number_of_digits; i++){
    if (i==0){
      lc.setDigit(device, start_position + i, get_digit(number_to_display, i) , dp); //for the first digit, use dp parameter for decimal point display
    }
    else{
      lc.setDigit(device, start_position + i, get_digit(number_to_display, i) , false); //for other digits, dont show DP
    }
  }
}

int get_digit(int number, int digit){
  return (int)floor((int)(floor(number/(pow(10,digit)))) % 10);
}

boolean is_even(int value){
  return (value%2 == 0);
}
