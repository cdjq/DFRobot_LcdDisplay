/*!
 * @file DFRobot_LcdDisplay.cpp
 * @brief Define the infrastructure of the DFRobot_LcdDisplay class
 * @details This library can drive the DFR0997 display, and it can easily drive the color screen through both the I2C interface and UART interface
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @License     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @maintainer [qsjhyy](yihuan.huang@dfrobot.com)
 * @version  V1.0
 * @date  2023-05-29
 * @url https://github.com/DFRobot/DFRobot_LcdDisplay
 */
#include "DFRobot_LcdDisplay.h"
#include <Wire.h>
#include <Arduino.h>

uint8_t wordLen[10];

DFRobot_LcdDisplay::DFRobot_LcdDisplay()
{
}

bool DFRobot_LcdDisplay::begin()
{
  return true;
}

void DFRobot_LcdDisplay::drawPixel(int16_t x, int16_t y, uint16_t color)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAWPIXEL, CMDLEN_OF_DRAWPIXEL);
  if (320 <= x) {
    x = 319;
  }
  if (240 <= y) {
    y = 239;
  }
  cmd[4] = x >> 8;
  cmd[5] = x & 0xFF;
  cmd[6] = y >> 8;
  cmd[7] = y & 0xFF;
  cmd[8] = color >> 8;
  cmd[9] = color & 0xFF;
  writeCommand(cmd, CMDLEN_OF_DRAWPIXEL);
  free(cmd);
}

void DFRobot_LcdDisplay::cleanScreen()
{
  uint8_t* cmd = creatCommand(0x1D, 0x04);
  writeCommand(cmd, 4);
  delay(1500);
  free(cmd);
}

uint8_t DFRobot_LcdDisplay::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t width, uint32_t color)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_LINE, CMD_DRAW_LINE_LEN);
  uint8_t id = getID(CMD_OF_DRAW_LINE);
  cmd[4] = id;
  cmd[5] = width;
  cmd[6] = color >> 16;
  cmd[7] = color >> 8;
  cmd[8] = color & 0xFF;
  cmd[9] = x0 >> 8;
  cmd[10] = x0 & 0xFF;
  cmd[11] = y0 >> 8;
  cmd[12] = y0 & 0xFF;
  cmd[13] = x1 >> 8;
  cmd[14] = x1 & 0xFF;
  cmd[15] = y1 >> 8;
  cmd[16] = y1 & 0xFF;
  writeCommand(cmd, CMD_DRAW_LINE_LEN);
  free(cmd);
  return id;
}

void DFRobot_LcdDisplay::updateLine(uint8_t id, int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t width, uint32_t color){
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_LINE, CMD_DRAW_LINE_LEN);
  cmd[4] = id;
  cmd[5] = width;
  cmd[6] = color >> 16;
  cmd[7] = color >> 8;
  cmd[8] = color & 0xFF;
  cmd[9] = x0 >> 8;
  cmd[10] = x0 & 0xFF;
  cmd[11] = y0 >> 8;
  cmd[12] = y0 & 0xFF;
  cmd[13] = x1 >> 8;
  cmd[14] = x1 & 0xFF;
  cmd[15] = y1 >> 8;
  cmd[16] = y1 & 0xFF;
  writeCommand(cmd, CMD_DRAW_LINE_LEN);
  delay(10);
  free(cmd);
}

void DFRobot_LcdDisplay::deleteLine(uint8_t id){
  uint8_t* cmd = creatCommand(CMD_DELETE_OBJ, CMD_DELETE_OBJ_LEN);
  cmd[4] = CMD_OF_DRAW_LINE;
  cmd[5] = id;
  writeCommand(cmd, CMD_DELETE_OBJ_LEN);
  free(cmd);
  deleteNodeByID((GenericNode**)&line_head,id);
}

uint8_t DFRobot_LcdDisplay::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t borderWidth, uint32_t borderColor, uint8_t fill, uint32_t fillColor, uint8_t rounded)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_RECT, CMD_OF_DRAW_RECT_LEN);
  uint8_t id = getID(CMD_OF_DRAW_RECT);
  cmd[4] = id;
  cmd[5] = borderWidth;
  cmd[6] = borderColor >> 16;
  cmd[7] = borderColor >> 8;
  cmd[8] = borderColor & 0xFF;
  cmd[9] = fill;
  cmd[10] = fillColor >> 16;
  cmd[11] = fillColor >> 8;
  cmd[12] = fillColor & 0xFF;
  cmd[13] = rounded;
  cmd[14] = x >> 8;
  cmd[15] = x & 0xFF;
  cmd[16] = y >> 8;
  cmd[17] = y & 0xFF;
  cmd[18] = w >> 8;
  cmd[19] = w & 0xFF;
  cmd[20] = h >> 8;
  cmd[21] = h & 0xFF;
  writeCommand(cmd, CMD_OF_DRAW_RECT_LEN);
  free(cmd);
  return id;
}

void DFRobot_LcdDisplay::updateRect(uint8_t id, int16_t x, int16_t y, int16_t w, int16_t h, uint8_t borderWidth, uint32_t borderColor, uint8_t fill, uint32_t fillColor, uint8_t rounded)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_RECT, CMD_OF_DRAW_RECT_LEN);
  cmd[4] = id;
  cmd[5] = borderWidth;
  cmd[6] = borderColor >> 16;
  cmd[7] = borderColor >> 8;
  cmd[8] = borderColor & 0xFF;
  cmd[9] = fill;
  cmd[10] = fillColor >> 16;
  cmd[11] = fillColor >> 8;
  cmd[12] = fillColor & 0xFF;
  cmd[13] = rounded;
  cmd[14] = x >> 8;
  cmd[15] = x & 0xFF;
  cmd[16] = y >> 8;
  cmd[17] = y & 0xFF;
  cmd[18] = w >> 8;
  cmd[19] = w & 0xFF;
  cmd[20] = h >> 8;
  cmd[21] = h & 0xFF;
  writeCommand(cmd, CMD_OF_DRAW_RECT_LEN);
  free(cmd);
}

void DFRobot_LcdDisplay::deleteRect(uint8_t id){
  uint8_t* cmd = creatCommand(CMD_DELETE_OBJ, CMD_DELETE_OBJ_LEN);
  cmd[4] = CMD_OF_DRAW_RECT;
  cmd[5] = id;
  writeCommand(cmd, CMD_DELETE_OBJ_LEN);
  free(cmd);
  deleteNodeByID((GenericNode**)&rect_head,id);
}

uint8_t DFRobot_LcdDisplay::drawCircle(int16_t x, int16_t y, int16_t r, uint8_t borderWidth, uint32_t borderColor, uint8_t fill, uint32_t fillColor)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_CIRCLE, CMD_OF_DRAW_CIRCLE_LEN);
  uint8_t id = getID(CMD_OF_DRAW_CIRCLE);
  cmd[4] = id;
  cmd[5] = borderWidth;
  cmd[6] = borderColor >> 16;
  cmd[7] = borderColor >> 8;
  cmd[8] = borderColor & 0xFF;
  cmd[9] = fill;
  cmd[10] = fillColor >> 16;
  cmd[11] = fillColor >> 8;
  cmd[12] = fillColor & 0xFF;
  cmd[13] = r >> 8;
  cmd[14] = r & 0xFF;
  cmd[15] = x >> 8;
  cmd[16] = x & 0xFF;
  cmd[17] = y >> 8;
  cmd[18] = y & 0xFF;
  writeCommand(cmd, CMD_OF_DRAW_CIRCLE_LEN);
  free(cmd);
  return id;
}

