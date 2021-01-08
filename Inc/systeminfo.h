#include "main.h"
#define SOFTWARE_MAJOR_REVISION     1   // XXX  update when a major change occurs (ie, protocol)
#define SOFTWARE_MINOR_REVISION     0  // XXX  update for major and minor changes
#define SOFTWARE_UPDATE_DATE		"01/05/2020"

typedef struct _SYSTEMINFO{
	uint8_t softwareMajorVersion;
	uint8_t softwareMinorVersion;
	uint8_t softwareUpdateDate[20];
	uint32_t mcuVersion;
	uint32_t mcuDeviceID;
	uint32_t mcuRevisionID;
	uint32_t cameraID;
	uint8_t flashCapacity;
}SYSTEMINFO;
