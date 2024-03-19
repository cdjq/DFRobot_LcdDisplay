/*!
 * @file DFRobot_LcdDisplay.h
 * @brief Define the infrastructure of the DFRobot_LcdDisplay class
 * @details The library supports driving DFR0997 screens through both I2C and UART interfaces. It provides convenient functions to control and drive the color screen.
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @License     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @maintainer [qsjhyy](yihuan.huang@dfrobot.com)
 * @version  V1.0
 * @date  2023-05-29
 * @url https://github.com/DFRobot/DFRobot_LcdDisplay
 */
#ifndef DFROBOT_LCDDISPLAY_H_
#define DFROBOT_LCDDISPLAY_H_
#include <Wire.h>
#include <Arduino.h>
#include <String.h>

#ifndef ENABLE_DBG
  # define ENABLE_DBG   //!< Open this macro and you can see the details of the program
# ifdef ENABLE_DBG
#   ifdef DBG
#    undef DBG
#   endif
#   define DBG(...) {Serial.print("["); Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
# elif !defined(DBG)
#   define DBG(...)
# endif
#endif

// color
#define BLACK               0x000000    // 黑色
#define BLUE                0x0000FF    // 蓝色
#define RED                 0xFF0000    // 红色
#define GREEN               0x00FF00    // 绿色
#define CYAN                0x00FFFF    // 青色
#define MAGENTA             0xFF00FF    // 洋红色
#define YELLOW              0xFFFF00    // 黄色
#define WHITE               0xFFFFFF    // 白色
#define NAVY                0x000080    // 海军蓝
#define DARKGREEN           0x556B2F    // 深绿色
#define DARKCYAN            0x008B8B    // 深青色
#define MAROON              0x800000    // 栗色
#define PURPLE              0x800080    // 紫色
#define OLIVE               0x808000    // 橄榄色
#define LIGHTGREY           0xD3D3D3    // 浅灰色
#define DARKGREY            0xA9A9A9    // 深灰色
#define ORANGE              0xFFA500    // 橙色
#define GREENYELLOW         0x9ACD32    // 绿黄色
#define DCYAN               0x008B8B    // 深青色

// cmd len
#define CMDLEN_OF_DRAWPIXEL        10    // 绘制像素的命令长度
#define CMDLEN_OF_FILLSCREEN       6     // 填充屏幕的命令长度
#define CMDLEN_OF_SETBACKLIGHT     5     // 设置背光的命令长度
#define CMDLEN_OF_DRAWLINE         14    // 绘制线条的命令长度
#define CMDLEN_OF_DRAWRECT         14    // 绘制矩形的命令长度
#define CMDLEN_OF_FILLRECT         14    // 填充矩形的命令长度
#define CMDLEN_OF_DRAWROUNDRECT    15    // 绘制圆角矩形的命令长度
#define CMDLEN_OF_FILLROUNDRECT    15    // 填充圆角矩形的命令长度
#define CMDLEN_OF_DRAWCIRCLE       11    // 绘制圆形的命令长度
#define CMDLEN_OF_FILLCIRCLE       11    // 填充圆形的命令长度
#define CMDLEN_OF_DRAWTRIANGLE     18    // 绘制三角形的命令长度
#define CMDLEN_OF_FILLTRIANGLE     18    // 填充三角形的命令长度
#define CMDLEN_OF_DRAWICON         13    // 绘制图标的命令长度
#define CMDLEN_OF_DRAWSTRING       36    // 绘制字符串的命令长度
#define CMDLEN_OF_HEAD_LEN         3     // 命令头长度

#define CMDLEN_DRAW_LVGLSLIDER       14    // 绘制LVGL滑块的命令长度
#define CMDLEN_DRAW_LVGLBAR          15    // 绘制LVGL进度条的命令长度
#define CMDLEN_DRAW_LVGLARC          14    // 绘制LVGL圆弧的命令长度
#define CMDLEN_DRAW_LVGLGAUGE        14    // 绘制LVGL仪表盘的命令长度
#define CMDLEN_DRAW_LVGLSTATION      14    // 绘制LVGL站点的命令长度
#define CMDLEN_DRAW_LVGLCOMPASS      14    // 绘制LVGL指南针的命令长度
#define CMDLEN_DRAW_LVGLMETER        14    // 绘制LVGL计量器的命令长度
#define CMDLEN_DRAW_LVGLCHART        14    // 绘制LVGL图表的命令长度

#define CMDLEN_CHANGE_LVGLARC_ROTATION       9    // 更改LVGL圆弧旋转的命令长度
#define CMDLEN_CHANGE_LVGLBAR_VALUE          9    // 更改LVGL进度条值的命令长度
#define CMDLEN_CHANGE_LVGLSLIDER_VALUE       9    // 更改LVGL滑块值的命令长度
#define CMDLEN_CHANGE_LVGLGAUGE_SCALE        10   // 更改LVGL仪表盘刻度的命令长度
#define CMDLEN_CHANGE_LVGLGAUGE_RANGE        10   // 更改LVGL仪表盘范围的命令长度
#define CMDLEN_CHANGE_LVGLGAUGE_VALUE        8    // 更改LVGL仪表盘值的命令长度
#define CMDLEN_CHANGE_LVGLCOMPASS_VALUE      8    // 更改LVGL指南针值的命令长度
#define CMDLEN_CHANGE_LVGLMETER_SCALE        9    // 更改LVGL计量器刻度的命令长度
#define CMDLEN_CHANGE_LVGLMETER_RANGE        10   // 更改LVGL计量器范围的命令长度
#define CMDLEN_CHANGE_LVGLMETER_VALUE        8    // 更改LVGL计量器值的命令长度
#define CMDLEN_CHANGE_LVGLCHART_SERIE        9    // 更改LVGL图表系列的命令长度
#define CMDLEN_CHANGE_LVGLCHART_POINT        9    // 更改LVGL图表数据点的命令长度
#define CMDLEN_CHANGE_LVGLSTATION_VALUE      9    // 更改LVGL站点值的命令长度