void DFRobot_LcdDisplay::updateCircle(uint8_t id, int16_t x, int16_t y, int16_t r, uint8_t borderWidth, uint32_t borderColor, uint8_t fill, uint32_t fillColor)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_CIRCLE, CMD_OF_DRAW_CIRCLE_LEN);
  cmd[4] = id;
  cmd[5] = borderWidth;
  cmd[6] = borderColor >> 16;
  cmd[7] = borderColor >> 8;
  cmd[8] = borderColor & 0xFF;
  cmd[9] = fill;
  cmd[10] = fillColor >> 16;
  cmd[11] = fillColor >> 8;
  cmd[12] = fillColor & 0xFF;
  cmd[13] = r >> 8;
  cmd[14] = r & 0xFF;
  cmd[15] = x >> 8;
  cmd[16] = x & 0xFF;
  cmd[17] = y >> 8;
  cmd[18] = y & 0xFF;
  writeCommand(cmd, CMD_OF_DRAW_CIRCLE_LEN);
  free(cmd);
}

void DFRobot_LcdDisplay::deleteCircle(uint8_t id){
  uint8_t* cmd = creatCommand(CMD_DELETE_OBJ, CMD_DELETE_OBJ_LEN);
  cmd[4] = CMD_OF_DRAW_CIRCLE;
  cmd[5] = id;
  writeCommand(cmd, CMD_DELETE_OBJ_LEN);
  free(cmd);
  deleteNodeByID((GenericNode**)&circle_head,id);
}

uint8_t DFRobot_LcdDisplay::drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
  int16_t x2, int16_t y2, uint8_t borderWidth, uint32_t borderColor, uint8_t fill, uint32_t fillColor)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_TRIANGLE, CMD_OF_DRAW_TRIANGLE_LEN);
  uint8_t id = getID(CMD_OF_DRAW_TRIANGLE);
  cmd[4] = id;
  cmd[5] = borderWidth;
  cmd[6] = borderColor >> 16;
  cmd[7] = borderColor >> 8;
  cmd[8] = borderColor & 0xFF;
  cmd[9] = fill;
  cmd[10] = fillColor >> 16;
  cmd[11] = fillColor >> 8;
  cmd[12] = fillColor & 0xFF;
  cmd[13] = x0 >> 8;
  cmd[14] = x0 & 0xFF;
  cmd[15] = y0 >> 8;
  cmd[16] = y0 & 0xFF;
  cmd[17] = x1 >> 8;
  cmd[18] = x1 & 0xFF;
  cmd[19] = y1 >> 8;
  cmd[20] = y1 & 0xFF;
  cmd[21] = x2 >> 8;
  cmd[22] = x2 & 0xFF;
  cmd[23] = y2 >> 8;
  cmd[24] = y2 & 0xFF;
  writeCommand(cmd, CMD_OF_DRAW_TRIANGLE_LEN);
  free(cmd);
  return id;
}

void DFRobot_LcdDisplay::updateTriangle(uint8_t id, int16_t x0, int16_t y0, int16_t x1, int16_t y1,
  int16_t x2, int16_t y2, uint8_t borderWidth, uint32_t borderColor, uint8_t fill, uint32_t fillColor)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_TRIANGLE, CMD_OF_DRAW_TRIANGLE_LEN);
  cmd[4] = id;
  cmd[5] = borderWidth;
  cmd[6] = borderColor >> 16;
  cmd[7] = borderColor >> 8;
  cmd[8] = borderColor & 0xFF;
  cmd[9] = fill;
  cmd[10] = fillColor >> 16;
  cmd[11] = fillColor >> 8;
  cmd[12] = fillColor & 0xFF;
  cmd[13] = x0 >> 8;
  cmd[14] = x0 & 0xFF;
  cmd[15] = y0 >> 8;
  cmd[16] = y0 & 0xFF;
  cmd[17] = x1 >> 8;
  cmd[18] = x1 & 0xFF;
  cmd[19] = y1 >> 8;
  cmd[20] = y1 & 0xFF;
  cmd[21] = x2 >> 8;
  cmd[22] = x2 & 0xFF;
  cmd[23] = y2 >> 8;
  cmd[24] = y2 & 0xFF;
  writeCommand(cmd, CMD_OF_DRAW_TRIANGLE_LEN);
  free(cmd);
}

void DFRobot_LcdDisplay::deleteTriangle(uint8_t id){
  uint8_t* cmd = creatCommand(CMD_DELETE_OBJ, CMD_DELETE_OBJ_LEN);
  cmd[4] = CMD_OF_DRAW_TRIANGLE;
  cmd[5] = id;
  writeCommand(cmd, CMD_DELETE_OBJ_LEN);
  free(cmd);
  deleteNodeByID((GenericNode**)&triangle_head,id);
}

uint8_t DFRobot_LcdDisplay::drawIcon(int16_t x, int16_t y, uint16_t iconNum, uint16_t size)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_ICON_INTERNAL, CMD_OF_DRAW_ICON_INTERNAL_LEN);
  uint8_t id = getID(CMD_OF_DRAW_ICON_INTERNAL);
  cmd[4] = id;
  cmd[5] = iconNum >> 8;
  cmd[6] = iconNum & 0xFF;
  cmd[7] = size >> 8;
  cmd[8] = size & 0xFF;
  cmd[9] = x >> 8;
  cmd[10] = x & 0xFF;
  cmd[11] = y >> 8;
  cmd[12] = y & 0xFF;
  writeCommand(cmd, CMD_OF_DRAW_ICON_INTERNAL_LEN);
  free(cmd);
  return id;
}

uint8_t DFRobot_LcdDisplay::drawIcon(int16_t x, int16_t y, String str, uint16_t zoom){
  char* data = str.c_str();
  uint8_t length = strlen(data);
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_ICON_EXTERNAL, length + 11);
  uint8_t id = getID(CMD_OF_DRAW_ICON_INTERNAL);
  cmd[4] = id;
  cmd[5] = zoom >> 8;
  cmd[6] = zoom & 0xFF;
  cmd[7] = x >> 8;
  cmd[8] = x & 0xFF;
  cmd[9] = y >> 8;
  cmd[10] = y & 0xFF;
  memcpy(cmd+11, data, length);
  writeCommand(cmd, length + 11);
  free(cmd);
  return id;
}

void DFRobot_LcdDisplay::setAngleIcon(uint8_t id, int16_t angle){
  uint8_t* cmd = creatCommand(CMD_SET_ANGLE_OBJ, CMD_SET_ANGLE_OBJ_LEN);
  cmd[4] = CMD_OF_DRAW_ICON_INTERNAL;
  cmd[5] = id;
  cmd[6] = angle >> 8;
  cmd[7] = angle & 0xFF;
  writeCommand(cmd, CMD_SET_ANGLE_OBJ_LEN);
  free(cmd);
}

void DFRobot_LcdDisplay::updateIcon(uint8_t iconId, int16_t x, int16_t y, uint16_t iconNum, uint16_t size)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_ICON_INTERNAL, CMD_OF_DRAW_ICON_INTERNAL_LEN);
  cmd[4] = iconId;
  cmd[5] = iconNum >> 8;
  cmd[6] = iconNum & 0xFF;
  cmd[7] = size >> 8;
  cmd[8] = size & 0xFF;
  cmd[9] = x >> 8;
  cmd[10] = x & 0xFF;
  cmd[11] = y >> 8;
  cmd[12] = y & 0xFF;
  writeCommand(cmd, CMD_OF_DRAW_ICON_INTERNAL_LEN);
  free(cmd);
}

