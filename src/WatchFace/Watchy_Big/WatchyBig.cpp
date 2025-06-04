#include "WatchyBig.h"

void WatchyFace::drawSimpleWatchFace()
{
	display.fillScreen(wf_params.darkMode ? GxEPD_BLACK : GxEPD_WHITE);
	display.setTextColor(wf_params.darkMode ? GxEPD_WHITE : GxEPD_BLACK);
	drawTime(currentTime);
}

void drawTime(tmElements_t currentTime)
{
	uint8_t displayHour;
	uint16_t color = (WatchyFace::wf_params.darkMode ? GxEPD_WHITE : GxEPD_BLACK);
	if (HOUR_12_24 == 12)
	{
		displayHour = ((currentTime.Hour + 11) % 12) + 1;
	}
	else
	{
		displayHour = currentTime.Hour;
	}
	drawNumber(displayHour, 0, 0, color);
	drawNumber(currentTime.Minute, 0, 100, color);

	if (WatchyFace::wf_params.hours_am_pm == true)
	{
		WatchyFace::display.setFont(&DSEG7_Classic_Regular_15);
		WatchyFace::display.setCursor(0, 108);
		WatchyFace::display.print("p");
	}
}

void drawNumber(uint8_t number, uint8_t x, uint8_t y, uint16_t color)
{
	int ones = number % 10;
	int tens = (number / 10) % 10;
	drawDigit(tens, x, y, color);
	drawDigit(ones, x + 100, y, color);
}
void drawDigit(uint8_t digit, uint8_t x, uint8_t y, uint16_t color)
{
	uint8_t countSegment = Digits[digit].count;
	for (uint8_t i = 0; i < countSegment; i++)
	{
		SegmentBitmap segment = Digits[digit].segments[i];
		WatchyFace::display.drawBitmap(x + segment.x_offset, y + segment.y_offset, segment.bitmap, segment.width, segment.height, color);
	}
}
