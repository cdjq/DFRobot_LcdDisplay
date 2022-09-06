/**！
 * @file grapics.ino
 * @brief 显示基本图形
 * @details 可以显示的基本图形有,点,线,圆,矩形,三角形等
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2022-07-20
 * @url https://github.com/DFRobot/DFRobot_LcdDisplay
 */
/*
 * User-selectable macro definition color
 * BLACK_RGB565 BLUE_RGB565 RED_RGB565 GREEN_RGB565 CYAN_RGB565 MAGENTA_RGB565
 * YELLOW_RGB565 WHITE_RGB565 NAVY_RGB565 DARKGREEN_RGB565 DARKCYAN_RGB565 MAROON_RGB565
 * PURPLE_RGB565 OLIVE_RGB565 LIGHTGREY_RGB565 DARKGREY_RGB565 ORANGE_RGB565
 * GREENYELLOW_RGB565 DCYAN_RGB565
 */

#include "DFRobot_LcdDisplay.h"
DFRobot_Lcd_UART lcd;
#if ((defined ARDUINO_AVR_UNO) || (defined ARDUINO_AVR_NANO))
    #include <SoftwareSerial.h>
    SoftwareSerial Serial1(2, 3);  //RX, TX
    #define FPSerial Serial1
    
#else
    #define FPSerial Serial1
#endif
void setup(void){

  //Rx and tx should be mapping into D2 and D3 when using Firebeetle-ESP32
  #if (defined ESP32)
     Serial1.begin(9600, SERIAL_8N1, /*rx =*/D2, /*tx =*/D3);
  #else
  Serial1.begin(9600);
  #endif
  Serial.begin(115200);
  
  lcd.begin(Serial1);

//  lcd.drawPixel(/*x=*/20,/*y=*/20,/*color=*/0xf8);
//
//  
//  lcd.fillRect(/*x=*/22,/*y=*/22,/*width=*/20,/*height*/20,/*color=*/0x660);
//   
  //lcd.drawLine(/*x=*/2,/*y=*/22,/*width=*/80,/*height*/80,/*color=*/0x660);
//  lcd.drawRect(/*x=*/22,/*y=*/22,/*width=*/20,/*height*/20,/*color=*/0x660);
//  lcd.fillRect(/*x=*/22,/*y=*/22,/*width=*/20,/*height*/20,/*color=*/0x660);
//  lcd.drawRoundRect(/*x=*/60,/*y=*/60,/*width=*/20,/*height*/20,/*圆角半径*/4,/*color=*/0x660);
//  lcd.fillRoundRect(/*x=*/22,/*y=*/22,/*width=*/20,/*height*/20,/*圆角半径*/6,/*color=*/0x660);
//  lcd.drawCircle(/*x=*/60,/*y=*/60,/*radius=*/20,/*color=*/0x660);
//  lcd.fillCircle(/*x=*/60,/*y=*/60,/*radius=*/20,/*color=*/0x660);
//  lcd.drawTriangle(/*x0=*/10,/*y0=*/10,/*x1=*/10,/*y1=*/60,/*x2=*/60,/*y2=*/40,/*color=*/0x660);
//  lcd.fillTriangle(/*x0=*/60,/*y0=*/60,/*x1=*/10,/*y1=*/60,/*x2=*/60,/*y2=*/40,/*color=*/0x660);

}

void loop(void){

    testDrawPixel();
    testLine();
    testFastLines(PURPLE_RGB565,YELLOW_RGB565);       
    testRects(BLACK_RGB565,WHITE_RGB565);
    testRoundRects();
    testCircles(24,BLUE_RGB565);
    testTriangles(YELLOW_RGB565);
}




/* Test to draw a pixel*/
void testDrawPixel() {
  //Clear screen
  lcd.fillScreen(BLACK_RGB565);
  int x = 0;
  int y = 128;
  for(int i = 0; i <= 160/2; i += 10){
    for (x = 160 - i; x >= i; x-=10 ){
      /*
       * @ brief draw a pixel
       * @ param x coordinate
       *         y coordinate
       * c pixel color
       */
      lcd.drawPixel(x, y, ORANGE_RGB565);
      delay(10);
    }
  
    for (y = 128 - i; y >= i; y-=10){
      lcd.drawPixel(x, y, ORANGE_RGB565);
      delay(10);
    }
  
    for (x = i; x <= 160 - i + 1; x+=10 ){
      lcd.drawPixel(x, y, ORANGE_RGB565);
      delay(10);
    }
  
    for (y = i; y <= 128 - i + 1; y+=10){
      lcd.drawPixel(x, y, ORANGE_RGB565);
      delay(10);
    }
  }
}

