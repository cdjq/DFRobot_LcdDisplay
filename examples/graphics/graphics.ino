/**!
 * @file grapics.ino
 * @brief Displaying basic shapes.
 * @details The basic shapes that can be displayed include point, line, circle, rectangle, triangle, and more.
 * @n  Most parameters are related to the screen size (320*240). Please ensure that the custom parameters do not exceed the screen limits.
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @maintainer [qsjhyy](yihuan.huang@dfrobot.com)
 * @version  V1.0
 * @date  2023-05-29
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

//#define I2C_COMMUNICATION  // I2C communication. If you want to use UART communication, comment out this line of code.

#ifdef  I2C_COMMUNICATION
  /**
    * Using the I2C interface.
    */
  DFRobot_Lcd_IIC lcd(&Wire, /*I2CAddr*/ 0x2c);
#else
  /**
    * Using the UART interface.
    */
  #if ((defined ARDUINO_AVR_UNO) || (defined ESP8266) || (defined ARDUINO_BBC_MICROBIT_V2))
    #include <SoftwareSerial.h>
    SoftwareSerial softSerial(/*rx =*/4, /*tx =*/5);
    #define FPSerial softSerial
  #else
    #define FPSerial Serial1
  #endif
  DFRobot_Lcd_UART lcd(FPSerial);
#endif

/**
 * User-selectable macro definition color
 * BLACK_RGB565 BLUE_RGB565 RED_RGB565 GREEN_RGB565 CYAN_RGB565 MAGENTA_RGB565
 * YELLOW_RGB565 WHITE_RGB565 NAVY_RGB565 DARKGREEN_RGB565 DARKCYAN_RGB565 MAROON_RGB565
 * PURPLE_RGB565 OLIVE_RGB565 LIGHTGREY_RGB565 DARKGREY_RGB565 ORANGE_RGB565
 * GREENYELLOW_RGB565 DCYAN_RGB565
 */
void setup(void)
{
  #ifndef  I2C_COMMUNICATION
    #if (defined ESP32)
      FPSerial.begin(9600, SERIAL_8N1, /*rx =*/D2, /*tx =*/D3);
    #else
      FPSerial.begin(9600);
    #endif
  #endif

  Serial.begin(115200);

  lcd.begin();
  lcd.setBackgroundColor(WHITE);
  //testLine();
  //lcd.drawTriangle(10, 10,10,100,50,60, 1, 0x0000FF,1,0x000000);
  //testCircles();
  //lcd.drawRect(5, 5,310, 230, 1, 0x0000FF, 1, 0x000000,  1);
  //testFastLines(0xFFFF00,0x00FFFF);
  //testTriangles();
}

void loop(void){
  //testRects();
  //testLine();
  //testFastLines(0xFFFF,0x00FFFF);
  //testRects(0x000000,0xFFFFFF);
  //testCircles();
  testTriangles();
/*
  testDrawPixel();
  testLine();
  testFastLines(PURPLE_RGB565,YELLOW_RGB565);
  testRects(BLACK_RGB565,WHITE_RGB565);
  testRoundRects();
  testCircles(24,BLUE_RGB565);
  testTriangles(YELLOW_RGB565);
*/
}
uint32_t fillColor = 0x00FF00;
uint32_t borderColor = 0xFF0000;
uint32_t generateRandomColor() {
    uint8_t r = rand() % 256;
    uint8_t g = rand() % 256;
    uint8_t b = rand() % 256;
    return (r << 16) | (g << 8) | b;
}

/* Test to draw a line*/
void testLine(){
// 0x00FF is the color data in the format of RGB565
  uint32_t color = 0xFF0000;
  uint8_t lineNum = 0;
  //lcd.fillScreen(BLACK_RGB565);
  for (int16_t x=0; x < 319; x+=5) {
    /*
     * @ brief draw a line
     * @ param x0 The x-coordinate of the first vertex
     *         y0 The y-coordinate of the first vertex
     *         x1 The x-coordinate of the second vertex
     *         y1 The y-coordinate of the second vertex
     *         width line width
     *         c line color
     */
    lcd.drawLine(320/2, 240/2, x, 0, 1, color-=0x040000);
    lineNum++;
  }
  
  color = 0x00FF00;
  for (int16_t y=0; y < 240; y+=5) {
    lcd.drawLine(320/2, 240/2, 319, y, 1, color-=0x000500);
    lineNum++;
  }
  color = 0x0000FF;
  for (int16_t x = 319; x >= 0; x-=5) {
    lcd.drawLine(320/2, 240/2, x,239, 1, color-=0x000004);
    lineNum++;
  }
  
  color = 0xFFFF00;
  
  for (int16_t y = 239; y >= 0; y-=5) {
    lcd.drawLine(320/2, 240/2, 0, y, 1,color-=0x050500);
    lineNum++;
  }
  delay(9000);

  lineNum = 1;
  color = 0xFFFF00;
  for (int16_t x=0; x < 319; x+=5) {
    lcd.updateLine(lineNum, 320/2, 240/2, x, 0, 1, color-=0x040400);
    lineNum++;
  }

  color = 0xFF0000;
  for (int16_t y=0; y < 240; y+=5) {
    lcd.updateLine(lineNum, 320/2, 240/2, 319, y, 1, color-=0x050000);
    lineNum++;
  }

  color = 0x00FF00;
  for (int16_t x = 319; x >= 0; x-=5) {
    lcd.updateLine(lineNum, 320/2, 240/2, x,239, 1, color-=0x000400);
    lineNum++;
  }

  color = 0x0000FF;
  for (int16_t y = 239; y >= 0; y-=5) {
    lcd.updateLine(lineNum, 320/2, 240/2, 0, y, 1,color-=0x000005);
    lineNum++;
  }
  delay(9000);
  for(uint8_t i = 1; i <= lineNum; i++){
    lcd.deleteLine(i);
  }
  delay(9000);
  
}

