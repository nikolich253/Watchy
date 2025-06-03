#include "main.h"

WatchyBig watchyBig;
Watchy7SEG watchy7Seg;

buttons lastPressedButton = NULL_BTN;
showFaceMode sfm = SIMPLE;
TimerHandle_t watchyTimerFace;
TimerHandle_t watchyTimerButton;



void timerButtonCallback(TimerHandle_t xTimer){
    lastPressedButton = NULL_BTN;
}

void timerFaceCallback(TimerHandle_t xTimer)
{
    // Например, обновляем экран каждые 5 секунд
    sfm = SIMPLE;
    WatchyFace::display.refresh(true); // Частичное обновление
}

void WatchyFace::init()
{
    // Создаем таймер сброса на простой циферблат(период 5 секунд, автоперезагрузка)
    watchyTimerFace = xTimerCreate(
        "WatchyTimerFace",        // Название (для отладки)
        pdMS_TO_TICKS(30000), // Период (5 секунд)
        pdFALSE,              // Автоповтор (true)
        (void *)0,            // ID таймера (можно передать данные)
        timerFaceCallback         // Функция-обработчик
    );

    // Создаём таймер сброса кнопок (период 5 секунд, автоперезагрузка)
    watchyTimerButton = xTimerCreate(
        "WatchyTimerButton",        // Название (для отладки)
        pdMS_TO_TICKS(1000), // Период (2 секунд)
        pdFALSE,              // Автоповтор (true)
        (void *)0,            // ID таймера (можно передать данные)
        timerButtonCallback         // Функция-обработчик
    );
}

void WatchyFace::showWatchFace(bool partialRefresh)
{
    RTC.read(currentTime);
}

void WatchyFace::handleButtonPress()
{
    if (guiState == WATCHFACE_STATE)
    {
        xTimerStart(watchyTimerButton, 0);
        // Up and Down switches
        uint64_t wakeupBit = esp_sleep_get_ext1_wakeup_status();
        if (wakeupBit & UP_BTN_MASK)
        {
            sfm = DETAIL;
            if (lastPressedButton == UP_BTN)
            {
                settings.hours_am_pm = !settings.hours_am_pm;
                lastPressedButton = NULL_BTN;
            }
            else
            {
                lastPressedButton = UP_BTN;
            }
            WatchyFace::showWatchFace(true);
            xTimerStart(watchyTimerFace, 0);
            return;
        }
        if (wakeupBit & DOWN_BTN_MASK)
        {
            sfm = DETAIL;
            if (lastPressedButton == DOWN_BTN)
            {
                settings.darkMode = !settings.darkMode;
                lastPressedButton = NULL_BTN;
            }
            else
            {
                lastPressedButton = DOWN_BTN;
            }
            xTimerStart(watchyTimerFace, 0);
            WatchyFace::showWatchFace(true);
            return;
        }
        if (wakeupBit & BACK_BTN_MASK)
        {
            sfm = DETAIL;
            lastPressedButton = BACK_BTN;
            xTimerStart(watchyTimerFace, 0);
            WatchyFace::showWatchFace(true);
            return;
        }
        if (wakeupBit & MENU_BTN_MASK)
        {
            lastPressedButton = MENU_BTN;
            Watchy::handleButtonPress();
            return;
        }
    }
    else
    {
        Watchy::handleButtonPress();
    }
    return;
}