void DFRobot_LcdDisplay::updateIcon(uint8_t iconId, int16_t x, int16_t y, String str, uint16_t zoom){
  char* data = str.c_str();
  uint8_t length = strlen(data);
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_ICON_EXTERNAL, length + 11);
  cmd[4] = iconId;
  cmd[5] = zoom >> 8;
  cmd[6] = zoom & 0xFF;
  cmd[7] = x >> 8;
  cmd[8] = x & 0xFF;
  cmd[9] = y >> 8;
  cmd[10] = y & 0xFF;
  memcpy(cmd+11, data, length);
  writeCommand(cmd, length + 11);
  free(cmd);
}

void DFRobot_LcdDisplay::deleteIcon(uint8_t id){
  uint8_t* cmd = creatCommand(CMD_DELETE_OBJ, CMD_DELETE_OBJ_LEN);
  cmd[4] = CMD_OF_DRAW_ICON_INTERNAL;
  cmd[5] = id;
  writeCommand(cmd, CMD_DELETE_OBJ_LEN);
  free(cmd);
  deleteNodeByID((GenericNode**)&icon_head, id);
}

uint8_t DFRobot_LcdDisplay::drawGif(int16_t x, int16_t y, uint16_t gifNum, uint16_t size)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_GIF_INTERNAL, CMD_OF_DRAW_GIF_INTERNAL_LEN);
  uint8_t id = getID(CMD_OF_DRAW_GIF_INTERNAL);
  cmd[4] = id;
  cmd[5] = gifNum >> 8;
  cmd[6] = gifNum & 0xFF;
  cmd[7] = size >> 8;
  cmd[8] = size & 0xFF;
  cmd[9] = x >> 8;
  cmd[10] = x & 0xFF;
  cmd[11] = y >> 8;
  cmd[12] = y & 0xFF;
  writeCommand(cmd, CMD_OF_DRAW_GIF_INTERNAL_LEN);
  free(cmd);
  return id;
}

void DFRobot_LcdDisplay::deleteGif(uint8_t id){
  uint8_t* cmd = creatCommand(CMD_DELETE_OBJ, CMD_DELETE_OBJ_LEN);
  cmd[4] = CMD_OF_DRAW_GIF_INTERNAL;
  cmd[5] = id;
  writeCommand(cmd, CMD_DELETE_OBJ_LEN);
  free(cmd);
  deleteNodeByID((GenericNode**)&gif_head, id);
}

DFRobot_LcdDisplay::sControlinf_t* DFRobot_LcdDisplay::drawDiskImg(int16_t x, int16_t y, String pathStr, uint16_t size)
{
  sControlinf_t* img = (sControlinf_t*)malloc(sizeof(sControlinf_t));
  if (img == NULL) {
    DBG("img malloc fail !");
  }
  img->x = x;
  img->y = y;
  img->id = pathStr.endsWith(".png");   // 0: .bmp ; 1: .png
  img->number = getNumber(1);
  img->inf = NULL;

  sControlinf_t* obj = &head;
  while (obj->inf != NULL) {
    obj = obj->inf;
  }
  obj->inf = img;

  if (size > 512) size = 512;
  if (size < 128) size = 128;

  int16_t length = pathStr.length() - 4;   // Remove the suffix to save on transmission byte count
  if (20 <= length) {
    DBG("The path name is too long. Shorten the path name");
    return NULL;
  }
  uint8_t* cmd = creatCommand(CMD_OF_DRAWDISKIMG, 12 + length);
  cmd[4] = img->number;
  cmd[5] = img->id;
  cmd[6] = x >> 8;
  cmd[7] = x & 0xFF;
  cmd[8] = y >> 8;
  cmd[9] = y & 0xFF;
  cmd[10] = size >> 8;
  cmd[11] = size & 0xFF;
  for (uint8_t i = 0; i < length; i++) {
    cmd[12 + i] = pathStr[i];
  }

  writeCommand(cmd, 12 + length);
  free(cmd);

  delay(1500);   // Reading and parsing images from a USB drive is slow, resulting in slow display

  return img;
}

uint8_t DFRobot_LcdDisplay::creatSlider(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_SLIDER, CMD_OF_DRAW_SLIDER_LEN);
  uint8_t id = getID(CMD_OF_DRAW_SLIDER);
  cmd[4] = id;
  cmd[5] = color >> 16;
  cmd[6] = color >> 8;
  cmd[7] = color & 0xFF;
  cmd[8] = x >> 8;
  cmd[9] = x & 0xFF;
  cmd[10] = y >> 8;
  cmd[11] = y & 0xFF;
  cmd[12] = width >> 8;
  cmd[13] = width & 0xFF;
  cmd[14] = height >> 8;
  cmd[15] = height & 0xFF;
  writeCommand(cmd, CMD_OF_DRAW_SLIDER_LEN);
  free(cmd);
  return id;
}

void DFRobot_LcdDisplay::updateSlider(uint8_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_SLIDER, CMD_OF_DRAW_SLIDER_LEN);
  cmd[4] = id;
  cmd[5] = color >> 16;
  cmd[6] = color >> 8;
  cmd[7] = color & 0xFF;
  cmd[8] = x >> 8;
  cmd[9] = x & 0xFF;
  cmd[10] = y >> 8;
  cmd[11] = y & 0xFF;
  cmd[12] = width >> 8;
  cmd[13] = width & 0xFF;
  cmd[14] = height >> 8;
  cmd[15] = height & 0xFF;
  writeCommand(cmd, CMD_OF_DRAW_SLIDER_LEN);
  free(cmd);
}

void DFRobot_LcdDisplay::setSliderValue(uint8_t sliderId, uint16_t value)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_SLIDER_VALUE, CMD_SET_SLIDER_VALUE_LEN);
  cmd[4] = sliderId;
  cmd[5] = value >> 8;
  cmd[6] = value & 0xFF;
  writeCommand(cmd, CMD_SET_SLIDER_VALUE_LEN);
  free(cmd);
}

void DFRobot_LcdDisplay::deleteSlider(uint8_t id){
  uint8_t* cmd = creatCommand(CMD_DELETE_OBJ, CMD_DELETE_OBJ_LEN);
  cmd[4] = CMD_OF_DRAW_SLIDER;
  cmd[5] = id;
  writeCommand(cmd, CMD_DELETE_OBJ_LEN);
  free(cmd);
  deleteNodeByID((GenericNode**)&slider_head, id);
}

uint8_t DFRobot_LcdDisplay::creatBar(uint16_t x, uint16_t y, uint16_t width, uint8_t height, uint32_t color)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_BAR, CMD_OF_DRAW_BAR_LEN);
  uint8_t id = getID(CMD_OF_DRAW_BAR);
  cmd[4] = id;
  cmd[5] = color >> 16;
  cmd[6] = color >> 8;
  cmd[7] = color & 0xFF;
  cmd[8] = x >> 8;
  cmd[9] = x & 0xFF;
  cmd[10] = y >> 8;
  cmd[11] = y & 0xFF;
  cmd[12] = width >> 8;
  cmd[13] = width & 0xFF;
  cmd[14] = height >> 8;
  cmd[15] = height & 0xFF;
  writeCommand(cmd, CMD_OF_DRAW_BAR_LEN);
  free(cmd);
  return id;
}

