/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x64 size display using SPI to communicate
4 or 5 pins are required to interface

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


// If using software SPI (the default case):
//#define OLED_MOSI   9
//#define OLED_CLK   10
//#define OLED_DC    11
//#define OLED_CS    12
//#define OLED_RESET 13

#define OLED_MOSI   D7 //Connect to D1 on OLED
#define OLED_CLK    D5 //Connect to D0 on OLED 
#define OLED_DC     D1 //Connect to DC on OLED
#define OLED_CS     D8 //Connect to CS on OLED
#define OLED_RESET  D3 //Connect to RES on OLED

const int BALL_RADIUS = 5;

Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

int pos_x = random(1+BALL_RADIUS,128-BALL_RADIUS);
int pos_y = random(1+BALL_RADIUS,64-BALL_RADIUS);
int delay_time = 200;
int vector[2] = {1, 1};


void setup()   {      


  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC);
  // init done
  vector[0] = random(-1,2);
  vector[1] = random(-1,2);
}

void loop() {
  draw_ball(pos_x, pos_y);
  delay(delay_time);
  pos_x += vector[0];
  pos_y += vector[1];
  delay_time -= 1;

  if (pos_x > 128-BALL_RADIUS || pos_x < 0+BALL_RADIUS) {
     vector[0] = -vector[0];
  }
  if (pos_y > 64-BALL_RADIUS || pos_y < 0+BALL_RADIUS) {
     vector[1] = -vector[1];
  }

  if (delay_time < 0) {
    delay_time = 0;
  }

   
  display.clearDisplay();
  
  
}

void draw_ball(int x, int y) {          


  // draw a white circle, 5 pixel radius
  display.fillCircle(x, y, BALL_RADIUS, WHITE);
  display.display();
   

}




