#include <stdint.h>
//#include <tonc.h>
#include "../source/advikku_global.h"
#include "zetakick_bin.h"
#include "zetasnare_bin.h"

#define END 0xff
#define HOLD 0xfe

//byte 0 - note
//byte 1 - instrument
//byte 2 - effect command
//byte 3 - effect value

const uint8_t basicSongOrder1[] = {
	0x18,
	0, 2, 0x00, 0x00, 2, 2, 0x09, 0x00, 4, 2, 0x09, 0x40, 0, 2, 0x09, 0x80,
	0, 1, 0x00, 0xcc, 2, 1, 0x00, 0xcc, 4, 1, 0x00, 0xcc, 0, 1, 0x00, 0xcc,
	4, 1, 0x00, 0x00, 5, 1, 0x00, 0x00, 7, 1, 0x00, 0x00, HOLD, 0, 0x00, 0x00,
	4, 1, 0x04, 0x82, 5, 1, 0x04, 0x12, 7, 1, 0x04, 0x82, HOLD, 0, 0x00, 0x00,
	END
};

const uint8_t basicSongOrder2[] = {
	0x18,
	24, 2, 0x00, 0x00, 64, 0, 0x03, 0x02, HOLD, 0, 0x03, 0x02, HOLD, 0, 0x03, 0x02, 
	HOLD, 0, 0x03, 0x02, HOLD, 0, 0x03, 0x02, HOLD, 0, 0x03, 0x02, HOLD, 0, 0x03, 0x02, 
	HOLD, 0, 0x03, 0x02, HOLD, 0, 0x03, 0x02, HOLD, 0, 0x03, 0x02, HOLD, 0, 0x03, 0x02, 
	HOLD, 0, 0x03, 0x02, HOLD, 0, 0x03, 0x02, HOLD, 0, 0x03, 0x02, HOLD, 0, 0x03, 0x02, 
	END
};

const uint8_t basicSongOrder3[] = {
	0x18,
	24, 2, 0x00, 0x00, 26, 2, 0x09, 0x00, 28, 2, 0x09, 0x40, 24, 2, 0x09, 0x80,
	24, 1, 0x00, 0xcc, 26, 1, 0x00, 0xcc, 28, 1, 0x00, 0xcc, 24, 1, 0x00, 0xcc,
	28, 1, 0x00, 0x00, 29, 1, 0x00, 0x00, 31, 1, 0x00, 0x00, HOLD, 0, 0x00, 0x00,
	28, 1, 0x04, 0x82, 29, 1, 0x04, 0x12, 31, 1, 0x04, 0x82, HOLD, 0, 0x00, 0x00,
	END
};

const uint8_t basicSongOrder4[] = {
	0x18,
	SNOI_FREQ(5) | SNOI_OCTAVE(2), 1, 0x00, 0x00,
	HOLD, 0, 0x00, 0x00,
	SNOI_FREQ(0) | SNOI_OCTAVE(2), 2, 0x00, 0x00,
	HOLD, 0, 0x00, 0x00,
	SNOI_FREQ(5) | SNOI_OCTAVE(2), 1, 0x00, 0x00,
	SNOI_FREQ(5) | SNOI_OCTAVE(2), 1, 0x07, 0x0c,
	SNOI_FREQ(0) | SNOI_OCTAVE(2), 2, 0x00, 0x00,
	HOLD, 0, 0x00, 0x00,
	SNOI_FREQ(5) | SNOI_OCTAVE(2), 1, 0x00, 0x00,
	HOLD, 0, 0x00, 0x00,
	SNOI_FREQ(0) | SNOI_OCTAVE(2), 2, 0x00, 0x00,
	HOLD, 0, 0x00, 0x00,
	SNOI_FREQ(5) | SNOI_OCTAVE(2), 1, 0x00, 0x00,
	SNOI_FREQ(5) | SNOI_OCTAVE(2), 1, 0x00, 0x00,
	SNOI_FREQ(0) | SNOI_OCTAVE(2), 2, 0x00, 0x00,
	HOLD, 0, 0x00, 0x00,
	END
};

const uint16_t basicSaw[] = {
	0x0011, 0x2233, 0x4455, 0x6677, 0x8899, 0xaabb, 0xccdd, 0xeeff
};

//byte 0 - length + duty
//byte 1 - step time + step direction + initial volume
const uint16_t basicSquareInstruments[] = {
	SSQR_LEN(60) | SSQR_DUTY1_4 | SSQR_TIME(7) | SSQR_DEC | SSQR_IVOL(4),
	SSQR_LEN(16) | SSQR_DUTY1_2 | SSQR_TIME(0) | SSQR_DEC | SSQR_IVOL(15)
};

const uint16_t basicWaveInstruments[] = {
	SWAV_LEN(60) | SWAV_VOL75, SWAV_LEN_ON,
	SWAV_LEN(16) | SWAV_VOL100, SWAV_LEN_OFF
};

const uint16_t basicNoiseInstruments[] = {
	SSQR_LEN(60) | SNOI_LONG_PACK | SSQR_TIME(7) | SSQR_DEC | SSQR_IVOL(4),
	SSQR_LEN(16) | SNOI_SHORT_PACK | SSQR_TIME(2) | SSQR_DEC | SSQR_IVOL(15)
};

const uint8_t * const basicSong[] = {
	basicSongOrder2, basicSongOrder1, basicSongOrder3, basicSongOrder4
};