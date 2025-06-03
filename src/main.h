#ifndef MAIN_H
#define MAIN_H

#include <Watchy.h>
#include "settings.h"
#include "WatchFace/Watchy_Big/WatchyBig.h"
#include "WatchFace/Watchy_7_SEG/Watchy_7_SEG.h"

#include "WatchFace/Watchy_7_SEG/Dusk2Dawn.h"
#include "WatchFace/Watchy_7_SEG/moonPhaser.h"
#include "WatchFace/Watchy_7_SEG/icons.h"

#include "WatchFace/Fonts/Font_Big.h"
#include "WatchFace/Fonts/DSEG7_Classic_Regular_15.h"
#include "WatchFace/Fonts/Seven_Segment10pt7b.h"
#include "WatchFace/Fonts/DSEG7_Classic_Regular_15.h"
#include "WatchFace/Fonts/DSEG7_Classic_Bold_25.h"
#include "WatchFace/Fonts/DSEG7_Classic_Regular_39.h"

RTC_DATA_ATTR bool light = true;
RTC_DATA_ATTR int face = 0;
RTC_DATA_ATTR int timeoutWatchFace = 0;

typedef enum showFaceMode
{
    SIMPLE,
    DETAIL,
} showFaceMode;

typedef enum face_mode
{
    MAIN_BIG_FACE = 0,
    MAIN_STANDART_FACE = 1,
    ONLY_STANDART_FACE = 2,
} face_mode;

typedef enum buttons
{
    NULL_BTN,
    UP_BTN,
    DOWN_BTN,
    BACK_BTN,
    MENU_BTN,
} buttons;

void timerFaceCallback(TimerHandle_t xTimer);
void timerButtonCallback(TimerHandle_t xTimer);




class WatchyFace : public Watchy
{
    using Watchy::Watchy;

public:
    void init();
    void drawSimpleFace();
    void showWatchFace(bool partialRefresh);
    void drawWatchFace();
    void drawTime();
    void drawDate();
    void drawSteps();
    void drawWeather();
    void drawBattery();

    //        void drawWeather();
    //        void drawEva();
    void drawLine();
    void drawFiel();
    void drawMoon();
    void drawSun();

    virtual void handleButtonPress();


};

#endif