#define CMDLEN_DEINIT_LVGL          5     // LVGL反初始化的命令长度
#define CMDLEN_RESET_LVGL           4     // LVGL重置的命令长度
#define CMDLEN_INIT_LVGL            7     // LVGL初始化的命令长度

#define CMD_DELETE_OBJ_LEN            0x06    // 删除对象的命令长度
#define CMD_SET_TOP_OBJ_LEN           0x06    // 设置顶部对象的命令长度
#define CMD_SET_COMPASS_VALUE_LEN     0x07    // 设置指南针值的命令长度
#define CMD_SET_LEN                   0x07    // 设置长度的命令长度
#define CMD_SET_GAUGE_VALUE_LEN       0x07    // 设置仪表盘值的命令长度
#define CMD_SET_LINE_METER_VALUE_LEN  0x07    // 设置线性仪表盘值的命令长度
#define CMD_SET_BAR_VALUE_LEN         0x07    // 设置进度条值的命令长度
#define CMD_SET_SLIDER_VALUE_LEN      0x07    // 设置滑块值的命令长度
#define CMD_SET_ANGLE_OBJ_LEN         0x08    // 设置角度对象的命令长度
#define CMD_DRAW_COMPASS_LEN          0x0B    // 绘制指南针的命令长度
#define CMD_DRAW_CHART_LEN            0x09    // 绘制图表的命令长度
#define CMD_DRAW_SERIE_LEN            0x09    // 绘制系列的命令长度
#define CMD_OF_DRAW_ICON_INTERNAL_LEN 0x0D    // 绘制图标的内部命令长度
#define CMD_OF_DRAW_GIF_INTERNAL_LEN  0x0D    // 绘制GIF的内部命令长度
#define CMD_OF_DRAW_BAR_LEN           0x10    // 绘制进度条的命令长度
#define CMD_OF_DRAW_SLIDER_LEN        0x10    // 绘制滑块的命令长度
#define CMD_DRAW_LINE_LEN             0x11    // 绘制线条的命令长度
#define CMD_OF_DRAW_CIRCLE_LEN        0x13    // 绘制圆形的命令长度
#define CMD_OF_DRAW_GAUGE_LEN         0x15    // 绘制仪表盘的命令长度
#define CMD_OF_DRAW_LINE_METER_LEN    0x15    // 绘制线性仪表盘的命令长度
#define CMD_OF_DRAW_RECT_LEN          0x16    // 绘制矩形的命令长度
#define CMD_OF_DRAW_TRIANGLE_LEN      0x19    // 绘制三角形的命令长度


// cmd
#define CMD_SET_BACKGROUND_COLOR      0x19    // 设置背景颜色的命令
#define CMD_SET_BACKGROUND_IMG        0x1A    // 设置背景图像的命令

#define CMD_OF_DRAW_LINE              0x03    // 绘制线条的命令
#define CMD_OF_DRAW_RECT              0x04    // 绘制矩形的命令
#define CMD_OF_DRAW_CIRCLE            0x06    // 绘制圆形的命令
#define CMD_OF_DRAW_TRIANGLE          0x07    // 绘制三角形的命令
#define CMD_OF_DRAW_ICON_INTERNAL     0x08    // 绘制内部图标的命令
#define CMD_OF_DRAW_ICON_EXTERNAL     0x09    // 绘制外部图标的命令
#define CMD_OF_DRAW_BAR               0x0A    // 绘制进度条的命令
#define CMD_OF_DRAW_BAR_VALUE         0x0B    // 绘制进度条值的命令
#define CMD_OF_DRAW_SLIDER            0x0C    // 绘制滑块的命令
#define CMD_OF_DRAW_SLIDER_VALUE      0x0D    // 绘制滑块值的命令
#define CMD_OF_DRAW_LINE_METER        0x10    // 绘制线性仪表盘的命令
#define CMD_OF_DRAW_LINE_METER_VALUE  0x11    // 绘制线性仪表盘值的命令
#define CMD_OF_DRAW_COMPASS           0x0E    // 绘制指南针的命令
#define CMD_OF_DRAW_COMPASS_VALUE     0x0F    // 绘制指南针值的命令
#define CMD_OF_DRAW_GAUGE             0x12    // 绘制仪表盘的命令
#define CMD_OF_DRAW_GAUGE_VALUE       0x13    // 绘制仪表盘值的命令
#define CMD_OF_DRAW_LINE_CHART        0x14    // 绘制折线图的命令
#define CMD_OF_DRAW_LINE_CHART_TEXT   0x15    // 绘制折线图文本的命令
#define CMD_OF_DRAW_SERIE             0x16    // 绘制系列的命令
#define CMD_OF_DRAW_SERIE_DATA        0x17    // 绘制系列数据的命令
#define CMD_OF_DRAW_TEXT              0x18    // 绘制文本的命令
#define CMD_DELETE_OBJ                0x1B    // 删除对象的命令
#define CMD_SET_TOP_OBJ               0x1C    // 设置顶部对象的命令
#define CMD_SET_ANGLE_OBJ             0x1E    // 设置角度对象的命令
#define CMD_OF_DRAW_GIF_INTERNAL      0x1F    // 绘制内部GIF的命令

