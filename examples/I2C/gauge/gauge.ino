
/**！
 * @file gauge.ino
 * @brief 表盘控件
 * @details 可用于如速度,压力的显示
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2022-07-20
 * @url https://github.com/DFRobot/DFRobot_LcdDisplay
 */

#include "DFRobot_LcdDisplay.h"
DFRobot_Lcd_IIC lcd;

DFRobot_Lcd_IIC::sControlinf_t *gauge;
/*
 * User-selectable macro definition color
 * BLACK_RGB565 BLUE_RGB565 RED_RGB565 GREEN_RGB565 CYAN_RGB565 MAGENTA_RGB565
 * YELLOW_RGB565 WHITE_RGB565 NAVY_RGB565 DARKGREEN_RGB565 DARKCYAN_RGB565 MAROON_RGB565
 * PURPLE_RGB565 OLIVE_RGB565 LIGHTGREY_RGB565 DARKGREY_RGB565 ORANGE_RGB565
 * GREENYELLOW_RGB565 DCYAN_RGB565
 */
void setup(void){

  lcd.begin();
  //复位屏幕
  lcd.reset();
  //初始化
  lcd.lvglInit(/*显示背景色*/CYAN_RGB565);
  //创建一个表盘控件
  gauge = lcd.creatGauge(/*x=*/35,/*y = */19,/*width*/90,/*height*/90,/*颜色*/NAVY_RGB565);
  //设置表盘参数
  lcd.setGaugeScale(gauge,/*angle of the scale*/270,/*起始值*/0,/*终止值*/100);

}

void loop(void){


  //设置表盘的值
  lcd.setGaugeValue(gauge,/*数值*/20);
  delay(3000);
  lcd.setGaugeValue(gauge,80);
  delay(3000);
}