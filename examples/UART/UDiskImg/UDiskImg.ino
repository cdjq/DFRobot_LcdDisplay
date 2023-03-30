/**!
 * @file UDiskImg.ino
 * @brief  显示u盘的图片
 * @details  通过不同的路径名来显示不同的图片(屏幕最大尺寸320*240);
 * @n  可显示: 16位或者24位(色深)的bmp图片; 小尺寸(70*70以下)png图片
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author  [qsjhyy](yihuan.huang@dfrobot.com)
 * @version  V1.0
 * @date  2023-03-01
 * @url https://github.com/DFRobot/DFRobot_LcdDisplay
 */
#include "DFRobot_LcdDisplay.h"

DFRobot_Lcd_UART lcd;
DFRobot_Lcd_UART::sControlinf_t* img1;
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
  lcd.lvglInit(/*显示背景色*/WHITE_RGB565);
  // 显示u盘的图片, 可显示: 16位或者24位(色深)的bmp图片(屏幕最大尺寸320*240), 小尺寸(70*70以下)png图片
  // 最后一个参数为缩放指数范围为(128~512),128-缩小一倍,512-放大一倍
  img1 = lcd.drawDiskImg(/*x=*/0, /*y=*/0, /*文件路径名(String类型)*/"/2.bmp", /*缩放指数*/256);
  delay(1000);
  lcd.lvglDelete(img1);
  Serial.println("/1.bmp");
  img1 = lcd.drawDiskImg(0, 0, "/1.bmp", 256);
  delay(1000);
  lcd.lvglDelete(img1);
  Serial.println("/2.bmp");
  img1 = lcd.drawDiskImg(0, 0, "/2.bmp", 256);
}

void loop(void)
{
}
