/**!
 * @file font.ino
 * @brief 文字显示示例
 * @details 现在可支持中文和ASCII字符,韩文,日文,希腊语,西里尔文
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
  //绘制文字
  //第四个参数为字体大小, 0: 24像素高度, 1: 12像素高度, 该参数只适用eChinese,eAscii两种文字

  //日文
  lcd.setFont(DFRobot_LcdDisplay::eShiftJis);
  lcd.drawString(/*x=*/10,/*y=*/10, "こんにちは",/*字体大小*/1,/*前景色*/RED_RGB565,/*背景色*/GREEN_RGB565);
  //韩文
  lcd.setFont(DFRobot_LcdDisplay::eKorean);
  lcd.drawString(/*x=*/10,/*y=*/45, "안녕하세요",/*字体大小*/1,/*前景色*/RED_RGB565,/*背景色*/GREEN_RGB565);

  //西里尔字母(俄罗斯语、乌克兰语、卢森尼亚语、白俄罗斯语、保加利亚语、塞尔维亚语、马其顿语等)
  lcd.setFont(DFRobot_LcdDisplay::eCyrillic);
  lcd.drawString(/*x=*/10,/*y=*/80, "Привет мир",/*字体大小*/1,/*前景色*/RED_RGB565,/*背景色*/GREEN_RGB565);
  //希腊语
  lcd.setFont(DFRobot_LcdDisplay::eGreece);
  lcd.drawString(/*x=*/10,/*y=*/115, "Γεια σου κόσμε",/*字体大小*/1,/*前景色*/RED_RGB565,/*背景色*/GREEN_RGB565);

  //中文
  lcd.setFont(DFRobot_LcdDisplay::eChinese);
  lcd.drawString(/*x=*/10,/*y=*/150, "你好世界",/*字体大小*/0,/*前景色*/RED_RGB565,/*背景色*/GREEN_RGB565);
  //ACSII
  lcd.setFont(DFRobot_LcdDisplay::eAscii);
  lcd.drawString(/*x=*/10,/*y=*/195, "hello, world. 0123456789",/*字体大小*/0,/*前景色*/RED_RGB565,/*背景色*/GREEN_RGB565);
}

void loop(void)
{
  delay(3000);
}