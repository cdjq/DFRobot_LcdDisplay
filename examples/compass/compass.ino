
/**!
 * @file compass.ino
 * @brief 指南针控件示例
 * @details 可通过传感器得到的方位值来,设置指针的指向
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2022-07-20
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

DFRobot_LcdDisplay::sControlinf_t *compss;

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
  lcd.lvglInit(/*bg_color=*/GREEN_RGB565);
  //创建指南针控件
  compss = lcd.creatCompass(/*x=*/16,/*y=*/0,/*width=*/128,/*height*/128);
  //设置指南针指针角度
}

void loop(void)
{
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