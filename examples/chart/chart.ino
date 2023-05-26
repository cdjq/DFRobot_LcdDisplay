/**!
 * @file chart.ino
 * @brief 创建一个图表
 * @details 创建一个图表,并可以向表里面添加数据来绘制柱状图/折线图
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

DFRobot_LcdDisplay::sControlinf_t* chart;

uint8_t id1 = 0, id2 = 0;

uint16_t point1[5] = { 10,90,30,10,90 };
uint16_t point2[5] = { 90,30,80,10,100 };

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
  lcd.lvglInit(GREEN_RGB565);
  /*图表样式:1-折线图,2-折线图带阴影,3-柱状图*/
  chart = lcd.creatChart(/*x轴刻度标签*/"Jan\nFeb\nMar\nApr\nMay", /*y轴刻度标签*/"100\n80\n60\n40\n20\n0", /*图表样式:1-3*/3);

  //Allocate and add a data series to the chart
  id1 = lcd.creatChartSerie(chart, /*颜色*/RED_RGB565);
  id2 = lcd.creatChartSerie(chart, BLUE_RGB565);

  //Set the value of points from an array
  lcd.addChart(chart, id1, /*每个点对应的值的数组*/point1, /*构成线的点数*/5);
  lcd.addChart(chart, id2, point2, 5);
}

void loop(void)
{
  delay(3000);
}