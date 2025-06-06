#pragma once

#include <Arduino.h>

typedef struct {
	uint8_t x_offset;	 // offset x in bitmap 100x100
	uint8_t y_offset;	 // offset y in bitmap 100x100
	uint8_t width;     // Bitmap dimensions in pixels
	uint8_t height;    // Bitmap dimensions in pixels
	uint8_t *bitmap;
  bool v_flip;       // true = flip bitmap vertically
  bool h_flip;       // true = flip bitmap horizontally
} SegmentBitmap;

typedef struct {
	uint8_t count;
	const SegmentBitmap segments[7];
} DigitSegments;

const uint8_t Segment_A_Bitmap[] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00,
  0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00,
  0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00,
  0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
  0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00,
  0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
  0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00,
  0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00,
  0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00,
  0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00,
  0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00,
  0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00,
  0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
const uint8_t Segment_B_Bitmap[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x08, 0x00,
  0x00, 0x00, 0x00, 0x3c, 0x00,
  0x00, 0x00, 0x00, 0x7e, 0x00,
  0x00, 0x00, 0x00, 0xff, 0x00,
  0x00, 0x00, 0x01, 0xff, 0x80,
  0x00, 0x00, 0x07, 0xff, 0x80,
  0x00, 0x00, 0x0f, 0xff, 0xc0,
  0x00, 0x00, 0x1f, 0xff, 0xc0,
  0x00, 0x00, 0x3f, 0xff, 0xe0,
  0x00, 0x00, 0xff, 0xff, 0xe0,
  0x00, 0x01, 0xff, 0xff, 0xe0,
  0x00, 0x03, 0xff, 0xff, 0xe0,
  0x00, 0x07, 0xff, 0xff, 0xe0,
  0x00, 0x1f, 0xff, 0xff, 0xe0,
  0x00, 0x3f, 0xff, 0xff, 0xe0,
  0x00, 0x7f, 0xff, 0xff, 0xe0,
  0x00, 0xff, 0xff, 0xff, 0xe0,
  0x03, 0xff, 0xff, 0xff, 0xe0,
  0x07, 0xff, 0xff, 0xff, 0xe0,
  0x0f, 0xff, 0xff, 0xff, 0xe0,
  0x1f, 0xff, 0xff, 0xff, 0xe0,
  0x1f, 0xff, 0xff, 0xff, 0xe0,
  0x1f, 0xff, 0xff, 0xff, 0xe0,
  0x1f, 0xff, 0xff, 0xff, 0xe0,
  0x1f, 0xff, 0xff, 0xff, 0xe0,
  0x1f, 0xff, 0xff, 0xff, 0xe0,
  0x1f, 0xff, 0xff, 0xff, 0xe0,
  0x1f, 0xff, 0xff, 0xff, 0xe0,
  0x1f, 0xff, 0xff, 0xff, 0xe0,
  0x07, 0xff, 0xff, 0xff, 0xe0,
  0x01, 0xff, 0xff, 0xff, 0xe0,
  0x00, 0xff, 0xff, 0xff, 0xe0,
  0x00, 0x3f, 0xff, 0xff, 0xe0,
  0x00, 0x0f, 0xff, 0xff, 0xe0,
  0x00, 0x03, 0xff, 0xff, 0xe0,
  0x00, 0x00, 0xff, 0xff, 0xe0,
  0x00, 0x00, 0x3f, 0xff, 0xe0,
  0x00, 0x00, 0x0f, 0xff, 0xe0,
  0x00, 0x00, 0x03, 0xff, 0xe0,
  0x00, 0x00, 0x00, 0xff, 0xc0,
  0x00, 0x00, 0x00, 0x3f, 0x00,
  0x00, 0x00, 0x00, 0x0c, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00,
};
const uint8_t Segment_G_Bitmap[] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00,
  0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00,
  0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00,
  0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
  0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
  0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00,
  0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00,
  0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00,
  0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const SegmentBitmap Segment_A PROGMEM = { 0, 0, 100, 28, (uint8_t *)Segment_A_Bitmap, false, false };
const SegmentBitmap Segment_B PROGMEM = { 63, 0, 38, 50, (uint8_t *)Segment_B_Bitmap, false, false };
const SegmentBitmap Segment_C PROGMEM = { 63, 51, 38, 50, (uint8_t *)Segment_B_Bitmap, true, false };
const SegmentBitmap Segment_D PROGMEM = { 0, 73, 100, 28,   (uint8_t *)Segment_A_Bitmap, true, false };
const SegmentBitmap Segment_E PROGMEM = { 0, 0, 38, 50, (uint8_t *)Segment_B_Bitmap, false, true };
const SegmentBitmap Segment_F PROGMEM = { 0, 51, 38, 50, (uint8_t *)Segment_B_Bitmap, true, true };
const SegmentBitmap Segment_G PROGMEM = { 0, 36, 100, 28, (uint8_t *)Segment_G_Bitmap, false, false };

const DigitSegments Digits[] PROGMEM = {
	{6, { Segment_A, Segment_B, Segment_C, Segment_D, Segment_E, Segment_F}},	//0
	{2, { Segment_B, Segment_C }},												//1
	{5, { Segment_A, Segment_B, Segment_D, Segment_F, Segment_G }},				//2
	{5, { Segment_A, Segment_B, Segment_C, Segment_D, Segment_G }},				//3
	{4, { Segment_B, Segment_C, Segment_E, Segment_G }},						//4
	{5, { Segment_A, Segment_C, Segment_D, Segment_E, Segment_G }},				//5
	{6, { Segment_A, Segment_C, Segment_D, Segment_E, Segment_F, Segment_G }},	//6
	{3, { Segment_A, Segment_B, Segment_C }},									//7
	{7, { Segment_A, Segment_B, Segment_C, Segment_D, Segment_E, Segment_F, Segment_G }},	//8
	{6, { Segment_A, Segment_B, Segment_C, Segment_D, Segment_E, Segment_G }}	//9
};