#define CMD_OF_DRAWPIXEL        2     // 绘制像素的命令
#define CMD_OF_DRAWLINE         3     // 绘制线条的命令
#define CMD_OF_DRAWRECT         4     // 绘制矩形的命令
#define CMD_OF_DRAWROUNDRECT    5     // 绘制圆角矩形的命令
#define CMD_OF_DRAWCIRCLE       6     // 绘制圆形的命令
#define CMD_OF_DRAWTRIANGLE     7     // 绘制三角形的命令
#define CMD_OF_SETBACKLIGHT     8     // 设置背光的命令
#define CMD_OF_FILLSCREEN       9     // 填充屏幕的命令
#define CMD_OF_FILLRECT         10    // 填充矩形的命令
#define CMD_OF_FILLROUNDRECT    11    // 填充圆角矩形的命令
#define CMD_OF_FILLCIRCLE       12    // 填充圆形的命令
#define CMD_OF_FILLTRIANGLE     13    // 填充三角形的命令

#define CMD_OF_DRAWICON         20    // 绘制图标的命令
#define CMD_OF_DRAWSTRING       21    // 绘制字符串的命令
#define CMD_OF_DRAWDISKIMG      23    // 绘制磁盘图像的命令

#define CMD_DRAW_LVGLSLIDER     31    // 绘制LVGL滑块的命令
#define CMD_DRAW_LVGLBAR        32    // 绘制LVGL进度条的命令
#define CMD_DRAW_LVGLARC        33    // 绘制LVGL圆弧的命令
#define CMD_DRAW_LVGLGAUGE      34    // 绘制LVGL仪表盘的命令
#define CMD_DRAW_LVGLSTATION    35    // 绘制LVGL站点的命令
#define CMD_DRAW_LVGLCOMPASS    36    // 绘制LVGL指南针的命令
#define CMD_DRAW_LVGLLINEMETER  37    // 绘制LVGL线性仪表盘的命令
#define CMD_DRAW_LVGLCHART      38    // 绘制LVGL图表的命令

#define CMD_RESET_LVGL          0x80    // 重置LVGL的命令
#define CMD_INIT_LVGL           0x81    // 初始化LVGL的命令
#define CMD_DEINIT_LVGL         0x82    // 反初始化LVGL的命令

#define CMD_HEADER_HIGH         0x55    // 命令头高位
#define CMD_HEADER_LOW          0xaa    // 命令头低位

#ifndef LCD_UNUSED
#define LCD_UNUSED(x) ((void) x)        // 定义未使用的宏
#endif


class DFRobot_LcdDisplay
{
public:

  /**
   * @enum sLcdIcon_t
   * @brief To display different icons using the library, you can select the corresponding enum for the desired icon.
   */
  typedef enum {
    // safe icons
    eIconDial,
    eIconDisabledAccess,
    eIconDown,
    eIconExit,
    eIconExitLeft,
    eIconExportRight,
    eIconFireescapeStairs,
    eIconFireExtinguisher,
    eIconFire,
    eIconHydrant,

    eIconLeft,
    eIconLifeladder,
    eIconMedicalCare,
    eIconRight,
    eIconUp,

    // expression icons
    eIconAngry,
    eIconBlink,
    eIconCry,
    eIconCute,
    eIconDepressed,

    eIconDizzy,
    eIconEmbarrassed,
    eIconFunny,
    eIconHappy,
    eIconKind,
    eIconLike,
    eIconPlayful,
    eIconResentful,
    eIconSad,
    eIconSerious,

    eIconShy,
    eIconSmile,
    eIconSurprised,
    eIconTear,
    eIconTired,

    // sensor icons
    eIconAlcohol,
    eIconAntennaReceiver,
    eIconAntenna,
    eIconBattery,
    eIconBluetooth,

    eIconBulb,
    eIconCarbonDioxide,
    eIconColor,
    eIconCompass,
    eIconDistance,
    eIconDust,
    eIconHeartRate,
    eIconLiquid,
    eIconMicrophone,
    eIconMountain,


    eIconPressure,
    eIconRaindrops,
    eIconThermometer,
    eIconWeigh,
    eIconWifi,
    eIconWind,

    // animal icons
    eIconBee,
    eIconBird,
    eIconButterfly,
    eIconCaterpillar,


    eIconChick,
    eIconChicken,
    eIconChipmunk,
    eIconCoccinellaSeptempunctata,
    eIconCow,
    eIconDog,
    eIconDolphin,
    eIconDragon,
    eIconElephant,
    eIconHorse,

    eIconMonkey,
    eIconOwl,
    eIconPig,
    eIconRabbit,
    eIconRooster,
    eIconSheep,
    eIconSnail,
    eIconSnake,
    eIconTurtle,
    eIconUnicorn,


    eIconWasp,
    eIconWorm,

    // Environment and Nature icons
    eIconBiofuel,
    eIconCarElectric,
    eIconDesertLandscape,
    eIconDirections,
    eIconEarth,
    eIconEcoAccumulatorBattery,
    eIconGlassRecycle,
    eIconGlobalWarming,


    eIconGreenPower,
    eIconGreenEnergy,
    eIconGreenhouse,
    eIconIcebergMelting,
    eIconLandscape,
    eIconNoPlastic,
    eIconNoSewage,
    eIconProtectEarth,
    eIconRainLandscape,
    eIconRecyclingCar,


    eIconRelaxLandscape,
    eIconSolar,
    eIconTap,
    eIconTrash,
    eIconTreeLandscape,
    eIconWaterRecycle,
    eIconWinterForest,

    // season icons
    eIconBeachBed,
    eIconBeachUmbrella8,
    eIconChristmasStocking,


    eIconCoconut,
    eIconFan,
    eIconFireplace,
    eIconGlove,
    eIconHat,
    eIconIceCream,
    eIconLifeBuoy,
    eIconSanta,
    eIconShorts,
    eIconSlipper,

    
    eIconSnowman,
    eIconSunny,
    eIconSweater,
    eIconSwimming,
    eIconSwimwear,
    eIconThanksgiving,
    eIconThermometerSnow,
    eIconWatermelon,

    // transport icons
    eIconAirplane,
    eIconAmbulance,


    eIconAutomobile,
    eIconBicycle,
    eIconBus,
    eIconBusStop,
    eIconDeliveryTruck,
    eIconFireEngine,
    eIconHelicopter,
    eIconHighSpeedRailway,
    eIconHorizontalTrafficLight,
    eIconKickScooter,


    eIconMotorScooter,
    eIconMotorway,
    eIconOncomingTaxi,
    eIconPoliceCar,
    eIconTractor,
    eIconVerticalTrafficLight,
    // Agriculture icons
    eIconBarn,
    eIconBarrier,
    eIconBoots,
    eIconCutWood,


    eIconEggs,
    eIconFertilizer,
    eIconFruits,
    eIconMilkContainer,
    eIconPlant,
    eIconSheafOfRice,
    eIconSprout,
    eIconStorageBucket,
    eIconTool,
    eIconTractor2,


    eIconVegetables,
    eIconWateringCan,
    eIconWellWater,
    eIconWheelbarrow,
    // people icons
    eIconDesigner,
    eIconDiver,
    eIconDoctor,
    eIconLabScientist,
    eIconMagicianMale,
    eIconNurse,


    eIconPhotographerMale,
    eIconPolice,
    eIconProgrammerMale,
    eIconSoldier,
    eIconSuccessGoalBusinessman,
    eIconSurgeon,
    eIconTeacher,

    // food icons
    eIconAvocado,
    eIconBanana,
    eIconBeerMug,


    eIconBentoBox,
    eIconBirthdayCake,
    eIconBread,
    eIconCake,
    eIconCarrot,
    eIconCheeseWedge,
    eIconCherry,
    eIconChocolateBar,
    eIconCutOfMeat,
    eIconEarOfCorn,


    eIconEgg,
    eIconFrenchFries,
    eIconGrapes,
    eIconGreenSalad,
    eIconHamburger,
    eIconHotBeverage,
    eIconPeach,
    eIconPineapple,
    eIconPopcorn,
    eIconPotato,


    eIconRedApple,
    eIconSalad,
    eIconShaomai,
    eIconSandwich,
    eIconShortcake,
    eIconStrawberry,
    // Numeric graphic icons
    eIconArrowDown,
    eIconArrowLeft,
    eIconArrowRight,
    eIconArrowUp,


    eIconDiamond,
    eIconEight,
    eIconFive,
    eIconFivePointedStar,
    eIconHeart,
    eIconNine,
    eIconFour,
    eIconOctagon,
    eIconOne,
    eIconPentagon,


    eIconRectangle,
    eIconSeven,
    eIconSix,
    eIconSquare,
    eIconThree,
    eIconTriangle,
    eIconTwo,
    eIconWindmillShape,
    eIconZero,
    // Weather icons
    eIconCloudy,


    eIconMoon,
    eIconLightning,
    eIconMoonCloudy,
    eIconRainUmbrella,
    eIconRainbow1,
    eIconRainbow2,
    eIconRainy,
    eIconSnow,
    eIconSonwy,
    eIconSunnyCloudy,


    eIconWhirlwind,
    // Music icons
    eIconAccordion,
    eIconBassDrum,
    eIconCDDiskDVD,
    eIconCello,
    eIconElectricGuitar,
    eIconFlute,
    eIconGuitar,
    eIconHarmonica,
    eIconHarp,


    eIconHeadphones,
    eIconMelodica,
    eIconMusic,
    eIconMusicStereo,
    eIconMusicTurntable,
    eIconMuteSoundOff,
    eIconPiano,
    eIconSaxophone,
    eIconSpeakerAudio,
    eIconTrumpet,


    eIconXylophone,
    // Sports icons
    eIconBadminton,
    eIconBasketball,
    eIconBowling,
    eIconChess,
    eIconCycling,
    eIconDarts,
    eIconDiving,
    eIconDumbbell,
    eIconGolf,


    eIconIceHockey,
    eIconKarate,
    eIconPingPong,
    eIconRunning,
    eIconSoccer,
    eIconTennis,
    eIconYoga,

    // Plant icons
    eIconBranch,
    eIconCactus1,
    eIconCactus2,


    eIconCactus3,
    eIconDeciduousTree,
    eIconDecorativePottedPlants,
    eIconFlower,
    eIconGrass,
    eIconGrass1,
    eIconLeaf,
    eIconPalmTree,
    eIconPottedPlantFlower,
    eIconRose,

    eIconRose1,
    eIconSunflower,
    eIconSunflower1,
    eIconTulips,

  }sLcdIcon_t;

  /**
   * @enum eLcdFont_t
   * @brief When using fonts, pass the following enums to the setFont() function to select different fonts
   */
  typedef enum {
    eChinese,/**<Chinese*/
    eShiftJis,/**<Japanese*/
    eAscii,/**<ACSII*/
    eGreece,/**<Greek*/
    eCyrillic,/**<Cyrillic*/
    eHebrew,/**<Hebrew*/
    eThailand,/**<Greek for unequal width*/
    eAlb,/**<Arabic*/
    eKhmer,/**<khmer*/
    eKorean,/**<Korean*/
  }eLcdFont_t;

  /**
    * @struct sControlinf_t
    * @brief Objects that point to different controls
    */
  typedef struct controlinf {
    uint32_t number; /**<Control ID */
    uint16_t id; /**<Control ID, different controls have different functionalities.*/
    int16_t x; /**<X coordinate of the control's position.*/
    int16_t y; /**<Y coordinate of the control's position.*/
    int16_t width; /**<Control width */
    int16_t height; /**<Control height*/
    uint16_t color; /**<Color Control*/
    struct controlinf* inf; /**<The next control pointer */
  }sControlinf_t;