/* Test to draw a line*/
void testLine(){
// 0x00FF is the color data in the format of RGB565
  uint16_t color = 0x00FF;
  lcd.fillScreen(BLACK_RGB565);
  for (int16_t x=0; x < 160; x+=6) {
    /*
     * @ brief draw a line
     * @ param x0 The x-coordinate of the first vertex
     *         y0 The y-coordinate of the first vertex
     *         x1 The x-coordinate of the second vertex
     *         y1 The y-coordinate of the second vertex
     *         c line color
     */
    lcd.drawLine(/*x0=*/160/*Screen width*//2, /*y0=*/128/*Screen height*//2, /*x1=*/x, /*y1=*/0, /*c=*/color+=0x0700);
  }
  for (int16_t y=0; y < 128; y+=6) {
    lcd.drawLine(160/2, 128/2, 160, y, color+=0x0700);
  }
 
  for (int16_t x = 160; x >= 0; x-=6) {
    lcd.drawLine(160/2, 128/2, x,128, color+=0x0700);
  }
  
  for (int16_t y = 128; y >= 0; y-=6) {
    lcd.drawLine(160/2, 128/2, 0, y, color+=0x0700);
  }
}

/* Test to fast draw line(need to set delay), only horizontal line and vertical line */
void testFastLines(uint16_t color1, uint16_t color2) {
  for (int16_t y=0; y < 128; y+=4) {

    lcd.drawLine(/*x=*/0, /*y=*/y, /*w=*/160,y,/*c=*/color2);
    delay(30);
  }
  
  for(int16_t x=0; x < 160; x+=3) {

    lcd.drawLine(/*x=*/x, /*y=*/0, /*h=*/x,128, /*c=*/color1);
    delay(30);
  }
}

/* Test to draw a rectangle*/
void testRects(uint16_t color1, uint16_t color2) { 
    lcd.fillScreen(BLACK_RGB565);
    int16_t x=160-12;
    for (; x > 100; x-=160/40) {
      /*
       * @ brief draw a hollow rectangle
       * @ param x The x-coordinate of the vertex 
       * @ param y The y-coordinate of the vertex
       * @ param w horizontal side length
       * @ param h longitudinal side length
       * @ param color Fill color, RGB color with 565 structure
       */
      lcd.drawRect(/*x=*/160/2 -x/2, /*y=*/128/2 -x/2 , /*w=*/x, /*h=*/x, /*color=*/color2+=0x0F00);
      delay(100);
    }
  
    /*
     * @ brief draw a filled rectangle
     * @ param x The x-coordinate of the vertex
     * @ param y The y-coordinate of the vertex
     * @ param w horizontal side length
     * @ param h longitudinal side length
     * @ param color Fill color, RGB color with 565 structure
     */
    lcd.fillRect(/*x=*/160/2 -x/2, /*y=*/128/2 -x/2 , /*w=*/x, /*h=*/x, /*color=*/color2);
    delay(100);
    for(; x > 6; x-=160/40){
      lcd.drawRect(160/2 -x/2, 128/2 -x/2 , x, x, color1);
      delay(100);
    }
}

