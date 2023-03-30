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
DFRobot_Lcd_UART lcd;
DFRobot_Lcd_UART::sControlinf_t *chart;
uint8_t id1 = 0;
uint8_t id2 = 0;
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
uint16_t point1[5]={10,90,30,10,90};
uint16_t point2[5]={90,30,80,10,99};

void setup(void){
  //Rx and tx should be mapping into D2 and D3 when using Firebeetle-ESP32
  #if (defined ESP32)
     Serial1.begin(9600, SERIAL_8N1, /*rx =*/D2, /*tx =*/D3);
  #else
  Serial1.begin(9600);
  #endif
  Serial.begin(115200);
  
  lcd.begin(Serial1);
  lcd.reset();
  lcd.lvglInit(0xf8);
  chart = lcd.creatChart(/*y轴刻度标签*/"99\n80\n60\n40\n20",/*x轴刻度标签*/"Jan\nFeb\nMar\nApr\nMay",/*图标样式*/3);
  //Allocate and add a data series to the chart
  id1 = lcd.creatChartSerie(chart,/*颜色*/0xf800);
  id2 = lcd.creatChartSerie(chart,0xf8);


  //Set the value of points from an array
  //添加一条线在图表中
  lcd.addChart(chart,id1,/**/point1,/*构成线的点数*/5);
  lcd.addChart(chart,id2,point2,5);
}

void loop(void){
  delay(3000);
}