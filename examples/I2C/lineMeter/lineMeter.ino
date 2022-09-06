/**！
 * @file lineMeter.ino
 * @brief 创建线形仪表控件
 * @details 创建三个线形仪表控件,并分别控制显示不同的值
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2022-07-20
 * @url https://github.com/DFRobot/DFRobot_LcdDisplay
 */
#include "DFRobot_LcdDisplay.h"

/*
 * User-selectable macro definition color
 * BLACK_RGB565 BLUE_RGB565 RED_RGB565 GREEN_RGB565 CYAN_RGB565 MAGENTA_RGB565
 * YELLOW_RGB565 WHITE_RGB565 NAVY_RGB565 DARKGREEN_RGB565 DARKCYAN_RGB565 MAROON_RGB565
 * PURPLE_RGB565 OLIVE_RGB565 LIGHTGREY_RGB565 DARKGREY_RGB565 ORANGE_RGB565
 * GREENYELLOW_RGB565 DCYAN_RGB565
 */
DFRobot_Lcd_IIC lcd;
DFRobot_Lcd_IIC::sControlinf_t *lineMeter1;
DFRobot_Lcd_IIC::sControlinf_t *lineMeter2;
DFRobot_Lcd_IIC::sControlinf_t *lineMeter3;
void setup(void){

   lcd.begin();
   //复位屏幕
   lcd.reset();
   //初始化
   lcd.lvglInit(/*显示背景色*/CYAN_RGB565);
   //创建线形仪表控件 
   lineMeter1 = lcd.creatLineMeter(/*x*/0,/*y*/45,/*width*/75,/*height*/75,/*颜色*/CYAN_RGB565);
   //设置表盘参数
   lcd.setMeterScale(lineMeter1,/*angle of the scale*/270,/*起始角度*/0,/*end of angle*/100);

   lineMeter2 = lcd.creatLineMeter(60,0,75,75,GREEN_RGB565);
   lcd.setMeterScale(lineMeter2,270,0,100);
   
   lineMeter3 = lcd.creatLineMeter(70,70,75,75,ORANGE_RGB565);
   
   lcd.setMeterScale(lineMeter3,270,0,100);


}

void loop(void){


  //设置表盘数值
  lcd.setMeterValue(lineMeter1,40);
  lcd.setMeterValue(lineMeter2,50);
  lcd.setMeterValue(lineMeter3,70);
  delay(3000);

  lcd.setMeterValue(lineMeter1,10);
  lcd.setMeterValue(lineMeter2,40);
  lcd.setMeterValue(lineMeter3,60);
  delay(3000);
}