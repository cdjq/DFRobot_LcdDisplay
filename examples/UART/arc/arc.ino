/**!
 * @file arc.ino
 * @brief 角度控件示例
 * @details 创建一个角度控件,然后控制角度产生变化
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2022-07-20
 * @url https://github.com/DFRobot/DFRobot_LcdDisplay
 */
#include "DFRobot_LcdDisplay.h"

DFRobot_Lcd_UART lcd;
DFRobot_Lcd_UART::sControlinf_t* arc;

void setup(void)
{
  Serial.begin(115200);

  lcd.begin(Serial1);
  //复位屏幕
  lcd.reset();
  /** 初始化
    * User-selectable macro definition color
    * BLACK_RGB565 BLUE_RGB565 RED_RGB565 GREEN_RGB565 CYAN_RGB565 MAGENTA_RGB565
    * YELLOW_RGB565 WHITE_RGB565 NAVY_RGB565 DARKGREEN_RGB565 DARKCYAN_RGB565 MAROON_RGB565
    * PURPLE_RGB565 OLIVE_RGB565 LIGHTGREY_RGB565 DARKGREY_RGB565 ORANGE_RGB565
    * GREENYELLOW_RGB565 DCYAN_RGB565
    */
  lcd.lvglInit(/*显示背景颜色*/DCYAN_RGB565);
  //创建一个角度控件
  arc = lcd.creatArc(/*x=*/30,/*y=*/14,/*width=*/100,/*height=*/100);
}

void loop(void)
{


  //控制角度控件的角度
  lcd.setArcRotation(arc,/*角度*/10);
  delay(2000);
  lcd.setArcRotation(arc, 60);
  delay(2000);
}