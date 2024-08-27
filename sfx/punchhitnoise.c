#include "../source/advikku_global.h"
#include <stdint.h>
#include <tonc.h>

#include "blank_raw.h"

/*
    Song name:  punchhitnoisepart
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

const uint8_t punchhitnoisepartSongHeader[] = {
    0x07,
    0x01,
    0x04,
    0x01,
    0x00,
    0x00,
    0x00
};

const uint8_t punchhitnoisepartSongOrder0[] = {
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

const uint16_t punchhitnoisepartWaveform0[] = {
    0x0000,
    0xffff,
    0xffff,
    0xffff,
    0xffff,
    0xffff,
    0xffff,
    0xffff,
};

const uint16_t punchhitnoisepartWaveform1[] = {
    0x0000,
    0x0000,
    0xffff,
    0xffff,
    0xffff,
    0xffff,
    0xffff,
    0xffff,
};

const uint16_t punchhitnoisepartWaveform2[] = {
    0x0000,
    0x0000,
    0x0000,
    0x0000,
    0xffff,
    0xffff,
    0xffff,
    0xffff,
};

const uint16_t punchhitnoisepartWaveform3[] = {
    0x0000,
    0x0000,
    0x0000,
    0x0000,
    0x0000,
    0x0000,
    0xffff,
    0xffff,
};

const uint16_t punchhitnoisepartWaveform4[] = {
    0x0001,
    0x1223,
    0x3445,
    0x5667,
    0x7889,
    0x9aab,
    0xbccd,
    0xdeef,
};

const uint16_t punchhitnoisepartWaveform5[] = {
    0xfedc,
    0xba98,
    0x7654,
    0x3210,
    0x1234,
    0x5678,
    0x9abc,
    0xdeff,
};

const uint16_t punchhitnoisepartWaveform6[] = {
    0x7acd,
    0xdb75,
    0x2113,
    0x68bd,
    0xdc97,
    0x4101,
    0x479c,
    0xddb8,
};

const uint16_t punchhitnoisepartWaveform7[] = {
    0x0f0f,
    0x0f0f,
    0x0f0f,
    0x0f0f,
    0x0f0f,
    0x0f0f,
    0x0f0f,
    0x0f0f,
};

const uint16_t punchhitnoisepartWaveform8[] = {
    0xfefc,
    0xfaf8,
    0xf6f4,
    0xf2f0,
    0xf2f4,
    0xf6f8,
    0xfafc,
    0xfeff,
};

const uint16_t punchhitnoisepartWaveform9[] = {
    0xfedd,
    0xccbb,
    0xaa99,
    0x8877,
    0x8abd,
    0xf124,
    0x578a,
    0xbdee,
};

const uint16_t punchhitnoisepartWaveform10[] = {
    0x8411,
    0x61ed,
    0x5747,
    0x5aad,
    0xcea3,
    0x1779,
    0xdd20,
    0x0347,
};

const uint16_t punchhitnoisepartWaveform11[] = {
    0xce00,
    0xbc55,
    0xa551,
    0xe8d5,
    0x2c62,
    0xe735,
    0xae11,
    0x4e59,
};

const uint16_t punchhitnoisepartWaveform12[] = {
    0x3959,
    0x6a44,
    0x5390,
    0xa006,
    0x1d23,
    0x46e8,
    0xe9ed,
    0x89c7,
};

const uint16_t punchhitnoisepartWaveform13[] = {
    0x5359,
    0x1886,
    0x1509,
    0x9b0e,
    0x4aca,
    0x5ba2,
    0x852a,
    0x2d45,
};

const uint16_t punchhitnoisepartWaveform14[] = {
    0xce1d,
    0xe6d7,
    0xa28c,
    0x58aa,
    0x1172,
    0xad07,
    0x780c,
    0x2ba6,
};

const uint16_t punchhitnoisepartWaveform15[] = {
    0x5dc9,
    0xd1ec,
    0x4263,
    0x7b86,
    0x05d9,
    0x70c3,
    0xc292,
    0x44b3,
};


const uint16_t punchhitnoisepartSquareInstruments[] = {
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
const uint16_t punchhitnoisepartWaveInstruments[] = {
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
const uint16_t * const punchhitnoisepartWaveforms[] = {
punchhitnoisepartWaveform0,
punchhitnoisepartWaveform1,
punchhitnoisepartWaveform2,
punchhitnoisepartWaveform3,
punchhitnoisepartWaveform4,
punchhitnoisepartWaveform5,
punchhitnoisepartWaveform6,
punchhitnoisepartWaveform7,
punchhitnoisepartWaveform8,
punchhitnoisepartWaveform9,
punchhitnoisepartWaveform10,
punchhitnoisepartWaveform11,
punchhitnoisepartWaveform12,
punchhitnoisepartWaveform13,
punchhitnoisepartWaveform14,
};
const uint16_t punchhitnoisepartNoiseInstruments[] = {
 SSQR_LEN(0) | SSQR_TIME(1) | SSQR_IVOL(15) | SSQR_INC | SNOI_LONG_PACK,
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
const uint8_t * const punchhitnoisepartDMAInstruments[] = {
    blank_raw
};

const uint16_t punchhitnoisepartDMADurations[] = {
    0
};
const advikSFXStruct punchhitnoisepartSFXStruct = {
    punchhitnoisepartSongOrder0,
    punchhitnoisepartSongHeader,
    punchhitnoisepartSquareInstruments,
    punchhitnoisepartWaveInstruments,
    punchhitnoisepartWaveforms,
    punchhitnoisepartNoiseInstruments,
    punchhitnoisepartDMAInstruments,
    punchhitnoisepartDMADurations
    };