  typedef struct chartinfo {
    uint8_t id; /**<chart ID */
    struct chartinfo* inf; /**<The next control pointer */
  }sChartinfo_t;

  typedef struct LineChartNode {
    uint8_t id;
    struct LineChartNode* next;
  } sLineChartNode_t;


  typedef struct GenericNode {
    uint8_t id;
    void* next;
  } sGenericNode_t;

public:
  /**
   * @fn DFRobot_LcdDisplay
   * @brief constructor
   * @return None
   */
  DFRobot_LcdDisplay();

  /**
   * @fn begin
   * @brief initialization function
   * @return Boolean type, initialized state
   * @retval true succeed
   * @retval false failed
   */
  bool begin();
  /**
   * @fn drawPixel
   * @brief Function to draw a pixel
   * @param x X-coordinate position of the pixel
   * @param y Y-coordinate position of the pixel
   * @param color The color of pixels, RGB565 format
   */
  void drawPixel(int16_t x, int16_t y, uint16_t color);

  /**
   * @fn setBackgroundColor
   * @brief Set the Background Color object
   * @param bg_color Background Color(R,G,B)
   */
  void setBackgroundColor(uint32_t bg_color = 0xFF0000);
  void setBackgroundImg(uint8_t location, String str);

  /**
   * @fn setFont
   * @brief Set font for easy calculation of consecutive font display positions.
   * @param font font type, eLcdFont_t
   */
  void setFont(eLcdFont_t font);

  void cleanScreen();

