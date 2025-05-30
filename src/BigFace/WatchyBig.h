#pragma once
#ifndef WATCHYBIG_H
#define WATCHYBIG_H

#include <math.h>
#include <Watchy.h>
#include "Font_Big.h"
#include "Dusk2Dawn.h"
#include "moonPhaser.h"
#include "../commonFaceFiles/Seven_Segment10pt7b.h"
#include "../commonFaceFiles/DSEG7_Classic_Regular_15.h"
#include "../commonFaceFiles/DSEG7_Classic_Bold_25.h"
#include "../commonFaceFiles/DSEG7_Classic_Regular_39.h"
#include "../commonFaceFiles/icons.h"

class WatchyBig : public Watchy {
    using Watchy::Watchy;
public:
    void drawWatchFace();
    void drawTime();
    void drawDate();
    void drawSteps();
    void drawWeather();
    void drawBattery();

//        void drawWeather();
//        void drawEva();
//        void drawLine();
    void drawFiel();
    void drawMoon();
    void drawSun();

    virtual void handleButtonPress();

private:
    void drawNumber(uint8_t number, uint8_t x, uint8_t y, uint16_t color);
    void drawDigit(uint8_t digit, uint8_t x, uint8_t y, uint16_t color);
};



#endif