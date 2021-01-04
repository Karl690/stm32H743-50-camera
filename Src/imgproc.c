#include "imgproc.h"
#include "color.h"
#include <math.h>
#define MARK_COLOR 0x9f05
void convertImageFormatRGB565ToGray(uint16_t* org, uint8_t* target, int width, int height){
	for(int i = 0; i < height; i ++) {
		for(int j = 0; j < width; j ++){
			uint16_t rgb565 = org[i*width + j];
			uint8_t g = convertRGB565toGray(rgb565);
			target[i*width + j] = g;
		}
	}
}

void backupImage(uint16_t* org, uint16_t* target, int width, int height){
	for(int i = 0; i < height; i ++) {
		for(int j = 0; j < width; j ++){
			uint16_t rgb565 = org[i*width + j];
			uint32_t g = convertRGB565ToRGB88(rgb565);
			uint16_t t = convertRGB888ToRGB565(g);
			target[i*width + j] = t;
		}
	}
}

void dilate(uint8_t* in_img, uint8_t* out_img, uint16_t width, uint16_t height) {
	for (uint16_t i=0; i< height; i++){
		for (uint16_t j=0; j< width; j++){
			if (in_img[i* height + j] == 1){
				if (i > 0 && in_img[(i-1)* width + j]==0) out_img[(i-1) * width + j] = 2;
				if (j > 0 && in_img[(i)* width + j-1]==0) out_img[i* width +j-1] = 2;
				if (i+1 < height && in_img[(i+1) * width  + j]==0) out_img[(i+1) * width + j] = 2;
				if (j+1 < width && in_img[i* width + j+1]==0) out_img[i * width + j+1] = 2;
			}
		}
	}
	for (uint16_t i=0; i < height; i++){
		for (uint16_t j=0; j < width; j++){
			if (out_img[i * width + j] == 2){
				out_img[i* width +j] = 1;
			}
		}
	}
}

void median_filter(uint8_t* img, uint16_t width, uint16_t height, const uint8_t k) {
#define MAX_KERNEL_SIZE  10
	float size = k * k;
	float kernel[k][k];
	for(uint8_t i = 0; i < k; i ++) {
		for(uint8_t j = 0; j < k; j ++) {
			kernel[i][j] = 1.0/size;
		}
	}
	int p = k /2;
	for (uint16_t i= p; i< height-p; i++){
		for (uint16_t j=p; j< width-p; j++){
			float sum = 0;

			for(int8_t m = -p, s = 0; m <= p; m ++, s ++) {
				for(int8_t n = -p, q = 0; n <= p; n ++, q ++){
					sum += kernel[s][q] * img[(i + m) * width + (j+n)];
				}
			}
			img[i * width + j] = (uint8_t)sum;
		}
	}
}
void threshold(uint8_t* img, uint8_t threshold) {

}

void copy_to_gray(uint8_t* in, uint8_t* out, uint16_t width, uint16_t height) {
	memcpy(out, in, sizeof(uint8_t) * width * height);
}
void copy_to_rgb565(uint16_t* in, uint16_t* out, uint16_t width, uint16_t height) {
	memcpy(out, in, sizeof(uint16_t) * width * height);
}
void extract_background(uint16_t* inframe, uint8_t* backgroundframe, uint8_t* outframe, uint16_t width, uint16_t height)
{
	//uint8_t tmpbuf[160][120] = {0};
	convertImageFormatRGB565ToGray(inframe, outframe, width, height);
	//median_filter(outframe, width, height, 3);

	//memcpy(&backgroundpic[0][0], &pic[0][0], sizeof(uint16_t) * width*height);
	//memset(binarybuffer, 0, sizeof(uint16_t) * width*height);

}

int detect_line(uint16_t* current_frame, uint16_t* prev_frame, uint16_t* diff_frame, const uint16_t width, const uint16_t height)
{
	uint8_t threshold = 10;
	for(uint16_t i = 0; i < height; i ++ ) {
		for(uint16_t j = 0; j < width; j ++ ) {
			HSV hsv = {0};
			RGB565ToHSV(current_frame[i * width+j], &hsv);
			uint8_t g1 = RGB565toGray(current_frame[i * width+j]);
			uint8_t g2 = RGB565toGray(prev_frame[i* width+j]);
			uint16_t diff = (uint16_t)abs(g1- g2);
			if(diff > threshold) {
				if((hsv.h < 10 || hsv.h > 340) && hsv.s > 70) {
					diff_frame[i * width + j] = MARK_COLOR;
				}else {
					diff_frame[i * width + j] = current_frame[i*width+j];
				}
			}else {
				diff_frame[i * width + j] = current_frame[i * width+j];
			}
		}
	}
	int p[width];
	int max_sum = 0;
	int max_pos = 0;
	for(uint16_t i = 0; i < width; i ++) {
		int sum = 0;
		for(uint16_t j = 0; j < height; j ++ ) {
			if(diff_frame[j * width + i] == MARK_COLOR)
				sum ++;
		}
		p[i] = sum;
		if(max_sum < sum) {
			max_sum = sum;
			max_pos = i;
		}
	}

	if(max_sum < height /2) max_pos = 0;
	return max_pos;
}
