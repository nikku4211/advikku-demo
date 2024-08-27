#include <stdint.h>
#include <tonc.h>
//converted by Nikku4211's furtoadvik.py, reliant on zumi.dxy's chipchune.py
#include "../source/advikku_global.h"
#include "blank_raw.h"
#include "zetakick_raw.h"
#include "zetasnare_raw.h"

#define END 0xff
#define HOLD 0xfe

//speed
//version
//channels
//song length in orders per channel
//song order loopstart
//commands linger flag
//use subpatterns flag

const uint8_t InstitutionalisedSongHeader[] = {
  0x08,
  0x01,
  0x06,
  0x08,
  0x00,
  0x01,
  0x00
};

const uint8_t InstitutionalisedSongOrderChan0_0[] = {
23, 5,
0x00, 0x00,
22, 5,
0x00, 0x00,
23, 5,
0x00, 0x00,
26, 5,
0x00, 0x00,
25, 5,
0x00, 0x00,
26, 5,
0x00, 0x00,
23, 5,
0x00, 0x00,
22, 5,
0x00, 0x00,
23, 5,
0x00, 0x00,
26, 5,
0x00, 0x00,
25, 5,
0x00, 0x00,
26, 5,
0x00, 0x00,
23, 5,
0x00, 0x00,
22, 5,
0x00, 0x00,
23, 5,
0x00, 0x00,
22, 5,
0x00, 0x00,
23, 5,
0x00, 0x00,
26, 5,
0x00, 0x00,
25, 5,
0x00, 0x00,
26, 5,
0x00, 0x00,
23, 5,
0x00, 0x00,
22, 5,
0x00, 0x00,
23, 5,
0x00, 0x00,
26, 5,
0x00, 0x00,
25, 5,
0x00, 0x00,
26, 5,
0x00, 0x00,
23, 5,
0x00, 0x00,
22, 5,
0x00, 0x00,
23, 5,
0x00, 0x00,
22, 5,
0x00, 0x00,
23, 5,
0x00, 0x00,
26, 5,
0x00, 0x00,
25, 5,
0x00, 0x00,
26, 5,
0x00, 0x00,
23, 5,
0x00, 0x00,
22, 5,
0x00, 0x00,
23, 5,
0x00, 0x00,
26, 5,
0x00, 0x00,
25, 5,
0x00, 0x00,
26, 5,
0x00, 0x00,
23, 5,
0x00, 0x00,
22, 5,
0x00, 0x00,
23, 5,
0x00, 0x00,
22, 5,
0x00, 0x00,
23, 5,
0x00, 0x00,
26, 5,
0x00, 0x00,
25, 5,
0x00, 0x00,
26, 5,
0x00, 0x00,
23, 5,
0x00, 0x00,
22, 5,
0x00, 0x00,
23, 5,
0x00, 0x00,
26, 5,
0x00, 0x00,
25, 5,
0x00, 0x00,
26, 5,
0x00, 0x00,
23, 5,
0x00, 0x00,
22, 5,
0x00, 0x00,
END
};
const uint8_t InstitutionalisedSongOrderChan1_0[] = {
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
END
};
const uint8_t InstitutionalisedSongOrderChan2_4[] = {
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
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
END
};
const uint8_t InstitutionalisedSongOrderChan3_0[] = {
36, 3,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x07,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x07,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x07,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x07,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x07,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x07,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x07,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x07,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x07,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x07,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x07,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x07,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x07,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x07,
HOLD, 0,
0x00, 0x00,
END
};
const uint8_t InstitutionalisedSongOrderChan4_0[] = {
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
END
};
const uint8_t InstitutionalisedSongOrderChan5_0[] = {
24, 1,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
24, 1,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
24, 2,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
24, 2,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
24, 1,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
24, 1,
0x00, 0x00,
24, 2,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
24, 2,
0x00, 0x00,
24, 1,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
24, 1,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
24, 2,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
24, 2,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
24, 1,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
24, 1,
0x00, 0x00,
24, 2,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
24, 2,
0x00, 0x00,
24, 1,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
24, 1,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
24, 2,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
24, 2,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
24, 1,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
24, 1,
0x00, 0x00,
24, 2,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
24, 2,
0x00, 0x00,
24, 1,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
24, 1,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
24, 2,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
24, 2,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
24, 1,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
24, 1,
0x00, 0x00,
24, 2,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
24, 2,
0x00, 0x00,
END
};
const uint8_t InstitutionalisedSongOrderChan2_5[] = {
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
END
};
const uint8_t InstitutionalisedSongOrderChan3_1[] = {
36, 3,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
END
};
const uint8_t InstitutionalisedSongOrderChan5_1[] = {
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
24, 1,
0x00, 0x00,
24, 2,
0x00, 0x00,
24, 1,
0x00, 0x00,
24, 1,
0x00, 0x00,
END
};
const uint8_t InstitutionalisedSongOrderChan1_1[] = {
23, 6,
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
23, 6,
0x04, 0x00,
HOLD, 0,
0x00, 0x00,
26, 6,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
25, 6,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
23, 6,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
22, 6,
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
25, 6,
0x04, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
23, 6,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
22, 6,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
21, 6,
0x04, 0x82,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
END
};
const uint8_t InstitutionalisedSongOrderChan2_0[] = {
11, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
11, 4,
0x0E, 0x04,
11, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
HOLD, 0,
0x00, 0x00,
11, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
11, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
5, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
11, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
11, 4,
0x0E, 0x04,
11, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
HOLD, 0,
0x00, 0x00,
11, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
11, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
6, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
11, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
11, 4,
0x0E, 0x04,
11, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
HOLD, 0,
0x00, 0x00,
11, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
11, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
5, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
11, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
11, 4,
0x0E, 0x04,
11, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
HOLD, 0,
0x00, 0x00,
11, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
11, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
6, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
END
};
const uint8_t InstitutionalisedSongOrderChan1_2[] = {
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
23, 6,
0x04, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
22, 6,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
21, 6,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
20, 6,
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
19, 6,
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
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
END
};
const uint8_t InstitutionalisedSongOrderChan2_1[] = {
11, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
11, 4,
0x0E, 0x04,
11, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
HOLD, 0,
0x00, 0x00,
11, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
11, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
5, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
11, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
11, 4,
0x0E, 0x04,
11, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
HOLD, 0,
0x00, 0x00,
11, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
11, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
6, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
10, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
10, 4,
0x0E, 0x04,
10, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
HOLD, 0,
0x00, 0x00,
10, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
10, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
6, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
10, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
10, 4,
0x0E, 0x04,
10, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
HOLD, 0,
0x00, 0x00,
10, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
10, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
6, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
END
};
const uint8_t InstitutionalisedSongOrderChan1_3[] = {
23, 6,
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
23, 6,
0x04, 0x00,
HOLD, 0,
0x00, 0x00,
26, 6,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
25, 6,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
23, 6,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
28, 6,
0x00, 0x00,
30, 6,
0x03, 0x10,
HOLD, 0,
0x04, 0x82,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x03, 0x00,
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
30, 6,
0x04, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
31, 6,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
28, 6,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
30, 6,
0x04, 0x82,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
END
};
const uint8_t InstitutionalisedSongOrderChan1_4[] = {
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
30, 6,
0x04, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
31, 6,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
28, 6,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
26, 6,
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
25, 6,
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
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
END
};
const uint8_t InstitutionalisedSongOrderChan3_2[] = {
36, 3,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x07,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x07,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x07,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x07,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x07,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x07,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x07,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x07,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x07,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x07,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x07,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x07,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x07,
HOLD, 0,
0x00, 0x00,
36, 3,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
36, 7,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
END
};
const uint8_t InstitutionalisedSongOrderChan0_1[] = {
13, 5,
0x00, 0x00,
13, 5,
0x00, 0x00,
13, 5,
0x00, 0x00,
13, 5,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
13, 5,
0x00, 0x00,
13, 5,
0x00, 0x00,
13, 5,
0x00, 0x00,
13, 5,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
13, 5,
0x00, 0x00,
13, 5,
0x00, 0x00,
13, 5,
0x00, 0x00,
13, 5,
0x00, 0x00,
13, 5,
0x00, 0x00,
13, 5,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
13, 5,
0x00, 0x00,
13, 5,
0x00, 0x00,
13, 5,
0x00, 0x00,
13, 5,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
13, 5,
0x00, 0x00,
13, 5,
0x00, 0x00,
14, 5,
0x00, 0x00,
14, 5,
0x00, 0x00,
14, 5,
0x00, 0x00,
14, 5,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
14, 5,
0x00, 0x00,
14, 5,
0x00, 0x00,
14, 5,
0x00, 0x00,
14, 5,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
14, 5,
0x00, 0x00,
14, 5,
0x00, 0x00,
14, 5,
0x00, 0x00,
14, 5,
0x00, 0x00,
14, 5,
0x00, 0x00,
14, 5,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
14, 5,
0x00, 0x00,
14, 5,
0x00, 0x00,
14, 5,
0x00, 0x00,
14, 5,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
14, 5,
0x00, 0x00,
14, 5,
0x00, 0x00,
END
};
const uint8_t InstitutionalisedSongOrderChan2_2[] = {
9, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
9, 4,
0x0E, 0x04,
9, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
HOLD, 0,
0x00, 0x00,
9, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
9, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
4, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
9, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
9, 4,
0x0E, 0x04,
9, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
HOLD, 0,
0x00, 0x00,
9, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
9, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
4, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
10, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
10, 4,
0x0E, 0x04,
10, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
HOLD, 0,
0x00, 0x00,
10, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
10, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
5, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
10, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
10, 4,
0x0E, 0x04,
10, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
HOLD, 0,
0x00, 0x00,
10, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
10, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
5, 4,
0x00, 0x00,
HOLD, 0,
0x0E, 0x04,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
END
};
const uint8_t InstitutionalisedSongOrderChan3_3[] = {
36, 7,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
36, 7,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
36, 7,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
36, 7,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
36, 7,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
36, 7,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
36, 7,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
36, 7,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
36, 7,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
36, 7,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
36, 7,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
36, 7,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
36, 7,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
36, 7,
0x0C, 0x0c,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
END
};
const uint8_t InstitutionalisedSongOrderChan0_2[] = {
13, 5,
0x00, 0x00,
13, 5,
0x00, 0x00,
13, 5,
0x00, 0x00,
13, 5,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
13, 5,
0x00, 0x00,
13, 5,
0x00, 0x00,
13, 5,
0x00, 0x00,
13, 5,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
13, 5,
0x00, 0x00,
13, 5,
0x00, 0x00,
13, 5,
0x00, 0x00,
13, 5,
0x00, 0x00,
13, 5,
0x00, 0x00,
13, 5,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
13, 5,
0x00, 0x00,
13, 5,
0x00, 0x00,
13, 5,
0x00, 0x00,
13, 5,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
13, 5,
0x00, 0x00,
13, 5,
0x00, 0x00,
14, 5,
0x00, 0x00,
14, 5,
0x00, 0x00,
14, 5,
0x00, 0x00,
14, 5,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
14, 5,
0x00, 0x00,
14, 5,
0x00, 0x00,
14, 5,
0x00, 0x00,
14, 5,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
14, 5,
0x00, 0x00,
14, 5,
0x00, 0x00,
14, 5,
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
END
};
const uint8_t InstitutionalisedSongOrderChan2_3[] = {
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
HOLD, 0,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
5, 4,
0x0E, 0x06,
5, 4,
0x0E, 0x06,
END
};
const uint8_t InstitutionalisedSongOrderChan5_2[] = {
24, 1,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
24, 1,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
24, 2,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
24, 2,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
24, 1,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
24, 1,
0x00, 0x00,
24, 2,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
24, 2,
0x00, 0x00,
24, 1,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
24, 1,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
24, 2,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
24, 2,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
24, 1,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
24, 1,
0x00, 0x00,
24, 2,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
24, 2,
0x00, 0x00,
24, 1,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
24, 1,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
24, 2,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
24, 2,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
24, 1,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
24, 1,
0x00, 0x00,
24, 2,
0x00, 0x00,
HOLD, 0,
0x00, 0x00,
24, 2,
0x00, 0x00,
24, 1,
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
24, 1,
0x00, 0x00,
24, 2,
0x00, 0x00,
24, 1,
0x00, 0x00,
24, 1,
0x0b, 0x01,
END
};
const uint8_t * const InstitutionalisedSong[] = {
InstitutionalisedSongOrderChan0_0,
InstitutionalisedSongOrderChan1_0,
InstitutionalisedSongOrderChan2_5,
InstitutionalisedSongOrderChan3_1,
InstitutionalisedSongOrderChan4_0,
InstitutionalisedSongOrderChan5_1,
InstitutionalisedSongOrderChan0_0,
InstitutionalisedSongOrderChan1_0,
InstitutionalisedSongOrderChan2_0,
InstitutionalisedSongOrderChan3_0,
InstitutionalisedSongOrderChan4_0,
InstitutionalisedSongOrderChan5_0,
InstitutionalisedSongOrderChan0_0,
InstitutionalisedSongOrderChan1_1,
InstitutionalisedSongOrderChan2_1,
InstitutionalisedSongOrderChan3_0,
InstitutionalisedSongOrderChan4_0,
InstitutionalisedSongOrderChan5_0,
InstitutionalisedSongOrderChan0_0,
InstitutionalisedSongOrderChan1_2,
InstitutionalisedSongOrderChan2_2,
InstitutionalisedSongOrderChan3_0,
InstitutionalisedSongOrderChan4_0,
InstitutionalisedSongOrderChan5_0,
InstitutionalisedSongOrderChan0_0,
InstitutionalisedSongOrderChan1_3,
InstitutionalisedSongOrderChan2_1,
InstitutionalisedSongOrderChan3_0,
InstitutionalisedSongOrderChan4_0,
InstitutionalisedSongOrderChan5_0,
InstitutionalisedSongOrderChan0_0,
InstitutionalisedSongOrderChan1_4,
InstitutionalisedSongOrderChan2_2,
InstitutionalisedSongOrderChan3_2,
InstitutionalisedSongOrderChan4_0,
InstitutionalisedSongOrderChan5_0,
InstitutionalisedSongOrderChan0_1,
InstitutionalisedSongOrderChan1_0,
InstitutionalisedSongOrderChan2_3,
InstitutionalisedSongOrderChan3_3,
InstitutionalisedSongOrderChan4_0,
InstitutionalisedSongOrderChan5_0,
InstitutionalisedSongOrderChan0_2,
InstitutionalisedSongOrderChan1_0,
InstitutionalisedSongOrderChan2_4,
InstitutionalisedSongOrderChan3_3,
InstitutionalisedSongOrderChan4_0,
InstitutionalisedSongOrderChan5_2,
};


