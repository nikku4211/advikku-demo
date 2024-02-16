#include <stdint.h>
//#include <tonc.h>
#include "../source/advikku.h"

#define END 0xff
#define HOLD 0xfe

//byte 0 - note
//byte 1 - instrument
//byte 2 - effect command
//byte 3 - effect value

const uint8_t basicSong[] = {
	0x0c,
	0, 1, 0x00, 0x00, 2, 1, 0x09, 0x00, 4, 1, 0x09, 0x40, 0, 1, 0x09, 0x80,
	0, 1, 0x00, 0x00, 2, 1, 0x00, 0x00, 4, 1, 0x00, 0x00, 0, 1, 0x00, 0x00,
	4, 0, 0x00, 0x00, 5, 0, 0x00, 0x00, 7, 0, 0x00, 0x00, HOLD, 0, 0x00, 0x00,
	4, 0, 0x00, 0x00, 5, 0, 0x00, 0x00, 7, 0, 0x00, 0x00, HOLD, 0, 0x00, 0x00,
	END
};

//byte 0 - length + duty
//byte 1 - step time + step direction + initial volume
const uint16_t basicInstruments[] = {
	SSQR_LEN(60) | SSQR_DUTY1_4 | SSQR_TIME(7) | SSQR_DEC | SSQR_IVOL(4),
	SSQR_LEN(16) | SSQR_DUTY1_2 | SSQR_TIME(4) | SSQR_DEC | SSQR_IVOL(12)
};