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

void loop(void){
    testTriangles();
}

//填充颜色
uint32_t fillColor = 0x00FF00;
//边框颜色
uint32_t borderColor = 0xFF0000;
//产生随机颜色
uint32_t generateRandomColor() {
    uint8_t r = rand() % 256;
    uint8_t g = rand() % 256;
    uint8_t b = rand() % 256;
    return (r << 16) | (g << 8) | b;
}

uint8_t trianglesId[10];
uint8_t triangles1;
void testTriangles(){
  //以屏幕顶端中心为顶点，屏幕底端为另外两顶点画一个三角形
  triangles1 = lcd.drawTriangle(160, 0, 0, 239, 319, 239, 1, borderColor, 0, fillColor);
  //更新这个三角形的三个顶点，以达到缩放的效果
  for (uint8_t i=0; i <10; i++){
    lcd.updateTriangle(trianglesId[0], 160, i*12, i*16, 239 - i*12,319-i*16, 239-i*12, 1, borderColor, 0, fillColor);
  }
  delay(1000);  
  //新增三角形，达到多个同心相似三角形
  for(uint8_t i = 9; i>0; i--){
    trianglesId[10-i] = lcd.drawTriangle(160, i*12, i*16, 239 - i*12,319-i*16, 239-i*12, 1, borderColor, 0, fillColor);
  }
  delay(1000);
  //使用随机色填充这些三角形  
  for(uint8_t i = 0; i<10; i++){
    fillColor = generateRandomColor();
    lcd.updateTriangle(trianglesId[i], 160, i*12, i*16, 239 - i*12,319-i*16, 239-i*12, 1, borderColor, 1, fillColor);
  }
  delay(1000);
  //一个一个删除这些三角形  
  for(uint8_t i = 0 ;i < 10;i++){
    lcd.deleteTriangle(trianglesId[i]);
  }
  delay(1000);
}
