#include "WatchyBig.h"

void WatchyBig::drawWatchFace() {
	display.fillScreen(settings.darkMode ? GxEPD_BLACK : GxEPD_WHITE);
	display.setTextColor(settings.darkMode ? GxEPD_WHITE : GxEPD_BLACK);
	drawTime();
}

void WatchyBig::drawTime() {
	uint8_t displayHour;
	uint16_t color = (settings.darkMode ? GxEPD_WHITE : GxEPD_BLACK);
	if (HOUR_12_24 == 12) {
		displayHour = ((currentTime.Hour + 11) % 12) + 1;
	}
	else {
		displayHour = currentTime.Hour;
	}
	drawNumber(displayHour, 0, 0, color);
	drawNumber(currentTime.Minute, 0, 100, color);

	if (settings.hours_am_pm == true) {
		display.setFont(&DSEG7_Classic_Regular_15);
		display.setCursor(0, 108);
		display.print("p");
	}
}


void WatchyBig::drawNumber(uint8_t number, uint8_t x, uint8_t y, uint16_t color) {
	int ones = number % 10;            // ������� (5)
	int tens = (number / 10) % 10;
	drawDigit(tens, x, y, color);
	drawDigit(ones, x + 100, y, color);
}

void WatchyBig::drawDigit(uint8_t digit, uint8_t x, uint8_t y, uint16_t color)
{
	uint8_t countSegment = Digits[digit].count;
	for (uint8_t i = 0; i < countSegment; i++) {
		SegmentBitmap segment = Digits[digit].segments[i];
		display.drawBitmap(x + segment.x_offset, y + segment.y_offset, segment.bitmap, segment.width, segment.height, color);
	}
}