void DFRobot_LcdDisplay::updateBar(uint8_t id, uint16_t x, uint16_t y, uint16_t width, uint8_t height, uint32_t color)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_BAR, CMD_OF_DRAW_BAR_LEN);
  cmd[4] = id;
  cmd[5] = color >> 16;
  cmd[6] = color >> 8;
  cmd[7] = color & 0xFF;
  cmd[8] = x >> 8;
  cmd[9] = x & 0xFF;
  cmd[10] = y >> 8;
  cmd[11] = y & 0xFF;
  cmd[12] = width >> 8;
  cmd[13] = width & 0xFF;
  cmd[14] = height >> 8;
  cmd[15] = height & 0xFF;
  writeCommand(cmd, CMD_OF_DRAW_BAR_LEN);
  free(cmd);
}

void DFRobot_LcdDisplay::setBar(uint8_t barId, uint16_t value)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_BAR_VALUE, CMD_SET_BAR_VALUE_LEN);
  if (cmd == NULL) {
    DBG("cmd null");
    return;
  }
  cmd[4] = barId;
  cmd[5] = value >> 8;
  cmd[6] = value;
  writeCommand(cmd, CMD_SET_BAR_VALUE_LEN);
  free(cmd);
}

void DFRobot_LcdDisplay::deleteBar(uint8_t id){
  uint8_t* cmd = creatCommand(CMD_DELETE_OBJ, CMD_DELETE_OBJ_LEN);
  cmd[4] = CMD_OF_DRAW_BAR;
  cmd[5] = id;
  writeCommand(cmd, CMD_DELETE_OBJ_LEN);
  free(cmd);
  deleteNodeByID((GenericNode**)&bar_head,id);
}

uint8_t DFRobot_LcdDisplay::getNumber(uint8_t id)
{
  LCD_UNUSED(id);
  uint16_t number = 1;
  sControlinf_t* obj = &head;
  sControlinf_t* last;
  while (1) {
    last = obj;
    obj = obj->inf;
    if (obj == NULL) {
      number = last->number + 1;
      break;
    }
  }
  return number;
}

uint8_t DFRobot_LcdDisplay:: getNewID(sGenericNode_t** head) {
    uint8_t id = 1;
    sGenericNode_t* temp = *head;
    if(temp == NULL){
      Serial.println("NULL");
    }

    // 查找链表中最后一个节点并获取当前最大ID
    while (temp) {
        id = temp->id + 1; // 更新ID
        if (!temp->next) {
            break;
        }
        temp = (sGenericNode_t*)temp->next;
    }

    // 创建新节点并设置ID
    sGenericNode_t* new_node = (sGenericNode_t*)malloc(sizeof(sGenericNode_t));
    if (new_node) {
        new_node->id = id;
        new_node->next = NULL;

        // 添加到链表末尾
        if (temp) {
            temp->next = new_node;
        } else {
            *head = new_node;
        }
    } else {
        // 处理内存分配失败的情况
        id = 0; // 返回错误代码或0表示失败
    }
    Serial.println(id);
    return id;
}

void DFRobot_LcdDisplay::deleteNodeByID(sGenericNode_t** head, uint8_t id) {
    // 检查是否提供了有效的头节点指针
    if (head == NULL || *head == NULL) {
        return;
    }
    sGenericNode_t* temp = *head;
    sGenericNode_t* prev = NULL;

    // 检查头节点是否是要删除的节点
    if (temp != NULL && temp->id == id) {
        *head = temp->next; // 改变头指针
        free(temp);         // 释放旧的头节点
        // 如果这是链表中的最后一个节点，确保 head 被设置为 NULL
        if (*head == NULL) {
            return;
        }
    } else {
        // 搜索要删除的节点，保留其前一个节点
        while (temp != NULL && temp->id != id) {
            prev = temp;
            temp = (sGenericNode_t*)temp->next;
        }
        // 如果没有找到该ID的节点，则返回
        if (temp == NULL) return;

        // 从链表中移除节点
        prev->next = temp->next;

        // 释放内存
        free(temp);
    }

    // 检查链表是否为空
    if (*head == NULL) {
        return;
    }

    // 检查链表是否为空
    temp = *head;
    while (temp) {
        if (temp->next != NULL) {
            return; // 发现至少还有一个节点
        }
        temp = (sGenericNode_t*)temp->next;
    }

    // 如果链表为空，则将 head 设置为 NULL
    *head = NULL;
}

uint8_t DFRobot_LcdDisplay::getID(uint8_t type)
{
  LCD_UNUSED(type);
  uint8_t id = 0;
  switch(type){
    case CMD_OF_DRAW_LINE_CHART:
      id = getNewID((GenericNode**)&line_chart_head);
      break;
    case CMD_OF_DRAW_SERIE:
      id = getNewID((GenericNode**)&series_head);
      break;
    case CMD_OF_DRAW_COMPASS:
      id = getNewID((GenericNode**)&compass_head);
      break;
    case CMD_OF_DRAW_TEXT:
      id = getNewID((GenericNode**)&text_head);
      break;
    case CMD_OF_DRAW_GAUGE:
      id = getNewID((GenericNode**)&gauge_head);
      break;
    case CMD_OF_DRAW_LINE:
      id = getNewID((GenericNode**)&line_head);
      break;
    case CMD_OF_DRAW_RECT:
      id = getNewID((GenericNode**)&rect_head);
      break;
    case CMD_OF_DRAW_TRIANGLE:
      id = getNewID((GenericNode**)&triangle_head);
      break;
    case CMD_OF_DRAW_CIRCLE:
      id = getNewID((GenericNode**)&circle_head);
      break;
    case CMD_OF_DRAW_LINE_METER:
      id = getNewID((GenericNode**)&lineMeter_head);
      break;
    case CMD_OF_DRAW_BAR:
      id = getNewID((GenericNode**)&bar_head);
      break;
    case CMD_OF_DRAW_SLIDER:
      id = getNewID((GenericNode**)&slider_head);
      break;
    case CMD_OF_DRAW_ICON_INTERNAL:
      id = getNewID((GenericNode**)&icon_head);
      break;
    case CMD_OF_DRAW_GIF_INTERNAL:
      id = getNewID((GenericNode**)&gif_head);
      break;
    default:
      break;
  }
  return id;
}

uint8_t DFRobot_LcdDisplay::creatGauge(uint16_t x, uint16_t y, uint16_t diameter, uint16_t start, uint16_t end, uint32_t pointerColor, uint32_t bgColor)
{
  uint8_t id = getID(CMD_OF_DRAW_GAUGE);
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_GAUGE, CMD_OF_DRAW_GAUGE_LEN);
  cmd[4] = id;
  cmd[5] = diameter >> 8;
  cmd[6] = diameter & 0xFF;
  cmd[7] = start >> 8;
  cmd[8] = start & 0xFF;
  cmd[9] = end >> 8;
  cmd[10] = end & 0xFF;
  cmd[11] = pointerColor >>16;
  cmd[12] = pointerColor >> 8;
  cmd[13] = pointerColor & 0xFF;
  cmd[14] = bgColor >>16;
  cmd[15] = bgColor >> 8;
  cmd[16] = bgColor & 0xFF;
  cmd[17] = x >> 8;
  cmd[18] = x & 0xFF;
  cmd[19] = y >> 8;
  cmd[20] = y & 0xFF;
  writeCommand(cmd, CMD_OF_DRAW_GAUGE_LEN);
  free(cmd);
 return id;
}

