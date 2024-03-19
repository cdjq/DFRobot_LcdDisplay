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

// 切换背景颜色
void testBackgroundColor(){
    lcd.setBackgroundColor(RED);
    delay(1000);
    lcd.setBackgroundColor(GREEN);
    delay(1000);
    lcd.setBackgroundColor(BLUE);
    delay(1000);
    lcd.setBackgroundColor(WHITE);
    delay(1000);
}

// 切换背景图片
void testBackgroundImg(){
    //内部存储的图片
    lcd.setBackgroundImg(0,"bgDream.png");
    delay(1000);
    //u盘存储的图片
    lcd.setBackgroundImg(1,"fish.png");
    delay(1000);
    //u盘存储的图片
    lcd.setBackgroundImg(1,"cat.png");
    delay(1000);
    //内部存储的图片
    lcd.setBackgroundImg(0,"bgScenery.png");
    delay(1000);
    //内部存储的图片
    lcd.setBackgroundImg(0,"bgCity.png");
    delay(1000);
    //内部存储的图片
    lcd.setBackgroundImg(0,"bgTechnology.png");
    delay(1000);
        //内部存储的图片
    lcd.setBackgroundImg(0,"bgScience.png");
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
    lcd.drawString( 10, 10, "您好，世界hello,World012\n안녕하세요こんにちは\nПривет мирΓεια σου κόσμε", 0, 0xFFFF00);
}

void loop(void)
{
    testBackgroundColor();
    testBackgroundImg();
}