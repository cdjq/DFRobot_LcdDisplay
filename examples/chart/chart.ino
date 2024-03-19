/**!
 * @file chart.ino
 * @brief Creating a chart
 * @details Creating a chart,And being able to add data to the chart to draw a bar chart/line chart.
 * @n  Most parameters are related to the screen size (320*240). Please ensure that the custom parameters do not exceed the screen limits.
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @maintainer [qsjhyy](yihuan.huang@dfrobot.com)
 * @version  V1.0
 * @date  2023-05-29
 * @url https://github.com/DFRobot/DFRobot_LcdDisplay
 */
#include "DFRobot_LcdDisplay.h"

//#define I2C_COMMUNICATION  // I2C communication. If you want to use UART communication, comment out this line of code.

#ifdef  I2C_COMMUNICATION
  /**
    * Using the I2C interface.
    */
  DFRobot_Lcd_IIC lcd(&Wire, /*I2CAddr*/ 0x2c);
#else
  /**
    * Using the UART interface.
    */
  #if ((defined ARDUINO_AVR_UNO) || (defined ESP8266) || (defined ARDUINO_BBC_MICROBIT_V2))
    #include <SoftwareSerial.h>
    SoftwareSerial softSerial(/*rx =*/4, /*tx =*/5);
    #define FPSerial softSerial
  #else
    #define FPSerial Serial1
  #endif
  DFRobot_Lcd_UART lcd(FPSerial);
#endif

DFRobot_LcdDisplay::sControlinf_t* chart;

uint8_t chartId1 = 0;
uint8_t chartId2 = 0;
uint8_t chartId3 = 0;
uint8_t id1_1 = 0, id1_2 = 0, id2_1 = 0, id2_2 = 0, id3_1 = 0, id3_2 = 0;

uint16_t point1[5] = { 10,90,30,0,90 };
uint16_t point2[5] = { 90,30,80,10,100 };


void testChart(){
    //创建一个图表，设置背景颜色为白色，模式为折线图模式
    chartId1 = lcd.creatChart(/*X-axis tick labels*/"Jan\nFeb\nMar\nApr\nMay", /*Y-axis tick labels*/"100\n80\n60\n40\n20\n0",/*background Color*/ 0xFFFFFF,/*Chart style:1-3*/1);
	//在这个图表上创建一个颜色为红色的数据系列
    id1_1 = lcd.creatChartSeries(chartId1, /*color*/0xFF0000);
	//往这个数据系列上添加5个点
    lcd.addChartSeriesData(chartId1, id1_1, point2, 5);
    delay(2000);
    //更新这个表格的数据系列的颜色为蓝色
    lcd.updateChartSeries(chartId1, id1_1, 0x0000FF);
    //更新这个表格为柱状图并且背景设置为绿色
    lcd.updateChart(chartId1, 0x00FF00, 2);
	  delay(2000);
    //更新这个表格的数据系列的颜色为绿色
    lcd.updateChartSeries(chartId1, id1_1, 0x00FF00);
    //更新这个表格为折线图并且背景设置为蓝色
    lcd.updateChart(chartId1, 0x0000FF, 3);
    //更新第2个点的值，从0开始计数
    for(uint8_t i = 0; i<5; i++){
        lcd.updateChartPoint(chartId1, id1_1, 2, 20*i);
        delay(1000);
    }

    //创建第二个表格
    chartId2 = lcd.creatChart("Jun\nJul\nAug\nSep", "100\n80\n60\n40\n20\n0",/*background Color*/ 0xFFFF00,/*Chart style:1-3*/1);
    //在这个表格上创建一个颜色为红色的数据系列
    id2_1 = lcd.creatChartSeries(chartId2, /*color*/0xFF0000);
    //在这个表格上创建一个颜色为蓝色的数据系列
    id2_2 = lcd.creatChartSeries(chartId2, /*color*/0x0000FF);
    //给数据系列id2_1添加数据
    lcd.addChartSeriesData(chartId2, id2_1, point1, 4);
    //给数据系列id2_2添加数据
    lcd.addChartSeriesData(chartId2, id2_2, point2, 4);
    delay(1000);

    //创建第三个表格
    chartId3 = lcd.creatChart("Jun\nJul\nAug\nSep", "100\n80\n60\n40\n20\n0",/*background Color*/ 0xFFFF00,/*Chart style:1-3*/2);
    //在这个表格上创建一个颜色为红色的数据系列
    id3_1 = lcd.creatChartSeries(chartId3, /*color*/0xFF0000);
    //在这个表格上创建一个颜色为蓝色的数据系列
    id3_2 = lcd.creatChartSeries(chartId3, /*color*/0x0000FF);
    //给数据系列id2_1添加数据
    lcd.addChartSeriesData(chartId3, id3_1, point1, 4);
    //给数据系列id2_2添加数据
    lcd.addChartSeriesData(chartId3, id3_2, point2, 4);
    delay(1000);
    //设置图表1置顶显示
    lcd.setTopChart(chartId1);
    delay(2000);
    //设置图表2置顶显示
    lcd.setTopChart(chartId2);
    delay(2000);
    //设置图表3置顶显示
    lcd.setTopChart(chartId3);
    delay(2000);
	  //删除图表3
    lcd.deleteChart(chartId3);
    delay(1000);
    //删除图表2
    lcd.deleteChart(chartId2);
    delay(1000);
    //删除图表1
    lcd.deleteChart(chartId1);
    delay(1000);
    
}
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
  lcd.cleanScreen();
  delay(500);
  lcd.setBackgroundColor(WHITE);
  
  
}

void loop(void)
{
	testChart();
	delay(1000);
}