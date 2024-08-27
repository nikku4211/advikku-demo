#include <stdint.h>
#include <tonc.h>
//converted by Nikku4211's furtoadvik.py, reliant on zumi.dxy's chipchune.py
#include "../source/advikku_global.h"
#include "blank_raw.h"
#include "youcantsay_raw.h"

#define END 0xff
#define HOLD 0xfe

//speed
//version
//channels
//song length in orders per channel
//song order loopstart
//commands linger flag
//use subpatterns flag

const uint8_t im_stupidSongHeader[] = {
  0x06,
  0x01,
  0x06,
  0x01,
  0x00,
  0x01,
  0x00
};

const uint8_t im_stupidSongOrderChan4_0[] = {
41, 1,
0x04, 0x82,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x04, 0x00,
END
};

const uint16_t im_stupidWaveformBlank[] = {
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
};

const uint16_t im_stupidSquareInstruments[] = {
0,
};

const uint16_t im_stupidWaveInstruments[] = {
0, SWAV_LEN_OFF,
};

const uint16_t * const im_stupidWaveforms[] = {
im_stupidWaveformBlank,
};

const uint16_t im_stupidNoiseInstruments[] = {
0,
};

const uint8_t * const im_stupidDMAInstruments[] = {
youcantsay_raw,
};

const uint16_t im_stupidDMADurations[] = {
160,
};

const advikSFXStruct im_stupidSFXStruct = {
im_stupidSongOrderChan4_0,
im_stupidSongHeader,
im_stupidSquareInstruments,
im_stupidWaveInstruments,
im_stupidWaveforms,
im_stupidNoiseInstruments,
im_stupidDMAInstruments,
im_stupidDMADurations
};