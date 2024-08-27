#include "../source/advikku_global.h"
#include <stdint.h>
#include <tonc.h>

#include "blank_raw.h"

/*
    Song name:  punchhitpulsepart
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

const uint8_t punchhitpulsepartSongHeader[] = {
    0x07,
    0x01,
    0x04,
    0x01,
    0x00,
    0x00,
    0x00
};

const uint8_t punchhitpulsepartSongOrder0[] = {
9,3,0x02, 0x80,
HOLD,0,0x0C, 0x00,
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

const uint16_t punchhitpulsepartWaveform0[] = {
    0x0000,
    0xffff,
    0xffff,
    0xffff,
    0xffff,
    0xffff,
    0xffff,
    0xffff,
};

const uint16_t punchhitpulsepartWaveform1[] = {
    0x0000,
    0x0000,
    0xffff,
    0xffff,
    0xffff,
    0xffff,
    0xffff,
    0xffff,
};

const uint16_t punchhitpulsepartWaveform2[] = {
    0x0000,
    0x0000,
    0x0000,
    0x0000,
    0xffff,
    0xffff,
    0xffff,
    0xffff,
};

const uint16_t punchhitpulsepartWaveform3[] = {
    0x0000,
    0x0000,
    0x0000,
    0x0000,
    0x0000,
    0x0000,
    0xffff,
    0xffff,
};

const uint16_t punchhitpulsepartWaveform4[] = {
    0x0001,
    0x1223,
    0x3445,
    0x5667,
    0x7889,
    0x9aab,
    0xbccd,
    0xdeef,
};

const uint16_t punchhitpulsepartWaveform5[] = {
    0xfedc,
    0xba98,
    0x7654,
    0x3210,
    0x1234,
    0x5678,
    0x9abc,
    0xdeff,
};

const uint16_t punchhitpulsepartWaveform6[] = {
    0x7acd,
    0xdb75,
    0x2113,
    0x68bd,
    0xdc97,
    0x4101,
    0x479c,
    0xddb8,
};

const uint16_t punchhitpulsepartWaveform7[] = {
    0x0f0f,
    0x0f0f,
    0x0f0f,
    0x0f0f,
    0x0f0f,
    0x0f0f,
    0x0f0f,
    0x0f0f,
};

const uint16_t punchhitpulsepartWaveform8[] = {
    0xfefc,
    0xfaf8,
    0xf6f4,
    0xf2f0,
    0xf2f4,
    0xf6f8,
    0xfafc,
    0xfeff,
};

const uint16_t punchhitpulsepartWaveform9[] = {
    0xfedd,
    0xccbb,
    0xaa99,
    0x8877,
    0x8abd,
    0xf124,
    0x578a,
    0xbdee,
};

const uint16_t punchhitpulsepartWaveform10[] = {
    0x8411,
    0x61ed,
    0x5747,
    0x5aad,
    0xcea3,
    0x1779,
    0xdd20,
    0x0347,
};

const uint16_t punchhitpulsepartWaveform11[] = {
    0x5350,
    0xab57,
    0x678a,
    0x1314,
    0x1088,
    0x1989,
    0x4b42,
    0x7b00,
};

const uint16_t punchhitpulsepartWaveform12[] = {
    0xbdbc,
    0x947b,
    0x6485,
    0x83d7,
    0xd981,
    0x3cdd,
    0xe810,
    0x4ca6,
};

const uint16_t punchhitpulsepartWaveform13[] = {
    0x0ae0,
    0x0048,
    0x3dc8,
    0x6574,
    0x54b8,
    0xae3b,
    0x0cee,
    0x09b8,
};

const uint16_t punchhitpulsepartWaveform14[] = {
    0xa34d,
    0x9384,
    0xa765,
    0xd852,
    0x5138,
    0x157c,
    0x8899,
    0x3531,
};

const uint16_t punchhitpulsepartWaveform15[] = {
    0xa689,
    0x3b55,
    0x2b37,
    0xbac2,
    0x52be,
    0x47a1,
    0xb7c3,
    0xbedb,
};


const uint16_t punchhitpulsepartSquareInstruments[] = {
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
const uint16_t punchhitpulsepartWaveInstruments[] = {
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
const uint16_t * const punchhitpulsepartWaveforms[] = {
punchhitpulsepartWaveform0,
punchhitpulsepartWaveform1,
punchhitpulsepartWaveform2,
punchhitpulsepartWaveform3,
punchhitpulsepartWaveform4,
punchhitpulsepartWaveform5,
punchhitpulsepartWaveform6,
punchhitpulsepartWaveform7,
punchhitpulsepartWaveform8,
punchhitpulsepartWaveform9,
punchhitpulsepartWaveform10,
punchhitpulsepartWaveform11,
punchhitpulsepartWaveform12,
punchhitpulsepartWaveform13,
punchhitpulsepartWaveform14,
};
const uint16_t punchhitpulsepartNoiseInstruments[] = {
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
const uint8_t * const punchhitpulsepartDMAInstruments[] = {
    blank_raw
};

const uint16_t punchhitpulsepartDMADurations[] = {
    0
};
const advikSFXStruct punchhitpulsepartSFXStruct = {
    punchhitpulsepartSongOrder0,
    punchhitpulsepartSongHeader,
    punchhitpulsepartSquareInstruments,
    punchhitpulsepartWaveInstruments,
    punchhitpulsepartWaveforms,
    punchhitpulsepartNoiseInstruments,
    punchhitpulsepartDMAInstruments,
    punchhitpulsepartDMADurations
    };
