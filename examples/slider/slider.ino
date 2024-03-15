/**!
 * @file slider.ino
 * @brief Creating a slider control and setting the slider value.
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

//填充颜色
uint32_t sliderColor = 0x00FF00;
//产生随机颜色
uint32_t generateRandomColor() {
    uint8_t r = rand() % 256;
    uint8_t g = rand() % 256;
    uint8_t b = rand() % 256;
    return (r << 16) | (g << 8) | b;
}
uint8_t sliderId[11];
void testSlider(){
  sliderId[0] = lcd.creatSlider(/*x = */0, /*y = */10, /*width=*/10, /*height=*/200, /*color*/RED);
  lcd.setSliderValue(sliderId[0],50);
  for(uint8_t i = 0; i <= 10; i++){
    sliderColor = generateRandomColor();
    lcd.updateSlider(sliderId[0],i*31, 10, 10, 200, sliderColor);
    delay(100);
  }

  for(uint8_t i = 0; i <= 10; i++){
    sliderColor = generateRandomColor();
    lcd.updateSlider(sliderId[0],310-i*31, 10, 10, 200, sliderColor);
    delay(100);
  }
  delay(1000);
  for(uint8_t i = 1; i <= 10; i++){
    sliderColor = generateRandomColor();
    sliderId[i] = lcd.creatSlider(i*31, 10, 10, 200 - i*10, sliderColor);
    delay(100);
    
  }
  delay(1000);
  for(uint8_t i = 0; i<=10; i++){
    lcd.setSliderValue(sliderId[i],rand()%100);
    delay(100);
  }
  delay(1000);
  for(uint8_t i = 0; i<=10; i++){
    sliderColor = generateRandomColor();
    lcd.updateSlider(sliderId[i], 10, i*23, 310 -i*20 , 10, sliderColor);
    delay(100);
  }
  delay(1000);
  for(uint8_t i = 0 ; i <= 10; i++){
    lcd.deleteSlider(sliderId[i]);
    delay(100);
  }
  
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
  lcd.setBackgroundColor(WHITE);
  testSlider();
}

void loop(void)
{
  testSlider();
  delay(1000);
}