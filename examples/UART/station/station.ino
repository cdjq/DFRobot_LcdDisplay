/**!
 * @file station.ino
 * @brief 创建气象站控件
 * @details 当前只支持温度显示
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2022-07-20
 * @url https://github.com/DFRobot/DFRobot_LcdDisplay
 */

#include "DFRobot_LcdDisplay.h"
DFRobot_Lcd_UART lcd;
DFRobot_Lcd_UART::sControlinf_t *station;
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
void setup(void){
   //Rx and tx should be mapping into D2 and D3 when using Firebeetle-ESP32
   #if (defined ESP32)
      Serial1.begin(9600, SERIAL_8N1, /*rx =*/D2, /*tx =*/D3);
   #else
   Serial1.begin(9600);
   #endif
   Serial.begin(115200);
   
   lcd.begin(Serial1);
   //复位屏幕
   lcd.reset();
   //初始化
   lcd.lvglInit(/*显示背景色*/0x660);
   delay(50);
   //创建气象站
   lcd.setFont(DFRobot_Lcd_UART::eShiftJis);
   station = lcd.creatStations(30,10,356,0xf800,"おんど");

}


void loop(void){
  //设置气象站所监测的值,如温度值
  lcd.setStationValue(station,"36.1℃");
  delay(1000);
  lcd.setStationValue(station,"39.0℃");
  delay(1000);
}