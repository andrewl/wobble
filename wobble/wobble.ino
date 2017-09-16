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
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13

//#define OLED_MOSI   D7 //Connect to D1 on OLED
//#define OLED_CLK    D5 //Connect to D0 on OLED 
//#define OLED_DC     D1 //Connect to DC on OLED
//#define OLED_CS     D8 //Connect to CS on OLED
//#define OLED_RESET  D3 //Connect to RES on OLED

Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

int pos_x = random(0,128);
int pos_y = random(0,64);
int delay_time = 200;


void setup()   {      


  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC);
  // init done
  
}

void loop() {
  draw_ball(pos_x, pos_y);
  delay(delay_time);
  pos_x += 1;
  pos_y += 1;
  delay_time -= 1;

  if (pos_x > 128 || pos_y > 64) {
     pos_x = random(0,128);
     pos_y = random(0,64);
  }

  if (delay_time < 0) {
    delay_time = 200;
  }

   
  display.clearDisplay();
  
  
}

void draw_ball(int x, int y) {          


  // draw a white circle, 5 pixel radius
  display.fillCircle(x, y, 5, WHITE);
  display.display();
   

}




