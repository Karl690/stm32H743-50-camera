
/*
 * color.c
 *
 *  Created on: Dec 20, 2020
 *      Author: falcon
 */

#include "color.h"
uint32_t RGB565ToRGB888(uint16_t rgb565) {
	uint32_t rgb888 = 0;

	rgb565 = (rgb565 >> 8) + ((rgb565 << 8) & 0xff00);

	uint16_t r1 = ((rgb565 & 0xF800)>>11);
	uint16_t g1 = ((rgb565 & 0x07E0)>>5);
	uint16_t b1 = (rgb565 & 0x001F);
	uint8_t r = (uint8_t)((r1 << 3) | (r1 >> 2));
	uint8_t g = (uint8_t)((g1 << 2) | (g1 >> 4));
	uint8_t b = (uint8_t)((b1 << 3) | (b1 >> 2));

	rgb888 = ((r&0x0ff)<<16)|((g&0x0ff)<<8)|(b&0x0ff);
	return rgb888;
}
uint16_t RGB888ToRGB565(uint32_t rgb888) {
	uint16_t rgb565 = 0;

	uint8_t r_8 = (uint8_t)((rgb888>>16)&0x0ff);
	uint8_t g_8 =(uint8_t)((rgb888>>8) &0x0ff);
	uint8_t b_8 =(uint8_t)( (rgb888)    &0x0ff);

	uint16_t b5 = (uint16_t)((b_8 >> 3) & 0x001f);
	uint16_t g5 = (uint16_t)(((g_8 >> 2) & 0x003f) << 5);
	uint16_t r5 = (uint16_t)(((r_8 >> 3) & 0x001f) << 11);

	rgb565 = (uint16_t)(b5 | g5 | r5);
	rgb565 = (rgb565 >> 8) + ((rgb565 << 8) & 0xff00);
	return rgb565;
}
uint8_t RGB565toGray(uint16_t rgb565) {
	uint8_t gray = 0;
	uint32_t rgb = RGB565ToRGB888(rgb565);
	uint8_t r = (uint8_t)((rgb>>16)&0x0ff);
	uint8_t g =(uint8_t)((rgb>>8) &0x0ff);
	uint8_t b = (uint8_t)(rgb & 0x0ff);
	gray = (uint8_t)(r*0.222 + g*0.666 + b*0.111);
	return gray;
}
uint16_t GrayToRGB565(uint8_t gray){
	uint32_t rgb888 = ((gray&0x0ff)<<16)|((gray&0x0ff)<<8)|(gray&0x0ff);
	return RGB888ToRGB565(rgb888);
}

void RGB565ToHSV(uint16_t rgb565, HSV* hsv) {
	uint32_t rgb = RGB565ToRGB888(rgb565);
	uint8_t r = (uint8_t)((rgb>>16)&0x0ff);
	uint8_t g =(uint8_t)((rgb>>8) &0x0ff);
	uint8_t b =(uint8_t)( (rgb)    &0x0ff);

	float fr, fg, fb;
	fr = r / 255.0; 	fg = g / 255.0; 	fb = b / 255.0;

	float cmax = fr > fb? fr: fb;
	cmax = cmax > fg? cmax : fg;
	float cmin = fr < fb? fr: fb;
	cmin = cmin < fg? cmin : fg;
	float diff = cmax-cmin;

	if(cmax == cmin) hsv->h =0;
	else if(cmax == r) hsv->h = (int)((int)(60 * ((fg - fb) / diff) + 360) % 360);
	else if(cmax == g) hsv->h = (int)((int)(60 * ((fb - fr) / diff) + 120) % 360);
	else if(cmax == b) hsv->h = (int)((int)(60 * ((fr - fg) / diff) + 240) % 360);

	if( cmax == 0) hsv->s = 0;
	else hsv->s = (diff / cmax) * 100;

	hsv->v = cmax * 100;
}
