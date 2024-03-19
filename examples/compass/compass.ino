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

uint8_t compassId[21];

void testCompass(){
    uint16_t y = 0;
    uint16_t x = 0;
    //在（0，0）点创建一个直径为64的指南针
    compassId[0] = lcd.creatCompass(x, y, 64);
    //更改这个指南针的坐标，使其移动起来
    for(uint8_t i = 0; i < 20; i++){
      lcd.updateCompass(compassId[0], x, y, 64);
      if((i+1)%5 == 0){
        y += 64;
        x = 0;
      }else{
        x += 64;
      }
      delay(200);
    }
    //删除这个指南针
    lcd.deleteCompass(compassId[0]);
    delay(200);
    x = 0;
    y = 0;
    //在不同的坐标点上创建指南针，使其满屏显示
    for(uint8_t i = 0; i < 20; i++){
      compassId[i] = lcd.creatCompass(x, y, 64);
      if((i+1)%5 == 0){
        y += 64;
        x = 0;
      }else{
        x += 64;
      }
      delay(200);
    }
    delay(1000);
	//一个一个删除指南针
    for(uint8_t i = 0; i < 20; i++){
      lcd.deleteCompass(compassId[i]);
      delay(200);
    }
    //在（0，0）点创建一个直径为64的指南针
    compassId[0] = lcd.creatCompass(0, 0, 30);
    //更改这个指南针，使其达到缩放的效果
    for(uint8_t i = 0 ; i<8; i++){
        lcd.updateCompass(compassId[0], 0, 0, 30*(i+1));
        delay(100);
    }
    for(uint8_t i = 0; i < 36; i++){
        lcd.setCompassScale(compassId[0],i*100);
        delay(50);
    }
    lcd.deleteCompass(compassId[0]);
    delay(2000);
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
  delay(200);
  //Initializing 
  lcd.setBackgroundColor(WHITE);

  testCompass();
}


void loop(void)
{
	testCompass();
    delay(2000);
}