const uint16_t InstitutionalisedWaveform0[] = {
0x00ff, 
0x00ff, 
0xff00, 
0x00ff, 
0xffff, 
0x00ff, 
0x0000, 
0x0000, 
};

const uint16_t InstitutionalisedWaveformBlank[] = {
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
};

const uint16_t InstitutionalisedSquareInstruments[] = {
0,
0,
SSQR_LEN(52) | SSQR_TIME(1) | SSQR_IVOL(12) |SSQR_INC |0,
SSQR_LEN(0) | SSQR_TIME(2) | SSQR_IVOL(15) | SSQR_INC |0,
SSQR_DUTY1_2 |SSQR_LEN(0) | SSQR_TIME(1) | SSQR_IVOL(14) |SSQR_INC |0,
SSQR_DUTY1_4 |SSQR_LEN(0) | SSQR_TIME(6) | SSQR_IVOL(15) |SSQR_INC |0,
SSQR_LEN(0) | SSQR_TIME(2) | SSQR_IVOL(12) |SSQR_INC |0,
};

const uint16_t InstitutionalisedWaveInstruments[] = {
0, SWAV_LEN_OFF,
0, SWAV_LEN_OFF,
SWAV_LEN(52) | 
0,
SWAV_LEN_ON,
0,
SWAV_LEN_OFF,
SWAV_LEN(0) | 
0,
SWAV_LEN_ON,
SWAV_LEN(0) | 
0,
SWAV_LEN_ON,
SWAV_LEN(0) | 
0,
SWAV_LEN_ON,
};

