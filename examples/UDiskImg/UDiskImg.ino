
/**!
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

#define I2C_COMMUNICATION  // I2C通信。如果你想使用UART通信，注释掉这行代码。

#ifdef  I2C_COMMUNICATION
  /**
    * 使用 i2c 接口
    */
  DFRobot_Lcd_IIC lcd(&Wire, /*I2CAddr*/ 0x2c);
#else
  /**
    * 使用 uart 接口
    */
  #if ((defined ARDUINO_AVR_UNO) || (defined ESP8266))
    #include <SoftwareSerial.h>
    SoftwareSerial softSerial(/*rx =*/4, /*tx =*/5);
    #define FPSerial softSerial
  #else
    #define FPSerial Serial1
  #endif
  DFRobot_Lcd_UART lcd(FPSerial);
#endif

DFRobot_LcdDisplay::sControlinf_t *img1, *img2;

/**
 * User-selectable macro definition color
 * BLACK_RGB565 BLUE_RGB565 RED_RGB565 GREEN_RGB565 CYAN_RGB565 MAGENTA_RGB565
 * YELLOW_RGB565 WHITE_RGB565 NAVY_RGB565 DARKGREEN_RGB565 DARKCYAN_RGB565 MAROON_RGB565
 * PURPLE_RGB565 OLIVE_RGB565 LIGHTGREY_RGB565 DARKGREY_RGB565 ORANGE_RGB565
 * GREENYELLOW_RGB565 DCYAN_RGB565
 */
void setup(void)
{
  #ifndef  I2C_COMMUNICATION
    #if (defined ESP32)
      FPSerial.begin(9600, SERIAL_8N1, /*rx =*/D2, /*tx =*/D3);
    #else
      FPSerial.begin(9600);
    #endif
  #endif

  Serial.begin(115200);

  lcd.begin();
  //初始化
  lcd.lvglInit(/*显示背景色*/WHITE_RGB565);
  delay(3000);
  // 显示u盘的图片, 可显示: 16位或者24位(色深)的bmp图片(屏幕最大尺寸320*240), 小尺寸(70*70以下)png图片
  // 最后一个参数为缩放指数范围为(128~512),128-缩小一倍,512-放大一倍
  img1 = lcd.drawDiskImg(/*x=*/0, /*y=*/0, /*文件路径名(String类型)*/"/sea.bmp", /*缩放指数*/256);
  delay(1000);
  lcd.lvglDelete(img1);
  img2 = lcd.drawDiskImg(0, 0, "/plants.png", 256);
  delay(1000);
  img1 = lcd.drawDiskImg(0, 0, "/cat.bmp", 256);
}

void loop(void)
{
}
