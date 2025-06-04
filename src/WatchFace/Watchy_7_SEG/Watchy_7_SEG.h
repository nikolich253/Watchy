#ifndef WATCHY_7_SEG_H
#define WATCHY_7_SEG_H

#include "main.h"
#include "Dusk2Dawn.h"
#include "moonPhaser.h"

#include "../Fonts/Seven_Segment10pt7b.h"
#include "../Fonts/DSEG7_Classic_Regular_15.h"
#include "../Fonts/DSEG7_Classic_Bold_25.h"
#include "../Fonts/DSEG7_Classic_Regular_39.h"
#include "icons.h"

#define WEATHER_ICON_WIDTH 48
#define WEATHER_ICON_HEIGHT 32

// void WatchyFace::drawDetailWatchFace();
void drawDetailTime(tmElements_t currentTime);
void drawDate(tmElements_t currentTime);
void drawSteps(tmElements_t currentTime);
void drawWeather(weatherData currentWeather);
void drawEva();
void drawBattery(float batt);
void drawLine();
void drawFiel();
void drawMoon(tmElements_t currentTime);

void drawSun(tmElements_t currentTime);
#endif
