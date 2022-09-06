/**！
 * @file slider.ino
 * @brief 创建滑条控件
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2022-07-20
 * @url https://github.com/DFRobot/DFRobot_LcdDisplay
 */
#include "DFRobot_LcdDisplay.h"
DFRobot_Lcd_IIC lcd;
DFRobot_Lcd_IIC::sControlinf_t *slider;

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
   lcd.lvglInit(/*显示背景色*/NAVY_RGB565);
   //创建一个滑条控件
   slider = lcd.creatSlider(/*x*/20,/*y*/60,/*width*/120,/*height*/15,/*颜色*/DCYAN_RGB565);


}

void loop(void){



  //设置滑条数值
  lcd.setSliderValue(slider,30);
  delay(3000);
  lcd.setSliderValue(slider,40);
  delay(3000);
}