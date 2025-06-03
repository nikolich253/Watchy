#pragma once
#ifndef WATCHYBIG_H
#define WATCHYBIG_H

#include <Watchy.h>
#include "../Settings.h"
#include "../Fonts/Font_Big.h"
#include "../Fonts/DSEG7_Classic_Regular_15.h"

class WatchyBig : public Watchy
{
    using Watchy::Watchy;
    watchySettings settings;

public:
    // Конструктор по умолчанию
    WatchyBig() {}
    WatchyBig(watchySettings s)
    {
        settings = s;
    }

    void drawWatchFace();
    void drawTime();
    // virtual void handleButtonPress();

private:
    void drawNumber(uint8_t number, uint8_t x, uint8_t y, uint16_t color);
    void drawDigit(uint8_t digit, uint8_t x, uint8_t y, uint16_t color);
};
#endif