  /**
   * @fn drawLine
   * @brief Draw a straight line on the screen.
   * @param x0 Start X-coordinate of the line.
   * @param y0 Start Y-coordinate of the line.
   * @param x1 End X-coordinate of the line.
   * @param y1 End Y-coordinate of the line.
   * @param width line width
   * @param color the color of the line, RGB888 format
   */
  uint8_t drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t width, uint32_t color);

  /**
   * @fn updateLine
   * @brief Update a straight line on the screen.
   * @param id Line id
   * @param x0 Start X-coordinate of the line.
   * @param y0 Start Y-coordinate of the line.
   * @param x1 End X-coordinate of the line.
   * @param y1 End Y-coordinate of the line.
   * @param width line width
   * @param color the color of the line, RGB888 format
   */
  void updateLine(uint8_t id, int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t width, uint32_t color);

  /**
   * 
   * @fn deleteLine
   * @brief Delete line
   * 
   * @param id line id
   */
  void deleteLine(uint8_t id);

  /**
   * @fn drawRect
   * @brief Draw rectangles on the screen
   * @param x Start of rectangle x coordinate
   * @param y Start of rectangle y coordinate
   * @param w  Width of a rectangle
   * @param h  Height of rectangle
   * @param borderWidth border width
   * @param borderColor border color
   * @param fill fill
   * @param fillColor fill color
   * @param rounded rounded
   * @return rect id
   * 
   */
  uint8_t drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t borderWidth, uint32_t borderColor, uint8_t fill, uint32_t fillColor, uint8_t rounded);

  /**
   * @fn updateRect
   * @brief update rectangles on the screen
   * @param id rectangles id
   * @param x Start of rectangle x coordinate
   * @param y Start of rectangle y coordinate
   * @param w  Width of a rectangle
   * @param h  Height of rectangle
   * @param borderWidth border width
   * @param borderColor border color
   * @param fill fill
   * @param fillColor fill color
   * @param rounded rounded
   * @return rect id
   * 
   */
  void updateRect(uint8_t id, int16_t x, int16_t y, int16_t w, int16_t h, uint8_t borderWidth, uint32_t borderColor, uint8_t fill, uint32_t fillColor, uint8_t rounded);
  
  /**
   * 
   * @fn deleteRect
   * @brief Delete rectangles
   * @param id rectangles id
   */
  void deleteRect(uint8_t id);

  /**
   * @fn drawCircle
   * @brief Draw circles on the screen
   * @param x Center of the circle x coordinate
   * @param y Center of the circle y coordinate
   * @param r  Radius of the circle
   * @param borderWidth border width
   * @param borderColor border Color
   * @param fill fill
   * @param fillColor fill color
   */
  uint8_t drawCircle(int16_t x, int16_t y, int16_t r, uint8_t borderWidth, uint32_t borderColor, uint8_t fill, uint32_t fillColor);

  /**
   * @fn updateCircle
   * @brief Update circles on the screen
   * @param id Circles id
   * @param x Center of the circle x coordinate
   * @param y Center of the circle y coordinate
   * @param r  Radius of the circle
   * @param borderWidth border width
   * @param borderColor border Color
   * @param fill fill
   * @param fillColor fill color
   */
  void updateCircle(uint8_t id, int16_t x, int16_t y, int16_t r, uint8_t borderWidth, uint32_t borderColor, uint8_t fill, uint32_t fillColor);

  /**
   * 
   * @fn deleteCircle
   * @brief Delete circles
   * @param id circles id
   */
  void deleteCircle(uint8_t id);

  /**
   * @fn drawTriangle
   * @brief Draw a triangle on the screen
   * @param x0 The x-coordinate of the first point of the triangle
   * @param y0 The y-coordinate of the first point of the triangle
   * @param x1 The x-coordinate of the second point of the triangle
   * @param y1 The y-coordinate of the second point of the triangle
   * @param x2 The x-coordinate of the third point of the triangle
   * @param y2 The y-coordinate of the third point of the triangle
   * @param borderWidth border width
   * @param borderColor border color
   * @param fill fill
   * @param fillColor fill color
   */
  uint8_t drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t borderWidth, uint32_t borderColor, uint8_t fill, uint32_t fillColor);

 /**
   * @fn updateTriangle
   * @brief Draw a triangle on the screen
   * @param id triangle id
   * @param x0 The x-coordinate of the first point of the triangle
   * @param y0 The y-coordinate of the first point of the triangle
   * @param x1 The x-coordinate of the second point of the triangle
   * @param y1 The y-coordinate of the second point of the triangle
   * @param x2 The x-coordinate of the third point of the triangle
   * @param y2 The y-coordinate of the third point of the triangle
   * @param borderWidth border width
   * @param borderColor border color
   * @param fill fill
   * @param fillColor fill color
   */
  void updateTriangle(uint8_t id, int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t borderWidth, uint32_t borderColor, uint8_t fill, uint32_t fillColor);

  /**
   * 
   * @fn deleteTriangle
   * @brief Delete Triangles
   * @param id Triangle id
   */
  void deleteTriangle(uint8_t id);

  /**
   * @fn drawIcon
   * @brief Draw an icon
   * @param x The x-coordinate of the first point of the icon
   * @param y The y-coordinate of the first point of the icon
   * @param id The icon's corresponding number
   * @param size Icon scaling factor
   * @return Icon id
   */
  uint8_t drawIcon(int16_t x, int16_t y, uint16_t id, uint16_t size = 255);
  uint8_t drawIcon(int16_t x, int16_t y, String str, uint16_t zoom);
  void setAngleIcon(uint8_t id, int16_t angle);

  void updateIcon(uint8_t iconId, int16_t x, int16_t y, uint16_t iconNum, uint16_t size);
  void updateIcon(uint8_t iconId, int16_t x, int16_t y, String str, uint16_t zoom);

  void deleteIcon(uint8_t id);

  uint8_t drawGif(int16_t x, int16_t y, uint16_t id, uint16_t size = 255);
  void deleteGif(uint8_t id);

  /**
   * @fn drawDiskImg
   * @brief Used to draw the pictures inside the USB drive (in BMP or PNG format).
   * @param x The x-coordinate of the first point in the picture
   * @param y The y-coordinate of the first point in the picture
   * @param str The full file name of the image, such as "/img/cat.bmp"
   * @param size Scale factor for image resizing
   * @return The object of the picture control
   * @note The size of bmp and png is limited due to the small ram
   */
  sControlinf_t* drawDiskImg(int16_t x, int16_t y, String str, uint16_t size = 255);

  /**
   * @fn creatSlider
   * @brief Create a slider control
   * @param x The x-coordinate of the slider
   * @param y The y-coordinate of the slider
   * @param width The width of the slider
   * @param height The height of the slide bar
   * @param color The color of the slider
   * @return Slider control handle
   */
  uint8_t creatSlider(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);

    /**
   * @fn updateSlider
   * @brief Update a slider control
   * @param x The x-coordinate of the slider
   * @param y The y-coordinate of the slider
   * @param width The width of the slider
   * @param height The height of the slide bar
   * @param color The color of the slider
   * @return Slider control handle
   */
  void updateSlider(uint8_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);

  /**
   * @fn setSliderValue
   * @brief Sets the slider value
   * @param sliderId Slider control handle
   * @param value The value of the slider
   */
  void setSliderValue(uint8_t sliderId, uint16_t value);

  /**
   * 
   * @fn deleteSlider
   * @brief Delete slider
   * @param id slider id
   */
  void deleteSlider(uint8_t id);

  /**
   * @fn creatBar
   * @brief Create a progress bar control
   * @param x The x coordinate of the progress bar
   * @param y The y coordinate of the progress bar
   * @param width Width of the progress bar
   * @param height Height of the progress bar
   * @param color Color of the progress bar
   * @return Bar id
   */
  uint8_t creatBar(uint16_t x, uint16_t y, uint16_t width, uint8_t height, uint32_t color);

  /**
   * @fn updateBar
   * @brief Update a progress bar control
   * @param id Bar id
   * @param x The x coordinate of the progress bar
   * @param y The y coordinate of the progress bar
   * @param width Width of the progress bar
   * @param height Height of the progress bar
   * @param color Color of the progress bar
   * @return Bar id
   */
  void updateBar(uint8_t id, uint16_t x, uint16_t y, uint16_t width, uint8_t height, uint32_t color);

  /**
   * @fn setBar
   * @brief Set the value of the progress bar, which can include a unit but must start with a number
   * @param obj Progress bar control handle
   * @param str Value of the progress bar
   */
  void setBar(uint8_t barId, uint16_t);

  /**
   * 
   * @fn deleteBar
   * @brief Delete bar
   * @param id bar id
   */
  void deleteBar(uint8_t id);

  /**
   * @fn creatChart
   * @brief Create a chart control
   * @param strX Label on the x axis of the chart
   * @param strY Label on the y axis of the chart
   * @param bgColor background color
   * @param type Type of chart (line chart / bar chart)
   * @return chart control handle
   */
  uint8_t creatChart(String strX, String strY, uint32_t bgColor, uint8_t type);

  /**
   * @fn updateChart
   * @brief Update a chart control
   * @param id Chart id
   * @param bgColor background color
   * @param type Type of chart (line chart / bar chart)
   * @return chart control handle
   */
  void updateChart(uint8_t id, uint32_t bgColor, uint8_t type);

  /**
   * @fn creatChartSeries
   * @brief Create a line chart or bar chart sequence in the chart
   * @param chartId chart id
   * @param color Color of line chart/bar chart
   * @return Return the index of the series
   */
  uint8_t creatChartSeries(uint8_t chartId, uint32_t color);

  /**
   * @fn updateChartSeries
   * @brief Update a line chart or bar chart sequence in the chart
   * @param chartId chart id
   * @param seriesId series id
   * @param color Color of line chart/bar chart
   * @return Return the index of the series
   */
  void updateChartSeries(uint8_t chartId, uint8_t seriesId, uint32_t color);

  /**
   * @fn addChart
   * @brief Assign a data sequence and add it to the chart
   * @param obj chart control handle
   * @param id the allocated data series
   * @param point A graph/bar chart requires an array of data
   * @param len  array length
   */
  uint8_t addChartSeriesData(uint8_t chartId, uint8_t SeriesId, uint16_t point[], uint8_t len);


  void updateChartPoint(uint8_t chartId, uint8_t SeriesId, uint8_t pointNum, uint16_t value);
  /**
   * 
   * @fn setTopChart
   * @brief Set Top chart
   * @param id chart id
   */
  void setTopChart(uint8_t id);

  /**
   * 
   * @fn deleteChart
   * @brief Delete chart
   * @param id chart id
   */
  void deleteChart(uint8_t id);

  /**
   * @fn creatGauge
   * @brief Create a dial control
   * @param x The x-axis coordinate of the control
   * @param y The y-axis coordinate of the control
   * @param diameter  Gauge diameter
   * @param start start value
   * @param end end value
   * @param pointerColor pointer color
   * @param bgColor background color
   * @return dial control handle
   */
  uint8_t creatGauge(uint16_t x, uint16_t y, uint16_t diameter, uint16_t start, uint16_t end, uint32_t pointerColor, uint32_t bgColor);

  /**
   * @fn updateGauge
   * @brief update a dial control
   * @param x The x-axis coordinate of the control
   * @param y The y-axis coordinate of the control
   * @param diameter  Gauge diameter
   * @param start start value
   * @param end end value
   * @param pointerColor pointer color
   * @param bgColor background color
   * @return dial control handle
   */
  void updateGauge(uint8_t id, uint16_t x, uint16_t y, uint16_t diameter, uint16_t start, uint16_t end, uint32_t pointerColor, uint32_t bgColor);

  /**
   * @fn setGaugeScale
   * @brief Setting the parameters of the dial control
   * @param obj dial control handle
   * @param angle angle of the scale (0..360)
   * @param start minimum value
   * @param end maximum value
   */
  void setGaugeScale(sControlinf_t * obj, uint16_t angle, int16_t start, int16_t end);

  /**
   * @fn setGaugeValue
   * @brief Sets the value indicated by the dial
   * @param gaugeId gauge id
   * @param value the new value
   */
  void setGaugeValue(uint8_t gaugeId, uint16_t value);

  /**
   * 
   * @fn deleteGauge
   * @brief Delete gauge
   * @param id gauge id
   */
  void deleteGauge(uint8_t id);

  /**
   * @fn creatCompass
   * @brief Creating a compass control
   * @param x The x-axis coordinate of the control
   * @param y The y-axis coordinate of the control
   * @param diameter  Compass diameter
   * @return compass id
   */
  uint8_t creatCompass(uint16_t x, uint16_t y, uint16_t diameter);

  /**
   * @fn updateCompass
   * @brief Update a compass control
   * @param id compass id
   * @param x The x-axis coordinate of the control
   * @param y The y-axis coordinate of the control
   * @param diameter  Compass diameter
   * @return compass id
   */
  void updateCompass(uint8_t id, uint16_t x, uint16_t y, uint16_t diameter);

  /**
   * @fn setCompassScale
   * @brief Setting the angle of the compass pointer
   * @param compassId compass id
   * @param scale Pointer angle(0~360)
   */
  void setCompassScale(uint8_t compassId, uint16_t scale);

  /**
   * 
   * @fn deleteCompass
   * @brief Delete compass
   * @param id compass id
   */
  void deleteCompass(uint8_t id);

  /**
   * @fn creatLineMeter
   * @brief Create a linear gauge control
   * @param x The x-axis coordinate of the control
   * @param y The y-axis coordinate of the control
   * @param size  LineMeter size
   * @param start minimum value
   * @param end maximum value
   * @param pointerColor pointer color
   * @param bgColor pointer color
   * @return linear meter id
   */
  uint8_t creatLineMeter(uint16_t x, uint16_t y, uint16_t size, uint16_t start, uint16_t end, uint32_t pointerColor, uint32_t bgColor);

  /**
   * @fn updateLineMeter
   * @brief update a linear gauge control
   * @param id
   * @param x The x-axis coordinate of the control
   * @param y The y-axis coordinate of the control
   * @param size  LineMeter size
   * @param start minimum value
   * @param end maximum value
   * @param pointerColor pointer color
   * @param bgColor pointer color
   */
  void updateLineMeter(uint8_t id, uint16_t x, uint16_t y, uint16_t size, uint16_t start, uint16_t end, uint32_t pointerColor, uint32_t bgColor);

  /**
   * @fn setMeterScale
   * @brief Sets parameters for the linear meter control
   * @param obj pointer to a line meter object
   * @param angle angle of the scale (0..360)
   * @param start minimum value
   * @param end maximum value
   */
  void setMeterScale(sControlinf_t* obj, uint16_t angle, int16_t start, int16_t end);

  /**
   * @fn setMeterValue
   * @brief Set a new value on the line meter
   * @param lineMeterId line meter id
   * @param value new value
   */
  void setMeterValue(uint8_t lineMeterId, uint16_t value);

  /**
   * 
   * @fn deleteLineMeter
   * @brief Delete LineMeter
   * @param id LineMeter id
   */
  void deleteLineMeter(uint8_t id);

  /**
   * 
   * @fn setTopLineMeter
   * @brief Set Top LineMeter
   * @param id LineMeter id
   */
  void setTopLineMeter(uint8_t id);

  /**
   * @fn drawString(uint8_t x, uint8_t y, String str, uint8_t type, uint16_t color, uint16_t bgColor)
   * @brief Display text on the screen
   * @param x The x-coordinate of the starting position
   * @param y The y-coordinate of the starting position
   * @param str The text to display
   * @param fontSize Text size (only applicable to eChinese and eAscii): 0 (24px size), 1 (12px size)
   * @param color Color of text
   */
  uint8_t drawString(uint16_t x, uint16_t y, String str, uint8_t fontSize, uint32_t color);

  void updateString(uint8_t id, uint16_t x, uint16_t y, String str, uint8_t fontSize, uint32_t color);

  void deleteString(uint8_t id);

  /**
   * @fn drawLcdTime
   * @brief Displays the set time on the screen
   * @param x The x-coordinate of the starting position
   * @param y The y-coordinate of the starting position
   * @param hour hour
   * @param Minute minute
   * @param seconds second
   * @param fontSize font size
   * @param color Color of text
   */
  uint8_t drawLcdTime(uint8_t x, uint8_t y, uint8_t hour, uint8_t Minute, uint8_t seconds, uint8_t fontSize, uint16_t color);
  void updateLcdTime(uint8_t id, uint8_t x, uint8_t y, uint8_t hour, uint8_t Minute, uint8_t seconds, uint8_t fontSize, uint16_t color);

  /**
   * @fn drawLcdDate
   * @brief Displays the set date on the screen
   * @param x The x-coordinate of the starting position
   * @param y The y-coordinate of the starting position
   * @param month month
   * @param day day
   * @param weeks weekday
   * @param fontSize font size
   * @param color Color of text
   */
  void drawLcdDate(uint8_t x, uint8_t y, uint8_t month, uint8_t day, uint8_t weeks, uint8_t fontSize, uint16_t color);

  /**
   * @fn lvglDelete
   * @brief Delete a specific control that has been created.
   * @param obj Delete the handle of a control object
   */
  void lvglDelete(sControlinf_t* obj);

