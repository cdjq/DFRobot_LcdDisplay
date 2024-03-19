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
    lcd.cleanScreen();
    delay(500);
    lcd.setBackgroundColor(WHITE);
}

void loop(void){
    testRects();
}

uint32_t generateRandomColor() {
    uint8_t r = rand() % 256;
    uint8_t g = rand() % 256;
    uint8_t b = rand() % 256;
    return (r << 16) | (g << 8) | b;
}

uint8_t rectsId[20];
void testRects() { 
    uint32_t fillColor = 0xFF0000;
    uint32_t borderColor = 0xFF0000;
    //从顶点开始画一个320*240的矩形，边框设置为1，边框颜色为随机，不填充，填充颜色为蓝色，不设置圆角
    rectsId[0] = lcd.drawRect(0, 0, 320, 240, 1, 0xFF0000, 0, 0x00FF00, 0);
    //更改这个矩形，更改起点、长宽，使其达到往屏幕中心缩小的效果
    for(uint8_t i = 0; i < 20; i++){
      uint16_t x = 320/40*i;
      uint16_t y = 240/40*i;
      uint16_t w = 320 - x *2;
      uint16_t h = 240 - y *2;
      //设置边框颜色为随机颜色
      borderColor = generateRandomColor();
      lcd.updateRect(rectsId[0], x, y, w, h, 1, borderColor, 0, 0x00FF00, 0);
    }
    delay(1000);
    //更改这个矩形，更改起点、长宽，并将边框颜色设置为蓝色，使其达到从屏幕中心放大的效果
    for(uint8_t i = 0; i <= 20; i++){
      uint16_t x = 320/40*(20-i);
      uint16_t y = 240/40*(20-i);
      uint16_t w = 320 - x *2;
      uint16_t h = 240 - y *2;
      //设置边框颜色为随机颜色
      borderColor = generateRandomColor();
      lcd.updateRect(rectsId[0], x, y, w, h, 1, borderColor, 0, 0x00FF00, 0);
    }
    delay(1000);
    //新增矩形，设置不同的起点、长宽，使其达到从屏幕边框逐渐向中心铺满的效果
    for(uint8_t i = 1; i < 20; i++){
      uint16_t x = 320/40*i;
      uint16_t y = 240/40*i;
      uint16_t w = 320 - x *2;
      uint16_t h = 240 - y *2;
      borderColor = generateRandomColor();
      rectsId[i] = lcd.drawRect(x, y, w, h, 1, borderColor, 0, 0x00FF00, 0);
    }
    delay(1000);
    
    //从中心开始更改这些矩形，将其改为圆角，并且使能填充，填充颜色为绿色渐变
    for(uint8_t i = 0; i <= 20; i++){
      uint16_t x = 320/40*(20-i);
      uint16_t y = 240/40*(20-i);
      uint16_t w = 320 - x *2;
      uint16_t h = 240 - y *2;
      //设置填充颜色为随机颜色
      borderColor = generateRandomColor();
      fillColor = generateRandomColor();
      lcd.updateRect(rectsId[20-i],x, y, w, h, 1, borderColor, 1, fillColor, 1);
    }
    
    delay(1000);
    //一个一个删除所有的矩形
    for(uint8_t i = 0; i < 20; i++){
      lcd.deleteRect(rectsId[i]);
    }
    delay(1000);
}