void DFRobot_LcdDisplay::updateGauge(uint8_t id, uint16_t x, uint16_t y, uint16_t diameter, uint16_t start, uint16_t end, uint32_t pointerColor, uint32_t bgColor)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_GAUGE, CMD_OF_DRAW_GAUGE_LEN);
  cmd[4] = id;
  cmd[5] = diameter >> 8;
  cmd[6] = diameter & 0xFF;
  cmd[7] = start >> 8;
  cmd[8] = start & 0xFF;
  cmd[9] = end >> 8;
  cmd[10] = end & 0xFF;
  cmd[11] = pointerColor >>16;
  cmd[12] = pointerColor >> 8;
  cmd[13] = pointerColor & 0xFF;
  cmd[14] = bgColor >>16;
  cmd[15] = bgColor >> 8;
  cmd[16] = bgColor & 0xFF;
  cmd[17] = x >> 8;
  cmd[18] = x & 0xFF;
  cmd[19] = y >> 8;
  cmd[20] = y & 0xFF;
  writeCommand(cmd, CMD_OF_DRAW_GAUGE_LEN);
  free(cmd);
 return id;
}

void DFRobot_LcdDisplay::setGaugeScale(sControlinf_t* obj, uint16_t angle, int16_t start, int16_t end)
{

  uint8_t* cmd = creatCommand(CMD_DRAW_LVGLGAUGE, CMDLEN_CHANGE_LVGLGAUGE_SCALE);
  cmd[4] = obj->number;
  cmd[5] = 3;
  cmd[6] = angle >> 8;
  cmd[7] = angle & 0xFF;
  cmd[8] = 6;
  cmd[9] = 6;

  writeCommand(cmd, CMDLEN_CHANGE_LVGLGAUGE_SCALE);
  free(cmd);

  uint8_t* cmd1 = creatCommand(CMD_DRAW_LVGLGAUGE, CMDLEN_CHANGE_LVGLGAUGE_RANGE);
  cmd1[4] = obj->number;
  cmd1[5] = 1;
  cmd1[6] = start >> 8;
  cmd1[7] = start & 0xFF;
  cmd1[8] = end >> 8;
  cmd1[9] = end & 0xFF;
  writeCommand(cmd1, CMDLEN_CHANGE_LVGLGAUGE_RANGE);
  free(cmd1);
}

void DFRobot_LcdDisplay::setGaugeValue(uint8_t gaugeId, uint16_t value)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_GAUGE_VALUE, CMD_SET_GAUGE_VALUE_LEN);
  cmd[4] = gaugeId;
  cmd[5] = value >> 8;
  cmd[6] = value & 0xFF;
  writeCommand(cmd, CMD_SET_GAUGE_VALUE_LEN);
  free(cmd);
}

void DFRobot_LcdDisplay::deleteGauge(uint8_t id){
  uint8_t* cmd = creatCommand(CMD_DELETE_OBJ, CMD_DELETE_OBJ_LEN);
  cmd[4] = CMD_OF_DRAW_GAUGE;
  cmd[5] = id;
  writeCommand(cmd, CMD_DELETE_OBJ_LEN);
  free(cmd);
  deleteNodeByID((GenericNode**)&gauge_head,id);
}


uint8_t DFRobot_LcdDisplay::creatCompass(uint16_t x, uint16_t y, uint16_t diameter)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_COMPASS,CMD_DRAW_COMPASS_LEN);
  uint8_t compassId = getID(CMD_OF_DRAW_COMPASS);
  cmd[4] = compassId;
  cmd[5] = diameter >> 8;
  cmd[6] = diameter & 0xFF;
  cmd[7] = x >> 8;
  cmd[8] = x & 0xFF;
  cmd[9] = y >> 8;
  cmd[10] = y & 0xFF;
  writeCommand(cmd, CMD_DRAW_COMPASS_LEN);
  free(cmd);
  return compassId;
}

void DFRobot_LcdDisplay::updateCompass(uint8_t id, uint16_t x, uint16_t y, uint16_t diameter)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_COMPASS,CMD_DRAW_COMPASS_LEN);
  cmd[4] = id;
  cmd[5] = diameter >> 8;
  cmd[6] = diameter & 0xFF;
  cmd[7] = x >> 8;
  cmd[8] = x & 0xFF;
  cmd[9] = y >> 8;
  cmd[10] = y & 0xFF;
  writeCommand(cmd, CMD_DRAW_COMPASS_LEN);
  free(cmd);
}

void DFRobot_LcdDisplay::setCompassScale(uint8_t compassId, uint16_t scale)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_COMPASS_VALUE, CMD_SET_COMPASS_VALUE_LEN);
  cmd[4] = compassId;
  cmd[5] = scale >> 8;
  cmd[6] = scale & 0xFF;

  writeCommand(cmd, CMD_SET_COMPASS_VALUE_LEN);
  free(cmd);
}

void DFRobot_LcdDisplay::deleteCompass(uint8_t id){
  uint8_t* cmd = creatCommand(CMD_DELETE_OBJ, CMD_DELETE_OBJ_LEN);
  cmd[4] = CMD_OF_DRAW_COMPASS;
  cmd[5] = id;
  writeCommand(cmd, CMD_DELETE_OBJ_LEN);
  free(cmd);
  deleteNodeByID((GenericNode**)&compass_head,id);
}

uint8_t DFRobot_LcdDisplay::utf8toUnicode(uint8_t* utf8, uint16_t& uni)
{
  uint8_t lenght = 0;
  uint8_t index = 0;

  if (utf8[index] >= 0xfc) {

    uni = utf8[index] & 1;
    index++;
    for (uint8_t i = 1;i <= 5;i++) {
      uni <<= 6;
      uni |= (utf8[index] & 0x3f);

      index++;
    }
    lenght = 6;
  } else if (utf8[index] >= 0xf8) {

    uni = utf8[index] & 3;
    index++;
    for (uint8_t i = 1;i <= 4;i++) {
      uni <<= 6;
      uni |= (utf8[index] & 0x03f);

      index++;
    }
    lenght = 5;
  } else if (utf8[index] >= 0xf0) {

    uni = utf8[index] & 7;
    index++;
    for (uint8_t i = 1;i <= 3;i++) {
      uni <<= 6;
      uni |= (utf8[index] & 0x03f);
      index++;
    }
    lenght = 4;
  } else if (utf8[index] >= 0xe0) {
    uni = utf8[index] & 15;
    index++;
    for (uint8_t i = 1;i <= 2;i++) {
      uni <<= 6;
      uni |= (utf8[index] & 0x03f);
      index++;
    }
    lenght = 3;
  } else if (utf8[index] >= 0xc0) {

    uni = utf8[index] & 0x1f;
    index++;
    for (uint8_t i = 1;i <= 1;i++) {
      uni <<= 6;
      uni |= (utf8[index] & 0x03f);
      index++;


    }
    lenght = 2;
  } else if (utf8[index] <= 0x80) {
    uni = (utf8[index] & 0x7f);
    lenght = 1;

  } else {
    DBG("no this");
  }
  return lenght;
}

void DFRobot_LcdDisplay::drawStringHepler(uint16_t x, uint8_t y, uint8_t* uni, uint8_t lenght, uint8_t type, uint16_t color, uint16_t fgColor)
{


  uint8_t* cmd = creatCommand(CMD_OF_DRAWSTRING, lenght + 13);
  if (cmd == NULL) {
    DBG("cmd null");
  }
  cmd[4] = x >> 8;
  cmd[5] = x & 0xFF;
  cmd[6] = y;

  cmd[7] = type;
  cmd[8] = color >> 8;
  cmd[9] = color & 0xFF;
  cmd[10] = fgColor >> 8;
  cmd[11] = fgColor & 0xFF;
  cmd[12] = _font;
  for (uint8_t i = 0;i < lenght;i++) {
    cmd[13 + i] = uni[i];
  }
  writeCommand(cmd, lenght + 13);
  free(cmd);

}

