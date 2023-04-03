/**!
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

DFRobot_LcdDisplay::sControlinf_t *lineMeter1, *lineMeter2, *lineMeter3;

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
  lcd.lvglInit(/*显示背景色*/CYAN_RGB565);

  //创建线形仪表控件 
  lineMeter1 = lcd.creatLineMeter(/*x*/10,/*y*/100,/*width*/120,/*height*/120,/*颜色*/CYAN_RGB565);
  //设置表盘参数
  lcd.setMeterScale(lineMeter1,/*angle of the scale*/270,/*起始角度*/0,/*end of angle*/100);

  lineMeter2 = lcd.creatLineMeter(100,15,120,120,GREEN_RGB565);
  lcd.setMeterScale(lineMeter2,270,0,100);
  lineMeter3 = lcd.creatLineMeter(195,100,120,120,ORANGE_RGB565);
  lcd.setMeterScale(lineMeter3, 270, 0, 100);

}

void loop(void)
{
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