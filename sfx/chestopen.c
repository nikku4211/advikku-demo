#include "../source/advikku_global.h"
#include <stdint.h>
#include <tonc.h>

#include "blank_raw.h"

/*
    Song name:  chestopen
    Artist:     

    Converted using Nikku4211's ugetoadvik.py based on code by Valen Coffee Bat's uge2source.py
*/
#define END 0xff
#define HOLD 0xfe

//speed
//version
//channels
//song length in orders per channel
//song order loopstart
//commands linger flag
//use subpatterns flag

const uint8_t chestopenSongHeader[] = {
    0x02,
    0x01,
    0x04,
    0x01,
    0x00,
    0x00,
    0x00
};

const uint8_t chestopenSongOrder0[] = {
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

const uint16_t chestopenWaveform0[] = {
    0x0000,
    0xffff,
    0xffff,
    0xffff,
    0xffff,
    0xffff,
    0xffff,
    0xffff,
};

const uint16_t chestopenWaveform1[] = {
    0x0000,
    0x0000,
    0xffff,
    0xffff,
    0xffff,
    0xffff,
    0xffff,
    0xffff,
};

const uint16_t chestopenWaveform2[] = {
    0x0000,
    0x0000,
    0x0000,
    0x0000,
    0xffff,
    0xffff,
    0xffff,
    0xffff,
};

const uint16_t chestopenWaveform3[] = {
    0x0000,
    0x0000,
    0x0000,
    0x0000,
    0x0000,
    0x0000,
    0xffff,
    0xffff,
};

const uint16_t chestopenWaveform4[] = {
    0x0001,
    0x1223,
    0x3445,
    0x5667,
    0x7889,
    0x9aab,
    0xbccd,
    0xdeef,
};

const uint16_t chestopenWaveform5[] = {
    0xfedc,
    0xba98,
    0x7654,
    0x3210,
    0x1234,
    0x5678,
    0x9abc,
    0xdeff,
};

const uint16_t chestopenWaveform6[] = {
    0x7acd,
    0xdb75,
    0x2113,
    0x68bd,
    0xdc97,
    0x4101,
    0x479c,
    0xddb8,
};

const uint16_t chestopenWaveform7[] = {
    0x0f0f,
    0x0f0f,
    0x0f0f,
    0x0f0f,
    0x0f0f,
    0x0f0f,
    0x0f0f,
    0x0f0f,
};

const uint16_t chestopenWaveform8[] = {
    0xfefc,
    0xfaf8,
    0xf6f4,
    0xf2f0,
    0xf2f4,
    0xf6f8,
    0xfafc,
    0xfeff,
};

const uint16_t chestopenWaveform9[] = {
    0xfedd,
    0xccbb,
    0xaa99,
    0x8877,
    0x8abd,
    0xf124,
    0x578a,
    0xbdee,
};

const uint16_t chestopenWaveform10[] = {
    0x8411,
    0x61ed,
    0x5747,
    0x5aad,
    0xcea3,
    0x1779,
    0xdd20,
    0x0347,
};

const uint16_t chestopenWaveform11[] = {
    0x0e90,
    0x4068,
    0x499a,
    0x0911,
    0x576e,
    0xc82e,
    0x85ed,
    0x006a,
};

const uint16_t chestopenWaveform12[] = {
    0xb607,
    0xac67,
    0xc28a,
    0xaa51,
    0x598b,
    0xa535,
    0xde7c,
    0x709d,
};

const uint16_t chestopenWaveform13[] = {
    0x21a2,
    0x3d68,
    0xaacc,
    0x8dc1,
    0x312b,
    0x872c,
    0x24b8,
    0x9e67,
};

const uint16_t chestopenWaveform14[] = {
    0x92d6,
    0x84e0,
    0xc149,
    0xeaca,
    0xe0d2,
    0x703a,
    0xed03,
    0x1778,
};

const uint16_t chestopenWaveform15[] = {
    0x9628,
    0x9284,
    0x0cd7,
    0x0ce0,
    0x04c1,
    0xc283,
    0xea1c,
    0x8217,
};


const uint16_t chestopenSquareInstruments[] = {
 SSQR_LEN(0) | SSQR_TIME(0) | SSQR_IVOL(15) | SSQR_DUTY(0) | SSQR_INC,
 SSQR_LEN(0) | SSQR_TIME(0) | SSQR_IVOL(15) | SSQR_DUTY(1) | SSQR_INC,
 SSQR_LEN(0) | SSQR_TIME(0) | SSQR_IVOL(15) | SSQR_DUTY(2) | SSQR_INC,
 SSQR_LEN(0) | SSQR_TIME(0) | SSQR_IVOL(15) | SSQR_DUTY(3) | SSQR_INC,
 SSQR_LEN(0) | SSQR_TIME(1) | SSQR_IVOL(15) | SSQR_DUTY(0) | SSQR_INC,
 SSQR_LEN(0) | SSQR_TIME(1) | SSQR_IVOL(15) | SSQR_DUTY(1) | SSQR_INC,
 SSQR_LEN(0) | SSQR_TIME(1) | SSQR_IVOL(15) | SSQR_DUTY(2) | SSQR_INC,
 SSQR_LEN(0) | SSQR_TIME(1) | SSQR_IVOL(15) | SSQR_DUTY(3) | SSQR_INC,
 SSQR_LEN(0) | SSQR_TIME(0) | SSQR_IVOL(15) | SSQR_DUTY(2) | SSQR_INC,
 SSQR_LEN(0) | SSQR_TIME(0) | SSQR_IVOL(15) | SSQR_DUTY(2) | SSQR_INC,
 SSQR_LEN(0) | SSQR_TIME(0) | SSQR_IVOL(15) | SSQR_DUTY(2) | SSQR_INC,
 SSQR_LEN(0) | SSQR_TIME(0) | SSQR_IVOL(15) | SSQR_DUTY(2) | SSQR_INC,
 SSQR_LEN(0) | SSQR_TIME(0) | SSQR_IVOL(15) | SSQR_DUTY(2) | SSQR_INC,
 SSQR_LEN(0) | SSQR_TIME(0) | SSQR_IVOL(15) | SSQR_DUTY(2) | SSQR_INC,
 SSQR_LEN(0) | SSQR_TIME(0) | SSQR_IVOL(15) | SSQR_DUTY(2) | SSQR_INC,
};
const uint16_t chestopenWaveInstruments[] = {
 SWAV_LEN(0) | SWAV_VOL100, SWAV_LEN_OFF,
 SWAV_LEN(0) | SWAV_VOL100, SWAV_LEN_OFF,
 SWAV_LEN(0) | SWAV_VOL100, SWAV_LEN_OFF,
 SWAV_LEN(0) | SWAV_VOL100, SWAV_LEN_OFF,
 SWAV_LEN(0) | SWAV_VOL100, SWAV_LEN_OFF,
 SWAV_LEN(0) | SWAV_VOL100, SWAV_LEN_OFF,
 SWAV_LEN(0) | SWAV_VOL100, SWAV_LEN_OFF,
 SWAV_LEN(0) | SWAV_VOL100, SWAV_LEN_OFF,
 SWAV_LEN(0) | SWAV_VOL100, SWAV_LEN_OFF,
 SWAV_LEN(0) | SWAV_VOL100, SWAV_LEN_OFF,
 SWAV_LEN(0) | SWAV_VOL100, SWAV_LEN_OFF,
 SWAV_LEN(0) | SWAV_VOL100, SWAV_LEN_OFF,
 SWAV_LEN(0) | SWAV_VOL100, SWAV_LEN_OFF,
 SWAV_LEN(0) | SWAV_VOL100, SWAV_LEN_OFF,
 SWAV_LEN(0) | SWAV_VOL100, SWAV_LEN_OFF,
};
const uint16_t * const chestopenWaveforms[] = {
chestopenWaveform0,
chestopenWaveform1,
chestopenWaveform2,
chestopenWaveform3,
chestopenWaveform4,
chestopenWaveform5,
chestopenWaveform6,
chestopenWaveform7,
chestopenWaveform8,
chestopenWaveform9,
chestopenWaveform10,
chestopenWaveform11,
chestopenWaveform12,
chestopenWaveform13,
chestopenWaveform14,
};
const uint16_t chestopenNoiseInstruments[] = {
 SSQR_LEN(0) | SSQR_TIME(0) | SSQR_IVOL(15) | SSQR_INC | SNOI_LONG_PACK,
 SSQR_LEN(0) | SSQR_TIME(0) | SSQR_IVOL(15) | SSQR_INC | SNOI_LONG_PACK,
 SSQR_LEN(0) | SSQR_TIME(0) | SSQR_IVOL(15) | SSQR_INC | SNOI_LONG_PACK,
 SSQR_LEN(0) | SSQR_TIME(0) | SSQR_IVOL(15) | SSQR_INC | SNOI_LONG_PACK,
 SSQR_LEN(0) | SSQR_TIME(0) | SSQR_IVOL(15) | SSQR_INC | SNOI_LONG_PACK,
 SSQR_LEN(0) | SSQR_TIME(0) | SSQR_IVOL(15) | SSQR_INC | SNOI_LONG_PACK,
 SSQR_LEN(0) | SSQR_TIME(0) | SSQR_IVOL(15) | SSQR_INC | SNOI_LONG_PACK,
 SSQR_LEN(0) | SSQR_TIME(0) | SSQR_IVOL(15) | SSQR_INC | SNOI_LONG_PACK,
 SSQR_LEN(0) | SSQR_TIME(0) | SSQR_IVOL(15) | SSQR_INC | SNOI_LONG_PACK,
 SSQR_LEN(0) | SSQR_TIME(0) | SSQR_IVOL(15) | SSQR_INC | SNOI_LONG_PACK,
 SSQR_LEN(0) | SSQR_TIME(0) | SSQR_IVOL(15) | SSQR_INC | SNOI_LONG_PACK,
 SSQR_LEN(0) | SSQR_TIME(0) | SSQR_IVOL(15) | SSQR_INC | SNOI_LONG_PACK,
 SSQR_LEN(0) | SSQR_TIME(0) | SSQR_IVOL(15) | SSQR_INC | SNOI_LONG_PACK,
 SSQR_LEN(0) | SSQR_TIME(0) | SSQR_IVOL(15) | SSQR_INC | SNOI_LONG_PACK,
 SSQR_LEN(0) | SSQR_TIME(0) | SSQR_IVOL(15) | SSQR_INC | SNOI_LONG_PACK,
};
const uint8_t * const chestopenDMAInstruments[] = {
    blank_raw
};

const uint16_t chestopenDMADurations[] = {
    0
};
const advikSFXStruct chestopenSFXStruct = {
    chestopenSongOrder0,
    chestopenSongHeader,
    chestopenSquareInstruments,
    chestopenWaveInstruments,
    chestopenWaveforms,
    chestopenNoiseInstruments,
    chestopenDMAInstruments,
    chestopenDMADurations
    };
