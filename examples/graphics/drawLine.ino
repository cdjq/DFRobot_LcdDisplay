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
    testLine();
}

void testLine(){
    //设置颜色为红色
    uint32_t color = 0xFF0000;
    uint8_t lineNum = 0;
    //从屏幕中心开始向上边框画线（每间隔5个像素点画一条线，并且每条线的颜色由红色逐渐变暗）
    for (int16_t x=0; x < 319; x+=5) {
        //画线，返回的线条ID是从1开始的，所以这里直接以lineNum来记录即可
    	lcd.drawLine(320/2, 240/2, x, 0, 1, color-=0x040000);
    	lineNum++;
  	}
  	//设置颜色为绿色
    color = 0x00FF00;
    //从屏幕中心开始向右边框画线（每间隔5个像素点画一条线，并且每条线的颜色由绿色逐渐变暗）
    for (int16_t y=0; y < 240; y+=5) {
      lcd.drawLine(320/2, 240/2, 319, y, 1, color-=0x000500);
      lineNum++;
    }
    //设置颜色为蓝色
    color = 0x0000FF;
    //从屏幕中心开始向下边框画线（每间隔5个像素点画一条线，并且每条线的颜色由蓝色逐渐变暗）
    for (int16_t x = 319; x >= 0; x-=5) {
      lcd.drawLine(320/2, 240/2, x,239, 1, color-=0x000004);
      lineNum++;
    }
    //设置颜色为黄色
    color = 0xFFFF00;
    //从屏幕中心开始向右边框画线（每间隔5个像素点画一条线，并且每条线的颜色由黄色逐渐变暗）
    for (int16_t y = 239; y >= 0; y-=5) {
      lcd.drawLine(320/2, 240/2, 0, y, 1,color-=0x050500);
      lineNum++;
    }
    delay(9000);
    //将线条ID定位到1号线条
    lineNum = 1;
    //设置颜色为黄色
    color = 0xFFFF00;
    //将屏幕中心向上边框画的线条颜色更改为由黄色逐渐变暗
    for (int16_t x=0; x < 319; x+=5) {
      lcd.updateLine(lineNum, 320/2, 240/2, x, 0, 1, color-=0x040400);
      lineNum++;
    }
    //设置颜色为红色
    color = 0xFF0000;
    //将屏幕中心向右边框画的线条颜色更改为由红色逐渐变暗
    for (int16_t y=0; y < 240; y+=5) {
      lcd.updateLine(lineNum, 320/2, 240/2, 319, y, 1, color-=0x050000);
      lineNum++;
    }
	//设置颜色为绿色
    color = 0x00FF00;
    //将屏幕中心向下边框画的线条颜色更改为由绿色逐渐变暗
    for (int16_t x = 319; x >= 0; x-=5) {
      lcd.updateLine(lineNum, 320/2, 240/2, x,239, 1, color-=0x000400);
      lineNum++;
    }
	//设置颜色
    color = 0x0000FF;
    //将屏幕中心向右边框画的线条颜色更改为由蓝色逐渐变暗
    for (int16_t y = 239; y >= 0; y-=5) {
      lcd.updateLine(lineNum, 320/2, 240/2, 0, y, 1,color-=0x000005);
      lineNum++;
    }
    delay(9000);
    //一条一条删除所有线条
    for(uint8_t i = 1; i <= lineNum; i++){
      lcd.deleteLine(i);
    }
    delay(9000);
}

