/*OLED Temprature, Humid and time
Created 19/09/2013
Jed Hodson 
*/
#include <SPI.h>
#include <SD.h>
#include <FTOLED.h>
#include <fonts/SystemFont5x7.h>
#include <fonts/Arial14.h>
#include <fonts/Arial_Black_16.h>
#include <fonts/Droid_Sans_36.h>
#include "DHT.h"
#include <Wire.h>
#include "RTClib.h"
#define DHTPIN 3
#define DHTTYPE DHT22 
DHT dht(DHTPIN, DHTTYPE);

RTC_DS1307 RTC;
const byte pin_cs = 7;
const byte pin_dc = 2;
const byte pin_reset = 3;

OLED oled(pin_cs, pin_dc, pin_reset);

const char *WELCOME = "Temprature,\nHumidity \nand Time\nOn OLED \nDisplay\nJed Hodson \n2013";
const char *ERRORHAP = "An ERROR has\noccured,\nplease try\nagain later!";
void setup() {
  //Start everything up
  oled.begin();
  dht.begin();
  Wire.begin();
  RTC.begin();
  //Display start up message
  oled.selectFont(Arial14);
  oled.drawString(10,101,WELCOME,GREEN,BLACK);
  //Check everythings connected
  //No RTC!
  if (! RTC.isrunning()) {
    oled.selectFont(Arial14);
    //DISPLAY ERROR MESSAGE
    oled.drawString(10,101,ERRORHAP,RED,BLACK);
  }
  // following line sets the RTC to the date & time this sketch was compiled
  RTC.adjust(DateTime(__DATE__, __TIME__));
  //And DHT22
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(t) || isnan(h)) {
    oled.drawString(10,101,ERRORHAP,RED,BLACK);
  }
}



void loop() {
  oled.begin();
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(t) || isnan(h)) {
    oled.drawString(10,101,ERRORHAP,RED,BLACK);
  } 
  else {
    DateTime now = RTC.now();
    //Time to make some Strings
    String dateString = "";
    dateString += String(now.day());
    dateString += "/";
    dateString += String(now.month());
    dateString += "/";
    dateString += String(now.year());
    int temp = t;
    String tempString = "";
    tempString += String(temp);
    tempString += "*C";
    int humid = h;
    String humidString = "";
    humidString += String(humid);
    humidString += "%RH";
    String timeString = "";
    timeString += String(now.hour());
    timeString += ":";
    timeString += String(now.minute());
    


    oled.selectFont(Arial_Black_16);
    oled.drawString(63,15,humidString,ROYALBLUE,BLACK);

    oled.selectFont(Arial_Black_16);
    oled.drawString(15,15,tempString,RED,BLACK);

    oled.selectFont(SystemFont5x7);
    oled.drawString(25,105,dateString,WHITE,BLACK);

    oled.selectFont(Droid_Sans_36);
    oled.drawString(10,45,timeString,GREEN,BLACK);


  } 
}










