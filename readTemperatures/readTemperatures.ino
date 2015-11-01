
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
  sensor.initialise (8);
 }
void loop(){
  sensor.measure(true); //get new readings from the sensor
  tft.setTextColor(ST7735_RED);
  tft.setRotation(1);
  tft.fillRect(0,0, 160, 16, ST7735_BLACK);
  tft.setCursor(10, 0);
  tft.print("Ta:");
  tft.print(sensor.getAmbient());
  tft.setCursor(60, 0);
  tft.print(sensor.getMinTemp());
  tft.print(" - ");
  tft.print(sensor.getMaxTemp());
  tft.setRotation(0);
  for(int y=0;y<4;y++){ //go through all the rows

    for(int x=0;x<16;x++){ //go through all the columns
      int16_t valueAtXY= sensor.irData[y+x*4]; // extract the temperature at position x/y
      tft.fillRect(28*y, 10*x, 28, 10, getScaleValue(sensor.getTemperature(y+x*4), sensor.getMinTemp(), sensor.getMaxTemp()));
      //tft.setCursor(32*y, 10*x);
      //tft.print(sensor.getTemperature(y+x*4));
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

float getScaleValue(float temp, float minTemp, float maxTemp){
  uint8_t scale = ((minTemp - maxTemp) / -32.0)*(temp) + (-1.0) * (minTemp - maxTemp)/(-32.0);
  uint16_t color = scale << 11 | scale << 6 | scale;
  return color;
}



