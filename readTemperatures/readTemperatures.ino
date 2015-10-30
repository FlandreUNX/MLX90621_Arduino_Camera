
/*
* This project creates a small thermal camera using the MELEXIS MLX90621
*
* Adapted by Josh Long (https://github.com/longjos) Oct 2015
* Based on a https://github.com/robinvanemden/MLX90621_Arduino_Processing
*
* Original work by:
* 2013 by Felix Bonowski
* Based on a forum post by maxbot: http://forum.arduino.cc/index.php/topic,126244.msg949212.html#msg949212
* This code is in the public domain.
*/
#include <SPI.h>
#include <Arduino.h>
#include <Wire.h>
#include "MLX90621.h"
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

#define TFT_CS 10
#define TFT_RST 0
#define TFT_DC 8

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

#define TFT_SCLK 13
#define TFT_MOSI 11

MLX90621 sensor; // create an instance of the Sensor class

void setup(){
  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST7735_BLACK);
  sensor.initialise (4);
 }
void loop(){
  sensor.measure(true); //get new readings from the sensor
  tft.setTextColor(ST7735_RED);
  for(int y=0;y<4;y++){ //go through all the rows

    for(int x=0;x<16;x++){ //go through all the columns
      int16_t valueAtXY= sensor.irData[y+x*4]; // extract the temperature at position x/y
      tft.fillRect(32*y, 10*x, 32, 10, (uint16_t) valueAtXY);
      tft.setCursor(32*y, 10*x);
      tft.print(sensor.getTemperature(y+x*4));
      //tft.print(sensor.irData[y+x*4]);
    }
  }
  //tft.setCursor(10, 10);
  //tft.print(sensor.getAmbient());
  //tft.print(sensor.ptat);
  //tft.print(sensor.cpix);
  //tft.setCursor(10, 20);
  //tft.print(sensor.a_common);
  //delay(31);
};



