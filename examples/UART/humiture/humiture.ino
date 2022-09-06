/**！
 * @file humiture.ino
 * @brief 气象站综合示例
 * @details 可以显示天气,日期,时间,温度,湿度
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2022-07-20
 * @url https://github.com/DFRobot/DFRobot_LcdDisplay
 */

#include "DFRobot_LcdDisplay.h"
#include <MsTimer2.h>

DFRobot_Lcd_UART lcd;
DFRobot_Lcd_UART::sControlinf_t *bar1;
DFRobot_Lcd_UART::sControlinf_t *bar2;
/*
 * User-selectable macro definition color
 * BLACK_RGB565 BLUE_RGB565 RED_RGB565 GREEN_RGB565 CYAN_RGB565 MAGENTA_RGB565
 * YELLOW_RGB565 WHITE_RGB565 NAVY_RGB565 DARKGREEN_RGB565 DARKCYAN_RGB565 MAROON_RGB565
 * PURPLE_RGB565 OLIVE_RGB565 LIGHTGREY_RGB565 DARKGREY_RGB565 ORANGE_RGB565
 * GREENYELLOW_RGB565 DCYAN_RGB565
 */
#if ((defined ARDUINO_AVR_UNO) || (defined ARDUINO_AVR_NANO))
    #include <SoftwareSerial.h>
    SoftwareSerial Serial1(2, 3);  //RX, TX
    #define FPSerial Serial1
    
#else
    #define FPSerial Serial1
#endif
uint8_t hour = 9;
uint8_t Minute = 8;
uint8_t second = 56;

void flash()                        //中断处理函数，处理时间的改变
{
  second++;



  if (second > 59) {
    second = 0;
    Minute++;
  }

  if (Minute > 59) {
    Minute = 0;
    hour++;
  }
}


void setup(void) {

  //Rx and tx should be mapping into D2 and D3 when using Firebeetle-ESP32
  #if (defined ESP32)
     Serial1.begin(9600, SERIAL_8N1, /*rx =*/D2, /*tx =*/D3);
  #else
  Serial1.begin(9600);
  #endif
  Serial.begin(115200);
  
  lcd.begin(Serial1);
  lcd.reset();
  lcd.lvglInit(0x0000);
  //创建温度显示的进度条
  bar1 = lcd.creatBar(25, 75, 55, 14, 0xfa20);
  //创建湿度显示的进度条
  bar2 = lcd.creatBar(25, 95, 55, 14, 0x867d);
  //创建图标
  lcd.drawIcon(0, 64, DFRobot_Lcd_UART::eIconThermometer, 200);
  lcd.drawIcon(-8, 84, DFRobot_Lcd_UART::eIconRaindrops, 200);
  lcd.drawIcon(120, 2, DFRobot_Lcd_UART::eIconRains, 300);
  lcd.drawIcon(122, 80, DFRobot_Lcd_UART::eIconLaugh, 320);
  //显示当前时间
  lcd.drawLcdTime(5,10,hour,Minute,second,0,0xf800, 0);
  //显示当前日期
  lcd.drawLcdDate(5,42,7,18,1,1,0xf800, 0);
  //显示当前天气
  lcd.drawString(113, 36, "大雨", 0, 0xfa20, 0);

  MsTimer2::set(1000, flash);        // 中断设置函数，每 1000ms 进入一次中断
  MsTimer2::start();                //开始计时
}

void loop(void) {

  //显示当前时间
  lcd.drawLcdTime(5,10,hour,Minute,second,0,0xf800, 0);
  lcd.setBar(bar2, String(10)+"%");

  lcd.setBar(bar1,  String(80)+"℃");


  delay(500);

  lcd.setBar(bar1, String(30)+"℃");
  lcd.setBar(bar2,  String(80)+"%");

  delay(500);

}