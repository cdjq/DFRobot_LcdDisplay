
/**!
 * @file drawIcon.ino
 * @brief 图标显示示例示例
 * @details 通过不同的图标编号来显示不同的图标
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

 // 已经烧入固件里面的图标
#if 0   // 注释, 只能是0
    // 安全safe icon
eIconDial, eIconDisabledAccess, eIconDown, eIconExit, eIconExitLeft, eIconExportRight, eIconFireescapeStairs,
eIconFireExtinguisher, eIconFire, eIconHydrant, eIconLeft, eIconLifeladder, eIconMedicalCare, eIconRight, eIconUp,

// 表情expression icon
eIconAngry, eIconBlink, eIconCry, eIconCute, eIconDepressed, eIconDizzy, eIconEmbarrassed, eIconFunny,
eIconHappy, eIconKind, eIconLike, eIconPlayful, eIconResentful, eIconSad, eIconSerious, eIconShy, eIconSmile, eIconSurprised,
eIconTear, eIconTired,

// 传感器sensor icon
eIconAlcohol, eIconAntennaReceiver, eIconAntenna, eIconBattery, eIconBluetooth, eIconBulb, eIconCarbonDioxide,
eIconColor, eIconCompass, eIconDistance, eIconDust, eIconHeartRate, eIconLiquid, eIconMicrophone, eIconMountain,
eIconPressure, eIconRaindrops, eIconThermometer, eIconWeigh, eIconWifi, eIconWind,

// 动物animal icon
eIconBee, eIconBird, eIconButterfly, eIconCaterpillar, eIconChick, eIconChicken, eIconChipmunk,
eIconCoccinellaSeptempunctata, eIconCow, eIconDog, eIconDolphin, eIconDragon, eIconElephant, eIconHorse,
eIconMonkey, eIconOwl, eIconPig, eIconRabbit, eIconRooster, eIconSheep, eIconSnail, eIconSnake, eIconTurtle,
eIconUnicorn, eIconWasp, eIconWorm,

// 环境与自然Environment and Nature icon
eIconBiofuel, eIconCarElectric, eIconDesertLandscape, eIconDirections, eIconEarth, eIconEcoAccumulatorBattery,
eIconGlassRecycle, eIconGlobalWarming, eIconGreenPower, eIconGreenEnergy, eIconGreenhouse, eIconIcebergMelting,
eIconLandscape, eIconNoPlastic, eIconNoSewage, eIconProtectEarth, eIconRainLandscape, eIconRecyclingCar,
eIconRelaxLandscape, eIconSolar, eIconTap, eIconTrash, eIconTreeLandscape, eIconWaterRecycle, eIconWinterForest,

// 季节 season icon
eIconBeachBed, eIconBeachUmbrella8, eIconChristmasStocking, eIconCoconut, eIconFan, eIconFireplace, eIconGlove,
eIconHat, eIconIceCream, eIconLifeBuoy, eIconSanta, eIconShorts, eIconSlipper, eIconSnowman, eIconSunny,
eIconSweater, eIconSwimming, eIconSwimwear, eIconThanksgiving, eIconThermometerSnow, eIconWatermelon,

// 交通工具 transport icon
eIconAirplane, eIconAmbulance, eIconAutomobile, eIconBicycle, eIconBus, eIconBusStop, eIconDeliveryTruck,
eIconFireEngine, eIconHelicopter, eIconHighSpeedRailway, eIconHorizontalTrafficLight, eIconKickScooter,
eIconMotorScooter, eIconMotorway, eIconOncomingTaxi, eIconPoliceCar, eIconTractor, eIconVerticalTrafficLight,

// 农业Agriculture icon
eIconBarn, eIconBarrier, eIconBoots, eIconCutWood, eIconEggs, eIconFertilizer, eIconFruits, eIconMilkContainer,
eIconPlant, eIconSheafOfRice, eIconSprout, eIconStorageBucket, eIconTool, eIconTractor2, eIconVegetables,
eIconWateringCan, eIconWellWater, eIconWheelbarrow,

// 人物形象 people icon
eIconDesigner, eIconDiver, eIconDoctor, eIconLabScientist, eIconMagicianMale, eIconNurse, eIconPhotographerMale,
eIconPolice, eIconProgrammerMale, eIconSoldier, eIconSuccessGoalBusinessman, eIconSurgeon, eIconTeacher,

// 食物 food icon
eIconAvocado, eIconBanana, eIconBeerMug, eIconBentoBox, eIconBirthdayCake, eIconBread, eIconCake, eIconCarrot,
eIconCheeseWedge, eIconCherry,/**<樱桃*/ eIconChocolateBar,/**<巧克力*/ eIconCutOfMeat,/**<肉*/ eIconEarOfCorn,/**<玉米*/
eIconEgg,/**<鸡蛋*/ eIconFrenchFries,/**<薯条*/ eIconGrapes,/**<葡萄*/ eIconGreenSalad,/**<绿沙拉*/ eIconHamburger,/**<汉堡包*/
eIconHotBeverage,/**<热饮料*/ eIconPeach,/**<桃子*/ eIconPineapple,/**<菠萝*/ eIconPopcorn,/**<爆米花*/ eIconPotato,/**<土豆*/
eIconRedApple,/**<红苹果*/ eIconSalad,/**<沙拉*/ eIconShaomai,/**<烧卖*/ eIconSandwich,/**<三明治*/ eIconShortcake,/**<短蛋糕*/
eIconStrawberry,/**<草莓*/

