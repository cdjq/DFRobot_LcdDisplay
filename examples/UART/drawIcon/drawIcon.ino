
/**！
 * @file drawIcon.ino
 * @brief 图标显示示例示例
 * @details 通过不同的图标编号来显示不同的值
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2022-07-20
 * @url https://github.com/DFRobot/DFRobot_LcdDisplay
 */

#include "DFRobot_LcdDisplay.h"

  // eIconUnhappy,  /**<不开心*/
  // eIconCrying,  /**<哭泣*/
  // eIconLaugh,  /**<大笑*/
  // eIconWhimsy,  /**<搞怪*/
  // eIconSurprised,  /**<惊讶*/
  // eIconSleep,  /**<睡眠*/
  // eIconSmile,  /**<微笑*/
  // eIconNoInductive,  /**<无感*/
  // eIconFierce,  /**<凶狠*/
  //传感器图标
  // eIconWeighing,/**<称重*/
  // eIconLightBulb,/**<灯泡*/
  // eIconBattery,/**<电池*/
  // eIconCarbonDioxide,/**<二氧化碳*/
  // eIconWind,/**<风*/
  // eIconMountain,/**<高山*/
  // eIconAlcohol,/**<酒精*/
  // eIconDistance,/**<距离*/
  // eIconMicrophone,/**<麦克风*/
  // eIconWater,/**<水*/
  // eIconThermometer,/**<温度计*/
  // eIconHeartRate,/**<心率*/
  // eIconPressure,/**<压力*/
  // eIconLiquid,/**<液体*/
  // eIconRaindrops,/**<雨滴*/
  // eIconCompass,/**<指南针*/
  //其它图标
  // eIconClock,/**<闹钟*/
  // eIconRunning,/**<跑步*/
  // eIconCar,/**<车*/
  // eIconCalendar,/**<日历*/
  // eIconAlarm,/**<报警器*/
  // eIconBluetooth,/**<蓝牙*/
  
  //天气图标
  // eIconRainbow,/**<彩虹*/
  // eIconRains ,/**<大雨*/
  // eIconCloudy,/**<多云*/
  // eIconWindy,/**<刮风*/
  // eIconSun,/**<晴*/
  // eIconLightning,/**<闪电*/
  // eIconSnows,/**<雪花*/
  // eIconOvercast,/**<阴天*/
  // eIconUmbrella,/**<雨伞*/
  // eIconMoon,/**<月亮*/
DFRobot_Lcd_UART lcd;
DFRobot_Lcd_UART::sControlinf_t *icon1;
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

void setup(void){
  //Rx and tx should be mapping into D2 and D3 when using Firebeetle-ESP32
  #if (defined ESP32)
     Serial1.begin(9600, SERIAL_8N1, /*rx =*/D2, /*tx =*/D3);
  #else
  Serial1.begin(9600);
  #endif
  Serial.begin(115200);
  
  lcd.begin(Serial1);
   //复位屏幕
   lcd.reset();
   //初始化
   lcd.lvglInit(/*显示背景色*/WHITE_RGB565);
   //绘制图标
   //最后一个参数为缩放指数范围为(128~512),128-缩小一倍,512-放大一倍
   lcd.drawIcon(/*x=*/0,/*y =*/32,/*图标编号*/DFRobot_Lcd_UART::eIconUnhappy,/*缩放指数*/256);
   lcd.drawIcon(0,64,DFRobot_Lcd_UART::eIconCrying,256);
   lcd.drawIcon(0,96,DFRobot_Lcd_UART::eIconLaugh,256);
   lcd.drawIcon(0,128,DFRobot_Lcd_UART::eIconFierce,256);

   lcd.drawIcon(32,32,DFRobot_Lcd_UART::eIconThermometer,256);
   lcd.drawIcon(32,64,DFRobot_Lcd_UART::eIconAlarm,256);
   lcd.drawIcon(32,96,DFRobot_Lcd_UART::eIconAlcohol,256);
   lcd.drawIcon(32,128,DFRobot_Lcd_UART::eIconCompass,256);
   
   lcd.drawIcon(64,32,DFRobot_Lcd_UART::eIconMoon,256);
   lcd.drawIcon(64,64,DFRobot_Lcd_UART::eIconOvercast,256);
   icon1 = lcd.drawIcon(64,96,DFRobot_Lcd_UART::eIconLightning,256);
   lcd.drawIcon(64,128,DFRobot_Lcd_UART::eIconSun,256);

   lcd.drawIcon(0,0,DFRobot_Lcd_UART::eIconRainbow,256);
   lcd.drawIcon(32,0,DFRobot_Lcd_UART::eIconCar,256);
   lcd.drawIcon(64,0,DFRobot_Lcd_UART::eIconHeartRate,256);
   lcd.drawIcon(96,0,DFRobot_Lcd_UART::eIconRaindrops,256);
   lcd.drawIcon(128,0,DFRobot_Lcd_UART::eIconWeighing,256);

   lcd.drawIcon(96,32,DFRobot_Lcd_UART::eIconMountain,256);
   lcd.drawIcon(128,32,DFRobot_Lcd_UART::eIconMicrophone,256);

    lcd.drawIcon(96,64,DFRobot_Lcd_UART::eIconWindy,256);
   lcd.drawIcon(128,64,DFRobot_Lcd_UART::eIconBattery,256);

    lcd.drawIcon(96,96,DFRobot_Lcd_UART::eIconCompass,256);
  lcd.drawIcon(128,96,DFRobot_Lcd_UART::eIconCarbonDioxide,256);
}

void loop(void){


  delay(5000);
   lcd.lvglDelete(icon1);
   icon1 = lcd.drawIcon(64,96,DFRobot_Lcd_UART::eIconLaugh,256);
   delay(5000);
    lcd.lvglDelete(icon1);
    icon1 = lcd.drawIcon(64,96,DFRobot_Lcd_UART::eIconRaindrops,256);


}