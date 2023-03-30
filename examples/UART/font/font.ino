/**!
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

DFRobot_Lcd_UART lcd;
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



void setup(void)
{
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
  lcd.lvglInit(/*显示背景色*/0xf80);
  //绘制文字
  //第四个参数为字体大小,0-24像素高度,1-12像素高度

  //日文
  lcd.setFont(DFRobot_Lcd_UART::eShiftJis);
  lcd.drawString(/*x=*/10,/*y=*/10, "こんにちは",/*字体大小*/1,/*前景色*/0xf800,/*背景色*/0xf80);
  //韩文
  lcd.setFont(DFRobot_Lcd_UART::eKorean);
  lcd.drawString(/*x=*/10,/*y=*/34, "안녕하세요",/*字体大小*/1,/*前景色*/0xf800,/*背景色*/0xf80);

  //西里尔字母(俄罗斯语、乌克兰语、卢森尼亚语、白俄罗斯语、保加利亚语、塞尔维亚语、马其顿语等)
  lcd.setFont(DFRobot_Lcd_UART::eCyrillic);
  lcd.drawString(/*x=*/10,/*y=*/65, "ф",/*字体大小*/1,/*前景色*/0xf800,/*背景色*/0xf80);
  //希伯来文
  lcd.setFont(DFRobot_Lcd_UART::eHebrew);
  lcd.drawString(/*x=*/30,/*y=*/65, "פ",/*字体大小*/1,/*前景色*/0xf800,/*背景色*/0xf80);
  //阿拉伯
  lcd.setFont(DFRobot_Lcd_UART::eAlb);
  lcd.drawString(/*x=*/50,/*y=*/65, "ز",/*字体大小*/1,/*前景色*/0xf800,/*背景色*/0xf80);

  //希腊语
  lcd.setFont(DFRobot_Lcd_UART::eGreece);
  lcd.drawString(/*x=*/70,/*y=*/65, "Ϊ",/*字体大小*/1,/*前景色*/0xf800,/*背景色*/0xf80);


  //中文
  lcd.setFont(DFRobot_Lcd_UART::eChinese);
  lcd.drawString(/*x=*/10,/*y=*/83, "你好世界",/*字体大小*/1,/*前景色*/0xf800,/*背景色*/0xf80);
  //ACSII
  lcd.setFont(DFRobot_Lcd_UART::eAscii);
  lcd.drawString(/*x=*/10,/*y=*/104, "hello,world",/*字体大小*/1,/*前景色*/0xf800,/*背景色*/0xf80);

}

void loop(void)
{
  delay(3000);
}