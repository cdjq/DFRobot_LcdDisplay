/*!
 * @file DFRobot_LcdDisplay.h
 * @brief Define the infrastructure of the DFRobot_LcdDisplay class
 * @details 该库能驱动DFR0997屏幕,通过IIC接口和UART接口便可以方便地驱动彩色屏幕
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @License     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2022-03-1
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
#define BLACK_RGB565        0x0000
#define BLUE_RGB565         0x001F
#define RED_RGB565          0xF800
#define GREEN_RGB565        0x07E0
#define CYAN_RGB565         0x07FF
#define MAGENTA_RGB565      0xF81F
#define YELLOW_RGB565       0xFFE0
#define WHITE_RGB565        0xFFFF
#define NAVY_RGB565         0x000F
#define DARKGREEN_RGB565    0x03E0
#define DARKCYAN_RGB565     0x03EF
#define MAROON_RGB565       0x7800
#define PURPLE_RGB565       0x780F
#define OLIVE_RGB565        0x7BE0
#define LIGHTGREY_RGB565    0xC618
#define DARKGREY_RGB565     0x7BEF
#define ORANGE_RGB565       0xFD20
#define GREENYELLOW_RGB565  0xAFE5
#define DCYAN_RGB565        0x03EF

// cmd len
#define CMDLEN_OF_DRAWPIXEL        10
#define CMDLEN_OF_FILLSCREEN       6
#define CMDLEN_OF_SETBACKLIGHT     5
#define CMDLEN_OF_DRAWLINE         14
#define CMDLEN_OF_DRAWRECT         14
#define CMDLEN_OF_FILLRECT         14
#define CMDLEN_OF_DRAWROUNDRECT    15
#define CMDLEN_OF_FILLROUNDRECT    15
#define CMDLEN_OF_DRAWCIRCLE       11
#define CMDLEN_OF_FILLCIRCLE       11
#define CMDLEN_OF_DRAWTRIANGLE     18
#define CMDLEN_OF_FILLTRIANGLE     18
#define CMDLEN_OF_DRAWICON         13
#define CMDLEN_OF_DRAWSTRING       36
#define CMDLEN_OF_HEAD_LEN         3

#define CMDLEN_DRAW_LVGLSLIDER       14
#define CMDLEN_DRAW_LVGLBAR          15
#define CMDLEN_DRAW_LVGLARC          14
#define CMDLEN_DRAW_LVGLGAUGE        14
#define CMDLEN_DRAW_LVGLSTATION      14
#define CMDLEN_DRAW_LVGLCOMPASS      14
#define CMDLEN_DRAW_LVGLMETER        14
#define CMDLEN_DRAW_LVGLCHART        14

#define CMDLEN_CHANGE_LVGLARC_ROTATION       9
#define CMDLEN_CHANGE_LVGLBAR_VALUE          9
#define CMDLEN_CHANGE_LVGLSLIDER_VALUE       9
#define CMDLEN_CHANGE_LVGLGAUGE_SCALE        10
#define CMDLEN_CHANGE_LVGLGAUGE_RANGE        10
#define CMDLEN_CHANGE_LVGLGAUGE_VALUE        8
#define CMDLEN_CHANGE_LVGLCOMPASS_VALUE      8
#define CMDLEN_CHANGE_LVGLMETER_SCALE        9
#define CMDLEN_CHANGE_LVGLMETER_RANGE        10
#define CMDLEN_CHANGE_LVGLMETER_VALUE        8
#define CMDLEN_CHANGE_LVGLCHART_SERIE        9
#define CMDLEN_CHANGE_LVGLCHART_POINT        9
#define CMDLEN_CHANGE_LVGLSTATION_VALUE      9

#define CMDLEN_DEINIT_LVGL          5
#define CMDLEN_RESET_LVGL           4
#define CMDLEN_INIT_LVGL            7

// cmd
#define CMD_OF_DRAWPIXEL        2
#define CMD_OF_DRAWLINE         3
#define CMD_OF_DRAWRECT         4
#define CMD_OF_DRAWROUNDRECT    5
#define CMD_OF_DRAWCIRCLE       6
#define CMD_OF_DRAWTRIANGLE     7
#define CMD_OF_SETBACKLIGHT     8
#define CMD_OF_FILLSCREEN       9
#define CMD_OF_FILLRECT         10
#define CMD_OF_FILLROUNDRECT    11
#define CMD_OF_FILLCIRCLE       12
#define CMD_OF_FILLTRIANGLE     13

#define CMD_OF_DRAWICON         20
#define CMD_OF_DRAWSTRING       21
#define CMD_OF_DRAWSTRING2      22
#define CMD_OF_DRAWDISKIMG      23   // hyy

#define CMD_DRAW_LVGLSLIDER     31
#define CMD_DRAW_LVGLBAR        32
#define CMD_DRAW_LVGLSLIDER     31
#define CMD_DRAW_LVGLARC        33
#define CMD_DRAW_LVGLGAUGE      34
#define CMD_DRAW_LVGLSTATION    35
#define CMD_DRAW_LVGLCOMPASS    36
#define CMD_DRAW_LVGLLINEMETER  37
#define CMD_DRAW_LVGLCHART      38

#define CMD_RESET_LVGL          0x80
#define CMD_INIT_LVGL           0x81
#define CMD_DEINIT_LVGL         0x82

#define CMD_HEADER_HIGH         0x55
#define CMD_HEADER_LOW          0xaa

#ifndef HYY_LCD_UNUSED
#define HYY_LCD_UNUSED(x) ((void) x)
#endif


class DFRobot_LcdDisplay
{
public:

  /**
   * @enum sLcdIcon_t
   * @brief 表示不同的图标,当要显示图标时,选择对应的枚举即可
   */
  typedef enum {
    // 安全safe icon
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

    // 表情expression icon
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

    // 传感器sensor icon
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
    eIconLight,
    eIconUVLight,

    // 动物animal icon
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

    // 环境与自然Environment and Nature icon
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

    // 季节 season icon
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

    // 交通工具 transport icon
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

    // 农业Agriculture icon
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

    // 人物形象 people icon
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

    // 食物 food icon
    eIconAvocado,
    eIconBanana,
    eIconBeerMug,
    eIconBentoBox,
    eIconBirthdayCake,
    eIconBread,
    eIconCake,
    eIconCarrot,
    eIconCheeseWedge,
    eIconCherry,/**<樱桃*/
    eIconChocolateBar,/**<巧克力*/
    eIconCutOfMeat,/**<肉*/
    eIconEarOfCorn,/**<玉米*/
    eIconEgg,/**<鸡蛋*/
    eIconFrenchFries,/**<薯条*/
    eIconGrapes,/**<葡萄*/
    eIconGreenSalad,/**<绿沙拉*/
    eIconHamburger,/**<汉堡包*/
    eIconHotBeverage,/**<热饮料*/
    eIconPeach,/**<桃子*/
    eIconPineapple,/**<菠萝*/
    eIconPopcorn,/**<爆米花*/
    eIconPotato,/**<土豆*/
    eIconRedApple,/**<红苹果*/
    eIconSalad,/**<沙拉*/
    eIconShaomai,/**<烧卖*/
    eIconSandwich,/**<三明治*/
    eIconShortcake,/**<短蛋糕*/
    eIconStrawberry,/**<草莓*/

    //数字图形图标
    eIconArrowDown,/**<向下箭头*/
    eIconArrowLeft,/**<向左箭头*/
    eIconArrowRight,/**<向右箭头*/
    eIconArrowUp,/**<向上箭头*/
    eIconDiamond,/**<菱形*/
    eIconEight,/**<数字8*/
    eIconFive,/**<数字5*/
    eIconFivePointedStar,/**<五角星*/
    eIconHeart,/**<心形*/
    eIconNine,/**<数字9*/
    eIconFour,/**<数字4*/
    eIconOctagon,/**<八边形*/
    eIconOne,/**<数字1*/
    eIconPentagon,/**<五边形*/
    eIconRectangle,/**<矩形*/
    eIconSeven,/**<数字7*/
    eIconSix,/**<数字6*/
    eIconSquare,/**<正方形*/
    eIconThree,/**<数字3*/
    eIconTriangle,/**<三角形*/
    eIconTwo,/**<数字2*/
    eIconWindmillShape,/**<风车形*/
    eIconZero,/**<数字0*/

    //天气图标
    eIconCloudy,/**<多云*/
    eIconMoon,/**<月亮*/
    eIconLightning,/**<闪电*/
    eIconMoonCloudy,/**<多云夜晚*/
    eIconRainUmbrella,/**<下雨有伞*/
    eIconRainbow1,/**<彩虹1*/
    eIconRainbow2,/**<彩虹2*/
    eIconRainy,/**<下雨*/
    eIconSnow,/**<雪*/
    eIconSnowy,/**<有雪的天气*/
    eIconSunnyCloudy,/**<晴天多云*/
    eIconWhirlwind,/**<旋风*/

    // 音乐图标
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

    // 运动图标
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

    // 植物图标
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
   * @brief 当使用字体,把以下枚举传入setFont()函数,选择不同的字体
   */
  typedef enum {
    eChinese,/**<中文*/
    eShiftJis,/**<日文*/
    eAscii,/**<ACSII*/
    eGreece,/**<希腊文*/
    eCyrillic,/**<西里尔文*/
    eHebrew,/**<希伯来文*/
    eThailand,/**<不等宽希腊文*/
    eAlb,/**<阿拉伯文*/
    eKhmer,/**<高棉文*/
    eKorean,/**<韩文*/
  }eLcdFont_t;

  /**
    * @struct sControlinf_t
    * @brief 指向不同的控件的对象
    */
  typedef struct controlinf {
    uint32_t number; /**<控件编号 */
    uint16_t id; /**<控件id,不同的控件有不同的作用*/
    int16_t x; /**<控件所在位置的x坐标*/
    int16_t y; /**<控件所在位置的y坐标*/
    int16_t width; /**<控件宽度 */
    int16_t height; /**<控件高度*/
    uint16_t color; /**<控件颜色*/
    struct controlinf* inf; /**<下一个控件指针 */
  }sControlinf_t;

public:
  /**
   * @fn DFRobot_LcdDisplay
   * @brief 构造函数
   * @return None
   */
  DFRobot_LcdDisplay();

  /**
   * @fn begin
   * @brief 初始化函数
   * @return true(成功)/false(失败)
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
   * @fn lvglInit
   * @brief 初始化lvgl,但是用lvgl的控件或者图标时,需要调用此函数
   * @param bg_color lvgl背景颜色
   */
  void lvglInit(uint16_t bg_color = 0xffee);

  /**
   * @fn setFont
   * @brief 设置字体, 方便计算一连串字体的显示位置
   * @param font 字体种类, eLcdFont_t
   */
  void setFont(eLcdFont_t font);
  /**
   * @fn fillScreen
   * @brief Function to refresh screen
   * @param color color to fill screen, RGB565 format
   */
  void fillScreen(uint16_t color);

  /**
   * @fn setBackLight
   * @brief 设置屏幕背光
   * @param on true(打开)/false(关闭)
   */
  void setBackLight(bool on);

  /**
   * @fn drawLine
   * @brief 在屏幕上画一条直线
   * @param x0 直线起点x坐标
   * @param y0 直线起点y坐标
   * @param x1 直线终点x坐标
   * @param y1 直线终点y坐标
   * @param color the color of the line, RGB565 format
   */
  void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);

  /**
   * @fn drawRect
   * @brief 在屏幕上画矩形
   * @param x 矩形起点x坐标
   * @param y 矩形起点y坐标
   * @param w  矩形的宽度
   * @param h  矩形的高度
   * @param color 矩形颜色
   */
  void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

  /**
   * @fn fillRect
   * @brief 在屏幕上填充矩形
   * @param x 矩形起点x坐标
   * @param y 矩形起点y坐标
   * @param w  矩形的宽度
   * @param h  矩形的高度
   * @param color 矩形颜色
   */
  void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

  /**
   * @fn drawRoundRect
   * @brief 在屏幕上画圆角矩形
   * @param x0 矩形起点x坐标
   * @param y0 矩形起点y坐标
   * @param w  矩形的宽度
   * @param h  矩形的高度
   * @param radius  圆角半径
   * @param color 矩形颜色
   */
  void drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
    int16_t radius, uint16_t color);

  /**
   * @fn fillRoundRect
   * @brief 在屏幕上填充圆角矩形
   * @param x0 矩形起点x坐标
   * @param y0 矩形起点y坐标
   * @param w  矩形的宽度
   * @param h  矩形的高度
   * @param radius  圆角半径
   * @param color 矩形颜色
   */
  void fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
    int16_t radius, uint16_t color);

  /**
   * @fn drawCircle
   * @brief 在屏幕画圆
   * @param x0 圆心x坐标
   * @param y0 圆心y坐标
   * @param r  圆的半径
   * @param color 圆的颜色
   */
  void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);

  /**
   * @fn fillCircle
   * @brief 在屏幕填充圆
   * @param x0 圆心x坐标
   * @param y0 圆心y坐标
   * @param r  圆的半径
   * @param color 圆的颜色
   */
  void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);

  /**
   * @fn drawTriangle
   * @brief 在屏幕画一个三角形
   * @param x0 三角形第一个点的x坐标
   * @param y0 三角形第一个点的y坐标
   * @param x1 三角形第二个点的x坐标
   * @param y1 三角形第二个点的y坐标
   * @param x2 三角形第三个点的x坐标
   * @param y2 三角形第三个点的y坐标
   * @param color 圆的颜色
   */
  void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
    int16_t x2, int16_t y2, uint16_t color);

  /**
   * @fn fillTriangle
   * @brief 在屏幕填充一个三角形
   * @param x0 三角形第一个点的x坐标
   * @param y0 三角形第一个点的y坐标
   * @param x1 三角形第二个点的x坐标
   * @param y1 三角形第二个点的y坐标
   * @param x2 三角形第三个点的x坐标
   * @param y2 三角形第三个点的y坐标
   * @param color 圆的颜色
   */
  void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
    int16_t x2, int16_t y2, uint16_t color);

  /**
   * @fn drawIcon
   * @brief 绘制一个图标
   * @param x 图标第一个点的x坐标
   * @param y 图标第一个点的y坐标
   * @param id 图标对应的编号
   * @param size 图标大小缩放系数
   * @return 图标控件的对象
   */
  sControlinf_t* drawIcon(int16_t x, int16_t y, uint16_t id, uint16_t size = 255);

  /**
   * @fn drawDiskImg
   * @brief 绘制u盘里面的图片(bmp或者png)
   * @param x 图片第一个点的x坐标
   * @param y 图片第一个点的y坐标
   * @param str 图片完整文件名, 如 "/img/cat.bmp"
   * @param size 图片大小缩放系数
   * @return 图片控件的对象
   * @note 因ram较小, bmp 和 png 的规格有限制
   */
  sControlinf_t* drawDiskImg(int16_t x, int16_t y, String str, uint16_t size = 255);

  /**
   * @fn creatSlider
   * @brief 创建一个滑条控件
   * @param x 滑条的x坐标
   * @param y 滑条的y坐标
   * @param width 滑条的宽度
   * @param height 滑条的高度
   * @param color 滑条的颜色
   * @return 滑条控件的对象
   */
  sControlinf_t* creatSlider(uint16_t x, uint16_t y, uint8_t width, uint8_t height, uint16_t color);

  /**
   * @fn setSliderValue
   * @brief 设置滑条的值
   * @param obj 滑条控件的对象
   * @param value 滑条的值
   */
  void setSliderValue(sControlinf_t* obj, uint8_t value);

  /**
   * @fn creatBar
   * @brief 创建一个进度条控件
   * @param x 进度条的x坐标
   * @param y 进度条的y坐标
   * @param width 进度条的宽度
   * @param height 进度条的高度
   * @param color 进度条的颜色
   * @return 进度条控件的对象
   */
  sControlinf_t* creatBar(uint16_t x, uint16_t y, uint16_t width, uint8_t height, uint16_t color);

  /**
   * @fn setBar
   * @brief 设置进度条值,可带单位,但必须由数字开始
   * @param obj 滑条控件的对象
   * @param str 滑条的值
   */
  void setBar(sControlinf_t* obj, String str);

  /**
   * @fn creatChart
   * @brief 创建一个图表控件
   * @param strX 图表x轴上的标签
   * @param strY 图表y轴上的标签
   * @param type 图表的类型(折线图/柱状图)
   * @return 图表控件的对象
   */
  sControlinf_t* creatChart(String strX, String strY, uint8_t type);

  /**
   * @fn creatChartSerie
   * @brief 在图表中创建折线图或柱状图序列
   * @param obj 图表控件的对象
   * @param color 折线图/柱状图的颜色
   * @return 返回图的编号
   */
  uint8_t creatChartSerie(sControlinf_t* obj, uint16_t color);

  /**
   * @fn addChart
   * @brief 分配数据序列并将其添加到图表中
   * @param obj 图表控件的对象
   * @param id the allocated data series
   * @param point 曲线图/柱状图需要数据的数组
   * @param len  数组长度
   */
  uint8_t addChart(sControlinf_t* obj, uint8_t id, uint16_t point[], uint8_t len);

  /**
   * @fn creatGauge
   * @brief 创建一个表盘控件
   * @param x 控件所在x轴坐标
   * @param y 控件所在y轴坐标
   * @param width  控件的宽度
   * @param height 控件的高度
   * @param color 控件的颜色
   * @return 表盘控件的对象
   */
  sControlinf_t* creatGauge(uint16_t x, uint16_t y, uint8_t width, uint8_t height, uint16_t color);

  /**
   * @fn setGaugeScale
   * @brief 设置表盘的参数
   * @param obj 表盘的对象
   * @param angle angle of the scale (0..360)
   * @param start minimum value
   * @param end maximum value
   */
  void setGaugeScale(sControlinf_t* obj, uint16_t angle, int16_t start, int16_t end);

  /**
   * @fn setGaugeValue
   * @brief 设置表盘指示的值
   * @param obj 表盘的对象
   * @param value the new value
   */
  void setGaugeValue(sControlinf_t* obj, uint16_t value);

  /**
   * @fn creatCompass
   * @brief 创建一个指南针控件
   * @param x 控件所在x轴坐标
   * @param y 控件所在y轴坐标
   * @param width  控件的宽度
   * @param height 控件的高度
   * @return 指南针控件的对象
   */
  sControlinf_t* creatCompass(uint16_t x, uint16_t y, uint8_t width, uint8_t height);

  /**
   * @fn setCompassScale
   * @brief 设置指南针指针的角度
   * @param obj 指南针的对象
   * @param scale 指针角度(0~360)
   */
  void setCompassScale(sControlinf_t* obj, uint16_t scale);

  /**
   * @fn creatArc
   * @brief 创建一个角度控件
   * @param x 控件所在x轴坐标
   * @param y 控件所在y轴坐标
   * @param width  控件的宽度
   * @param height 控件的高度
   * @return 角度控件的对象
   */
  sControlinf_t* creatArc(uint16_t x, uint16_t y, uint8_t width, uint8_t height);

  /**
   * @fn setArcRotation
   * @brief 设置角度控件数值
   * @param obj 角度控件的对象
   * @param rotation the new value
   */
  void setArcRotation(sControlinf_t* obj, uint16_t rotation);

  /**
   * @fn creatLineMeter
   * @brief 创建一个线形仪表控件
   * @param x 控件所在x轴坐标
   * @param y 控件所在y轴坐标
   * @param width  控件的宽度
   * @param height 控件的高度
   * @param color 控件的颜色
   * @return 线形仪表控件的对象
   */
  sControlinf_t* creatLineMeter(uint16_t x, uint16_t y, uint8_t width, uint8_t height, uint16_t color);

  /**
   * @fn setMeterScale
   * @brief 设置线形仪表控件的参数
   * @param obj pointer to a line meter object
   * @param angle angle of the scale (0..360)
   * @param start minimum value
   * @param end maximum value
   */
  void setMeterScale(sControlinf_t* obj, uint16_t angle, int16_t start, int16_t end);

  /**
   * @fn setMeterValue
   * @brief 在线路仪表上设置一个新值
   * @param obj pointer to a line meter object
   * @param value new value
   */
  void setMeterValue(sControlinf_t* obj, uint16_t value);

  /**
   * @fn drawString(uint8_t x, uint8_t y, String str, uint8_t type, uint16_t color)
   * @brief 在屏幕上显示文字
   * @param x 起始位置的x坐标
   * @param y 起始位置的y坐标
   * @param str 要显示的文字
   * @param type 文字大小(只适用于eChinse和eAscii),0(24大小),1(12大小)
   * @param color 文字的颜色
   */
  void drawString(uint16_t x, uint8_t y, String str, uint8_t type, uint16_t color);

  /**
   * @fn drawString(uint8_t x, uint8_t y, String str, uint8_t type, uint16_t color, uint16_t bgColor)
   * @brief 在屏幕上显示文字
   * @param x 起始位置的x坐标
   * @param y 起始位置的y坐标
   * @param str 要显示的文字
   * @param type 文字大小(只适用于eChinse和eAscii),0(24大小),1(12大小)
   * @param color 文字的颜色
   * @param bgColor 文字背景的颜色
   */
  void drawString(uint16_t x, uint8_t y, String str, uint8_t type, uint16_t color, uint16_t bgColor);

  /**
   * @fn drawLcdTime
   * @brief 在屏幕上显示设置的时间
   * @param x 起始位置的x坐标
   * @param y 起始位置的y坐标
   * @param hour 小时
   * @param Minute 分钟
   * @param seconds 秒
   * @param fontSize 字体大小
   * @param color 字体颜色
   * @param bgColor 字体背景颜色
   */
  void drawLcdTime(uint8_t x, uint8_t y, uint8_t hour, uint8_t Minute, uint8_t seconds, uint8_t fontSize, uint16_t color, uint16_t bgColor);

  /**
   * @fn drawLcdDate
   * @brief 在屏幕上显示设置的日期
   * @param x 起始位置的x坐标
   * @param y 起始位置的y坐标
   * @param month 月份
   * @param day 天数
   * @param weeks 星期数
   * @param fontSize 字体大小
   * @param color 字体颜色
   * @param bgColor 字体背景颜色
   */
  void drawLcdDate(uint8_t x, uint8_t y, uint8_t month, uint8_t day, uint8_t weeks, uint8_t fontSize, uint16_t color, uint16_t bgColor);

  /**
   * @fn lvglDelete
   * @brief 指定某个已创建的控件进行删除
   * @param obj 要删除对象的控件
   */
  void lvglDelete(sControlinf_t* obj);

  /**
   * @fn reset
   * @brief 复位显示屏,显示屏复位后,创建的lvlg控件全部删除,显示的内容也一并清楚
   */
  void reset();

