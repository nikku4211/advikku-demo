#include <stdint.h>
#include "advikku_global.h"
#include "advikku_update.h"

// --------------------------------------------------------------------
// GLOBAL PLAYER VARIABLES
// --------------------------------------------------------------------

// Advikku variables
uint16_t advik_start = 0;
uint16_t advik_loop_point = 1;
uint16_t advik_ticks_per_row_counter = 6;
uint16_t advik_ticks_per_row_value = 6;
uint16_t advik_current = 0;

uint16_t advik_arp_tick = 0;
uint16_t advik_arp_index = 0;

// --------------------------------------------------------------------
// CHANNEL PLAYER VARIABLES
// --------------------------------------------------------------------

uint16_t advik_ch1_arp_enabled = 0;

uint16_t advik_ch1_portamento_direction = 0;
uint16_t advik_ch1_portamento_freq = 0;
uint16_t advik_ch1_portamento_freq_goal = 0;
uint16_t advik_ch1_previous_freq = 0;

uint16_t advik_ch1_held_note = 0;

uint16_t advik_ch1_vib_position = 0;
uint16_t advik_ch1_vib_ticks_counter = 0;
uint16_t advik_ch1_vib_enabled = 0;

uint16_t advik_ch1_delay_ticks_counter = 0;
uint16_t advik_ch1_delay_enabled = 0;
uint16_t advik_ch1_cut_delay_enabled = 0;

uint16_t advik_ch2_arp_enabled = 0;

uint16_t advik_ch2_portamento_direction = 0;
uint16_t advik_ch2_portamento_freq = 0;
uint16_t advik_ch2_portamento_freq_goal = 0;
uint16_t advik_ch2_previous_freq = 0;

uint16_t advik_ch2_held_note = 0;

uint16_t advik_ch2_vib_position = 0;
uint16_t advik_ch2_vib_ticks_counter = 0;
uint16_t advik_ch2_vib_enabled = 0;

uint16_t advik_ch2_delay_ticks_counter = 0;
uint16_t advik_ch2_delay_enabled = 0;
uint16_t advik_ch2_cut_delay_enabled = 0;

uint16_t advik_ch3_arp_enabled = 0;

uint16_t advik_ch3_portamento_direction = 0;
uint16_t advik_ch3_portamento_freq = 0;
uint16_t advik_ch3_portamento_freq_goal = 0;
uint16_t advik_ch3_previous_freq = 0;

uint16_t advik_ch3_held_note = 0;

uint16_t advik_ch3_vib_position = 0;
uint16_t advik_ch3_vib_ticks_counter = 0;
uint16_t advik_ch3_vib_enabled = 0;

uint16_t advik_ch3_delay_ticks_counter = 0;
uint16_t advik_ch3_delay_enabled = 0;
uint16_t advik_ch3_cut_delay_enabled = 0;

uint16_t advik_ch4_delay_ticks_counter = 0;
uint16_t advik_ch4_delay_enabled = 0;
uint16_t advik_ch4_cut_delay_enabled = 0;

const uint8_t * const * advik_global_current_order;
const uint16_t * advik_current_square_instruments;
const uint16_t * advik_current_wave_instruments;
const uint16_t * advik_current_noise_instruments;
const uint16_t * advik_current_dma_instruments;

const uint8_t * advik_ch1_current_order;
const uint8_t * advik_ch2_current_order;
const uint8_t * advik_ch3_current_order;
const uint8_t * advik_ch4_current_order;
const uint8_t * advik_ch5_current_order;
const uint8_t * advik_ch6_current_order;

// --------------------------------------------------------------------
// TONE GENERATOR
// --------------------------------------------------------------------

// --------------------------------------------------------------------
// CONSTANTS
// --------------------------------------------------------------------

const uint16_t snd_freqs[]=
{
	44,  156,  262,  363,  457,  547,  631,  710,  786,  854,  923,  986,
	1046, 1102, 1155, 1205, 1253, 1297, 1339, 1379, 1417, 1452, 1486, 1517,
	1546, 1575, 1602, 1627, 1650, 1673, 1694, 1714, 1732, 1750, 1767, 1783,
	1798, 1812, 1825, 1837, 1849, 1860, 1871, 1881, 1890, 1899, 1907, 1915,
	1923, 1930, 1936, 1943, 1949, 1954, 1959, 1964, 1969, 1974, 1978, 1982,
	1985, 1988, 1992, 1995, 1998, 2001, 2004, 2006, 2009, 2011, 2013, 2015
};

const int16_t vib_table[]=
{
	     0,   24,   49,   74,   97,  120,  141,  161,
     180,  197,  212,  224,  235,  244,  250,  253,
     255,  253,  250,  244,  235,  224,  212,  197,
     180,  161,  141,  120,   97,   74,   49,   24,
       0,  -24,  -49,  -74,  -97, -120, -141, -161,
    -180, -197, -212, -224, -235, -244, -250, -253,
    -255, -253, -250, -244, -235, -224, -212, -197,
    -180, -161, -141, -120,  -97,  -74,  -49,  -24,
};
// --------------------------------------------------------------------
// MACROS
// --------------------------------------------------------------------