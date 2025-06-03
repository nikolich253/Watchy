#ifndef MAIN_H
#define MAIN_H

#include <Watchy.h>
#include "WatchFace/Watchy_Big/WatchyBig.h"
#include "WatchFace/Watchy_7_SEG/Watchy_7_SEG.h"
#include "settings.h"

RTC_DATA_ATTR bool light = true;
RTC_DATA_ATTR int face = 0;
RTC_DATA_ATTR int timeoutWatchFace = 0;

typedef enum showFaceMode
{
    SIMPLE,
    DETAIL,
} showFaceMode;

void timerFaceCallback(TimerHandle_t xTimer);
void timerButtonCallback(TimerHandle_t xTimer);

class WatchyFace : public Watchy
{
    using Watchy::Watchy;

public:
    void init();
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

private:
    void drawNumber(uint8_t number, uint8_t x, uint8_t y, uint16_t color);
    void drawDigit(uint8_t digit, uint8_t x, uint8_t y, uint16_t color);
};

#endif