const uint16_t * const InstitutionalisedWaveforms[] = {
InstitutionalisedWaveformBlank,
InstitutionalisedWaveformBlank,
InstitutionalisedWaveformBlank,
InstitutionalisedWaveform0,
InstitutionalisedWaveformBlank,
InstitutionalisedWaveformBlank,
InstitutionalisedWaveformBlank,
};

const uint16_t InstitutionalisedNoiseInstruments[] = {
0,
0,
SSQR_LEN(52) | SSQR_TIME(1) | SSQR_IVOL(12) | SNOI_LONG_PACK | SSQR_INC | 0,
SSQR_LEN(0) | SSQR_TIME(2) | SSQR_IVOL(15) | SSQR_INC | SNOI_LONG_PACK | 0,
SSQR_LEN(0) | SSQR_TIME(1) | SSQR_IVOL(14) | SNOI_LONG_PACK | SSQR_INC | 0,
SSQR_LEN(0) | SSQR_TIME(6) | SSQR_IVOL(15) | SNOI_LONG_PACK | SSQR_INC | 0,
SSQR_LEN(0) | SSQR_TIME(2) | SSQR_IVOL(12) | SNOI_LONG_PACK | SSQR_INC | 0,
};

const uint8_t * const InstitutionalisedDMAInstruments[] = {
zetakick_raw,
zetasnare_raw,
blank_raw,
blank_raw,
blank_raw,
blank_raw,
blank_raw,
};

const uint16_t InstitutionalisedDMADurations[] = {
5,
9,
0,
0,
0,
0,
0,
};

const advikSongStruct InstitutionalisedSongStruct = {
InstitutionalisedSong,
InstitutionalisedSongHeader,
InstitutionalisedSquareInstruments,
InstitutionalisedWaveInstruments,
InstitutionalisedWaveforms,
InstitutionalisedNoiseInstruments,
InstitutionalisedDMAInstruments,
InstitutionalisedDMADurations
};