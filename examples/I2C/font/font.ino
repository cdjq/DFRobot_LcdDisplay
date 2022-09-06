/**！
 * @file font.ino
 * @brief 文字显示示例
 * @details 现在可支持中文和ASCII字符,韩文,日文,西里尔文,阿拉伯文,希腊语,希伯来文
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2022-07-20
 * @url https://github.com/DFRobot/DFRobot_LcdDisplay
 */

#include "DFRobot_LcdDisplay.h"

DFRobot_Lcd_IIC lcd;



void setup(void){
   Serial.begin(115200);
   lcd.begin();
   //复位屏幕
   lcd.reset();
   //初始化
   lcd.lvglInit(/*显示背景色*/0xf80);
   //绘制文字
   //第四个参数为字体大小,0-24像素高度,1-12像素高度,该参数只使用eChinese,eAscii两种文字

   //日文
   lcd.setFont(DFRobot_Lcd_IIC::eShiftJis);
   lcd.drawString(/*x=*/10,/*y=*/10,"こんにちは",/*字体大小*/1,/*前景色*/0xf800,/*背景色*/0xf80);
   //韩文
   lcd.setFont(DFRobot_Lcd_IIC::eKorean);
   lcd.drawString(/*x=*/10,/*y=*/34,"안녕하세요",/*字体大小*/1,/*前景色*/0xf800,/*背景色*/0xf80);
   
   //西里尔字母(俄罗斯语、乌克兰语、卢森尼亚语、白俄罗斯语、保加利亚语、塞尔维亚语、马其顿语等)
   lcd.setFont(DFRobot_Lcd_IIC::eCyrillic);
   lcd.drawString(/*x=*/10,/*y=*/65,"ф",/*字体大小*/1,/*前景色*/0xf800,/*背景色*/0xf80);
   //希伯来文
   lcd.setFont(DFRobot_Lcd_IIC::eHebrew);
   lcd.drawString(/*x=*/30,/*y=*/65,"פ",/*字体大小*/1,/*前景色*/0xf800,/*背景色*/0xf80);
   //阿拉伯
   lcd.setFont(DFRobot_Lcd_IIC::eAlb);
   lcd.drawString(/*x=*/50,/*y=*/65,"ز",/*字体大小*/1,/*前景色*/0xf800,/*背景色*/0xf80);
 
   //希腊语
   lcd.setFont(DFRobot_Lcd_IIC::eGreece);
   lcd.drawString(/*x=*/70,/*y=*/65,"Ϊ",/*字体大小*/1,/*前景色*/0xf800,/*背景色*/0xf80);

   
   //中文
   lcd.setFont(DFRobot_Lcd_IIC::eChinese);
   lcd.drawString(/*x=*/10,/*y=*/83,"你好世界",/*字体大小*/1,/*前景色*/0xf800,/*背景色*/0xf80);
     //ACSII
   lcd.setFont(DFRobot_Lcd_IIC::eAscii);
   lcd.drawString(/*x=*/10,/*y=*/104,"hello,world",/*字体大小*/1,/*前景色*/0xf800,/*背景色*/0xf80);
   
}

void loop(void){
  delay(3000);
}  