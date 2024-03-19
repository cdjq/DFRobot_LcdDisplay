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

// Icons that are already burned into the firmware.
#if 0   // This is a comment. To avoid compilation errors, it can only be 0.
// sensor icons
eIconAlcohol, eIconAntennaReceiver, eIconAntenna, eIconBattery, eIconBluetooth, eIconBulb, eIconCarbonDioxide,
eIconColor, eIconCompass, eIconDistance, eIconDust, eIconHeartRate, eIconLiquid, eIconMicrophone, eIconMountain,
eIconPressure, eIconRaindrops, eIconThermometer, eIconWeigh, eIconWifi, eIconWind, eIconLight, eIconUVLight,

// expression icons
eIconAngry, eIconBlink, eIconCry, eIconCute, eIconDepressed, eIconDizzy, eIconEmbarrassed, eIconFunny,
eIconHappy, eIconKind, eIconLike, eIconPlayful, eIconResentful, eIconSad, eIconSerious, eIconShy, eIconSmile, eIconSurprised,
eIconTear, eIconTired,

// Environment and Nature icons
eIconBiofuel, eIconCarElectric, eIconDesertLandscape, eIconDirections, eIconEarth, eIconEcoAccumulatorBattery,
eIconGlassRecycle, eIconGlobalWarming, eIconGreenPower, eIconGreenEnergy, eIconGreenhouse, eIconIcebergMelting,
eIconLandscape, eIconNoPlastic, eIconNoSewage, eIconProtectEarth, eIconRainLandscape, eIconRecyclingCar,
eIconRelaxLandscape, eIconSolar, eIconTap, eIconTrash, eIconTreeLandscape, eIconWaterRecycle, eIconWinterForest,

// season icons
eIconBeachBed, eIconBeachUmbrella8, eIconChristmasStocking, eIconCoconut, eIconFan, eIconFireplace, eIconGlove,
eIconHat, eIconIceCream, eIconLifeBuoy, eIconSanta, eIconShorts, eIconSlipper, eIconSnowman, eIconSunny,
eIconSweater, eIconSwimming, eIconSwimwear, eIconThanksgiving, eIconThermometerSnow, eIconWatermelon,

// Weather icons
eIconCloudy,    eIconMoon,    eIconLightning,    eIconMoonCloudy,
eIconRainUmbrella,    eIconRainbow1,    eIconRainbow2,    eIconRainy,
eIconSnow,    eIconSnowy,    eIconSunnyCloudy,    eIconWhirlwind,

// Sports icons
eIconBadminton, eIconBasketball, eIconBowling, eIconChess, eIconCycling, eIconDarts, eIconDiving, eIconDumbbell,
eIconGolf, eIconIceHockey, eIconKarate, eIconPingPong, eIconRunning, eIconSoccer, eIconTennis, eIconYoga,

// animal icons
eIconBee, eIconBird, eIconButterfly, eIconCaterpillar, eIconChick, eIconChicken, eIconChipmunk,
eIconCoccinellaSeptempunctata, eIconCow, eIconDog, eIconDolphin, eIconDragon, eIconElephant, eIconHorse,
eIconMonkey, eIconOwl, eIconPig, eIconRabbit, eIconRooster, eIconSheep, eIconSnail, eIconSnake, eIconTurtle,
eIconUnicorn, eIconWasp, eIconWorm,

// Plant icons
eIconBranch, eIconCactus1, eIconCactus2, eIconCactus3, eIconDeciduousTree, eIconDecorativePottedPlants, eIconFlower,
eIconGrass, eIconGrass1, eIconLeaf, eIconPalmTree, eIconPottedPlantFlower, eIconRose, eIconRose1, eIconSunflower,
eIconSunflower1, eIconTulips,

