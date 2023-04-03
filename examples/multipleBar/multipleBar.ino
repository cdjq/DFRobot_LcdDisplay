
/**!
 * @file multipleBar.ino
 * @brief 进度条控件示例
 * @details 创建三个进度条控件,并分别控制每个控件显示不同的值
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

DFRobot_LcdDisplay::sControlinf_t *bar1, *bar2, *bar3;   // 进度条句柄

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
  lcd.lvglInit(/*显示背景颜色*/CYAN_RGB565);
  //创建进度条控件
  bar1 = lcd.creatBar(/*x = */10,/*y = */10,/*width=*/270,/*height=*/50,/*进度条颜色*/ORANGE_RGB565);
  bar2 = lcd.creatBar(10,90,270,50,YELLOW_RGB565);
  bar3 = lcd.creatBar(10,170,270,50,LIGHTGREY_RGB565);
}

void loop(void)
{
  //设置进度条值,可带单位,但必须由数字开始
  lcd.setBar(bar1,"80°C");
  lcd.setBar(bar2,"10°C");
  lcd.setBar(bar3,"20°C");
  delay(2000);

  lcd.setBar(bar1,"30°C");
  lcd.setBar(bar2,"80°C");
  lcd.setBar(bar3,"50°C");
  delay(2000);
}
