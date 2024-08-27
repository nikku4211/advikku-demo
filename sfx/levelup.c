#include "../source/advikku_global.h"
#include <stdint.h>
#include <tonc.h>

#include "blank_raw.h"

/*
    Song name:  levelup
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

const uint8_t levelupSongHeader[] = {
    0x03,
    0x01,
    0x04,
    0x01,
    0x00,
    0x00,
    0x00
};

const uint8_t levelupSongOrder0[] = {
5,3,0x00, 0x00,
21,3,0x00, 0x00,
24,3,0x00, 0x00,
21,3,0x00, 0x00,
24,3,0x00, 0x00,
29,3,0x00, 0x00,
24,3,0x00, 0x00,
29,3,0x00, 0x00,
33,3,0x00, 0x00,
29,3,0x00, 0x00,
33,3,0x00, 0x00,
36,3,0x00, 0x00,
33,3,0x00, 0x00,
36,3,0x00, 0x00,
41,3,0x00, 0x00,
45,3,0x00, 0x00,
8,3,0x00, 0x00,
24,3,0x00, 0x00,
27,3,0x00, 0x00,
24,3,0x00, 0x00,
27,3,0x00, 0x00,
32,3,0x00, 0x00,
27,3,0x00, 0x00,
32,3,0x00, 0x00,
36,3,0x00, 0x00,
32,3,0x00, 0x00,
36,3,0x00, 0x00,
39,3,0x00, 0x00,
36,3,0x00, 0x00,
39,3,0x00, 0x00,
44,3,0x00, 0x00,
48,3,0x00, 0x00,
11,3,0x00, 0x00,
26,3,0x00, 0x00,
29,3,0x00, 0x00,
26,3,0x00, 0x00,
29,3,0x00, 0x00,
33,3,0x00, 0x00,
29,3,0x00, 0x00,
33,3,0x00, 0x00,
38,3,0x00, 0x00,
33,3,0x00, 0x00,
38,3,0x00, 0x00,
41,3,0x00, 0x00,
38,3,0x00, 0x00,
41,3,0x00, 0x00,
45,3,0x00, 0x00,
50,3,0x00, 0x00,
7,3,0x00, 0x00,
26,3,0x00, 0x00,
31,3,0x00, 0x00,
26,3,0x00, 0x00,
31,3,0x00, 0x00,
35,3,0x00, 0x00,
31,3,0x00, 0x00,
35,3,0x00, 0x00,
38,3,0x00, 0x00,
35,3,0x00, 0x00,
38,3,0x00, 0x00,
43,3,0x00, 0x00,
38,3,0x00, 0x00,
43,3,0x00, 0x00,
47,3,0x00, 0x00,
50,3,0x00, 0x00,
END
};

const uint16_t levelupWaveform0[] = {
    0x0000,
    0xffff,
    0xffff,
    0xffff,
    0xffff,
    0xffff,
    0xffff,
    0xffff,
};

const uint16_t levelupWaveform1[] = {
    0x0000,
    0x0000,
    0xffff,
    0xffff,
    0xffff,
    0xffff,
    0xffff,
    0xffff,
};

const uint16_t levelupWaveform2[] = {
    0x0000,
    0x0000,
    0x0000,
    0x0000,
    0xffff,
    0xffff,
    0xffff,
    0xffff,
};

const uint16_t levelupWaveform3[] = {
    0x0000,
    0x0000,
    0x0000,
    0x0000,
    0x0000,
    0x0000,
    0xffff,
    0xffff,
};

const uint16_t levelupWaveform4[] = {
    0x0001,
    0x1223,
    0x3445,
    0x5667,
    0x7889,
    0x9aab,
    0xbccd,
    0xdeef,
};

const uint16_t levelupWaveform5[] = {
    0xfedc,
    0xba98,
    0x7654,
    0x3210,
    0x1234,
    0x5678,
    0x9abc,
    0xdeff,
};

const uint16_t levelupWaveform6[] = {
    0x7acd,
    0xdb75,
    0x2113,
    0x68bd,
    0xdc97,
    0x4101,
    0x479c,
    0xddb8,
};

const uint16_t levelupWaveform7[] = {
    0x0f0f,
    0x0f0f,
    0x0f0f,
    0x0f0f,
    0x0f0f,
    0x0f0f,
    0x0f0f,
    0x0f0f,
};

const uint16_t levelupWaveform8[] = {
    0xfefc,
    0xfaf8,
    0xf6f4,
    0xf2f0,
    0xf2f4,
    0xf6f8,
    0xfafc,
    0xfeff,
};

const uint16_t levelupWaveform9[] = {
    0xfedd,
    0xccbb,
    0xaa99,
    0x8877,
    0x8abd,
    0xf124,
    0x578a,
    0xbdee,
};

const uint16_t levelupWaveform10[] = {
    0x8411,
    0x61ed,
    0x5747,
    0x5aad,
    0xcea3,
    0x1779,
    0xdd20,
    0x0347,
};

const uint16_t levelupWaveform11[] = {
    0x7286,
    0xa608,
    0xbaa8,
    0x2d0b,
    0x3db6,
    0xa355,
    0x9799,
    0xdaad,
};

const uint16_t levelupWaveform12[] = {
    0x232d,
    0x6403,
    0x371a,
    0x6854,
    0xe632,
    0x84a2,
    0x1a8e,
    0x48d0,
};

const uint16_t levelupWaveform13[] = {
    0x187c,
    0x5224,
    0x87e5,
    0x6b20,
    0xdc3a,
    0x8879,
    0x0487,
    0x577d,
};

const uint16_t levelupWaveform14[] = {
    0x0578,
    0x010a,
    0xab53,
    0xe244,
    0xb0a9,
    0x689c,
    0x7eec,
    0x501b,
};

const uint16_t levelupWaveform15[] = {
    0xc07d,
    0x24ba,
    0x028e,
    0x1231,
    0xbe3c,
    0xd892,
    0x9916,
    0x7d00,
};


const uint16_t levelupSquareInstruments[] = {
 SSQR_LEN(0) | SSQR_TIME(0) | SSQR_IVOL(15) | SSQR_DUTY(0) | SSQR_INC,
 SSQR_LEN(0) | SSQR_TIME(0) | SSQR_IVOL(15) | SSQR_DUTY(1) | SSQR_INC,
 SSQR_LEN(0) | SSQR_TIME(0) | SSQR_IVOL(10) | SSQR_DUTY(2) | SSQR_INC,
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
const uint16_t levelupWaveInstruments[] = {
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
const uint16_t * const levelupWaveforms[] = {
levelupWaveform0,
levelupWaveform1,
levelupWaveform2,
levelupWaveform3,
levelupWaveform4,
levelupWaveform5,
levelupWaveform6,
levelupWaveform7,
levelupWaveform8,
levelupWaveform9,
levelupWaveform10,
levelupWaveform11,
levelupWaveform12,
levelupWaveform13,
levelupWaveform14,
};
const uint16_t levelupNoiseInstruments[] = {
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
const uint8_t * const levelupDMAInstruments[] = {
    blank_raw
};

const uint16_t levelupDMADurations[] = {
    0
};
const advikSFXStruct levelupSFXStruct = {
    levelupSongOrder0,
    levelupSongHeader,
    levelupSquareInstruments,
    levelupWaveInstruments,
    levelupWaveforms,
    levelupNoiseInstruments,
    levelupDMAInstruments,
    levelupDMADurations
    };
