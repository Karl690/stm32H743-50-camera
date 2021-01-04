#include "constant.h"
#include "lcd.h"

#include "lcd_draw.h"


void draw_grayscale_frame(ST7735_Object_t *pObj, uint32_t Xpos, uint32_t Ypos, uint8_t *pData, uint32_t Width, uint32_t Height, uint8_t IsAxis){
	int32_t ret = ST7735_OK;
	static uint8_t pdata[640];
	uint8_t *pixel = pData;
	uint32_t i, j;
	extern ST7735_Ctx_t ST7735Ctx;
	if(((Xpos + Width) > ST7735Ctx.Width) || ((Ypos + Height) > ST7735Ctx.Height))
	{
		ret = ST7735_ERROR;
	}
	else
	{
		for(j = 0; j < Height; j++)
		{

			if(ST7735_SetCursor(pObj, Xpos, Ypos+j) != ST7735_OK)
			{
				ret = ST7735_ERROR;
			}
			else
			{
				for(i = 0; i < Width; i++)
				{
					if(IsAxis == 1 && (i == Width /2 || j == Height/2)) {
						pdata[2U*i] = 0x07;
						pdata[2U*i+1U] = 0xE0;
					}
					else {
						uint8_t g = pData[(Height-j-1)*Width*1U + (Width - i-1) * 1U];
						uint16_t p = GrayToRGB565(g);
						pdata[2U*i] = (uint8_t)(p & 0xFF);
						pdata[(2U*i) + 1U] = (uint8_t)((p >> 8) & 0xFF);

					}
				}
				if(st7735_send_data(&pObj->Ctx, (uint8_t*)&pdata[0], 2U*Width) != ST7735_OK)
				{
					ret = ST7735_ERROR;
				}
			}
		}
	}
}
void draw_rgb565_frame(ST7735_Object_t *pObj, uint32_t Xpos, uint32_t Ypos, uint16_t *pData, uint32_t Width, uint32_t Height, uint8_t IsAxis){
	int32_t ret = ST7735_OK;
	static uint8_t pdata[640];
	uint32_t i, j;
	extern ST7735_Ctx_t ST7735Ctx;
	if(((Xpos + Width) > ST7735Ctx.Width) || ((Ypos + Height) > ST7735Ctx.Height))
	{
		ret = ST7735_ERROR;
	}
	else
	{
		for(j = 0; j < Height; j++)
		{

			if(ST7735_SetCursor(pObj, Xpos, Ypos+j) != ST7735_OK)
			{
				ret = ST7735_ERROR;
			}
			else
			{
				for(i = 0; i < Width; i++)
				{
					if(IsAxis == 1 && (i == Width /2 || j == Height/2)) {
						pdata[2U*i] = 0x07;
						pdata[2U*i+1U] = 0xE0;
					}
					else {
						uint16_t pixel = pData[(Height-j-1)*Width + (Width - i-1)];
						pdata[2U*i] = (uint8_t)(pixel & 0xFF);
						pdata[(2U*i) + 1U] = (uint8_t)((pixel >> 8) & 0xFF);
					}
				}
				if(st7735_send_data(&pObj->Ctx, (uint8_t*)&pdata[0], 2U*Width) != ST7735_OK)
				{
					ret = ST7735_ERROR;
				}
			}
		}
	}

}
