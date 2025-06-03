#ifndef WATCHY_7_SEG_H
#define WATCHY_7_SEG_H
#include <math.h>
#include <Watchy.h>
#include "Dusk2Dawn.h"
#include "moonPhaser.h"
#include "../Fonts/Seven_Segment10pt7b.h"
#include "../Fonts/DSEG7_Classic_Regular_15.h"
#include "../Fonts/DSEG7_Classic_Bold_25.h"
#include "../Fonts/DSEG7_Classic_Regular_39.h"
#include "icons.h"

#define WEATHER_ICON_WIDTH 48
#define WEATHER_ICON_HEIGHT 32

void drawDetailWatchFace();
void drawTime();
void drawDate();
void drawSteps();
void drawWeather();
void drawEva();
void drawBattery();
void drawLine();
void drawFiel();
void drawMoon();

void drawSun();
#endif
