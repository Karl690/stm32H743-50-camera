#include "constant.h"
#include "command.h"
#include "systeminfo.h"
#include "vcp.h"
void command_vcp_process(uint8_t* buf, uint16_t len) {
	extern uint8_t LCD_log_text[30];
	memset(LCD_log_text, 0, sizeof(LCD_log_text));
	if(len == 1) {
		extern uint8_t IsDrawingAxis;
		extern uint8_t IsLiveStream;
		switch(buf[0]) {
		case PING_CHAR:
			sendRevisionString("PingReply");
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

void pingReply (void){
	sendRevisionString("PingReply");
}

void sendRevisionString(char *reason){
	extern SYSTEMINFO SystemInfo;
	uint8_t trans_buffer[100] = {0};
	trans_buffer[0] = PING_CHAR;
	sprintf(trans_buffer+1, ">Hy: %s :\nsw %d.%03d :mcu 0x%03x 0x%04x", reason, SystemInfo.softwareMajorVersion, SystemInfo.softwareMinorVersion, SystemInfo.mcuDeviceID, SystemInfo.mcuRevisionID);
	CDC_Transmit_FS(trans_buffer, strlen(trans_buffer));
}