void DFRobot_LcdDisplay::setFont(eLcdFont_t font)
{
  _font = font;
}

void DFRobot_LcdDisplay::setBackgroundColor(uint32_t bg_color)
{
  uint8_t* cmd = creatCommand(CMD_SET_BACKGROUND_COLOR, CMD_SET_LEN);
  cmd[4] = bg_color >> 16;
  cmd[5] = bg_color >> 8;
  cmd[6] = bg_color & 0xFF;
  writeCommand(cmd, CMD_SET_LEN);
  free(cmd);
  delay(300);
}

void DFRobot_LcdDisplay::setBackgroundImg(uint8_t location, String str){
  char* data = str.c_str();
  uint8_t length = strlen(data);
  uint8_t* cmd = creatCommand(CMD_SET_BACKGROUND_IMG, length + 5);
  cmd[4] = location;
  memcpy(cmd+5, data, length);
  writeCommand(cmd, length + 5);
  free(cmd);
}

uint16_t DFRobot_LcdDisplay::getWordLen(uint8_t* utf8, uint8_t len)
{
  uint16_t index = 0;
  // uint32_t uni = 0;
  uint16_t length = 0;DBG("\n");
  DBG("len=");DBG(len);
  while (index < len) {
    DBG("index=");DBG(index);
    if (utf8[index] >= 0xfc) {
      index++;
      for (uint8_t i = 1;i <= 5;i++) {
        index++;
      }
      length += 1;
    } else if (utf8[index] >= 0xf8) {
      index++;
      for (uint8_t i = 1;i <= 4;i++) {
        index++;
      }
      length += 1;
    } else if (utf8[index] >= 0xf0) {
      index++;
      for (uint8_t i = 1;i <= 3;i++) {
        index++;
      }
      length += 15;
    } else if (utf8[index] >= 0xe0) {
      index++;
      for (uint8_t i = 1;i <= 2;i++) {
        index++;
      }
      length += 15;
    } else if (utf8[index] >= 0xc0) {

      index++;
      for (uint8_t i = 1;i <= 1;i++) {
        index++;
      }
      length += 9;
    } else if (utf8[index] <= 0x80) {
      index++;
      length += 9;
    }
  }
  return length;
}

uint8_t DFRobot_LcdDisplay::drawString(uint16_t x, uint16_t y, String str, uint8_t fontSize, uint32_t color)
{
  char* data = str.c_str();
  uint8_t length = strlen(data);
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_TEXT, length + 13);
  uint8_t id = getID(CMD_OF_DRAW_TEXT);
  cmd[4] = id;
  cmd[5] = fontSize;
  cmd[6] = color >> 16;
  cmd[7] = color >> 8;
  cmd[8] = color & 0xFF;
  cmd[9] = x >> 8;
  cmd[10] = x & 0xFF;
  cmd[11] = y >> 8;
  cmd[12] = y & 0xFF;
  memcpy(cmd+13, data, length);
  writeCommand(cmd, length + 13);
  free(cmd);
  return id;
}

void DFRobot_LcdDisplay::updateString(uint8_t id, uint16_t x, uint16_t y, String str, uint8_t fontSize, uint32_t color)
{
  char* data = str.c_str();
  uint16_t length = strlen(data);
  if(length > 242){
    length = 242;
  }
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_TEXT, length + 13);
  if(cmd != NULL){
    cmd[4] = id;
    cmd[5] = fontSize;
    cmd[6] = color >> 16;
    cmd[7] = color >> 8;
    cmd[8] = color & 0xFF;
    cmd[9] = x >> 8;
    cmd[10] = x & 0xFF;
    cmd[11] = y >> 8;
    cmd[12] = y & 0xFF;
    memcpy(cmd+13, data, length);
    writeCommand(cmd, length + 13);
    free(cmd);
  }
}

void DFRobot_LcdDisplay::deleteString(uint8_t id){
  uint8_t* cmd = creatCommand(CMD_DELETE_OBJ, CMD_DELETE_OBJ_LEN);
  cmd[4] = CMD_OF_DRAW_TEXT;
  cmd[5] = id;
  writeCommand(cmd, CMD_DELETE_OBJ_LEN);
  free(cmd);
  deleteNodeByID((GenericNode**)&text_head,id);
}

uint8_t DFRobot_LcdDisplay::drawLcdTime(uint8_t x, uint8_t y, uint8_t hour, uint8_t Minute, uint8_t seconds, uint8_t fontSize, uint16_t color)
{
  String time1 = "";

  if (hour < 10) {
    time1 += "0";
  }
  time1 += String(hour);
  time1 += ":";
  if (Minute < 10) {
    time1 += "0";
  }
  time1 += String(Minute);
  time1 += ":";
  if (seconds < 10) {
    time1 += "0";
  }
  time1 += String(seconds);

  return drawString(x, y, time1, fontSize, color);
}

void DFRobot_LcdDisplay::updateLcdTime(uint8_t id, uint8_t x, uint8_t y, uint8_t hour, uint8_t Minute, uint8_t seconds, uint8_t fontSize, uint16_t color)
{
  String time1 = "";

  if (hour < 10) {
    time1 += "0";
  }
  time1 += String(hour);
  time1 += ":";
  if (Minute < 10) {
    time1 += "0";
  }
  time1 += String(Minute);
  time1 += ":";
  if (seconds < 10) {
    time1 += "0";
  }
  time1 += String(seconds);

  updateString(id, x, y, time1, fontSize, color);
}

void DFRobot_LcdDisplay::drawLcdDate(uint8_t x, uint8_t y, uint8_t month, uint8_t day, uint8_t weeks, uint8_t fontSize, uint16_t color)
{
  String date = "";
  if (month < 10) {
    date += "0";
  }
  date += String(month);
  date += "月";
  if (day < 10) {
    date += "0";
  }
  date += String(day);
  date += "日 周";
  if (weeks == 1) {
    date += "一";
  } else if (weeks == 2) {
    date += "二";
  } else if (weeks == 3) {
    date += "三";
  } else if (weeks == 4) {
    date += "四";
  } else if (weeks == 5) {
    date += "五";
  } else if (weeks == 6) {
    date += "六";
  } else if (weeks == 7) {
    date += "日";
  }
  drawString(x, y, date, fontSize, color);
}

uint8_t DFRobot_LcdDisplay::creatLineMeter(uint16_t x, uint16_t y, uint16_t size, uint16_t start, uint16_t end, uint32_t pointerColor, uint32_t bgColor)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_LINE_METER, CMD_OF_DRAW_LINE_METER_LEN);
  uint8_t id = getID(CMD_OF_DRAW_LINE_METER);
  cmd[4] = id;
  cmd[5] = size >> 8;
  cmd[6] = size & 0xFF;
  cmd[7] = start >> 8;
  cmd[8] = start & 0xFF;
  cmd[9] = end >> 8;
  cmd[10] = end & 0xFF;
  cmd[11] = pointerColor >> 16;
  cmd[12] = pointerColor >> 8;
  cmd[13] = pointerColor & 0xFF;
  cmd[14] = bgColor >> 16;
  cmd[15] = bgColor >> 8;
  cmd[16] = bgColor & 0xFF;
  cmd[17] = x >> 8;
  cmd[18] = x & 0xFF;
  cmd[19] = y >> 8;
  cmd[20] = y & 0xFF;
  writeCommand(cmd, CMD_OF_DRAW_LINE_METER_LEN);
  free(cmd);
  return id;
}