private:
  TwoWire* _pWire;
  sControlinf_t head;
  sGenericNode_t *line_chart_head = NULL;
  sGenericNode_t *series_head = NULL;
  sGenericNode_t *compass_head = NULL;
  sGenericNode_t *text_head = NULL;
  sGenericNode_t *gauge_head = NULL;
  sGenericNode_t *line_head = NULL;
  sGenericNode_t *rect_head = NULL;
  sGenericNode_t *circle_head = NULL;
  sGenericNode_t *triangle_head = NULL;
  sGenericNode_t *lineMeter_head = NULL;
  sGenericNode_t *bar_head = NULL;
  sGenericNode_t *slider_head = NULL;
  sGenericNode_t *icon_head = NULL;
  sGenericNode_t *gif_head = NULL;
  eLcdFont_t _font = eAscii;
  uint8_t _deviceAddr;

  uint16_t getWordLen(uint8_t* utf8, uint8_t len);
  uint8_t utf8toUnicode(uint8_t* utf8, uint16_t& uni);
  uint8_t addChartPoint(sControlinf_t* obj, uint8_t id, uint16_t value);
  uint8_t setChartTickTexts(sControlinf_t* obj, String xtext, String ytext);
  uint8_t setChartAxisTexts(uint8_t chartId, uint8_t axis, String text);
  void drawStringHepler(uint16_t x, uint8_t y, uint8_t* uni, uint8_t lenght, uint8_t type, uint16_t color, uint16_t fgColor);
  uint8_t getNewID(sGenericNode_t** head);
  void deleteNodeByID(sGenericNode_t** head, uint8_t id);
  uint8_t getNumber(uint8_t id);
  uint8_t getID(uint8_t type);

  uint8_t* creatCommand(uint8_t cmd, uint8_t len);
  virtual void writeCommand(uint8_t* pBuf, uint16_t len) = 0;
  virtual void readACK(uint8_t* pBuf, uint16_t len) = 0;
};


