#include "../source/advikku_global.h"
#include <stdint.h>
#include <tonc.h>

#include "blank_raw.h"

#define END 0xff
#define HOLD 0xfe

//speed
//version
//channels
//song length in orders per channel
//song order loopstart
//commands linger flag
//use subpatterns flag

const uint8_t blankSongHeader[] = {
    0x0a,
    0x01,
    0x04,
    0x01,
    0x00,
    0x00,
    0x00
};

const uint8_t blankSongOrderBlank[] = {
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
HOLD,0,0x00, 0x00,
END
};

const uint8_t* const blankSong[] = {
blankSongOrderBlank,
blankSongOrderBlank,
blankSongOrderBlank,
blankSongOrderBlank
};
const uint16_t blankWaveformBlank[] = {
    0x0000,
    0x0000,
    0x0000,
    0x0000,
    0x0000,
    0x0000,
    0x0000,
    0x0000,
};

const uint16_t blankSquareInstruments[] = {
 SSQR_LEN(0) | SSQR_TIME(0) | SSQR_IVOL(15) | SSQR_DUTY(0) | SSQR_INC
};
const uint16_t blankWaveInstruments[] = {
 SWAV_LEN(0) | SWAV_VOL100, SWAV_LEN_OFF
};
const uint16_t * const blankWaveforms[] = {
blankWaveformBlank
};
const uint16_t blankNoiseInstruments[] = {
 SSQR_LEN(48) | SSQR_TIME(1) | SSQR_IVOL(15) | SSQR_INC | SNOI_LONG_PACK
};
const uint8_t * const blankDMAInstruments[] = {
    blank_raw
};

const uint16_t blankDMADurations[] = {
    0
};
const advikSongStruct blankSongStruct = {
    blankSong,
    blankSongHeader,
    blankSquareInstruments,
    blankWaveInstruments,
    blankWaveforms,
    blankNoiseInstruments,
    blankDMAInstruments,
    blankDMADurations
    };
