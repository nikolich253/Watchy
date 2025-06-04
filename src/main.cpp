#include "main.h"

void timerButtonCallback(TimerHandle_t xTimer)
{
    WatchyFace::wf_params.lastPressedButton = NULL_BTN;
}

void timerFaceCallback(TimerHandle_t xTimer)
{
    // Например, обновляем экран каждые 5 секунд
    WatchyFace::wf_params.sfm = SIMPLE;
    WatchyFace::display.refresh(true); // Частичное обновление
}

void WatchyFace::init()
{
    wf_params.darkMode = false;
    wf_params.lastPressedButton = NULL_BTN;
    wf_params.hours_am_pm = false;
    wf_params.sfm = SIMPLE;

    // Создаем таймер сброса на простой циферблат(период 5 секунд, автоперезагрузка)
    wf_params.watchyTimerFace = xTimerCreate(
        "WatchyTimerFace",    // Название (для отладки)
        pdMS_TO_TICKS(30000), // Период (5 секунд)
        pdFALSE,              // Автоповтор (true)
        (void *)0,            // ID таймера (можно передать данные)
        timerFaceCallback     // Функция-обработчик
    );

    // Создаём таймер сброса кнопок (период 5 секунд, автоперезагрузка)
    wf_params.watchyTimerButton = xTimerCreate(
        "WatchyTimerButton", // Название (для отладки)
        pdMS_TO_TICKS(1000), // Период (2 секунд)
        pdFALSE,             // Автоповтор (true)
        (void *)0,           // ID таймера (можно передать данные)
        timerButtonCallback  // Функция-обработчик
    );
}

void WatchyFace::showWatchFace(bool partialRefresh)
{
    RTC.read(currentTime);
    if (wf_params.sfm == SIMPLE)
    {
        drawSimpleWatchFace();
    }
    else
    {
        drawDetailWatchFace();
    }
}

void WatchyFace::handleButtonPress()
{
    if (guiState == WATCHFACE_STATE)
    {
        xTimerStart(WatchyFace::wf_params.watchyTimerButton, 0);
        // Up and Down switches
        uint64_t wakeupBit = esp_sleep_get_ext1_wakeup_status();
        if (wakeupBit & UP_BTN_MASK)
        {
            wf_params.sfm = DETAIL;
            if (wf_params.lastPressedButton == UP_BTN)
            {
                wf_params.hours_am_pm = !wf_params.hours_am_pm;
                wf_params.lastPressedButton = NULL_BTN;
            }
            else
            {
                wf_params.lastPressedButton = UP_BTN;
            }
            WatchyFace::showWatchFace(true);
            xTimerStart(WatchyFace::wf_params.watchyTimerFace, 0);
            return;
        }
        if (wakeupBit & DOWN_BTN_MASK)
        {
            wf_params.sfm = DETAIL;
            if (wf_params.lastPressedButton == DOWN_BTN)
            {
                wf_params.darkMode = !wf_params.darkMode;
                wf_params.lastPressedButton = NULL_BTN;
            }
            else
            {
                wf_params.lastPressedButton = DOWN_BTN;
            }
            xTimerStart(WatchyFace::wf_params.watchyTimerFace, 0);
            WatchyFace::showWatchFace(true);
            return;
        }
        if (wakeupBit & BACK_BTN_MASK)
        {
            wf_params.sfm = SIMPLE;
            wf_params.lastPressedButton = BACK_BTN;
            xTimerStart(WatchyFace::wf_params.watchyTimerFace, 0);
            WatchyFace::showWatchFace(true);
            return;
        }
        if (wakeupBit & MENU_BTN_MASK)
        {
            wf_params.lastPressedButton = MENU_BTN;
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