//数字图形图标
eIconArrowDown,/**<向下箭头*/    eIconArrowLeft,/**<向左箭头*/    eIconArrowRight,/**<向右箭头*/    eIconArrowUp,/**<向上箭头*/
eIconDiamond,/**<菱形*/    eIconEight,/**<数字8*/    eIconFive,/**<数字5*/    eIconFivePointedStar,/**<五角星*/    eIconHeart,/**<心形*/
eIconNine,/**<数字9*/    eIconFour,/**<数字4*/    eIconOctagon,/**<八边形*/    eIconOne,/**<数字1*/    eIconPentagon,/**<五边形*/
eIconRectangle,/**<矩形*/    eIconSeven,/**<数字7*/    eIconSix,/**<数字6*/    eIconSquare,/**<正方形*/    eIconThree,/**<数字3*/
eIconTriangle,/**<三角形*/    eIconTwo,/**<数字2*/    eIconWindmillShape,/**<风车形*/    eIconZero,/**<数字0*/

//天气图标
eIconCloudy,/**<多云*/    eIconMoon,/**<月亮*/    eIconLightning,/**<闪电*/    eIconMoonCloudy,/**<多云夜晚*/
eIconRainUmbrella,/**<下雨有伞*/    eIconRainbow1,/**<彩虹1*/    eIconRainbow2,/**<彩虹2*/    eIconRainy,/**<下雨*/
eIconSnow,/**<雪*/    eIconSnowy,/**<有雪的天气*/    eIconSunnyCloudy,/**<晴天多云*/    eIconWhirlwind,/**<旋风*/

// 音乐图标
eIconAccordion, eIconBassDrum, eIconCDDiskDVD, eIconCello, eIconElectricGuitar, eIconFlute, eIconGuitar,
eIconHarmonica, eIconHarp, eIconHeadphones, eIconMelodica, eIconMusic, eIconMusicStereo, eIconMusicTurntable,
eIconMuteSoundOff, eIconPiano, eIconSaxophone, eIconSpeakerAudio, eIconTrumpet, eIconXylophone,

// 运动图标
eIconBadminton, eIconBasketball, eIconBowling, eIconChess, eIconCycling, eIconDarts, eIconDiving, eIconDumbbell,
eIconGolf, eIconIceHockey, eIconKarate, eIconPingPong, eIconRunning, eIconSoccer, eIconTennis, eIconYoga,

// 植物图标
eIconBranch, eIconCactus1, eIconCactus2, eIconCactus3, eIconDeciduousTree, eIconDecorativePottedPlants, eIconFlower,
eIconGrass, eIconGrass1, eIconLeaf, eIconPalmTree, eIconPottedPlantFlower, eIconRose, eIconRose1, eIconSunflower,
eIconSunflower1, eIconTulips,
#endif

DFRobot_LcdDisplay::sControlinf_t* icon1;

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
  //绘制图标
  //最后一个参数为缩放指数范围为(128~512),128-缩小一倍,512-放大一倍
  icon1 = lcd.drawIcon(/*x=*/0,/*y =*/0,/*图标编号*/DFRobot_LcdDisplay::eIconDial,/*缩放指数*/128);
  lcd.drawIcon(0, 60, DFRobot_LcdDisplay::eIconDisabledAccess, 128);
  lcd.drawIcon(0, 120, DFRobot_LcdDisplay::eIconAngry, 128);
  lcd.drawIcon(0, 180, DFRobot_LcdDisplay::eIconBlink, 128);

  lcd.drawIcon(64, 0, DFRobot_LcdDisplay::eIconAlcohol, 128);
  lcd.drawIcon(64, 60, DFRobot_LcdDisplay::eIconAntennaReceiver, 128);
  lcd.drawIcon(64, 120, DFRobot_LcdDisplay::eIconBee, 128);
  lcd.drawIcon(64, 180, DFRobot_LcdDisplay::eIconBird, 128);

  lcd.drawIcon(128, 0, DFRobot_LcdDisplay::eIconBiofuel, 128);
  lcd.drawIcon(128, 60, DFRobot_LcdDisplay::eIconCarElectric, 128);
  lcd.drawIcon(128, 120, DFRobot_LcdDisplay::eIconBeachBed, 128);
  lcd.drawIcon(128, 180, DFRobot_LcdDisplay::eIconBeachUmbrella8, 128);

  lcd.drawIcon(192, 0, DFRobot_LcdDisplay::eIconAirplane, 128);
  lcd.drawIcon(192, 60, DFRobot_LcdDisplay::eIconAmbulance, 128);
  lcd.drawIcon(192, 120, DFRobot_LcdDisplay::eIconBarn, 128);
  lcd.drawIcon(192, 180, DFRobot_LcdDisplay::eIconBarrier, 128);

  lcd.drawIcon(256, 0, DFRobot_LcdDisplay::eIconDesigner, 128);
  lcd.drawIcon(256, 60, DFRobot_LcdDisplay::eIconDiver, 128);
  lcd.drawIcon(256, 120, DFRobot_LcdDisplay::eIconCloudy, 128);
  lcd.drawIcon(256, 180, DFRobot_LcdDisplay::eIconAvocado, 128);
}

void loop(void)
{
  delay(5000);
  lcd.lvglDelete(icon1);
  icon1 = lcd.drawIcon(0, 0, DFRobot_LcdDisplay::eIconAccordion, 128);
  delay(5000);
  lcd.lvglDelete(icon1);
  icon1 = lcd.drawIcon(0, 0, DFRobot_LcdDisplay::eIconBadminton, 128);
}