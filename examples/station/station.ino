/**!
 * @file station.ino
 * @brief 气象站综合示例
 * @details 可以显示天气,日期,时间,温度,湿度,风速
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2022-07-20
 * @url https://github.com/DFRobot/DFRobot_LcdDisplay
 */
#include "DFRobot_LcdDisplay.h"
#include <MsTimer2.h>

#define I2C_COMMUNICATION  // I2C通信。如果你想使用UART通信，注释掉这行代码。
#ifdef  I2C_COMMUNICATION
 /**
   * 使用 i2c 接口
   */
DFRobot_Lcd_IIC lcd(&Wire, /*I2CAddr*/ 0x2c);
#else
 /**
   * 使用 uart 接口
   */
#if ((defined ARDUINO_AVR_UNO) || (defined ESP8266))
#include <SoftwareSerial.h>
SoftwareSerial softSerial(/*rx =*/4, /*tx =*/5);
#define FPSerial softSerial
#else
#define FPSerial Serial1
#endif
DFRobot_Lcd_UART lcd(FPSerial);
#endif

DFRobot_LcdDisplay::sControlinf_t * bar1, * bar2, * bar3;

uint8_t hour = 9, Minute = 8, second = 56;

void flash()   //中断处理函数，处理时间的改变
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
  lcd.lvglInit(YELLOW_RGB565);

  //创建图标, 记得先显示图标, 图标对"点线字符"等, 会有干扰覆盖作用
  lcd.drawIcon(25, 100, DFRobot_LcdDisplay::eIconRainy, 200);
  lcd.drawIcon(140, 30, DFRobot_LcdDisplay::eIconThermometer, 200);
  lcd.drawIcon(135, 90, DFRobot_LcdDisplay::eIconRaindrops, 200);
  lcd.drawIcon(115, 155, DFRobot_LcdDisplay::eIconWind, 200);

  //显示当前时间
  lcd.drawLcdTime(10, 10, hour, Minute, second, 0, ORANGE_RGB565, WHITE_RGB565);
  //显示当前日期
  lcd.drawLcdDate(10, 50, 3, 29, 3, 1, LIGHTGREY_RGB565, WHITE_RGB565);
  //显示当前天气
  lcd.drawString(38, 170, "大雨", 0, RED_RGB565, DARKGREEN_RGB565);

  //创建温度显示的进度条
  bar1 = lcd.creatBar(180, 60, 80, 20, RED_RGB565);
  //创建湿度显示的进度条
  bar2 = lcd.creatBar(180, 120, 80, 20, BLUE_RGB565);
  //创建风速显示的进度条
  bar3 = lcd.creatBar(180, 180, 80, 20, GREEN_RGB565);

  MsTimer2::set(1000, flash);        // 中断设置函数，每 1000ms 进入一次中断
  MsTimer2::start();                //开始计时
}

void loop(void)
{
  //显示当前时间
  lcd.drawLcdTime(10, 10, hour, Minute, second, 0, ORANGE_RGB565, WHITE_RGB565);
  lcd.setBar(bar1, String(25) + " °C");
  lcd.setBar(bar2, String(80) + " %");
  lcd.setBar(bar3, String(10) + " m/s");
  delay(300);

  lcd.setBar(bar1, String(28) + " °C");
  lcd.setBar(bar2, String(60) + " %");
  lcd.setBar(bar3, String(15) + " m/s");
  delay(300);

  lcd.setBar(bar1, String(30) + " °C");
  lcd.setBar(bar2, String(50) + " %");
  lcd.setBar(bar3, String(20) + " m/s");
  delay(400);
}
