#include "../source/advikku_global.h"
#include <stdint.h>
#include <tonc.h>

#include "blank_raw.h"

/*
    Song name:  buttonpress
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

const uint8_t buttonpressSongHeader[] = {
    0x02,
    0x01,
    0x04,
    0x01,
    0x00,
    0x00,
    0x00
};

const uint8_t buttonpressSongOrder0[] = {
30,3,0x00, 0x00,
42,3,0x00, 0x00,
30,3,0x00, 0x00,
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
END
};

const uint16_t buttonpressWaveform0[] = {
    0x0000,
    0xffff,
    0xffff,
    0xffff,
    0xffff,
    0xffff,
    0xffff,
    0xffff,
};

const uint16_t buttonpressWaveform1[] = {
    0x0000,
    0x0000,
    0xffff,
    0xffff,
    0xffff,
    0xffff,
    0xffff,
    0xffff,
};

const uint16_t buttonpressWaveform2[] = {
    0x0000,
    0x0000,
    0x0000,
    0x0000,
    0xffff,
    0xffff,
    0xffff,
    0xffff,
};

const uint16_t buttonpressWaveform3[] = {
    0x0000,
    0x0000,
    0x0000,
    0x0000,
    0x0000,
    0x0000,
    0xffff,
    0xffff,
};

const uint16_t buttonpressWaveform4[] = {
    0x0001,
    0x1223,
    0x3445,
    0x5667,
    0x7889,
    0x9aab,
    0xbccd,
    0xdeef,
};

const uint16_t buttonpressWaveform5[] = {
    0xfedc,
    0xba98,
    0x7654,
    0x3210,
    0x1234,
    0x5678,
    0x9abc,
    0xdeff,
};

const uint16_t buttonpressWaveform6[] = {
    0x7acd,
    0xdb75,
    0x2113,
    0x68bd,
    0xdc97,
    0x4101,
    0x479c,
    0xddb8,
};

const uint16_t buttonpressWaveform7[] = {
    0x0f0f,
    0x0f0f,
    0x0f0f,
    0x0f0f,
    0x0f0f,
    0x0f0f,
    0x0f0f,
    0x0f0f,
};

const uint16_t buttonpressWaveform8[] = {
    0xfefc,
    0xfaf8,
    0xf6f4,
    0xf2f0,
    0xf2f4,
    0xf6f8,
    0xfafc,
    0xfeff,
};

const uint16_t buttonpressWaveform9[] = {
    0xfedd,
    0xccbb,
    0xaa99,
    0x8877,
    0x8abd,
    0xf124,
    0x578a,
    0xbdee,
};

const uint16_t buttonpressWaveform10[] = {
    0x8411,
    0x61ed,
    0x5747,
    0x5aad,
    0xcea3,
    0x1779,
    0xdd20,
    0x0347,
};

const uint16_t buttonpressWaveform11[] = {
    0x53e3,
    0x6a85,
    0x32d5,
    0xda4a,
    0x7cde,
    0x5011,
    0x92c7,
    0x1218,
};

const uint16_t buttonpressWaveform12[] = {
    0x7121,
    0xd220,
    0xacd9,
    0x583e,
    0x3654,
    0x74ce,
    0xa3e4,
    0x2d2a,
};

const uint16_t buttonpressWaveform13[] = {
    0x1845,
    0x0c82,
    0x5044,
    0x6cd7,
    0x7eed,
    0x1c71,
    0xd593,
    0x6783,
};

const uint16_t buttonpressWaveform14[] = {
    0x9036,
    0xbdd0,
    0x7c08,
    0x8658,
    0xd9e5,
    0x29b0,
    0xd71d,
    0x80b7,
};

const uint16_t buttonpressWaveform15[] = {
    0xadb8,
    0x7ca6,
    0xc170,
    0x633a,
    0xe661,
    0xc659,
    0x633d,
    0x3148,
};


const uint16_t buttonpressSquareInstruments[] = {
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
const uint16_t buttonpressWaveInstruments[] = {
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
const uint16_t * const buttonpressWaveforms[] = {
buttonpressWaveform0,
buttonpressWaveform1,
buttonpressWaveform2,
buttonpressWaveform3,
buttonpressWaveform4,
buttonpressWaveform5,
buttonpressWaveform6,
buttonpressWaveform7,
buttonpressWaveform8,
buttonpressWaveform9,
buttonpressWaveform10,
buttonpressWaveform11,
buttonpressWaveform12,
buttonpressWaveform13,
buttonpressWaveform14,
};
const uint16_t buttonpressNoiseInstruments[] = {
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
const uint8_t * const buttonpressDMAInstruments[] = {
    blank_raw
};

const uint16_t buttonpressDMADurations[] = {
    0
};
const advikSFXStruct buttonpressSFXStruct = {
    buttonpressSongOrder0,
    buttonpressSongHeader,
    buttonpressSquareInstruments,
    buttonpressWaveInstruments,
    buttonpressWaveforms,
    buttonpressNoiseInstruments,
    buttonpressDMAInstruments,
    buttonpressDMADurations
    };
