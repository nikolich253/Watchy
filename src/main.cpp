#include "main.h"

void timerButtonCallback(TimerHandle_t xTimer)
{
    wf_params_ptr->lastPressedButton = NULL_BTN;
}

void timerFaceCallback(TimerHandle_t xTimer)
{
    // Например, обновляем экран каждые 5 секунд
    wf_params_ptr->sfm = SIMPLE;
    WatchyFace::display.refresh(true); // Частичное обновление
}

void WatchyFace::init()
{
    wf_params_ptr->darkMode = false;
    wf_params_ptr->lastPressedButton = NULL_BTN;
    wf_params_ptr->hours_am_pm = false;
    wf_params_ptr->sfm = SIMPLE;

    // Создаем таймер сброса на простой циферблат(период 5 секунд, автоперезагрузка)
    wf_params_ptr->watchyTimerFace = xTimerCreate(
        "WatchyTimerFace",    // Название (для отладки)
        pdMS_TO_TICKS(30000), // Период (5 секунд)
        pdFALSE,              // Автоповтор (true)
        (void *)0,            // ID таймера (можно передать данные)
        timerFaceCallback     // Функция-обработчик
    );

    // Создаём таймер сброса кнопок (период 5 секунд, автоперезагрузка)
    wf_params_ptr->watchyTimerButton = xTimerCreate(
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
    if (wf_params_ptr->sfm == SIMPLE)
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
        xTimerStart(wf_params_ptr->watchyTimerButton, 0);
        // Up and Down switches
        uint64_t wakeupBit = esp_sleep_get_ext1_wakeup_status();
        if (wakeupBit & UP_BTN_MASK)
        {
            wf_params_ptr->sfm = DETAIL;
            if (wf_params_ptr->lastPressedButton == UP_BTN)
            {
                wf_params_ptr->hours_am_pm = !wf_params_ptr->hours_am_pm;
                wf_params_ptr->lastPressedButton = NULL_BTN;
            }
            else
            {
                wf_params_ptr->lastPressedButton = UP_BTN;
            }
            WatchyFace::showWatchFace(true);
            xTimerStart(wf_params_ptr->watchyTimerFace, 0);
            return;
        }
        if (wakeupBit & DOWN_BTN_MASK)
        {
            wf_params_ptr->sfm = DETAIL;
            if (wf_params_ptr->lastPressedButton == DOWN_BTN)
            {
                wf_params_ptr->darkMode = !wf_params_ptr->darkMode;
                wf_params_ptr->lastPressedButton = NULL_BTN;
            }
            else
            {
                wf_params_ptr->lastPressedButton = DOWN_BTN;
            }
            xTimerStart(wf_params_ptr->watchyTimerFace, 0);
            WatchyFace::showWatchFace(true);
            return;
        }
        if (wakeupBit & BACK_BTN_MASK)
        {
            wf_params_ptr->sfm = SIMPLE;
            wf_params_ptr->lastPressedButton = BACK_BTN;
            xTimerStart(wf_params_ptr->watchyTimerFace, 0);
            WatchyFace::showWatchFace(true);
            return;
        }
        if (wakeupBit & MENU_BTN_MASK)
        {
            wf_params_ptr->lastPressedButton = MENU_BTN;
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