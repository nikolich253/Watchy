#include "Watchy_7_SEG.h"

// wf_params_ptr -> darkMode
// #define wf_params_ptr -> darkMode false

// wf_params_ptr -> hours_am_pm, change it to 12 to switch to 12-hour
// #define wf_params_ptr -> hours_am_pm 24

// change it to your location
//          latitude, longitude, timezone
#define LOC 31.00, 121.00, 8

// RTC_DATA_ATTR int showState = 0;
// RTC_DATA_ATTR bool wf_params_ptr -> hours_am_pm = true;

moonPhaser moonP;

void WatchyFace::drawDetailWatchFace()
{
    WatchyFace::display.fillScreen(wf_params_ptr -> darkMode ? GxEPD_BLACK : GxEPD_WHITE);
    WatchyFace::display.setTextColor(wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    drawFiel();
    drawDetailTime(currentTime);
    drawDate(currentTime);
    drawSteps(currentTime);
    drawWeather(Watchy::getWeatherData());

    drawBattery(Watchy::getBatteryVoltage());
    drawEva();
    drawLine();

    WatchyFace::display.drawBitmap(118, 168, WIFI_CONFIGURED ? wifi : wifioff, 25, 18, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    if (BLE_CONFIGURED)
    {
        WatchyFace::display.drawBitmap(100, 75, bluetooth, 13, 21, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    }
    drawMoon(currentTime);
    drawSun(currentTime);
}

void drawDetailTime(tmElements_t currentTime)
{
    WatchyFace::display.setFont(&DSEG7_Classic_Bold_53);
    WatchyFace::display.setCursor(6, 53 + 5);

    long ss = currentTime.Hour * 60 + currentTime.Minute;
    int sh = ss / 60;

    if (wf_params_ptr -> hours_am_pm == false && sh >= 12)
    {
        WatchyFace::display.fillRect(7, 60, 25, 9, wf_params_ptr -> darkMode ? GxEPD_BLACK : GxEPD_WHITE);
        WatchyFace::display.drawBitmap(7, 60, pm, 25, 9, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    }
    else if (wf_params_ptr -> hours_am_pm == false && sh < 12)
    {
        WatchyFace::display.fillRect(7, 60, 25, 9, wf_params_ptr -> darkMode ? GxEPD_BLACK : GxEPD_WHITE);
        WatchyFace::display.drawBitmap(7, 60, am, 25, 9, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    }

    if (wf_params_ptr -> hours_am_pm == false && sh > 12)
    {
        sh -= 12;
    }
    int sm = ss % 60;
    int a = sh >= 10 ? sh / 10 : 0;
    int b = sh % 10;
    int c = sm >= 10 ? sm / 10 : 0;
    int d = sm % 10;

    if (a == 0)
        WatchyFace::display.drawBitmap(11, 5, fd_0, 33, 53, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 1)
        WatchyFace::display.drawBitmap(11, 5, fd_1, 33, 53, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 2)
        WatchyFace::display.drawBitmap(11, 5, fd_2, 33, 53, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 3)
        WatchyFace::display.drawBitmap(11, 5, fd_3, 33, 53, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 4)
        WatchyFace::display.drawBitmap(11, 5, fd_4, 33, 53, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 5)
        WatchyFace::display.drawBitmap(11, 5, fd_5, 33, 53, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 6)
        WatchyFace::display.drawBitmap(11, 5, fd_6, 33, 53, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 7)
        WatchyFace::display.drawBitmap(11, 5, fd_7, 33, 53, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 8)
        WatchyFace::display.drawBitmap(11, 5, fd_8, 33, 53, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 9)
        WatchyFace::display.drawBitmap(11, 5, fd_9, 33, 53, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);

    if (b == 0)
        WatchyFace::display.drawBitmap(55, 5, fd_0, 33, 53, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 1)
        WatchyFace::display.drawBitmap(55, 5, fd_1, 33, 53, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 2)
        WatchyFace::display.drawBitmap(55, 5, fd_2, 33, 53, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 3)
        WatchyFace::display.drawBitmap(55, 5, fd_3, 33, 53, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 4)
        WatchyFace::display.drawBitmap(55, 5, fd_4, 33, 53, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 5)
        WatchyFace::display.drawBitmap(55, 5, fd_5, 33, 53, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 6)
        WatchyFace::display.drawBitmap(55, 5, fd_6, 33, 53, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 7)
        WatchyFace::display.drawBitmap(55, 5, fd_7, 33, 53, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 8)
        WatchyFace::display.drawBitmap(55, 5, fd_8, 33, 53, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 9)
        WatchyFace::display.drawBitmap(55, 5, fd_9, 33, 53, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);

    if (c == 0)
        WatchyFace::display.drawBitmap(111, 5, fd_0, 33, 53, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 1)
        WatchyFace::display.drawBitmap(111, 5, fd_1, 33, 53, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 2)
        WatchyFace::display.drawBitmap(111, 5, fd_2, 33, 53, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 3)
        WatchyFace::display.drawBitmap(111, 5, fd_3, 33, 53, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 4)
        WatchyFace::display.drawBitmap(111, 5, fd_4, 33, 53, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 5)
        WatchyFace::display.drawBitmap(111, 5, fd_5, 33, 53, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 6)
        WatchyFace::display.drawBitmap(111, 5, fd_6, 33, 53, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 7)
        WatchyFace::display.drawBitmap(111, 5, fd_7, 33, 53, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 8)
        WatchyFace::display.drawBitmap(111, 5, fd_8, 33, 53, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 9)
        WatchyFace::display.drawBitmap(111, 5, fd_9, 33, 53, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);

    if (d == 0)
        WatchyFace::display.drawBitmap(155, 5, fd_0, 33, 53, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 1)
        WatchyFace::display.drawBitmap(155, 5, fd_1, 33, 53, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 2)
        WatchyFace::display.drawBitmap(155, 5, fd_2, 33, 53, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 3)
        WatchyFace::display.drawBitmap(155, 5, fd_3, 33, 53, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 4)
        WatchyFace::display.drawBitmap(155, 5, fd_4, 33, 53, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 5)
        WatchyFace::display.drawBitmap(155, 5, fd_5, 33, 53, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 6)
        WatchyFace::display.drawBitmap(155, 5, fd_6, 33, 53, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 7)
        WatchyFace::display.drawBitmap(155, 5, fd_7, 33, 53, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 8)
        WatchyFace::display.drawBitmap(155, 5, fd_8, 33, 53, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 9)
        WatchyFace::display.drawBitmap(155, 5, fd_9, 33, 53, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
}

void drawDate(tmElements_t currentTime)
{
    WatchyFace::display.setFont(&Seven_Segment10pt7b);

    int16_t x1, y1;
    uint16_t w, h;

    String dayOfWeek = dayStr(currentTime.Wday);
    dayOfWeek = dayOfWeek.substring(0, dayOfWeek.length() - 3);
    WatchyFace::display.getTextBounds(dayOfWeek, 5, 85, &x1, &y1, &w, &h);
    if (currentTime.Wday == 4)
    {
        w = w - 5;
    }
    WatchyFace::display.setCursor(76 - w, 86);
    WatchyFace::display.println(dayOfWeek);

    String month = monthShortStr(currentTime.Month);
    WatchyFace::display.getTextBounds(month, 60, 110, &x1, &y1, &w, &h);
    WatchyFace::display.setCursor(79 - w, 110);
    WatchyFace::display.println(month);

    // WatchyFace::display.setFont(&DSEG7_Classic_Bold_25);
    // WatchyFace::display.setCursor(6, 120);
    // if(currentTime.Day < 10)
    // {
    // WatchyFace::display.print("0");
    // }
    // WatchyFace::display.println(currentTime.Day);
    // WatchyFace::display.setCursor(6, 154);
    // WatchyFace::display.println(tmYearToCalendar(currentTime.Year));// offset from 1970, since year is stored in uint8_t

    int da = currentTime.Day;
    int ye = currentTime.Year + 1970;

    int a = da / 10;
    int b = da % 10;
    int c = ye / 1000;
    ye = ye % 1000;
    int d = ye / 100;
    ye = ye % 100;
    int e = ye / 10;
    ye = ye % 10;
    int f = ye;

    if (a == 0)
        WatchyFace::display.drawBitmap(8, 95, dd_0, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 1)
        WatchyFace::display.drawBitmap(8, 95, dd_1, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 2)
        WatchyFace::display.drawBitmap(8, 95, dd_2, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 3)
        WatchyFace::display.drawBitmap(8, 95, dd_3, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 4)
        WatchyFace::display.drawBitmap(8, 95, dd_4, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 5)
        WatchyFace::display.drawBitmap(8, 95, dd_5, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 6)
        WatchyFace::display.drawBitmap(8, 95, dd_6, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 7)
        WatchyFace::display.drawBitmap(8, 95, dd_7, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 8)
        WatchyFace::display.drawBitmap(8, 95, dd_8, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 9)
        WatchyFace::display.drawBitmap(8, 95, dd_9, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);

    if (b == 0)
        WatchyFace::display.drawBitmap(29, 95, dd_0, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 1)
        WatchyFace::display.drawBitmap(29, 95, dd_1, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 2)
        WatchyFace::display.drawBitmap(29, 95, dd_2, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 3)
        WatchyFace::display.drawBitmap(29, 95, dd_3, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 4)
        WatchyFace::display.drawBitmap(29, 95, dd_4, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 5)
        WatchyFace::display.drawBitmap(29, 95, dd_5, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 6)
        WatchyFace::display.drawBitmap(29, 95, dd_6, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 7)
        WatchyFace::display.drawBitmap(29, 95, dd_7, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 8)
        WatchyFace::display.drawBitmap(29, 95, dd_8, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 9)
        WatchyFace::display.drawBitmap(29, 95, dd_9, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);

    if (c == 0)
        WatchyFace::display.drawBitmap(8, 129, dd_0, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 1)
        WatchyFace::display.drawBitmap(8, 129, dd_1, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 2)
        WatchyFace::display.drawBitmap(8, 129, dd_2, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 3)
        WatchyFace::display.drawBitmap(8, 129, dd_3, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 4)
        WatchyFace::display.drawBitmap(8, 129, dd_4, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 5)
        WatchyFace::display.drawBitmap(8, 129, dd_5, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 6)
        WatchyFace::display.drawBitmap(8, 129, dd_6, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 7)
        WatchyFace::display.drawBitmap(8, 129, dd_7, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 8)
        WatchyFace::display.drawBitmap(8, 129, dd_8, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 9)
        WatchyFace::display.drawBitmap(8, 129, dd_9, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);

    if (d == 0)
        WatchyFace::display.drawBitmap(29, 129, dd_0, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 1)
        WatchyFace::display.drawBitmap(29, 129, dd_1, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 2)
        WatchyFace::display.drawBitmap(29, 129, dd_2, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 3)
        WatchyFace::display.drawBitmap(29, 129, dd_3, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 4)
        WatchyFace::display.drawBitmap(29, 129, dd_4, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 5)
        WatchyFace::display.drawBitmap(29, 129, dd_5, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 6)
        WatchyFace::display.drawBitmap(29, 129, dd_6, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 7)
        WatchyFace::display.drawBitmap(29, 129, dd_7, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 8)
        WatchyFace::display.drawBitmap(29, 129, dd_8, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 9)
        WatchyFace::display.drawBitmap(29, 129, dd_9, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);

    if (e == 0)
        WatchyFace::display.drawBitmap(50, 129, dd_0, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 1)
        WatchyFace::display.drawBitmap(50, 129, dd_1, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 2)
        WatchyFace::display.drawBitmap(50, 129, dd_2, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 3)
        WatchyFace::display.drawBitmap(50, 129, dd_3, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 4)
        WatchyFace::display.drawBitmap(50, 129, dd_4, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 5)
        WatchyFace::display.drawBitmap(50, 129, dd_5, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 6)
        WatchyFace::display.drawBitmap(50, 129, dd_6, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 7)
        WatchyFace::display.drawBitmap(50, 129, dd_7, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 8)
        WatchyFace::display.drawBitmap(50, 129, dd_8, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 9)
        WatchyFace::display.drawBitmap(50, 129, dd_9, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);

    if (f == 0)
        WatchyFace::display.drawBitmap(71, 129, dd_0, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 1)
        WatchyFace::display.drawBitmap(71, 129, dd_1, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 2)
        WatchyFace::display.drawBitmap(71, 129, dd_2, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 3)
        WatchyFace::display.drawBitmap(71, 129, dd_3, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 4)
        WatchyFace::display.drawBitmap(71, 129, dd_4, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 5)
        WatchyFace::display.drawBitmap(71, 129, dd_5, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 6)
        WatchyFace::display.drawBitmap(71, 129, dd_6, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 7)
        WatchyFace::display.drawBitmap(71, 129, dd_7, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 8)
        WatchyFace::display.drawBitmap(71, 129, dd_8, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 9)
        WatchyFace::display.drawBitmap(71, 129, dd_9, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
}
void drawSteps(tmElements_t currentTime)
{
    // reset step counter at midnight
    if (currentTime.Hour == 0 && currentTime.Minute == 0)
    {
        // st4 = st3;
        // st3 = st2;
        // st2 = st1;
        // st1 = stepCount;
        sensor.resetStepCounter();
        // stepCount = 0;
    }
    uint32_t stepCount = sensor.getCounter();

    // WatchyFace::display.drawBitmap(10, 165, steps, 19, 23, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    // WatchyFace::display.setCursor(6, 190);
    // if (stepCount >= 10000)
    //     ;
    // else if (stepCount >= 1000)
    //     WatchyFace::display.print("0");
    // else if (stepCount >= 100)
    //     WatchyFace::display.print("00");
    // else if (stepCount >= 10)
    //     WatchyFace::display.print("000");
    // else if (stepCount >= 0)
    //     WatchyFace::display.print("0000");
    // WatchyFace::display.println(stepCount);

    // uint32_t l1 = 61 * st1 / 20000;
    // uint32_t l2 = 61 * st2 / 20000;
    // uint32_t l3 = 61 * st3 / 20000;
    // uint32_t l4 = 61 * st4 / 20000;
    uint32_t l5 = 61 * stepCount / 10000;

    if (l5 > 61)
    {
        l5 = 61;
    }

    // WatchyFace::display.fillRect(125, 73 + 61 - l1, 9, l4, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    // WatchyFace::display.fillRect(143, 73 + 61 - l1, 9, l3, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    // WatchyFace::display.fillRect(161, 73 + 61 - l1, 9, l2, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    // WatchyFace::display.fillRect(179, 73 + 61 - l1, 9, l1, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    WatchyFace::display.fillRect(131, 148, l5, 9, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    // WatchyFace::display.

    int a = stepCount / 10000;
    stepCount = stepCount % 10000;
    int b = stepCount / 1000;
    stepCount = stepCount % 1000;
    int c = stepCount / 100;
    stepCount = stepCount % 100;
    int d = stepCount / 10;
    int e = stepCount % 10;

    if (a == 0)
        WatchyFace::display.drawBitmap(8, 165, dd_0, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 1)
        WatchyFace::display.drawBitmap(8, 165, dd_1, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 2)
        WatchyFace::display.drawBitmap(8, 165, dd_2, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 3)
        WatchyFace::display.drawBitmap(8, 165, dd_3, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 4)
        WatchyFace::display.drawBitmap(8, 165, dd_4, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 5)
        WatchyFace::display.drawBitmap(8, 165, dd_5, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 6)
        WatchyFace::display.drawBitmap(8, 165, dd_6, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 7)
        WatchyFace::display.drawBitmap(8, 165, dd_7, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 8)
        WatchyFace::display.drawBitmap(8, 165, dd_8, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 9)
        WatchyFace::display.drawBitmap(8, 165, dd_9, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);

    if (b == 0)
        WatchyFace::display.drawBitmap(29, 165, dd_0, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 1)
        WatchyFace::display.drawBitmap(29, 165, dd_1, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 2)
        WatchyFace::display.drawBitmap(29, 165, dd_2, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 3)
        WatchyFace::display.drawBitmap(29, 165, dd_3, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 4)
        WatchyFace::display.drawBitmap(29, 165, dd_4, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 5)
        WatchyFace::display.drawBitmap(29, 165, dd_5, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 6)
        WatchyFace::display.drawBitmap(29, 165, dd_6, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 7)
        WatchyFace::display.drawBitmap(29, 165, dd_7, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 8)
        WatchyFace::display.drawBitmap(29, 165, dd_8, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 9)
        WatchyFace::display.drawBitmap(29, 165, dd_9, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);

    if (c == 0)
        WatchyFace::display.drawBitmap(50, 165, dd_0, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 1)
        WatchyFace::display.drawBitmap(50, 165, dd_1, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 2)
        WatchyFace::display.drawBitmap(50, 165, dd_2, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 3)
        WatchyFace::display.drawBitmap(50, 165, dd_3, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 4)
        WatchyFace::display.drawBitmap(50, 165, dd_4, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 5)
        WatchyFace::display.drawBitmap(50, 165, dd_5, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 6)
        WatchyFace::display.drawBitmap(50, 165, dd_6, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 7)
        WatchyFace::display.drawBitmap(50, 165, dd_7, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 8)
        WatchyFace::display.drawBitmap(50, 165, dd_8, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 9)
        WatchyFace::display.drawBitmap(50, 165, dd_9, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);

    if (d == 0)
        WatchyFace::display.drawBitmap(71, 165, dd_0, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 1)
        WatchyFace::display.drawBitmap(71, 165, dd_1, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 2)
        WatchyFace::display.drawBitmap(71, 165, dd_2, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 3)
        WatchyFace::display.drawBitmap(71, 165, dd_3, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 4)
        WatchyFace::display.drawBitmap(71, 165, dd_4, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 5)
        WatchyFace::display.drawBitmap(71, 165, dd_5, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 6)
        WatchyFace::display.drawBitmap(71, 165, dd_6, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 7)
        WatchyFace::display.drawBitmap(71, 165, dd_7, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 8)
        WatchyFace::display.drawBitmap(71, 165, dd_8, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 9)
        WatchyFace::display.drawBitmap(71, 165, dd_9, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);

    if (e == 0)
        WatchyFace::display.drawBitmap(92, 165, dd_0, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 1)
        WatchyFace::display.drawBitmap(92, 165, dd_1, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 2)
        WatchyFace::display.drawBitmap(92, 165, dd_2, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 3)
        WatchyFace::display.drawBitmap(92, 165, dd_3, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 4)
        WatchyFace::display.drawBitmap(92, 165, dd_4, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 5)
        WatchyFace::display.drawBitmap(92, 165, dd_5, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 6)
        WatchyFace::display.drawBitmap(92, 165, dd_6, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 7)
        WatchyFace::display.drawBitmap(92, 165, dd_7, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 8)
        WatchyFace::display.drawBitmap(92, 165, dd_8, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 9)
        WatchyFace::display.drawBitmap(92, 165, dd_9, 16, 25, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
}
void drawBattery(float battery)
{
    // WatchyFace::display.drawBitmap(154, 73, battery, 37, 21, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    // WatchyFace::display.fillRect(159, 78, 27, BATTERY_SEGMENT_HEIGHT, wf_params_ptr -> darkMode ? GxEPD_BLACK : GxEPD_WHITE);//clear battery segments
    int8_t batteryLevel = 0;
    if (battery > 4.1)
    {
        batteryLevel = 37;
    }
    else if (battery > 4.05 && battery <= 4.1)
    {
        batteryLevel = 33;
    }
    else if (battery > 4 && battery <= 4.05)
    {
        batteryLevel = 28;
    }

    else if (battery > 3.95 && battery <= 4)
    {
        batteryLevel = 23;
    }
    else if (battery > 3.9 && battery <= 3.95)
    {
        batteryLevel = 18;
    }
    else if (battery > 3.85 && battery <= 3.9)
    {
        batteryLevel = 13;
    }
    else if (battery > 3.8 && battery <= 3.85)
    {
        batteryLevel = 8;
    }
    else if (battery > 3.75 && battery <= 3.8)
    {
        batteryLevel = 4;
    }
    else if (battery <= 3.75)
    {
        batteryLevel = 0;
    }

    // for(int8_t batterySegments = 0; batterySegments < batteryLevel; batterySegments++)
    // {
    WatchyFace::display.fillRect(155, 169, batteryLevel, 15, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    // }
}

void drawFiel()
{
    WatchyFace::display.drawBitmap(0, 0, field, 200, 200, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
}

void drawMoon(tmElements_t currentTime)
{
    moonData_t moon; // variable to receive the data

    // January 31st, 2020 @ 1:30PM UTC
    int year = currentTime.Year + 1970;
    int32_t month = currentTime.Month;
    int32_t day = currentTime.Day;
    double hour = currentTime.Hour + 0.1;

    moon = moonP.getPhase(year, month, day, hour);

    int ag = moon.angle;
    double lt = moon.percentLit;

    // Waxing: 0-180
    // Waning: 180-360
    // WatchyFace::display.setCursor(100, 74);

    if (ag <= 180)
    {
        if (lt < 0.1)
            WatchyFace::display.drawBitmap(131, 74, luna1, 61, 61, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
        else if (lt < 0.25)
            WatchyFace::display.drawBitmap(131, 74, luna12, 61, 61, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
        else if (lt < 0.4)
            WatchyFace::display.drawBitmap(131, 74, luna11, 61, 61, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
        else if (lt < 0.6)
            WatchyFace::display.drawBitmap(131, 74, luna10, 61, 61, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
        else if (lt < 0.75)
            WatchyFace::display.drawBitmap(131, 74, luna9, 61, 61, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
        else if (lt < 0.9)
            WatchyFace::display.drawBitmap(131, 74, luna8, 61, 61, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
        else
            WatchyFace::display.drawBitmap(131, 74, luna7, 61, 61, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    }
    else
    {
        if (lt < 0.1)
            WatchyFace::display.drawBitmap(131, 74, luna1, 61, 61, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
        else if (lt < 0.25)
            WatchyFace::display.drawBitmap(131, 74, luna2, 61, 61, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
        else if (lt < 0.4)
            WatchyFace::display.drawBitmap(131, 74, luna3, 61, 61, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
        else if (lt < 0.6)
            WatchyFace::display.drawBitmap(131, 74, luna4, 61, 61, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
        else if (lt < 0.75)
            WatchyFace::display.drawBitmap(131, 74, luna5, 61, 61, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
        else if (lt < 0.9)
            WatchyFace::display.drawBitmap(131, 74, luna6, 61, 61, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
        else
            WatchyFace::display.drawBitmap(131, 74, luna7, 61, 61, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    }

    // WatchyFace::display.print(year);
    // // WatchyFace::display.print(moon.angle);
    // WatchyFace::display.setCursor(100, 100);
    // // WatchyFace::display.print(moon.percentLit);
    // WatchyFace::display.print(month);

    // WatchyFace::display.setCursor(100, 130);
    // WatchyFace::display.print(day);
    //  Serial.print( "Moon phase angle: " );
    //  Serial.print( moon.angle );             // angle is a integer between 0-360
    //  Serial.println( " degrees." );
    //  Serial.print( "Moon surface lit: " );
    //  Serial.println( moon.percentLit * 100 );  // percentLit is a real between 0-1
}

void drawSun(tmElements_t currentTime)
{
    Dusk2Dawn location(LOC);
    int year = currentTime.Year + 1970;
    int32_t month = currentTime.Month;
    int32_t day = currentTime.Day;
    int sr = location.sunrise(year, month, day, false);
    int ss = location.sunset(year, month, day, false);

    long k = currentTime.Hour * 60 + currentTime.Minute;
    int tk = (k - sr) * 60 / (ss - sr);
    if (k > ss)
        tk = 60;
    else if (k < sr)
        tk = 0;
    WatchyFace::display.drawBitmap(110, 132 - tk, arr, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);

    int rh = sr / 60;
    int rm = sr % 60;
    int sh = ss / 60;
    int sm = ss % 60;

    if (wf_params_ptr -> hours_am_pm == false && rh > 12)
    {
        rh -= 12;
    }

    if (wf_params_ptr -> hours_am_pm == false && sh > 12)
    {
        sh -= 12;
    }

    int a = sh >= 10 ? sh / 10 : 0;
    int b = sh % 10;
    int c = sm >= 10 ? sm / 10 : 0;
    int d = sm % 10;
    int e = rh >= 10 ? rh / 10 : 0;
    int f = rh % 10;
    int g = rm >= 10 ? rm / 10 : 0;
    int h = rm % 10;

    if (a == 0)
        WatchyFace::display.drawBitmap(116, 67, num_0, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 1)
        WatchyFace::display.drawBitmap(116, 67, num_1, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 2)
        WatchyFace::display.drawBitmap(116, 67, num_2, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 3)
        WatchyFace::display.drawBitmap(116, 67, num_3, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 4)
        WatchyFace::display.drawBitmap(116, 67, num_4, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 5)
        WatchyFace::display.drawBitmap(116, 67, num_5, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 6)
        WatchyFace::display.drawBitmap(116, 67, num_6, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 7)
        WatchyFace::display.drawBitmap(116, 67, num_7, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 8)
        WatchyFace::display.drawBitmap(116, 67, num_8, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 9)
        WatchyFace::display.drawBitmap(116, 67, num_9, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);

    if (b == 0)
        WatchyFace::display.drawBitmap(120, 67, num_0, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 1)
        WatchyFace::display.drawBitmap(120, 67, num_1, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 2)
        WatchyFace::display.drawBitmap(120, 67, num_2, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 3)
        WatchyFace::display.drawBitmap(120, 67, num_3, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 4)
        WatchyFace::display.drawBitmap(120, 67, num_4, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 5)
        WatchyFace::display.drawBitmap(120, 67, num_5, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 6)
        WatchyFace::display.drawBitmap(120, 67, num_6, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 7)
        WatchyFace::display.drawBitmap(120, 67, num_7, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 8)
        WatchyFace::display.drawBitmap(120, 67, num_8, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 9)
        WatchyFace::display.drawBitmap(120, 67, num_9, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);

    if (c == 0)
        WatchyFace::display.drawBitmap(128, 67, num_0, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 1)
        WatchyFace::display.drawBitmap(128, 67, num_1, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 2)
        WatchyFace::display.drawBitmap(128, 67, num_2, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 3)
        WatchyFace::display.drawBitmap(128, 67, num_3, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 4)
        WatchyFace::display.drawBitmap(128, 67, num_4, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 5)
        WatchyFace::display.drawBitmap(128, 67, num_5, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 6)
        WatchyFace::display.drawBitmap(128, 67, num_6, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 7)
        WatchyFace::display.drawBitmap(128, 67, num_7, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 8)
        WatchyFace::display.drawBitmap(128, 67, num_8, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 9)
        WatchyFace::display.drawBitmap(128, 67, num_9, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);

    if (d == 0)
        WatchyFace::display.drawBitmap(132, 67, num_0, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 1)
        WatchyFace::display.drawBitmap(132, 67, num_1, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 2)
        WatchyFace::display.drawBitmap(132, 67, num_2, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 3)
        WatchyFace::display.drawBitmap(132, 67, num_3, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 4)
        WatchyFace::display.drawBitmap(132, 67, num_4, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 5)
        WatchyFace::display.drawBitmap(132, 67, num_5, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 6)
        WatchyFace::display.drawBitmap(132, 67, num_6, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 7)
        WatchyFace::display.drawBitmap(132, 67, num_7, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 8)
        WatchyFace::display.drawBitmap(132, 67, num_8, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 9)
        WatchyFace::display.drawBitmap(132, 67, num_9, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);

    if (e == 0)
        WatchyFace::display.drawBitmap(116, 137, num_0, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 1)
        WatchyFace::display.drawBitmap(116, 137, num_1, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 2)
        WatchyFace::display.drawBitmap(116, 137, num_2, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 3)
        WatchyFace::display.drawBitmap(116, 137, num_3, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 4)
        WatchyFace::display.drawBitmap(116, 137, num_4, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 5)
        WatchyFace::display.drawBitmap(116, 137, num_5, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 6)
        WatchyFace::display.drawBitmap(116, 137, num_6, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 7)
        WatchyFace::display.drawBitmap(116, 137, num_7, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 8)
        WatchyFace::display.drawBitmap(116, 137, num_8, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 9)
        WatchyFace::display.drawBitmap(116, 137, num_9, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);

    if (f == 0)
        WatchyFace::display.drawBitmap(120, 137, num_0, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 1)
        WatchyFace::display.drawBitmap(120, 137, num_1, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 2)
        WatchyFace::display.drawBitmap(120, 137, num_2, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 3)
        WatchyFace::display.drawBitmap(120, 137, num_3, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 4)
        WatchyFace::display.drawBitmap(120, 137, num_4, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 5)
        WatchyFace::display.drawBitmap(120, 137, num_5, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 6)
        WatchyFace::display.drawBitmap(120, 137, num_6, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 7)
        WatchyFace::display.drawBitmap(120, 137, num_7, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 8)
        WatchyFace::display.drawBitmap(120, 137, num_8, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 9)
        WatchyFace::display.drawBitmap(120, 137, num_9, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);

    if (g == 0)
        WatchyFace::display.drawBitmap(128, 137, num_0, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (g == 1)
        WatchyFace::display.drawBitmap(128, 137, num_1, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (g == 2)
        WatchyFace::display.drawBitmap(128, 137, num_2, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (g == 3)
        WatchyFace::display.drawBitmap(128, 137, num_3, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (g == 4)
        WatchyFace::display.drawBitmap(128, 137, num_4, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (g == 5)
        WatchyFace::display.drawBitmap(128, 137, num_5, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (g == 6)
        WatchyFace::display.drawBitmap(128, 137, num_6, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (g == 7)
        WatchyFace::display.drawBitmap(128, 137, num_7, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (g == 8)
        WatchyFace::display.drawBitmap(128, 137, num_8, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (g == 9)
        WatchyFace::display.drawBitmap(128, 137, num_9, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);

    if (h == 0)
        WatchyFace::display.drawBitmap(132, 137, num_0, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (h == 1)
        WatchyFace::display.drawBitmap(132, 137, num_1, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (h == 2)
        WatchyFace::display.drawBitmap(132, 137, num_2, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (h == 3)
        WatchyFace::display.drawBitmap(132, 137, num_3, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (h == 4)
        WatchyFace::display.drawBitmap(132, 137, num_4, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (h == 5)
        WatchyFace::display.drawBitmap(132, 137, num_5, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (h == 6)
        WatchyFace::display.drawBitmap(132, 137, num_6, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (h == 7)
        WatchyFace::display.drawBitmap(132, 137, num_7, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (h == 8)
        WatchyFace::display.drawBitmap(132, 137, num_8, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    else if (h == 9)
        WatchyFace::display.drawBitmap(132, 137, num_9, 3, 5, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
}

void drawWeather(weatherData currentWeather)
{
    int8_t temperature = currentWeather.temperature;
    int16_t weatherConditionCode = currentWeather.weatherConditionCode;

    WatchyFace::display.setFont(&DSEG7_Classic_Regular_39);
    int16_t x1, y1;
    uint16_t w, h;
    WatchyFace::display.getTextBounds(String(temperature), 0, 0, &x1, &y1, &w, &h);
    if (159 - w - x1 > 87)
    {
        WatchyFace::display.setCursor(159 - w - x1, 150);
    }
    else
    {
        WatchyFace::display.setFont(&DSEG7_Classic_Bold_25);
        WatchyFace::display.getTextBounds(String(temperature), 0, 0, &x1, &y1, &w, &h);
        WatchyFace::display.setCursor(159 - w - x1, 136);
    }
    WatchyFace::display.println(temperature);
    WatchyFace::display.drawBitmap(165, 110, currentWeather.isMetric ? celsius : fahrenheit, 26, 20, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
    const unsigned char *weatherIcon;

    // https://openweathermap.org/weather-conditions
    if (weatherConditionCode > 801)
    {
        // Cloudy
        weatherIcon = cloudy;
    }
    else if (weatherConditionCode == 801)
    {
        // Few Clouds
        weatherIcon = cloudsun;
    }
    else if (weatherConditionCode == 800)
    {
        // Clear
        weatherIcon = sunny;
    }
    else if (weatherConditionCode >= 700)
    {
        // Atmosphere
        weatherIcon = atmosphere;
    }
    else if (weatherConditionCode >= 600)
    {
        // Snow
        weatherIcon = snow;
    }
    else if (weatherConditionCode >= 500)
    {
        // Rain
        weatherIcon = rain;
    }
    else if (weatherConditionCode >= 300)
    {
        // Drizzle
        weatherIcon = drizzle;
    }
    else if (weatherConditionCode >= 200)
    {
        // Thunderstorm
        weatherIcon = thunderstorm;
    }
    else
        return;
    WatchyFace::display.drawBitmap(145, 158, weatherIcon, WEATHER_ICON_WIDTH, WEATHER_ICON_HEIGHT, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
}

void drawEva()
{
    WatchyFace::display.drawBitmap(105, 100, eva, 100, 100, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
}

void drawLine()
{
    WatchyFace::display.drawBitmap(100, 72, line, 1, 77, wf_params_ptr -> darkMode ? GxEPD_WHITE : GxEPD_BLACK);
}
