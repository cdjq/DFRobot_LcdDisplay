
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
DFRobot_Lcd_IIC lcd;
DFRobot_Lcd_IIC::sControlinf_t *compss;

void setup(void){
  Serial.begin(115200);
  lcd.begin();
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