// food icons
eIconAvocado, eIconBanana, eIconBeerMug, eIconBentoBox, eIconBirthdayCake, eIconBread, eIconCake, eIconCarrot,
eIconCheeseWedge, eIconCherry, eIconChocolateBar, eIconCutOfMeat, eIconEarOfCorn,
eIconEgg, eIconFrenchFries, eIconGrapes, eIconGreenSalad, eIconHamburger,
eIconHotBeverage, eIconPeach, eIconPineapple, eIconPopcorn, eIconPotato,
eIconRedApple, eIconSalad, eIconShaomai, eIconSandwich, eIconShortcake,
eIconStrawberry,

// safe icons
eIconDial, eIconDisabledAccess, eIconDown, eIconExit, eIconExitLeft, eIconExportRight, eIconFireescapeStairs,
eIconFireExtinguisher, eIconFire, eIconHydrant, eIconLeft, eIconLifeladder, eIconMedicalCare, eIconRight, eIconUp,

// transport icons
eIconAirplane, eIconAmbulance, eIconAutomobile, eIconBicycle, eIconBus, eIconBusStop, eIconDeliveryTruck,
eIconFireEngine, eIconHelicopter, eIconHighSpeedRailway, eIconHorizontalTrafficLight, eIconKickScooter,
eIconMotorScooter, eIconMotorway, eIconOncomingTaxi, eIconPoliceCar, eIconTractor, eIconVerticalTrafficLight,

// Agriculture icons
eIconBarn, eIconBarrier, eIconBoots, eIconCutWood, eIconEggs, eIconFertilizer, eIconFruits, eIconMilkContainer,
eIconPlant, eIconSheafOfRice, eIconSprout, eIconStorageBucket, eIconTool, eIconTractor2, eIconVegetables,
eIconWateringCan, eIconWellWater, eIconWheelbarrow,

// people icons
eIconDesigner, eIconDiver, eIconDoctor, eIconLabScientist, eIconMagicianMale, eIconNurse, eIconPhotographerMale,
eIconPolice, eIconProgrammerMale, eIconSoldier, eIconSuccessGoalBusinessman, eIconSurgeon, eIconTeacher,

// Numeric graphic icons
eIconArrowDown,    eIconArrowLeft,    eIconArrowRight,    eIconArrowUp,
eIconDiamond,    eIconEight,    eIconFive,    eIconFivePointedStar,    eIconHeart,
eIconNine,    eIconFour,    eIconOctagon,    eIconOne,    eIconPentagon,
eIconRectangle,    eIconSeven,    eIconSix,    eIconSquare,    eIconThree,
eIconTriangle,    eIconTwo,    eIconWindmillShape,    eIconZero,

// Music icons
eIconAccordion, eIconBassDrum, eIconCDDiskDVD, eIconCello, eIconElectricGuitar, eIconFlute, eIconGuitar,
eIconHarmonica, eIconHarp, eIconHeadphones, eIconMelodica, eIconMusic, eIconMusicStereo, eIconMusicTurntable,
eIconMuteSoundOff, eIconPiano, eIconSaxophone, eIconSpeakerAudio, eIconTrumpet, eIconXylophone,

#endif


uint8_t iconId[15]; // 用于存储图标ID的数组
uint16_t iconNum = 0; // 起始图标编号
//先控制一个图标的移动和缩放，然后遍历显示完所有的内置图标
void testIcon(){
	if(iconNum == 0){
        //在(0,0)处创建一个图标，原尺寸大小显示
        iconId[0] = lcd.drawIcon(0, 0, lcd.eIconHappy, 256);
        delay(200);
        //把图标移动到（130，90），并更改其缩放大小
        for(uint8_t i = 0; i < 16; i++){
            lcd.updateIcon(iconId[0], 130, 90, lcd.eIconHappy, i*32);
            delay(100);
        }
        lcd.deleteIcon(iconId[0]);
        delay(100);
    }
    // 分成3行显示，每行显示5个图标，并存储他们的ID
    for (uint8_t row = 0; row < 3; row++) {
        for (uint8_t col = 0; col < 5; col++) {
            uint8_t index = row * 5 + col; // 计算iconId数组中的索引
            iconId[index] = lcd.drawIcon(64*col, 80*row, iconNum, 256); // 绘制图标并存储ID
            iconNum++;
            if (iconNum >= 294) { // 如果iconNum超过了总图标数，将其重置为0
                iconNum = 0;
            }
        }
    }

    // 在删除图标之前延迟以便查看
    delay(1000);

    // 删除已显示的图标
    for(uint8_t i = 0; i < 15; i++) {
        lcd.deleteIcon(iconId[i]); // 使用存储的ID删除
    }
    delay(1000);
}

