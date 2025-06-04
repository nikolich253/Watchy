#pragma once
#ifndef WATCHYBIG_H
#define WATCHYBIG_H

// #include <Watchy.h>
#include "main.h"
#include "../Fonts/Font_Big.h"
#include "../Fonts/DSEG7_Classic_Regular_15.h"

// void WatchyFace::drawSimpleWatchFace();

void drawTime(tmElements_t currentTime);
// virtual void handleButtonPress();

void drawNumber(uint8_t number, uint8_t x, uint8_t y, uint16_t color);
void drawDigit(uint8_t digit, uint8_t x, uint8_t y, uint16_t color);
#endif