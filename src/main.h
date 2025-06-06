#ifndef MAIN_H
#define MAIN_H

#include <Watchy.h>

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

typedef struct wf_params_t
{
    buttons lastPressedButton;
    showFaceMode sfm;
    face_mode current_face_mode;
    bool darkMode;
    bool hours_am_pm;
    TimerHandle_t watchyTimerFace;
    TimerHandle_t watchyTimerButton;
} wf_params_t;

extern wf_params_t *wf_params_ptr;

void timerFaceCallback(TimerHandle_t xTimer);
void timerButtonCallback(TimerHandle_t xTimer);

class AdafruitWatchy : public Adafruit_GFX
{
    using Adafruit_GFX::Adafruit_GFX;

public:
    void drawFlipBitmap(SegmentBitmap segment, int16_t x, int16_t y, int16_t color);
};

class WatchyFace : public Watchy
{
    using Watchy::Watchy;

public:
    int batt;
    weatherData weather;

    virtual void init();
    // virtual void showWatchFace(bool partialRefresh);
    virtual void handleButtonPress();

    void drawWatchFace();
    void drawSimpleWatchFace();
    void drawDetailWatchFace();
};

#endif