DFRobot_LcdDisplay::sControlinf_t* icon1;
uint8_t iconId2[20]; // 用于存储图标ID的数组

void testIcon2(){
  // Drawing icons
  // The last parameter is the scaling factor, ranging from 128 to 512, where 128 represents a 50% reduction and 512 represents a 100% increase in size.
  iconId2[0] = lcd.drawIcon(/*x=*/0,/*y =*/0,/*Icon number*/DFRobot_LcdDisplay::eIconDial,/*Scaling factor*/128);
  iconId2[1] = lcd.drawIcon(0, 60, DFRobot_LcdDisplay::eIconDisabledAccess, 128);
  iconId2[2] = lcd.drawIcon(0, 120, DFRobot_LcdDisplay::eIconAngry, 128);
  iconId2[3] = lcd.drawIcon(0, 180, DFRobot_LcdDisplay::eIconBlink, 128);

  iconId2[4] = lcd.drawIcon(64, 0, DFRobot_LcdDisplay::eIconAlcohol, 128);
  iconId2[5] = lcd.drawIcon(64, 60, DFRobot_LcdDisplay::eIconAntennaReceiver, 128);
  iconId2[6] = lcd.drawIcon(64, 120, DFRobot_LcdDisplay::eIconBee, 128);
  iconId2[7] = lcd.drawIcon(64, 180, DFRobot_LcdDisplay::eIconBird, 128);

  iconId2[8] = lcd.drawIcon(128, 0, DFRobot_LcdDisplay::eIconBiofuel, 128);
  iconId2[9] = lcd.drawIcon(128, 60, DFRobot_LcdDisplay::eIconCarElectric, 128);
  iconId2[10] = lcd.drawIcon(128, 120, DFRobot_LcdDisplay::eIconBeachBed, 128);
  iconId2[11] = lcd.drawIcon(128, 180, DFRobot_LcdDisplay::eIconBeachUmbrella8, 128);

  iconId2[12] = lcd.drawIcon(192, 0, DFRobot_LcdDisplay::eIconAirplane, 128);
  iconId2[13] = lcd.drawIcon(192, 60, DFRobot_LcdDisplay::eIconAmbulance, 128);
  iconId2[14] = lcd.drawIcon(192, 120, DFRobot_LcdDisplay::eIconBarn, 128);
  iconId2[15] = lcd.drawIcon(192, 180, DFRobot_LcdDisplay::eIconBarrier, 128);

  iconId2[16] = lcd.drawIcon(256, 0, DFRobot_LcdDisplay::eIconDesigner, 128);
  iconId2[17] = lcd.drawIcon(256, 60, DFRobot_LcdDisplay::eIconDiver, 128);
  iconId2[18] = lcd.drawIcon(256, 120, DFRobot_LcdDisplay::eIconCloudy, 128);
  iconId2[19] = lcd.drawIcon(256, 180, DFRobot_LcdDisplay::eIconAvocado, 128);

  // 在删除图标之前延迟以便查看
  delay(3000);

  // 删除已显示的图标
  for(uint8_t i = 0; i < 20; i++) {
      lcd.deleteIcon(iconId2[i]); // 使用存储的ID删除
  }
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

void loop(void){
    testIcon();
    // delay(1000);
    // testIcon2();
}
