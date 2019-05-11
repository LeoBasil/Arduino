/*
   Project:     Clock
   Hardware:    Arduino Nano - 8 Dig x 7 Seg LED Display - RTC DHT22
   Revision:    1.0
   Date:        2019-05-10
   Author:      LeoBasil
   License:     CC BY-NC-ND 4.0
                (Attribution-NonCommercial-NoDerivatives 4.0 International)
*/

#include <LedControl.h>       // Library for LED control with MAX72XX
#include <Wire.h>  //SDA = A4; SCL = A5
#include "DS3231.h"

// LedControl(int dataPin, int clkPin, int csPin, int numDevices)
LedControl lc = LedControl(11, 13, 10, 1);
RTClib RTC;


void setup() {
  //Serial.begin(9600);
  Wire.begin();

  lc.shutdown(0, false);      // The MAX72XX is in power-saving mode on startup, we have to do a wakeup call
  lc.setIntensity(0, 5);      // Set the brightness of display between 0 and 15

}


void loop() {
    DateTime now =RTC.now();
    

    //Serial.println(now.hour());
    //Serial.println(now.minute());
    
      //print month
      lc.setDigit(0,7,floor(now.month()/10),false);
      lc.setDigit(0,6,now.month()%10,true);

      //print day
      lc.setDigit(0,5,floor(now.day()/10),false);
      lc.setDigit(0,4,now.day()%10,true);

      //print hour;
      lc.setDigit(0,3,floor(now.hour()/10),false);
      lc.setDigit(0,2,now.hour()%10,true);

      //print minute;
      lc.setDigit(0,1,floor(now.minute()/10),false);
      lc.setDigit(0,0,now.minute()%10,is_even(now.second()));

      delay(1000);

}



boolean is_even(int value){
  return (value%2 == 0);
}
