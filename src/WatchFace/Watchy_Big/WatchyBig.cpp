#include "WatchyBig.h"

extern wf_params_t *wf_params_ptr;
extern Adafruit_GFX *AdafruitWatchy;

void WatchyFace::drawSimpleWatchFace()
{
	display.fillScreen(wf_params_ptr->darkMode ? GxEPD_BLACK : GxEPD_WHITE);
	display.setTextColor(wf_params_ptr->darkMode ? GxEPD_WHITE : GxEPD_BLACK);
	drawBigTime(currentTime);
}

void drawBigTime(tmElements_t currentTime)
{
	uint8_t displayHour;
	uint16_t color = (wf_params_ptr->darkMode ? GxEPD_WHITE : GxEPD_BLACK);
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

	if (wf_params_ptr->hours_am_pm == true)
	{
		WatchyFace::display.setFont(&DSEG7_Classic_Regular_15);
		WatchyFace::display.setCursor(0, 108);
		WatchyFace::display.print("p");
	}
}
void drawBitmapVmirror32(int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h, uint16_t color)
{
	int16_t byteWidth = (w + 7) / 8;
	AdafruitWatchy->startWrite();

	for (int16_t j = h - 1; j >= 0; j--)
	{
		uint8_t *row = &bitmap[j * byteWidth];
		int16_t i = 0;

		// Process 32 pixels at a time
		while (i + 31 < w)
		{
			uint32_t word = *((uint32_t *)(row + i / 8));
			for (int k = 0; k < 32; k++, i++)
			{
				if (word & (0x80000000 >> k))
				{
					AdafruitWatchy->writePixel(x + i, y + (h - 1 - j), color);
				}
			}
		}

		// Remaining pixels
		while (i < w)
		{
			if (row[i / 8] & (0x80 >> (i % 8)))
			{
				AdafruitWatchy->writePixel(x + i, y + (h - 1 - j), color);
			}
			i++;
		}
	}
	AdafruitWatchy->endWrite();
}
void drawBitmapHmirror32(int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h, uint16_t color)
{
	int16_t byteWidth = (w + 7) / 8;
	AdafruitWatchy->startWrite();

	for (int16_t j = 0; j < h; j++, y++)
	{
		uint8_t *row = &bitmap[j * byteWidth];
		int16_t i = 0;

		// Process 32-bit chunks (4 bytes at a time)
		while (i + 31 < w)
		{
			// Read 4 bytes as a 32-bit word (little-endian)
			uint32_t word = *((uint32_t *)(row + (w - i - 32) / 8));

			// Reverse the bit order of the entire 32-bit word
			word = __builtin_bswap32(word);									// Swap byte order
			word = ((word & 0xF0F0F0F0) >> 4) | ((word & 0x0F0F0F0F) << 4); // Swap nibbles
			word = ((word & 0xCCCCCCCC) >> 2) | ((word & 0x33333333) << 2); // Swap pairs
			word = ((word & 0xAAAAAAAA) >> 1) | ((word & 0x55555555) << 1); // Swap bits

			// Draw 32 pixels
			for (int k = 0; k < 32; k++, i++)
			{
				if (word & (1 << (31 - k)))
				{
					AdafruitWatchy->writePixel(x + i, y, color);
				}
			}
		}
	}
	AdafruitWatchy->endWrite();
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
