#include "main.h"

wf_params_t* wf_params_ptr = nullptr;
Adafruit_GFX* Adafruit_wf = nullptr;

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

void AdafruitWatchy::drawFlipBitmap(SegmentBitmap segment, int16_t x, int16_t y, int16_t color)
{
    int16_t byteWidth = (segment.width + 7) / 8;
    uint8_t _buffer[segment.width / 8 * segment.height]; // буфер размером в количество байт изображения
    for (int16_t j = 0; j < segment.height; j++)
    {
        for (int16_t i = 0; i < segment.width; i++)
        {
            uint8_t byteIndex = byteWidth * j + i / 8;
            uint8_t bitIndex = 7 - i % 8;
            uint8_t bitValue = (segment.bitmap[byteIndex] >> bitIndex) & 1;
            // Проверяем флаги вертикального и горизонтального зеркаления
            if (segment.v_flip){
                bitIndex = 7 - bitIndex;
            }
            if (segment.h_flip)
            {
                byteIndex = byteWidth * (segment.height - j - 1) + i / 8;
            }
            if (bitValue){
                    _buffer[byteWidth * j + i / 8] |= (1 << (7 - i % 8));
            }
            else{
                _buffer[byteWidth * j + i / 8] &= ~(1 << (7 - i % 8));
            }
        }
        Adafruit_wf->drawBitmap(x, y + j, &_buffer[byteWidth * j], segment.width, segment.height, color);
    }

    Adafruit_wf->startWrite();






    Adafruit_wf->endWrite();
}

void WatchyFace::init()
{
    Watchy::init();
    wf_params_ptr->darkMode = false;
    wf_params_ptr->lastPressedButton = NULL_BTN;
    wf_params_ptr->hours_am_pm = false;
    wf_params_ptr->sfm = SIMPLE;

    // Создаем таймер сброса на простой циферблат(период 5 секунд, автоперезагрузка)
    wf_params_ptr->watchyTimerFace = xTimerCreate(
        "WatchyTimerFace",    // Название (для отладки)
        pdMS_TO_TICKS(15000), // Период (15 секунд)
        pdFALSE,              // Автоповтор (true)
        (void *)0,            // ID таймера (можно передать данные)
        timerFaceCallback     // Функция-обработчик
    );

    // Создаём таймер сброса кнопок (период 5 секунд, автоперезагрузка)
    wf_params_ptr->watchyTimerButton = xTimerCreate(
        "WatchyTimerButton", // Название (для отладки)
        pdMS_TO_TICKS(1000), // Период (1 секунд)
        pdFALSE,             // Автоповтор (true)
        (void *)0,           // ID таймера (можно передать данные)
        timerButtonCallback  // Функция-обработчик
    );
}

void WatchyFace::drawWatchFace()
{
    RTC.read(currentTime);
    // ** UPDATE **
    // resets step counter at midnight daily
    if (currentTime.Hour == 00 && currentTime.Minute == 00)
    {
        sensor.resetStepCounter();
    }

    if (wf_params_ptr->sfm == SIMPLE)
    {
        drawSimpleWatchFace();
    }
    else
    {
        // ** GET BATTERY **
        batt = getBatteryVoltage()  - 3.3;
        weather = getWeatherData();
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