void DFRobot_LcdDisplay::updateLineMeter(uint8_t id, uint16_t x, uint16_t y, uint16_t size, uint16_t start, uint16_t end, uint32_t pointerColor, uint32_t bgColor)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_LINE_METER, CMD_OF_DRAW_LINE_METER_LEN);
  cmd[4] = id;
  cmd[5] = size >> 8;
  cmd[6] = size & 0xFF;
  cmd[7] = start >> 8;
  cmd[8] = start & 0xFF;
  cmd[9] = end >> 8;
  cmd[10] = end & 0xFF;
  cmd[11] = pointerColor >> 16;
  cmd[12] = pointerColor >> 8;
  cmd[13] = pointerColor & 0xFF;
  cmd[14] = bgColor >> 16;
  cmd[15] = bgColor >> 8;
  cmd[16] = bgColor & 0xFF;
  cmd[17] = x >> 8;
  cmd[18] = x & 0xFF;
  cmd[19] = y >> 8;
  cmd[20] = y & 0xFF;
  writeCommand(cmd, CMD_OF_DRAW_LINE_METER_LEN);
  free(cmd);
}

void DFRobot_LcdDisplay::deleteLineMeter(uint8_t id){
  uint8_t* cmd = creatCommand(CMD_DELETE_OBJ, CMD_DELETE_OBJ_LEN);
  cmd[4] = CMD_OF_DRAW_LINE_METER;
  cmd[5] = id;
  writeCommand(cmd, CMD_DELETE_OBJ_LEN);
  free(cmd);
  deleteNodeByID((GenericNode**)&lineMeter_head,id);
}

void DFRobot_LcdDisplay::setTopLineMeter(uint8_t id){
  uint8_t* cmd = creatCommand(CMD_SET_TOP_OBJ, CMD_SET_TOP_OBJ_LEN);
  cmd[4] = CMD_OF_DRAW_LINE_METER;
  cmd[5] = id;
  writeCommand(cmd, CMD_DELETE_OBJ_LEN);
  free(cmd);
}

uint8_t DFRobot_LcdDisplay::creatChart(String strX, String strY, uint32_t bgColor, uint8_t type)
{
  uint8_t * creatCmd = creatCommand(CMD_OF_DRAW_LINE_CHART, CMD_DRAW_CHART_LEN);
  uint8_t id = getID(CMD_OF_DRAW_LINE_CHART);
  creatCmd[4] = id;
  creatCmd[5] = type;
  creatCmd[6] = bgColor >> 16;
  creatCmd[7] = bgColor >> 8;
  creatCmd[8] = bgColor;
  writeCommand(creatCmd, CMD_DRAW_CHART_LEN);
  free(creatCmd);
  delay(100);
  setChartAxisTexts(id, 0, strX);
  delay(100);
  setChartAxisTexts(id, 1, strY);
  return id;
}

void DFRobot_LcdDisplay::updateChart(uint8_t id, uint32_t bgColor, uint8_t type)
{
  uint8_t * creatCmd = creatCommand(CMD_OF_DRAW_LINE_CHART, CMD_DRAW_CHART_LEN);
  creatCmd[4] = id;
  creatCmd[5] = type;
  creatCmd[6] = bgColor >> 16;
  creatCmd[7] = bgColor >> 8;
  creatCmd[8] = bgColor;
  writeCommand(creatCmd, CMD_DRAW_CHART_LEN);
  free(creatCmd);
}

uint8_t DFRobot_LcdDisplay::creatChartSeries(uint8_t chartId, uint32_t color)
{

  uint8_t* cmd = creatCommand(CMD_OF_DRAW_SERIE, CMD_DRAW_SERIE_LEN);
  uint8_t serieId = getID(CMD_OF_DRAW_SERIE);
  cmd[4] = serieId;
  cmd[5] = chartId;   
  cmd[6] = color >> 16;
  cmd[7] = color >> 8;
  cmd[8] = color ;
  writeCommand(cmd, CMDLEN_CHANGE_LVGLCHART_SERIE);
  free(cmd);
  return serieId;
}

void DFRobot_LcdDisplay::updateChartSeries(uint8_t chartId, uint8_t seriesId, uint32_t color){
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_SERIE, CMD_DRAW_SERIE_LEN);
  cmd[4] = seriesId;
  cmd[5] = chartId;   
  cmd[6] = color >> 16;
  cmd[7] = color >> 8;
  cmd[8] = color ;
  writeCommand(cmd, CMDLEN_CHANGE_LVGLCHART_SERIE);
  free(cmd);
}

uint8_t DFRobot_LcdDisplay::setChartTickTexts(sControlinf_t* obj, String xtext, String ytext)
{
  uint8_t len_x = xtext.length();
  uint8_t len_y = ytext.length();
  uint8_t* cmd = creatCommand(CMD_DRAW_LVGLCHART, len_x + 7);
  cmd[4] = obj->number;
  cmd[5] = 3;   // 3 : The type of instruction that stores label information
  cmd[6] = 1;   // Add the X-axis label
  for (uint8_t i = 0;i < len_x;i++) {
    cmd[7 + i] = xtext[i];
  }
  writeCommand(cmd, len_x + 7);
  free(cmd);

  delay(10);

  uint8_t* cmd1 = creatCommand(CMD_DRAW_LVGLCHART, len_y + 7);
  cmd1[4] = obj->number;
  cmd1[5] = 3;
  cmd1[6] = 2;   // Add the Y-axis label
  for (uint8_t i = 0;i < len_y;i++) {
    cmd1[7 + i] = ytext[i];
  }

  writeCommand(cmd1, len_y + 7);
  free(cmd1);
  return 1;
}

uint8_t DFRobot_LcdDisplay::setChartAxisTexts(uint8_t chartId, uint8_t axis, String text)
{
  uint8_t textLen = text.length();
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_LINE_CHART_TEXT, textLen + 6);
  cmd[4] = chartId;
  cmd[5] = axis;
  for (uint8_t i = 0;i < textLen;i++) {
    cmd[6 + i] = text[i];
  }
  writeCommand(cmd, textLen + 6);
  free(cmd);
  return 1;
}

uint8_t DFRobot_LcdDisplay::addChartPoint(sControlinf_t* obj, uint8_t id, uint16_t value)
{
  uint8_t* cmd = creatCommand(CMD_DRAW_LVGLCHART, CMDLEN_CHANGE_LVGLCHART_POINT);
  cmd[4] = obj->number;
  cmd[5] = 2;   // 2 : Added instruction type for chart series points
  cmd[6] = id;
  cmd[7] = value >> 8;
  cmd[8] = value & 0xFF;

  writeCommand(cmd, CMDLEN_CHANGE_LVGLCHART_POINT);
  free(cmd);
  return 1;
}

void DFRobot_LcdDisplay::updateChartPoint(uint8_t chartId, uint8_t SeriesId, uint8_t pointNum, uint16_t value){
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_SERIE_DATA, 10);
  cmd[4] = chartId;
  cmd[5] = SeriesId;
  cmd[6] = 1;
  cmd[7] = pointNum;
  cmd[8] = value >> 8;
  cmd[9] = value & 0xFF;
  writeCommand(cmd,  10);
  free(cmd);
}

