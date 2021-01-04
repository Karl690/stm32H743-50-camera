#include "constant.h"
#include "command.h"
#include "vcp.h"
void command_vcp_process(uint8_t* buf, uint16_t len) {
	extern uint8_t LCD_log_text[30];
	memset(LCD_log_text, 0, sizeof(LCD_log_text));
	if(len == 1) {
		extern uint8_t IsDrawingAxis;
		extern uint8_t IsLiveStream;
		switch(buf[0]) {
		case PING_CHAR:
			CDC_Transmit_FS(buf, len);
			sprintf(LCD_log_text, "PING REQUEST");
			break;
		case AXIS_VISIBLE_CHAR:
			IsDrawingAxis = 1;
			CDC_Transmit_FS(RESPOND_CHAR, 1);
			sprintf(LCD_log_text, "AXIS VISIBLE REQUEST");
			break;
		case AXIS_INVISIBLE_CHAR:
			IsDrawingAxis = 0;
			CDC_Transmit_FS(RESPOND_CHAR, 1);
			sprintf(LCD_log_text, "AXIS INVISIBLE REQUEST");
			break;
		case LCD_LIVESTREAM_CHAR:
			IsLiveStream = 1;
			CDC_Transmit_FS(RESPOND_CHAR, 1);
			sprintf(LCD_log_text, "CAMERA STREAM REQUEST");
			break;
		case LCD_LOGO_CHAR:
			IsLiveStream = 0;
			CDC_Transmit_FS(RESPOND_CHAR, 1);
			sprintf(LCD_log_text, "LOGO VISIBLE REQUEST");
			break;
		}

	}else {
		//memcpy(LCD_log_text, buf, len);
		CDC_Transmit_FS(buf, len);
	}

}


