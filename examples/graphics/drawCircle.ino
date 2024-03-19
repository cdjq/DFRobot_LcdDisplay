#include "DFRobot_LcdDisplay.h"

#define I2C_COMMUNICATION  // I2C communication. If you want to use UART communication, comment out this line of code.

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
    testCircles();
}

//填充颜色
uint32_t fillColor = 0x00FF00;
//边框颜色
uint32_t borderColor = 0xFF0000;
//产生随机颜色
uint32_t generateRandomColor() {
    uint8_t r = rand() % 256;
    uint8_t g = rand() % 256;
    uint8_t b = rand() % 256;
    return (r << 16) | (g << 8) | b;
}

uint8_t circlesId[21];
void testCircles() {
    //设置边框颜色为随机色
    borderColor = generateRandomColor();
    //以(160，120)为圆心,画一个半径1边框颜色为随机色的圆，不填充
    circlesId[0] = lcd.drawCircle(160, 120, 1, 2, borderColor, 0, 0x0000FF);
    //更改前面画的圆的半径，和边框颜色，以达到放大圆的效果
    for(uint8_t i = 0; i < 20; i++){
      borderColor = generateRandomColor();
      lcd.updateCircle(circlesId[0], 160, 120, 6*i, 2, borderColor, 0, 0x0000FF);
      delay(30);
    }
    //以(160,120)为圆心，添加多个圆，以达到多个同心圆的效果
    for(uint8_t i = 1; i < 20; i++){
      borderColor = generateRandomColor();
      circlesId[i] = lcd.drawCircle(160, 120, 120-6*i, 2, borderColor, 0, 0x0000FF);
    }
    delay(1000);

    //更改这些圆，将这些同心圆都更设置为填充颜色，并且颜色随机
    for(uint8_t i = 0; i < 20; i++){
      borderColor = generateRandomColor();
      fillColor = generateRandomColor();
      lcd.updateCircle(circlesId[20-i], 160, 120, 6*i, 2, borderColor, 1, fillColor);
    }
  
    delay(1000);
    //一个一个删除这些圆
    for(uint8_t i = 0; i < 20; i++){
      lcd.deleteCircle(circlesId[i]);
    }
    delay(1000);
}

