
/**！
 * @file compass.ino
 * @brief 指南针控件示例
 * @details 可通过传感器的得到的方位值来,设置指针的指向
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2022-07-20
 * @url https://github.com/DFRobot/DFRobot_LcdDisplay
 */



#include "DFRobot_LcdDisplay.h"
DFRobot_Lcd_UART lcd;
DFRobot_Lcd_UART::sControlinf_t *compss;
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
  lcd.lvglInit(/*bg_color=*/1);
  //创建指南针控件
  compss = lcd.creatCompass(/*x=*/16,/*y=*/0,/*width=*/128,/*height*/128,/*颜色*/0xf8);
  //设置指南针指针角度

}

void loop(void){

  lcd.setCompassScale(compss,/*角度*/90);
  delay(1000);
  lcd.setCompassScale(compss,/*角度*/120);
  delay(1000);
  lcd.setCompassScale(compss,/*角度*/150);
  delay(1000);
  lcd.setCompassScale(compss,/*角度*/180);
  delay(1000);
  lcd.setCompassScale(compss,/*角度*/210);
  delay(1000);
  lcd.setCompassScale(compss,/*角度*/240);
  delay(1000);
  lcd.setCompassScale(compss,/*角度*/270);
  delay(1000);
  lcd.setCompassScale(compss,/*角度*/300);
  delay(1000);
}