/* Test to draw a rounded rectangle */
void testRoundRects() {
  lcd.fillScreen(BLACK_RGB565);
// 0xF00F is the color data in the format of RGB565
  int color = 0xF00F;
  int i;
  int x = 0;
  int y = 0;
  int w = 160-3;
  int h = 128-3;
  for(i = 0 ; i <= 16; i+=2) {
    /*
     * @ brief Draw a hollow rounded rectangle
     * @ param x0 The x-coordinate of the start vertex 
     * @ param y0 The y-coordinate of the start vertex 
     * @ param w horizontal side length
     * @ param h longitudinal side length
     * @ param radius Round corner radius
     * @ param color border color, 565 structure RGB color
     */
    lcd.drawRoundRect(/*x0=*/x, /*y0=*/y, /*w=*/w, /*h=*/h, /*radius=*/20, /*color=*/color);
    x+=5;
    y+=5;
    w-=10;
    h-=10;
    color+=0x0100;
    delay(50);
  }
  for(i = 0 ; i <= 16; i+=2) {
    /*
     * @ brief Draw a filled and rounded rectangle
     * @ param x0 The x-coordinate of the start vertex
     * @ param y0 The y-coordinate of the start vertex
     * @ param w horizontal side length
     * @ param h longitudinal side length
     * @ param radius Round corner radius
     * @ param color Fill color, RGB color with 565 structure
     */
    lcd.fillRoundRect(/*x0=*/x, /*y0=*/y, /*w=*/w, /*h=*/h, /*radius=*/10, /*color=*/color);
    x+=5;
    y+=5;
    w-=10;
    h-=10;
    color+=0x0500;
    delay(50);
  }
}

/* Test to draw a circle */
void testCircles(uint8_t radius, uint16_t color) {
  lcd.fillScreen(BLACK_RGB565);
  for (int16_t x=radius; x <=160-radius; x+=radius*2) {
    for (int16_t y=radius; y <=128-radius; y+=radius*2) {
      /*
       * @ brief Draw a hollow circle
       * @ param x0 The x-coordinate of the center point
       * @ param y0 The y-coordinate of the center point
       * @ param r radius
       * @ param color Circle color, RGB color with 565 structure
       */
      lcd.drawCircle(/*x0=*/x, /*y0=*/y, /*r=*/radius, /*color=*/color);
        if(x == y ||x == -y ||x == y + 2*radius)
          /*
           * @ brief Draw a filled circle
           * @ param x0 The x-coordinate of the center point
           * @ param y0 The y-coordinate of the center point
           * @ param r radius
           * @ param color Fill color, RGB color with 565 structure
           */
          lcd.fillCircle(/*x0=*/x, /*y0=*/y, /*r=*/radius, /*color=*/color);
       color += 800;
       delay(100);
    }
  }
}

/* Test to draw a triangle */
void testTriangles(uint16_t color){
  lcd.fillScreen(BLACK_RGB565);
  
  for (int16_t i=0; i <=160; i+=24)
    /*
     * @ brief Draw a hollow triangle
     * @ param x0 The x-coordinate of the start vertex
     * @ param y0 The y-coordinate of the start vertex
     * @ param x1 The x-coordinate of the second vertex
     * @ param y1 The y-coordinate of the second vertex
     * @ param x2 The x-coordinate of the third vertex
     * @ param y2 The y-coordinate of the third vertex
     * @ param color border color, 565 structure RGB color
     */
    lcd.drawTriangle(/*x0=*/i,/*y0=*/0,/*x1=*/0,/*y1=*/128-i,/*x2=*/160-i,/*y2=*/128, /*color=*/color);
  
  for (int16_t i=0; i <160; i+=24)
    lcd.drawTriangle(160,i*4/3,0,128-i*4/3,i,0, color);

  for (int16_t i=0; i <160; i+=24)
    lcd.drawTriangle(160,i*4/3,i,0,160-i,128, color);

  color = RED_RGB565;
  for (int16_t i=0; i <=160; i+=24)
     /*
      * @ brief Draw a filled triangle
      * @ param x0 The x-coordinate of the start vertex
      * @ param y0 The y-coordinate of the start vertex
      * @ param x1 The x-coordinate of the second vertex
      * @ param y1 The y-coordinate of the second vertex
      * @ param x2 The x-coordinate of the third vertex
      * @ param y2 The y-coordinate of the third vertex
      * @ param color Fill color, RGB color with 565 structure
      */
    lcd.fillTriangle(/*x0=*/i,/*y0=*/0,/*x1=*/0,/*y1=*/128-i,/*x2=*/160-i,/*y2=*/128, /*color=*/color+=100);
  
  for (int16_t i=0; i <160; i+=24)
    lcd.fillTriangle(160,i*4/3,0,128-i*4/3,i,0, color+=100);

  for (int16_t i=0; i <160; i+=24)
    lcd.fillTriangle(160,i*4/3,i,0,160-i,128, color+=100);
}


