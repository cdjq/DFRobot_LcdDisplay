
/**!
 * @file gauge.ino
 * @brief Dial Control
 * @details Can be used for displaying values such as speed and pressure.
 * @n  Most parameters are related to the screen size (320*240). Please ensure that the custom parameters do not exceed the screen limits.
 * @n  After scaling the dial widget, the display quality may degrade. Please use appropriate parameters
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

uint32_t bgColor = GREEN;
uint32_t pointerColor = RED;
uint32_t generateRandomColor() {
    uint8_t r = rand() % 256;
    uint8_t g = rand() % 256;
    uint8_t b = rand() % 256;
    return (r << 16) | (g << 8) | b;
}

uint8_t gaugeId[13];
void testGauge(){
    uint16_t x = 0;
    uint16_t y = 0;
    //在（0，0）点创建一个仪表盘
    gaugeId[0] = lcd.creatGauge(0, 0, 120, 0, 100, pointerColor, bgColor);
    //设置该仪表盘的值为40
    lcd.setGaugeValue(gaugeId[0],40);
    //更改仪表盘的坐标，使其达到移动的效果
    for(uint8_t i = 0; i < 7; i++){
      lcd.updateGauge(gaugeId[0], i*32, 0, 120, 0, 100, pointerColor, bgColor);
      delay(100);
    }
    //删除这个仪表盘
    lcd.deleteGauge(gaugeId[0]);
    delay(100);
    //创建多个仪表盘，使用随机指针颜色、随机背景颜色、设置表盘值为随机，使其铺满整个屏幕
    for(uint8_t i = 0; i < 12; i++){
      bgColor = generateRandomColor();
      pointerColor = generateRandomColor();
      gaugeId[i] = lcd.creatGauge(x, y, 120, 0, 60, pointerColor, bgColor);
      lcd.setGaugeValue(gaugeId[i],rand()%60);
      if((i+1)%4 == 0){
          y += 80;
          x = 0;
      }else{
          x += 80;
      }
      delay(100);
    }
    delay(1000);
    //一个一个删除仪表盘
    for(uint8_t i = 0; i < 12; i++){
      lcd.deleteGauge(gaugeId[i]);
      delay(100);
    }
    //再创建一个仪表盘
    gaugeId[0] = lcd.creatGauge(0, 0, 120, 0, 100, pointerColor, bgColor);
    //更改这个仪表盘的大小，使其达到缩放的现象
    for(uint8_t i = 0; i < 10; i++){
      lcd.updateGauge(gaugeId[0], 0, 0, 120+i*12, 0, 100, pointerColor, bgColor);
      delay(100);
    }
    //随机设置该仪表盘的指针值
    for(uint8_t i = 0; i < 10; i++){
      lcd.setGaugeValue(gaugeId[0],rand()%100);
      delay(100);
    }
    //删除仪表盘
    lcd.deleteGauge(gaugeId[0]);
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
  //Initializing 
  lcd.cleanScreen();
  delay(500);
  lcd.setBackgroundColor(WHITE);
  
}

void loop(void)
{
  //Setting the value of the gauge.
  testGauge();
  delay(1000);
}