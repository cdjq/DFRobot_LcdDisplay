
/**！
 * @file  UDiskImg.ino
 * @brief  显示u盘的图片
 * @details  通过不同的路径名来显示不同的图片(屏幕最大尺寸320*240);
 * @n  可显示: 16位或者24位(色深)的bmp图片; 小尺寸(70*70以下)png图片
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license  The MIT License (MIT)
 * @author  [qsjhyy](yihuan.huang@dfrobot.com)
 * @version  V1.0
 * @date  2023-03-01
 * @url https://github.com/DFRobot/DFRobot_LcdDisplay
 */
#include "DFRobot_LcdDisplay.h"

DFRobot_Lcd_IIC lcd;
DFRobot_Lcd_IIC::sControlinf_t* img1;
DFRobot_Lcd_IIC::sControlinf_t* icon1;

void setup(void)
{
  Serial.begin(115200);
  lcd.begin();
  //复位屏幕
  lcd.reset();
  //初始化
  lcd.lvglInit(/*显示背景色*/WHITE_RGB565);
  delay(3000);
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
