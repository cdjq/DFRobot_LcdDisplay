
/**!
 * @file multipleBar.ino
 * @brief 进度条控件示例
 * @details 创建三个角度控件,并分别控制每个控件显示不同的值
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2022-07-20
 * @url https://github.com/DFRobot/DFRobot_LcdDisplay
 */


#include "DFRobot_LcdDisplay.h"
DFRobot_Lcd_UART lcd;
DFRobot_Lcd_UART::sControlinf_t *bar1; //进度条1
DFRobot_Lcd_UART::sControlinf_t *bar2;//进度条2
DFRobot_Lcd_UART::sControlinf_t *bar3;//进度条3
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
   delay(50);
   //初始化
   lcd.lvglInit(/*显示背景颜色*/CYAN_RGB565);
   //创建角度控件
   bar1 = lcd.creatBar(/*x = */10,/*y = */15,/*width=*/80,/*height=*/15,/*进度条颜色*/ORANGE_RGB565);
   bar2 = lcd.creatBar(10,55,80,15,YELLOW_RGB565);
   bar3 = lcd.creatBar(10,95,80,15,LIGHTGREY_RGB565);


}

void loop(void){


  //设置进度条值,可带单位,但必须由数字开始
  lcd.setBar(bar1,"80°C");
  lcd.setBar(bar2,"10°C");
  lcd.setBar(bar3,"20°C");

  delay(2000);

  lcd.setBar(bar1,"30°C");
  lcd.setBar(bar2,"80°C");
  lcd.setBar(bar3,"50°C");

  delay(2000);
}