private:
  /**
   * @fn creatStations
   * @brief 创建一个气象站控件
   * @param x 控件所在x轴坐标
   * @param y 控件所在y轴坐标
   * @param zoo  控件大小缩放指数(128~512)
   * @param color 控件的颜色
   * @param str 气象站图标里面的文字
   * @return 气象站控件的对象
   */
  sControlinf_t* creatStations(uint16_t x, uint16_t y, uint16_t zoo, uint16_t color, String str);

  /**
   * @fn setStationValue
   * @brief 设置气象站控件
   * @param obj 气象站控件的对象
   * @param value 气象监测值, 如温度
   */
  void setStationValue(sControlinf_t* obj, String value);

  TwoWire* _pWire;
  sControlinf_t head;
  eLcdFont_t _font = eAscii;
  uint8_t _deviceAddr;
  uint16_t getWordLen(uint8_t* utf8, uint8_t len);
  uint8_t addChartPoint(sControlinf_t* obj, uint8_t id, uint16_t value);
  uint8_t utf8toUnicode(uint8_t* utf8, uint16_t& uni);
  uint8_t setChartTickTexts(sControlinf_t* obj, String xtext, String ytext);
  void drawStringHepler(uint16_t x, uint8_t y, uint8_t* uni, uint8_t lenght, uint8_t type, uint16_t color, uint16_t fgColor);
  void drawStringHepler(uint16_t x, uint8_t y, uint8_t* uni, uint8_t lenght, uint8_t type, uint16_t color);
  uint8_t getNumber(uint8_t id);
  uint8_t* creatCommand(uint8_t cmd, uint8_t len);
  virtual void    writeCommand(uint8_t* pBuf, uint16_t len) = 0;
  virtual void    readACK(uint8_t* pBuf, uint16_t len) = 0;
};


class DFRobot_Lcd_IIC: public DFRobot_LcdDisplay
{
public:
  /**
   * @fn DFRobot_Lcd_IIC
   * @brief 构造函数
   * @param pWire I2C控制器对象
   * @param addr I2C地址,默认为0x2c
   * @return None
   */
  DFRobot_Lcd_IIC(TwoWire* pWire = &Wire, uint8_t addr = 0x2c);

  /**
   * @fn begin
   * @brief 初始化函数,初始化I2C控制器,打开屏幕背光
   * @return 布尔类型
   * @retval true 成功
   * @retval false 失败
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
   * @brief 构造函数
   * @return None
   */
  DFRobot_Lcd_UART(Stream& s);
  /**
   * @fn begin
   * @brief 初始化函数,初始化UART控制器,打开屏幕背光
   * @param s 传入UART对象
   * @retval true 成功
   * @retval false 失败
   */
  bool begin();

private:
  Stream* _s;
  void writeCommand(uint8_t* pBuf, uint16_t len);
  void readACK(uint8_t* pBuf, uint16_t len);
};

#endif