uint8_t DFRobot_LcdDisplay::addChartSeriesData(uint8_t chartId, uint8_t SeriesId, uint16_t point[], uint8_t len)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_SERIE_DATA, len*2 + 8);
  cmd[4] = chartId;
  cmd[5] = SeriesId;
  cmd[6] = 0;
  cmd[7] = 0;
  for(uint8_t i = 0; i < len; i++){
    cmd[8 + 2*i]     = point[i]>>8;
    cmd[8 + 2*i + 1] = point[i];
  }
  writeCommand(cmd,  len*2 + 8);
  free(cmd);
  return 1;
}

void DFRobot_LcdDisplay::setTopChart(uint8_t id){
  uint8_t* cmd = creatCommand(CMD_SET_TOP_OBJ, CMD_SET_TOP_OBJ_LEN);
  cmd[4] = CMD_OF_DRAW_LINE_CHART;
  cmd[5] = id;
  writeCommand(cmd, CMD_SET_TOP_OBJ_LEN);
  free(cmd);
}

void DFRobot_LcdDisplay::deleteChart(uint8_t id){
  uint8_t* cmd = creatCommand(CMD_DELETE_OBJ, CMD_DELETE_OBJ_LEN);
  cmd[4] = CMD_OF_DRAW_LINE_CHART;
  cmd[5] = id;
  writeCommand(cmd, CMD_DELETE_OBJ_LEN);
  free(cmd);
  deleteNodeByID((GenericNode**)&line_chart_head,id);
}


void DFRobot_LcdDisplay::setMeterValue(uint8_t lineMeterId, uint16_t value)
{

  uint8_t* cmd = creatCommand(CMD_OF_DRAW_LINE_METER_VALUE, CMD_SET_LINE_METER_VALUE_LEN);
  cmd[4] = lineMeterId;
  cmd[5] = value >> 8;
  cmd[6] = value & 0xFF;
  writeCommand(cmd, CMD_SET_LINE_METER_VALUE_LEN);
  free(cmd);
}

void DFRobot_LcdDisplay::setMeterScale(sControlinf_t* obj, uint16_t angle, int16_t start, int16_t end)
{
  uint8_t* cmd = creatCommand(CMD_DRAW_LVGLLINEMETER, CMDLEN_CHANGE_LVGLMETER_SCALE);
  cmd[4] = obj->number;
  cmd[5] = 3;
  cmd[6] = angle >> 8;
  cmd[7] = angle & 0xFF;
  cmd[8] = 18;

  writeCommand(cmd, CMDLEN_CHANGE_LVGLMETER_SCALE);
  free(cmd);

  uint8_t* cmd1 = creatCommand(CMD_DRAW_LVGLLINEMETER, CMDLEN_CHANGE_LVGLMETER_RANGE);
  cmd1[4] = obj->number;
  cmd1[5] = 1;
  cmd1[6] = start >> 8;
  cmd1[7] = start & 0xFF;
  cmd1[8] = end >> 8;
  cmd1[9] = end & 0xFF;
  writeCommand(cmd1, CMDLEN_CHANGE_LVGLMETER_RANGE);
  free(cmd1);
}

void DFRobot_LcdDisplay::lvglDelete(sControlinf_t* obj)
{
  if (obj == NULL) {
    DBG("NULL pointer");
    return;
  }
  uint8_t* cmd = creatCommand(CMD_DEINIT_LVGL, CMDLEN_DEINIT_LVGL);
  cmd[4] = obj->number;
  writeCommand(cmd, CMDLEN_DEINIT_LVGL);
  free(cmd);

  // uint16_t number = 1;
  sControlinf_t* objDel = &head;
  sControlinf_t* last;
  while (objDel->inf != NULL) {
    last = objDel;
    objDel = objDel->inf;
    if (obj->number == objDel->number) {
      last->inf = objDel->inf;
      free(objDel);
      break;
    }
  }
  delay(500);   // Make sure to delete succeed

}

uint8_t* DFRobot_LcdDisplay::creatCommand(uint8_t cmd, uint8_t len)
{
  uint8_t* data = (uint8_t*)malloc(sizeof(uint8_t) * len);
  if (data == NULL) {
    DBG("malloc FAIL");
    return NULL;
  }
  data[0] = CMD_HEADER_HIGH;
  data[1] = CMD_HEADER_LOW;
  data[2] = len - CMDLEN_OF_HEAD_LEN;
  data[3] = cmd;
  return data;
}

DFRobot_Lcd_IIC::DFRobot_Lcd_IIC(TwoWire* pWire, uint8_t addr)
{
  _deviceAddr = addr;
  _pWire = pWire;

}

bool DFRobot_Lcd_IIC::begin()
{
  _pWire->begin();
  if (_pWire == NULL) return false;
  _pWire->begin();
  _pWire->setClock(100000);
  _pWire->beginTransmission(_deviceAddr);
  if (_pWire->endTransmission() != 0) return false;

  return true;
}

void DFRobot_Lcd_IIC::writeCommand(uint8_t* pBuf, uint16_t len)
{
  uint16_t bytesSent = 0; // 已发送的字节数
  uint16_t bytesToSend = len; // 还需发送的字节数
  if (pBuf == NULL) {
    DBG("pBuf ERROR!! : null pointer");
  }
  Serial.print("len = ");
  Serial.println(len);
  while (bytesToSend > 0) {
    uint16_t currentTransferSize = (bytesToSend < 32) ? bytesToSend : 32;
    
    // 开始I2C传输
    _pWire->beginTransmission(_deviceAddr);
    
    // 发送当前批次的数据
    _pWire->write(&pBuf[bytesSent], currentTransferSize);
    
    // 结束当前I2C传输
    _pWire->endTransmission();
    
    // 更新已发送和待发送的字节数
    bytesSent += currentTransferSize;
    bytesToSend -= currentTransferSize;
    
    // 等待一小段时间再继续下一批次的发送，以确保设备处理完毕
    delay(2);
  }
}

void DFRobot_Lcd_IIC::readACK(uint8_t* pBuf, uint16_t len)
{
  if (pBuf == NULL) {
    DBG("pBuf ERROR!! : null pointer");
  }
  uint8_t* _pBuf = (uint8_t*)pBuf;
  _pWire->requestFrom(_deviceAddr, (uint8_t)len);
  for (uint16_t i = 0; i < len; i++) {

    _pBuf[i] = _pWire->read();
  }

}


DFRobot_Lcd_UART::DFRobot_Lcd_UART(Stream& s)
{
  _s = &s;
}

bool DFRobot_Lcd_UART::begin()
{
  // warning: the compiler can assume that the address of 's' will never be NULL
  if (_s == NULL) {
    return false;
  }
  return true;
}

void DFRobot_Lcd_UART::writeCommand(uint8_t* pBuf, uint16_t len)
{
  uint8_t* _pBuf = (uint8_t*)pBuf;
  _s->write((uint8_t*)_pBuf, len);
  delay(50);
}

void DFRobot_Lcd_UART::readACK(uint8_t* pBuf, uint16_t len)
{
  LCD_UNUSED(pBuf);
  LCD_UNUSED(len);

  long long current = millis();

  while (true) {

    if (_s->available()) {
      uint8_t data = _s->read();
      LCD_UNUSED(data);
    }
    if ((millis() - current) > 1000) break;
  }
  DBG("read error");
}