void testFastLines(uint32_t color1, uint32_t color2) {
  for (int16_t y=0; y < 240; y+=4) {

    lcd.drawLine(/*x=*/0, /*y=*/y, /*w=*/320, y, 2,/*c=*/color2);
    delay(30);
  }
  
  for(int16_t x=0; x < 320; x+=3) {

    lcd.drawLine(/*x=*/x, /*y=*/0, /*h=*/x, 240, 2,/*c=*/color1);
    delay(30);
  }
}

uint8_t rectsId[20];
void testRects() { 
    rectsId[0] = lcd.drawRect(0, 0, 320, 240, 1, 0xFF0000, 0, 0x00FF00, 0);
    for(uint8_t i = 0; i < 20; i++){
      uint16_t x = 320/40*i;
      uint16_t y = 240/40*i;
      uint16_t w = 320 - x *2;
      uint16_t h = 240 - y *2;
      lcd.updateRect(rectsId[0], x, y, w, h, 1, 0xFF0000, 0, 0x00FF00, 0);
    }
    delay(1000);
    for(uint8_t i = 0; i <= 20; i++){
      uint16_t x = 320/40*(20-i);
      uint16_t y = 240/40*(20-i);
      uint16_t w = 320 - x *2;
      uint16_t h = 240 - y *2;
      lcd.updateRect(rectsId[0], x, y, w, h, 1, 0x0000FF, 0, 0x00FF00, 0);
    }
    
    delay(1000);
    for(uint8_t i = 1; i < 20; i++){
      uint16_t x = 320/40*i;
      uint16_t y = 240/40*i;
      uint16_t w = 320 - x *2;
      uint16_t h = 240 - y *2;
      rectsId[i] = lcd.drawRect(x, y, w, h, 1, 0x0000FF, 0, 0x00FF00, 0);
    }
    delay(1000);
    for(uint8_t i = 0; i <= 20; i++){
      uint16_t x = 320/40*(20-i);
      uint16_t y = 240/40*(20-i);
      uint16_t w = 320 - x *2;
      uint16_t h = 240 - y *2;
      lcd.updateRect(rectsId[20-i],x, y, w, h, 1, 0xFF0000, 1, fillColor-=0x000C00, 1);
    }
    
    delay(1000);
    for(uint8_t i = 0; i < 20; i++){
      lcd.deleteRect(rectsId[i]);
    }
    delay(1000);
}

uint8_t circlesId[21];
void testCircles() {
  //lcd.fillScreen(BLACK_RGB565);
  borderColor = generateRandomColor();
  circlesId[0] = lcd.drawCircle(160, 120, 1, 2, borderColor, 0, 0x0000FF);
  for(uint8_t i = 0; i < 20; i++){
    borderColor = generateRandomColor();
    lcd.updateCircle(circlesId[0], 160, 120, 6*i, 2, borderColor, 0, 0x0000FF);
    delay(30);
  }

  for(uint8_t i = 1; i < 20; i++){
    borderColor = generateRandomColor();
    circlesId[i] = lcd.drawCircle(160, 120, 120-6*i, 2, borderColor, 0, 0x0000FF);
  }
  delay(1000);
  
  for(uint8_t i = 0; i < 20; i++){
    borderColor = generateRandomColor();
    fillColor = generateRandomColor();
    lcd.updateCircle(circlesId[20-i], 160, 120, 6*i, 2, borderColor, 1, fillColor);
  }

  delay(1000);
  for(uint8_t i = 0; i < 20; i++){
    lcd.deleteCircle(circlesId[i]);
  }
  delay(1000);
}
uint8_t trianglesId[10];
void testTriangles(){
  //lcd.fillScreen(BLACK_RGB565);
  trianglesId[0] = lcd.drawTriangle(160, 0, 0, 239, 319, 239, 1, borderColor, 0, fillColor);
  for (uint8_t i=0; i <10; i++){
    lcd.updateTriangle(trianglesId[0], 160, i*12, i*16, 239 - i*12,319-i*16, 239-i*12, 1, borderColor, 0, fillColor);
  }
  delay(1000);  
  for(uint8_t i = 9; i>0; i--){
    trianglesId[10-i] = lcd.drawTriangle(160, i*12, i*16, 239 - i*12,319-i*16, 239-i*12, 1, borderColor, 0, fillColor);
  }
  delay(1000);
  for(uint8_t i = 0; i<10; i++){
    fillColor = generateRandomColor();
    lcd.updateTriangle(trianglesId[i], 160, i*12, i*16, 239 - i*12,319-i*16, 239-i*12, 1, borderColor, 1, fillColor);
  }
  delay(1000);
  for(uint8_t i = 0 ;i < 10;i++){
    lcd.deleteTriangle(trianglesId[i]);
  }
  delay(1000);
}