class DFRobot_Lcd_IIC: public DFRobot_LcdDisplay
{
public:
  /**
   * @fn DFRobot_Lcd_IIC
   * @brief constructor
   * @param pWire I2C controller object
   * @param addr I2C address. The default value is 0x2c
   * @return None
   */
  DFRobot_Lcd_IIC(TwoWire* pWire = &Wire, uint8_t addr = 0x2c);

  /**
   * @fn begin
   * @brief Initialize the function to initialize the I2C controller and turn on the screen backlight
   * @return Boolean type, initialized state
   * @retval true succeed
   * @retval false failed
   */
  bool begin();

private:
  uint8_t _deviceAddr;
  TwoWire* _pWire;
  void    writeCommand(uint8_t* pBuf, uint16_t len);
  void    readACK(uint8_t* pBuf, uint16_t len);
};

class DFRobot_Lcd_UART: public DFRobot_LcdDisplay
{
public:
  /**
   * @fn DFRobot_Lcd_UART
   * @brief constructor
   * @return None
   */
  DFRobot_Lcd_UART(Stream& s);
  /**
   * @fn begin
   * @brief Initialize the function to initialize the UART controller and turn on the screen backlight
   * @param s Passing a UART object
   * @return Boolean type, initialized state
   * @retval true succeed
   * @retval false failed
   */
  bool begin();

private:
  Stream* _s;
  void writeCommand(uint8_t* pBuf, uint16_t len);
  void readACK(uint8_t* pBuf, uint16_t len);
};

#endif