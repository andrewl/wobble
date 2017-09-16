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

const int xInput = A0;
const int yInput = A1;
const int zInput = A2;


// If using software SPI (the default case):
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13

/**
  #define OLED_MOSI   D7 //Connect to D1 on OLED
  #define OLED_CLK    D5 //Connect to D0 on OLED
  #define OLED_DC     D1 //Connect to DC on OLED
  #define OLED_CS     D8 //Connect to CS on OLED
  #define OLED_RESET  D3 //Connect to RES on OLED
*/

const int BALL_RADIUS = 5;

Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

float pos_x = random(1 + BALL_RADIUS, 128 - BALL_RADIUS);
float pos_y = random(1 + BALL_RADIUS, 64 - BALL_RADIUS);
int delay_time = 1;
float vector[2] = {0, 0};
int sampleSize = 10;


void setup()   {
  Serial.begin(9600);
  analogReference(EXTERNAL);


  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC);
  // init done
  vector[0] = random(-1, 2);
  vector[1] = random(-1, 2);
}

void loop() {

  int xRaw = map(ReadAxis(xInput),  415, 620, 0, 1023);
  int yRaw = map(ReadAxis(yInput), 475, 550, 0, 1023);

  char message[60];

  sprintf(message, "%d %d", xRaw, yRaw);
  Serial.println(message);

  if (xRaw < 512) {
    vector[0] = 0.0 - (float)(512 - xRaw) / 512.0f;
  }
  else {
    vector[0] = (float)(xRaw - 512) / 512.0f;
  }

  if (yRaw < 512) {
    vector[1] =  (float)(512 - yRaw) / 512.0f;
  }
  else {
    vector[1] = 0.0 - (float)(yRaw - 512) / 512.0f;
  }


  //sprintf(message, "%d %d", vector[0], (int) vector[1] * 10);
  Serial.println(vector[1]);
  //Serial.println(message);


  if ( (pos_x > 128 - BALL_RADIUS && vector[0] > 0) ||
       (pos_x < 0 + BALL_RADIUS && vector[0] < 0) ||
       (pos_y > 64 - BALL_RADIUS && vector[1] > 0) ||
       (pos_y < 0 + BALL_RADIUS && vector[1] < 0)) {
    //do nothing
  }
  else {
    pos_x += vector[0];
    pos_y += vector[1];
  }

  draw_ball(pos_x, pos_y);

  delay(delay_time);


  display.clearDisplay();

}

void draw_ball(float x, float y) {

  // draw a white circle, 5 pixel radius
  display.fillCircle((int) x, (int) y, BALL_RADIUS, WHITE);
  display.display();


}


//
// Read "sampleSize" samples and report the average
//
int ReadAxis(int axisPin)
{
  long reading = 0;
  analogRead(axisPin);
  delay(1);
  for (int i = 0; i < sampleSize; i++)
  {
    reading += analogRead(axisPin);
  }
  return reading / sampleSize;
}