#if 0
/* Test to draw a pixel*/
void testDrawPixel()
{
  //Clear screen
  lcd.fillScreen(BLACK_RGB565);
  int x = 0;
  int y = 0;
  for(int i = 0; i <= 240/2; i += 10){
    for (x = i; x <= 320 - i - 10; x += 10){   // 上
      /*
       * @ brief draw a pixel
       * @ param x coordinate
       *         y coordinate
       * c pixel color
       */
      lcd.drawPixel(x, y, ORANGE_RGB565);
    }

    for (y = i; y <= 240 - i - 10; y += 10) {   // 右
      lcd.drawPixel(x, y, ORANGE_RGB565);
    }

    for (x = 320 - i; x >= i + 10; x -= 10) {   // 下
      lcd.drawPixel(x, y, ORANGE_RGB565);
    }

    for (y = 240 - i; y >= i + 20; y -= 10) {   // 左
      lcd.drawPixel(x, y, ORANGE_RGB565);
    }
    lcd.drawPixel(x, y, ORANGE_RGB565);
  }
}



/* Test to fast draw line(need to set delay), only horizontal line and vertical line */
void testFastLines(uint16_t color1, uint16_t color2) {
  for (int16_t y=0; y < 240; y+=4) {

    lcd.drawLine(/*x=*/0, /*y=*/y, /*w=*/320, y, /*c=*/color2);
    delay(30);
  }
  
  for(int16_t x=0; x < 320; x+=3) {

    lcd.drawLine(/*x=*/x, /*y=*/0, /*h=*/x, 240, /*c=*/color1);
    delay(30);
  }
}

/* Test to draw a rectangle*/
void testRects(uint16_t color1, uint16_t color2) { 
    lcd.fillScreen(BLACK_RGB565);
    int16_t x=320-12;
    for (; x > 100; x-=320/40) {
      /*
       * @ brief draw a hollow rectangle
       * @ param x The x-coordinate of the vertex 
       * @ param y The y-coordinate of the vertex
       * @ param w horizontal side length
       * @ param h longitudinal side length
       * @ param color Fill color, RGB color with 565 structure
       */
      lcd.drawRect(/*x=*/320/2 -x/2, /*y=*/240/2 -x/2 , /*w=*/x, /*h=*/x, /*color=*/color2+=0x0F00);
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
    lcd.fillRect(/*x=*/320/2 -x/2, /*y=*/240/2 -x/2 , /*w=*/x, /*h=*/x, /*color=*/color2);
    delay(100);
    for(; x > 6; x-=320/40){
      lcd.drawRect(320/2 -x/2, 240/2 -x/2 , x, x, color1);
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
  int w = 320-3;
  int h = 240-3;
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
  for (int16_t x=radius; x <=320-radius; x+=radius*2) {
    for (int16_t y=radius; y <=240-radius; y+=radius*2) {
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
  
  for (int16_t i=0; i <=320; i+=24)
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
    lcd.drawTriangle(/*x0=*/i,/*y0=*/0,/*x1=*/0,/*y1=*/240-i,/*x2=*/320-i,/*y2=*/240, /*color=*/color);
  
  for (int16_t i=0; i <320; i+=24)
    lcd.drawTriangle(320,i*4/3,0,240-i*4/3,i,0, color);

  for (int16_t i=0; i <320; i+=24)
    lcd.drawTriangle(320,i*4/3,i,0,320-i,240, color);

  color = RED_RGB565;
  for (int16_t i=0; i <=320; i+=24)
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
    lcd.fillTriangle(/*x0=*/i,/*y0=*/0,/*x1=*/0,/*y1=*/240-i,/*x2=*/320-i,/*y2=*/240, /*color=*/color+=100);
  
  for (int16_t i=0; i <320; i+=24)
    lcd.fillTriangle(320,i*4/3,0,240-i*4/3,i,0, color+=100);

  for (int16_t i=0; i <320; i+=24)
    lcd.fillTriangle(320,i*4/3,i,0,320-i,240, color+=100);
}

#endif

