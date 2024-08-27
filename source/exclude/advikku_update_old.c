#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tonc.h>

#include "advikku_global.h"
#include "advikku_update.h"

static inline void cell_sfx_ch1_play(){
	if (advik_ch_sfx_ticks_per_row_counter[0] > 0) {
		advik_ch_sfx_ticks_per_row_counter[0]--;
		if (advik_sfx_ch1_delay_enabled > 0) {
			if (advik_sfx_ch1_delay_ticks_counter > 0) {
				advik_sfx_ch1_delay_ticks_counter--;
			} else {
				if (advik_ch_sfx_order[0][advik_ch_sfx_current[0]-3] > 0x00){
					REG_SND1CNT = advik_sfx_current_square_instruments[0][advik_ch_sfx_order[0][advik_ch_sfx_current[0]-3] - 1];
				}
				if ((advik_sfx_current_square_instruments[0][advik_ch_sfx_order[0][advik_ch_sfx_current[0]-3] - 1] & SSQR_LEN_MASK) < 63)
					REG_SND1FREQ = SFREQ_RESET | snd_freqs[advik_ch_sfx_order[0][advik_ch_sfx_current[0]-4]] | SFREQ_TIMED;
				else
					REG_SND1FREQ = SFREQ_RESET | snd_freqs[advik_ch_sfx_order[0][advik_ch_sfx_current[0]-4]];
				advik_sfx_ch1_delay_enabled = 0;
			}
		} else if (advik_sfx_ch1_portamento_direction == 1) {
			advik_sfx_ch1_portamento_freq += advik_ch_sfx_order[0][advik_ch_sfx_current[0]-1];
			REG_SND1FREQ = advik_sfx_ch1_portamento_freq;
			advik_sfx_ch1_previous_freq = advik_sfx_ch1_portamento_freq;
		} else if (advik_sfx_ch1_portamento_direction == 2) {
			advik_sfx_ch1_portamento_freq -= advik_ch_sfx_order[0][advik_ch_sfx_current[0]-1];
			REG_SND1FREQ = advik_sfx_ch1_portamento_freq;
			advik_sfx_ch1_previous_freq = advik_sfx_ch1_portamento_freq;
		} else if (advik_sfx_ch1_portamento_direction == 3) {
			if (advik_sfx_ch1_portamento_freq > advik_sfx_ch1_portamento_freq_goal){
				advik_sfx_ch1_portamento_freq -= advik_ch_sfx_order[0][advik_ch_sfx_current[0]-1];
			} else if (advik_sfx_ch1_portamento_freq < advik_sfx_ch1_portamento_freq_goal){
				advik_sfx_ch1_portamento_freq += advik_ch_sfx_order[0][advik_ch_sfx_current[0]-1];
			}
			REG_SND1FREQ = advik_sfx_ch1_portamento_freq;
			advik_sfx_ch1_previous_freq = advik_sfx_ch1_portamento_freq;
		} else if (advik_sfx_ch1_cut_delay_enabled > 1) {
			if (advik_sfx_ch1_delay_ticks_counter > 0) {
				advik_sfx_ch1_delay_ticks_counter--;
			} else {
				REG_SND1CNT = 0;
				advik_sfx_ch1_cut_delay_enabled = 0;
			}
		} else if (advik_sfx_ch1_arp_enabled > 0) {
			switch (advik_arp_index) {
				case 1:
					REG_SND1FREQ = (snd_freqs[advik_ch_sfx_order[0][advik_ch_sfx_current[0]-4] + (advik_ch_sfx_order[0][advik_ch_sfx_current[0]-1] >> 4)]);
					break;
				case 2:
					REG_SND1FREQ = (snd_freqs[advik_ch_sfx_order[0][advik_ch_sfx_current[0]-4] + (advik_ch_sfx_order[0][advik_ch_sfx_current[0]-1] & 0x0f)]);
					break;
				default:
					REG_SND1FREQ = (snd_freqs[advik_ch_sfx_order[0][advik_ch_sfx_current[0]-4]]);
			}
		} else if (advik_sfx_ch1_vib_enabled > 0) {
			advik_sfx_ch1_vib_ticks_counter += advik_ch_sfx_order[0][advik_ch_sfx_current[0]-1] >> 4;
			advik_sfx_ch1_vib_position = advik_sfx_ch1_vib_ticks_counter & 63;
			if (advik_ch_sfx_order[0][advik_ch_sfx_current[0]-4] < 0xf0)
				REG_SND1FREQ = (snd_freqs[advik_ch_sfx_order[0][advik_ch_sfx_current[0]-4]] - ((vib_table[advik_sfx_ch1_vib_position] * (advik_sfx_ch1_vib_depth)) >> 5));
			else
				REG_SND1FREQ = (advik_sfx_ch1_held_note - ((vib_table[advik_sfx_ch1_vib_position] * (advik_sfx_ch1_vib_depth)) >> 5));
		}
	} else {
		if (!advik_ch_sfx_command_linger[0]){
			advik_sfx_ch1_arp_enabled = 0;
			advik_sfx_ch1_portamento_direction = 0;
			advik_sfx_ch1_vib_enabled = 0;
			advik_sfx_ch1_vib_ticks_counter = 0;
			//restore notes after vibrato end
			if (advik_sfx_ch1_held_note > 0) {
				REG_SND1FREQ = advik_sfx_ch1_held_note;
				advik_sfx_ch1_held_note = 0;
			}
		}
		switch (advik_ch_sfx_order[0][advik_ch_sfx_current[0]+2]) {
			//if arpeggio
			case 0x00:
				if (advik_ch_sfx_order[0][advik_ch_sfx_current[0]+3] > 0) {
					advik_sfx_ch1_arp_enabled = 1;
				} else if (advik_ch_sfx_order[0][advik_ch_sfx_current[0]+3] == 0 && advik_ch_sfx_command_linger[0]) {
					advik_sfx_ch1_arp_enabled = 0;
				}
				break;
			//if portamento up
			case 0x01:
				if (advik_ch_sfx_order[0][advik_ch_sfx_current[0]+3] > 0) {
					advik_sfx_ch1_portamento_direction = 1;
					if (advik_ch_sfx_order[0][advik_ch_sfx_current[0]] < 0xf0) {
						advik_sfx_ch1_portamento_freq = snd_freqs[advik_ch_sfx_order[0][advik_ch_sfx_current[0]]];
					} else if (advik_ch_sfx_order[0][advik_ch_sfx_current[0]] == 0xfe) {
						advik_sfx_ch1_portamento_freq = advik_sfx_ch1_previous_freq;
					}
				} else if (advik_ch_sfx_order[0][advik_ch_sfx_current[0]+3] == 0 && advik_ch_sfx_command_linger[0]) {
					advik_sfx_ch1_portamento_direction = 0;
				}
				break;
			//if portamento down
			case 0x02:
				if (advik_ch_sfx_order[0][advik_ch_sfx_current[0]+3] > 0) {
					advik_sfx_ch1_portamento_direction = 2;
					if (advik_ch_sfx_order[0][advik_ch_sfx_current[0]] < 0xf0) {
						advik_sfx_ch1_portamento_freq = snd_freqs[advik_ch_sfx_order[0][advik_ch_sfx_current[0]]];
					} else if (advik_ch_sfx_order[0][advik_ch_sfx_current[0]] == 0xfe) {
						advik_sfx_ch1_portamento_freq = advik_sfx_ch1_previous_freq;
					}
				} else if (advik_ch_sfx_order[0][advik_ch_sfx_current[0]+3] == 0 && advik_ch_sfx_command_linger[0]) {
					advik_sfx_ch1_portamento_direction = 0;
				}
				break;
			//if tone portamento
			case 0x03:
				if (advik_ch_sfx_order[0][advik_ch_sfx_current[0]+3] > 0) {
					advik_sfx_ch1_portamento_direction = 3;
					advik_sfx_ch1_portamento_freq = advik_sfx_ch1_previous_freq;
					if (advik_ch_sfx_order[0][advik_ch_sfx_current[0]] < 0xf0) {
						advik_sfx_ch1_portamento_freq_goal = snd_freqs[advik_ch_sfx_order[0][advik_ch_sfx_current[0]]];
					}
				} else if (advik_ch_sfx_order[0][advik_ch_sfx_current[0]+3] == 0 && advik_ch_sfx_command_linger[0]) {
					advik_sfx_ch1_portamento_direction = 0;
				}
				break;
			//if vibrato
			case 0x04:
				advik_sfx_ch1_vib_depth = advik_ch_sfx_order[0][advik_ch_sfx_current[0]+3] & 0x0f;
				advik_sfx_ch1_vib_enabled = 1;
				if (advik_ch_sfx_order[0][advik_ch_sfx_current[0]+3] == 0 && advik_ch_sfx_command_linger[0]) {
					advik_sfx_ch1_vib_enabled = 0;
					if (advik_sfx_ch1_held_note > 0) {
						REG_SND1FREQ = advik_sfx_ch1_held_note;
						advik_sfx_ch1_held_note = 0;
					}
				}
				break;
			//if set master volume
			case 0x05:
				REG_SNDDMGCNT = (REG_SNDDMGCNT & 0xff00) | advik_ch_sfx_order[0][advik_ch_sfx_current[0]+3];
				break;
			//if note delay
			case 0x07:
				advik_sfx_ch1_delay_enabled = 1;
				advik_sfx_ch1_delay_ticks_counter = advik_ch_sfx_order[0][advik_ch_sfx_current[0]+3] - 1;
				break;
			//if set global panning
			case 0x08:
				REG_SNDDMGCNT = (REG_SNDDMGCNT & 0x00ff) | (advik_ch_sfx_order[0][advik_ch_sfx_current[0]+3] << 8);
				break;
			//if change timbre
			case 0x09:
				REG_SND1CNT = (advik_sfx_current_square_instruments[0][advik_ch_sfx_order[0][advik_ch_sfx_current[0]+1]] & 0xff00) | advik_ch_sfx_order[0][advik_ch_sfx_current[0]+3];
				break;
			//if set volume
			case 0x0c:
				REG_SND1CNT = (advik_sfx_current_square_instruments[0][advik_ch_sfx_order[0][advik_ch_sfx_current[0]+1]] & 0x00ff) | (advik_ch_sfx_order[0][advik_ch_sfx_current[0]+3] << 8);
				break;
			//if pattern break
			case 0x0d:
				advik_ch_sfx_override[0] = 0;
				break;
			//if note cut
			case 0x0e:
				advik_sfx_ch1_cut_delay_enabled = 1;
				advik_sfx_ch1_delay_ticks_counter = advik_ch_sfx_order[0][advik_ch_sfx_current[0]+3] - 1;
				break;
			//if set tempo
			case 0x0f:
				advik_ch_sfx_ticks_per_row_value[0] = advik_ch_sfx_order[0][advik_ch_sfx_current[0]+3] - 1;
				break;
			//if set furnace panning
			case 0x80:
				REG_SNDDMGCNT = (REG_SNDDMGCNT & 0xeeff) | ((advik_ch_sfx_order[0][advik_ch_sfx_current[0]+3] & 0x01) << 8) | ((advik_ch_sfx_order[0][advik_ch_sfx_current[0]+3] & 0x10) << 12);
		}
		
		if (advik_ch_sfx_order[0][advik_ch_sfx_current[0]] < 0xf0 && !advik_sfx_ch1_delay_enabled) {
			//if instrument isn't 0, retrigger note
			if (advik_ch_sfx_order[0][advik_ch_sfx_current[0]+1] > 0x00){
				REG_SND1CNT = advik_sfx_current_square_instruments[0][advik_ch_sfx_order[0][advik_ch_sfx_current[0]+1] - 1];
			}
			advik_sfx_ch1_held_note = 0;
			if ((advik_sfx_current_square_instruments[0][advik_ch_sfx_order[0][advik_ch_sfx_current[0]+1] - 1] & SSQR_LEN_MASK))
				REG_SND1FREQ = SFREQ_RESET | snd_freqs[advik_ch_sfx_order[0][advik_ch_sfx_current[0]]] | SFREQ_TIMED;
			else
				REG_SND1FREQ = SFREQ_RESET | snd_freqs[advik_ch_sfx_order[0][advik_ch_sfx_current[0]]];
			advik_sfx_ch1_previous_freq = snd_freqs[advik_ch_sfx_order[0][advik_ch_sfx_current[0]]];
		} else if (advik_ch_sfx_order[0][advik_ch_sfx_current[0]] == 0xfe) {
			//make sure held note is saved
			if (advik_sfx_ch1_held_note == 0) {
				advik_sfx_ch1_held_note = advik_sfx_ch1_previous_freq;
			}
		}
		advik_ch_sfx_current[0] += 4;
		advik_ch_sfx_ticks_per_row_counter[0] = advik_ch_sfx_ticks_per_row_value[0];
		
		//if end of order is reached, don't loop
		if (advik_ch_sfx_order[0][advik_ch_sfx_current[0]] == 0xff) {
			advik_ch_sfx_override[0] = 0;
			advik_sfx_ch1_held_note = 0;
		}
	}
}
static inline void cell_sfx_ch2_play(){
	if (advik_ch_sfx_ticks_per_row_counter[1] > 0) {
		advik_ch_sfx_ticks_per_row_counter[1]--;
		if (advik_sfx_ch2_delay_enabled > 0) {
			if (advik_sfx_ch2_delay_ticks_counter > 0) {
				advik_sfx_ch2_delay_ticks_counter--;
			} else {
				if (advik_ch_sfx_order[1][advik_ch_sfx_current[1]-3] > 0x00){
					REG_SND2CNT = advik_sfx_current_square_instruments[1][advik_ch_sfx_order[1][advik_ch_sfx_current[1]-3] - 1];
				}
				if ((advik_sfx_current_square_instruments[1][advik_ch_sfx_order[1][advik_ch_sfx_current[1]-3] - 1] & SSQR_LEN_MASK) < 63)
					REG_SND2FREQ = SFREQ_RESET | snd_freqs[advik_ch_sfx_order[1][advik_ch_sfx_current[1]-4]] | SFREQ_TIMED;
				else
					REG_SND2FREQ = SFREQ_RESET | snd_freqs[advik_ch_sfx_order[1][advik_ch_sfx_current[1]-4]];
				advik_sfx_ch2_delay_enabled = 0;
			}
		} else if (advik_sfx_ch2_portamento_direction == 1) {
			advik_sfx_ch2_portamento_freq += advik_ch_sfx_order[1][advik_ch_sfx_current[1]-1];
			REG_SND2FREQ = advik_sfx_ch2_portamento_freq;
			advik_sfx_ch2_previous_freq = advik_sfx_ch2_portamento_freq;
		} else if (advik_sfx_ch2_portamento_direction == 2) {
			advik_sfx_ch2_portamento_freq -= advik_ch_sfx_order[1][advik_ch_sfx_current[1]-1];
			REG_SND2FREQ = advik_sfx_ch2_portamento_freq;
			advik_sfx_ch2_previous_freq = advik_sfx_ch2_portamento_freq;
		} else if (advik_sfx_ch2_portamento_direction == 3) {
			if (advik_sfx_ch2_portamento_freq > advik_sfx_ch2_portamento_freq_goal){
				advik_sfx_ch2_portamento_freq -= advik_ch_sfx_order[1][advik_ch_sfx_current[1]-1];
			} else if (advik_sfx_ch2_portamento_freq < advik_sfx_ch2_portamento_freq_goal){
				advik_sfx_ch2_portamento_freq += advik_ch_sfx_order[1][advik_ch_sfx_current[1]-1];
			}
			REG_SND2FREQ = advik_sfx_ch2_portamento_freq;
			advik_sfx_ch2_previous_freq = advik_sfx_ch2_portamento_freq;
		} else if (advik_sfx_ch2_cut_delay_enabled > 1) {
			if (advik_sfx_ch2_delay_ticks_counter > 0) {
				advik_sfx_ch2_delay_ticks_counter--;
			} else {
				REG_SND2CNT = 0;
				advik_sfx_ch2_cut_delay_enabled = 0;
			}
		} else if (advik_sfx_ch2_arp_enabled > 0) {
			switch (advik_arp_index) {
				case 1:
					REG_SND2FREQ = (snd_freqs[advik_ch_sfx_order[1][advik_ch_sfx_current[1]-4] + (advik_ch_sfx_order[1][advik_ch_sfx_current[1]-1] >> 4)]);
					break;
				case 2:
					REG_SND2FREQ = (snd_freqs[advik_ch_sfx_order[1][advik_ch_sfx_current[1]-4] + (advik_ch_sfx_order[1][advik_ch_sfx_current[1]-1] & 0x0f)]);
					break;
				default:
					REG_SND2FREQ = (snd_freqs[advik_ch_sfx_order[1][advik_ch_sfx_current[1]-4]]);
			}
		} else if (advik_sfx_ch2_vib_enabled > 0) {
			advik_sfx_ch2_vib_ticks_counter += advik_ch_sfx_order[1][advik_ch_sfx_current[1]-1] >> 4;
			advik_sfx_ch2_vib_position = advik_sfx_ch2_vib_ticks_counter & 63;
			if (advik_ch_sfx_order[1][advik_ch_sfx_current[1]-4] < 0xf0)
				REG_SND2FREQ = (snd_freqs[advik_ch_sfx_order[1][advik_ch_sfx_current[1]-4]] - ((vib_table[advik_sfx_ch2_vib_position] * (advik_sfx_ch2_vib_depth)) >> 5));
			else
				REG_SND2FREQ = (advik_sfx_ch2_held_note - ((vib_table[advik_sfx_ch2_vib_position] * (advik_sfx_ch2_vib_depth)) >> 5));
		}
	} else {
		if (!advik_ch_sfx_command_linger[1]){
			advik_sfx_ch2_arp_enabled = 0;
			advik_sfx_ch2_portamento_direction = 0;
			advik_sfx_ch2_vib_enabled = 0;
			advik_sfx_ch2_vib_ticks_counter = 0;
			//restore notes after vibrato end
			if (advik_sfx_ch2_held_note > 0) {
				REG_SND2FREQ = advik_sfx_ch2_held_note;
				advik_sfx_ch2_held_note = 0;
			}
		}
		switch (advik_ch_sfx_order[1][advik_ch_sfx_current[1]+2]) {
			//if arpeggio
			case 0x00:
				if (advik_ch_sfx_order[1][advik_ch_sfx_current[1]+3] > 0) {
					advik_sfx_ch2_arp_enabled = 1;
				} else if (advik_ch_sfx_order[1][advik_ch_sfx_current[1]+3] == 0 && advik_ch_sfx_command_linger[1]) {
					advik_sfx_ch2_arp_enabled = 0;
				}
				break;
			//if portamento up
			case 0x01:
				if (advik_ch_sfx_order[1][advik_ch_sfx_current[1]+3] > 0) {
					advik_sfx_ch2_portamento_direction = 1;
					if (advik_ch_sfx_order[1][advik_ch_sfx_current[1]] < 0xf0) {
						advik_sfx_ch2_portamento_freq = snd_freqs[advik_ch_sfx_order[1][advik_ch_sfx_current[1]]];
					} else if (advik_ch_sfx_order[1][advik_ch_sfx_current[1]] == 0xfe) {
						advik_sfx_ch2_portamento_freq = advik_sfx_ch2_previous_freq;
					}
				} else if (advik_ch_sfx_order[1][advik_ch_sfx_current[1]+3] == 0 && advik_ch_sfx_command_linger[1]) {
					advik_sfx_ch2_portamento_direction = 0;
				}
				break;
			//if portamento down
			case 0x02:
				if (advik_ch_sfx_order[1][advik_ch_sfx_current[1]+3] > 0) {
					advik_sfx_ch2_portamento_direction = 2;
					if (advik_ch_sfx_order[1][advik_ch_sfx_current[1]] < 0xf0) {
						advik_sfx_ch2_portamento_freq = snd_freqs[advik_ch_sfx_order[1][advik_ch_sfx_current[1]]];
					} else if (advik_ch_sfx_order[1][advik_ch_sfx_current[1]] == 0xfe) {
						advik_sfx_ch2_portamento_freq = advik_sfx_ch2_previous_freq;
					}
				} else if (advik_ch_sfx_order[1][advik_ch_sfx_current[1]+3] == 0 && advik_ch_sfx_command_linger[1]) {
					advik_sfx_ch2_portamento_direction = 0;
				}
				break;
			//if tone portamento
			case 0x03:
				if (advik_ch_sfx_order[1][advik_ch_sfx_current[1]+3] > 0) {
					advik_sfx_ch2_portamento_direction = 3;
					advik_sfx_ch2_portamento_freq = advik_sfx_ch2_previous_freq;
					if (advik_ch_sfx_order[1][advik_ch_sfx_current[1]] < 0xf0) {
						advik_sfx_ch2_portamento_freq_goal = snd_freqs[advik_ch_sfx_order[1][advik_ch_sfx_current[1]]];
					}
				} else if (advik_ch_sfx_order[1][advik_ch_sfx_current[1]+3] == 0 && advik_ch_sfx_command_linger[1]) {
					advik_sfx_ch2_portamento_direction = 0;
				}
				break;
			//if vibrato
			case 0x04:
				advik_sfx_ch2_vib_depth = advik_ch_sfx_order[1][advik_ch_sfx_current[1]+3] & 0x0f;
				advik_sfx_ch2_vib_enabled = 1;
				if (advik_ch_sfx_order[1][advik_ch_sfx_current[1]+3] == 0 && advik_ch_sfx_command_linger[1]) {
					advik_sfx_ch2_vib_enabled = 0;
					if (advik_sfx_ch2_held_note > 0) {
						REG_SND2FREQ = advik_sfx_ch2_held_note;
						advik_sfx_ch2_held_note = 0;
					}
				}
				break;
			//if set master volume
			case 0x05:
				REG_SNDDMGCNT = (REG_SNDDMGCNT & 0xff00) | advik_ch_sfx_order[1][advik_ch_sfx_current[1]+3];
				break;
			//if note delay
			case 0x07:
				advik_sfx_ch2_delay_enabled = 1;
				advik_sfx_ch2_delay_ticks_counter = advik_ch_sfx_order[1][advik_ch_sfx_current[1]+3] - 1;
				break;
			//if set global panning
			case 0x08:
				REG_SNDDMGCNT = (REG_SNDDMGCNT & 0x00ff) | (advik_ch_sfx_order[1][advik_ch_sfx_current[1]+3] << 8);
				break;
			//if change timbre
			case 0x09:
				REG_SND2CNT = (advik_sfx_current_square_instruments[1][advik_ch_sfx_order[1][advik_ch_sfx_current[1]+1]] & 0xff00) | advik_ch_sfx_order[1][advik_ch_sfx_current[1]+3];
				break;
			//if set volume
			case 0x0c:
				REG_SND2CNT = (advik_sfx_current_square_instruments[1][advik_ch_sfx_order[1][advik_ch_sfx_current[1]+1]] & 0x00ff) | (advik_ch_sfx_order[1][advik_ch_sfx_current[1]+3] << 8);
				break;
			//if pattern break
			case 0x0d:
				advik_ch_sfx_override[1] = 0;
				break;
			//if note cut
			case 0x0e:
				advik_sfx_ch2_cut_delay_enabled = 1;
				advik_sfx_ch2_delay_ticks_counter = advik_ch_sfx_order[1][advik_ch_sfx_current[1]+3] - 1;
				break;
			//if set tempo
			case 0x0f:
				advik_ch_sfx_ticks_per_row_value[1] = advik_ch_sfx_order[1][advik_ch_sfx_current[1]+3]-1;
				break;
			//if set furnace panning
			case 0x80:
				REG_SNDDMGCNT = (REG_SNDDMGCNT & 0xddff) | ((advik_ch_sfx_order[1][advik_ch_sfx_current[1]+3] & 0x01) << 9) | ((advik_ch_sfx_order[1][advik_ch_sfx_current[1]+3] & 0x10) << 13);
		}
		if (advik_ch_sfx_order[1][advik_ch_sfx_current[1]] < 0xf0 && !advik_sfx_ch2_delay_enabled) {
			//if instrument isn't 0, retrigger note
			if (advik_ch_sfx_order[1][advik_ch_sfx_current[1]+1] > 0x00){
				REG_SND2CNT = advik_sfx_current_square_instruments[1][advik_ch_sfx_order[1][advik_ch_sfx_current[1]+1] - 1];
			}
			advik_sfx_ch2_held_note = 0;
			if ((advik_sfx_current_square_instruments[1][advik_ch_sfx_order[1][advik_ch_sfx_current[1]+1] - 1] & SSQR_LEN_MASK))
				REG_SND2FREQ = SFREQ_RESET | snd_freqs[advik_ch_sfx_order[1][advik_ch_sfx_current[1]]] | SFREQ_TIMED;
			else
				REG_SND2FREQ = SFREQ_RESET | snd_freqs[advik_ch_sfx_order[1][advik_ch_sfx_current[1]]];
			advik_sfx_ch2_previous_freq = snd_freqs[advik_ch_sfx_order[1][advik_ch_sfx_current[1]]];
		} else if (advik_ch_sfx_order[1][advik_ch_sfx_current[1]] == 0xfe) {
			//make sure held note is saved
			if (advik_sfx_ch2_held_note == 0) {
				advik_sfx_ch2_held_note = advik_sfx_ch2_previous_freq;
			}
		}
		advik_ch_sfx_current[1] += 4;
		advik_ch_sfx_ticks_per_row_counter[1] = advik_ch_sfx_ticks_per_row_value[1];
		//if end of order is reached, don't loop
		if (advik_ch_sfx_order[1][advik_ch_sfx_current[1]] == 0xff) {
			advik_ch_sfx_override[1] = 0;
			advik_sfx_ch2_held_note = 0;
		}
	}
}
static inline void cell_sfx_ch3_play(){
	if (advik_ch_sfx_ticks_per_row_counter[2] > 0) {
		advik_ch_sfx_ticks_per_row_counter[2]--;
		if (advik_sfx_ch3_delay_enabled > 0) {
			if (advik_sfx_ch3_delay_ticks_counter > 0) {
				advik_sfx_ch3_delay_ticks_counter--;
			} else {
				if ((advik_sfx_current_wave_instruments[(advik_ch_sfx_order[2][advik_ch_sfx_current[2]-3] << 1)]) == SWAV_LEN_ON)
					REG_SND3FREQ = SFREQ_RESET | snd_freqs[advik_ch_sfx_order[2][advik_ch_sfx_current[2]-4]] | SFREQ_TIMED;
				else
					REG_SND3FREQ = SFREQ_RESET | snd_freqs[advik_ch_sfx_order[2][advik_ch_sfx_current[2]-4]];
				advik_sfx_ch3_delay_enabled = 0;
			}
		} else if (advik_sfx_ch3_portamento_direction == 1) {
			advik_sfx_ch3_portamento_freq += advik_ch_sfx_order[2][advik_ch_sfx_current[2]-1];
			REG_SND3FREQ = advik_sfx_ch3_portamento_freq;
			advik_sfx_ch3_previous_freq = advik_sfx_ch3_portamento_freq;
		} else if (advik_sfx_ch3_portamento_direction == 2) {
			advik_sfx_ch3_portamento_freq -= advik_ch_sfx_order[2][advik_ch_sfx_current[2]-1];
			REG_SND3FREQ = advik_sfx_ch3_portamento_freq;
			advik_sfx_ch3_previous_freq = advik_sfx_ch3_portamento_freq;
		} else if (advik_sfx_ch3_portamento_direction == 3) {
			if (advik_sfx_ch3_portamento_freq > advik_sfx_ch3_portamento_freq_goal){
				advik_sfx_ch3_portamento_freq -= advik_ch_sfx_order[2][advik_ch_sfx_current[2]-1];
			} else if (advik_sfx_ch3_portamento_freq < advik_sfx_ch3_portamento_freq_goal){
				advik_sfx_ch3_portamento_freq += advik_ch_sfx_order[2][advik_ch_sfx_current[2]-1];
			}
			REG_SND3FREQ = advik_sfx_ch3_portamento_freq;
			advik_sfx_ch3_previous_freq = advik_sfx_ch3_portamento_freq;
		} else if (advik_sfx_ch3_cut_delay_enabled > 1) {
			if (advik_sfx_ch3_delay_ticks_counter > 0) {
				advik_sfx_ch3_delay_ticks_counter--;
			} else {
				REG_SND3CNT = 0;
				advik_sfx_ch3_cut_delay_enabled = 0;
			}
		} else if (advik_sfx_ch3_arp_enabled > 0) {
			switch (advik_arp_index) {
				case 1:
					REG_SND3FREQ = (snd_freqs[advik_ch_sfx_order[2][advik_ch_sfx_current[2]-4] + (advik_ch_sfx_order[2][advik_ch_sfx_current[2]-1] >> 4)]);
					break;
				case 2:
					REG_SND3FREQ = (snd_freqs[advik_ch_sfx_order[2][advik_ch_sfx_current[2]-4] + (advik_ch_sfx_order[2][advik_ch_sfx_current[2]-1] & 0x0f)]);
					break;
				default:
					REG_SND3FREQ = (snd_freqs[advik_ch_sfx_order[2][advik_ch_sfx_current[2]-4]]);
			}
		} else if (advik_sfx_ch3_vib_enabled > 0) {
			advik_sfx_ch3_vib_ticks_counter += advik_ch_sfx_order[2][advik_ch_sfx_current[2]-1] >> 4;
			advik_sfx_ch3_vib_position = advik_sfx_ch3_vib_ticks_counter & 63;
			if (advik_ch_sfx_order[2][advik_ch_sfx_current[2]-4] < 0xf0)
				REG_SND3FREQ = (snd_freqs[advik_ch_sfx_order[2][advik_ch_sfx_current[2]-4]] - ((vib_table[advik_sfx_ch3_vib_position] * (advik_sfx_ch3_vib_depth)) >> 5));
			else
				REG_SND3FREQ = (advik_sfx_ch3_held_note - ((vib_table[advik_sfx_ch3_vib_position] * (advik_sfx_ch3_vib_depth)) >> 5));
		}
	} else {
		if (!advik_ch_sfx_command_linger[2]){
			advik_sfx_ch3_arp_enabled = 0;
			advik_sfx_ch3_portamento_direction = 0;
			advik_sfx_ch3_vib_enabled = 0;
			advik_sfx_ch3_vib_ticks_counter = 0;
			//restore notes after vibrato end
			if (advik_sfx_ch3_held_note > 0) {
				REG_SND3FREQ = advik_sfx_ch3_held_note;
				advik_sfx_ch3_held_note = 0;
			}
		}
		switch (advik_ch_sfx_order[2][advik_ch_sfx_current[2]+2]) {
			//if arpeggio
			case 0x00:
				if (advik_ch_sfx_order[2][advik_ch_sfx_current[2]+3] > 0) {
					advik_sfx_ch3_arp_enabled = 1;
				} else if (advik_ch_sfx_order[2][advik_ch_sfx_current[2]+3] == 0 && advik_ch_sfx_command_linger[2]) {
					advik_sfx_ch3_arp_enabled = 0;
				}
				break;
			//if portamento up
			case 0x01:
				if (advik_ch_sfx_order[2][advik_ch_sfx_current[2]+3] > 0) {
					advik_sfx_ch3_portamento_direction = 1;
					if (advik_ch_sfx_order[2][advik_ch_sfx_current[2]] < 0xf0) {
						advik_sfx_ch3_portamento_freq = snd_freqs[advik_ch_sfx_order[2][advik_ch_sfx_current[2]]];
					} else if (advik_ch_sfx_order[2][advik_ch_sfx_current[2]] == 0xfe) {
						advik_sfx_ch3_portamento_freq = advik_sfx_ch3_previous_freq;
					}
				} else if (advik_ch_sfx_order[2][advik_ch_sfx_current[2]+3] == 0 && advik_ch_sfx_command_linger[2]) {
					advik_sfx_ch3_portamento_direction = 0;
				}
				break;
			//if portamento down
			case 0x02:
				if (advik_ch_sfx_order[2][advik_ch_sfx_current[2]+3] > 0) {
					advik_sfx_ch3_portamento_direction = 2;
					if (advik_ch_sfx_order[2][advik_ch_sfx_current[2]] < 0xf0) {
						advik_sfx_ch3_portamento_freq = snd_freqs[advik_ch_sfx_order[2][advik_ch_sfx_current[2]]];
					} else if (advik_ch_sfx_order[2][advik_ch_sfx_current[2]] == 0xfe) {
						advik_sfx_ch3_portamento_freq = advik_sfx_ch3_previous_freq;
					}
				} else if (advik_ch_sfx_order[2][advik_ch_sfx_current[2]+3] == 0 && advik_ch_sfx_command_linger[2]) {
					advik_sfx_ch3_portamento_direction = 0;
				}
				break;
			//if tone portamento
			case 0x03:
				if (advik_ch_sfx_order[2][advik_ch_sfx_current[2]+3] > 0) {
					advik_sfx_ch3_portamento_direction = 3;
					advik_sfx_ch3_portamento_freq = advik_sfx_ch3_previous_freq;
					if (advik_ch_sfx_order[2][advik_ch_sfx_current[2]] < 0xf0) {
						advik_sfx_ch3_portamento_freq_goal = snd_freqs[advik_ch_sfx_order[2][advik_ch_sfx_current[2]]];
					}
				} else if (advik_ch_sfx_order[2][advik_ch_sfx_current[2]+3] == 0 && advik_ch_sfx_command_linger[2]) {
					advik_sfx_ch3_portamento_direction = 0;
				}
				break;
			//if vibrato
			case 0x04:
				advik_sfx_ch3_vib_depth = advik_ch_sfx_order[2][advik_ch_sfx_current[2]+3] & 0x0f;
				advik_sfx_ch3_vib_enabled = 1;
				if (advik_ch_sfx_order[2][advik_ch_sfx_current[2]+3] == 0 && advik_ch_sfx_command_linger[2]) {
					advik_sfx_ch3_vib_enabled = 0;
					if (advik_sfx_ch3_held_note > 0) {
						REG_SND3FREQ = advik_sfx_ch3_held_note;
						advik_sfx_ch3_held_note = 0;
					}
				}
				break;
			//if set master volume
			case 0x05:
				REG_SNDDMGCNT = (REG_SNDDMGCNT & 0xff00) | advik_ch_sfx_order[2][advik_ch_sfx_current[2]+3];
				break;
			//if note delay
			case 0x07:
				advik_sfx_ch3_delay_enabled = 1;
				advik_sfx_ch3_delay_ticks_counter = advik_ch_sfx_order[2][advik_ch_sfx_current[2]+3] - 1;
				break;
			//if set global panning
			case 0x08:
				REG_SNDDMGCNT = (REG_SNDDMGCNT & 0x00ff) | (advik_ch_sfx_order[2][advik_ch_sfx_current[2]+3] << 8);
				break;
			//if change timbre
			case 0x09:
				//copy channel 3 waveform over
				REG_SND3SEL = 0;
				memcpy((void *)REG_WAVE_RAM, advik_sfx_current_waveforms[advik_ch_sfx_order[2][advik_ch_sfx_current[2]+3] - 1], 16);
				REG_SND3SEL = 0xC0;
				break;
			//if set volume
			case 0x0c:
				REG_SND3CNT = (advik_ch_sfx_order[2][advik_ch_sfx_current[2]+3] << 8);
				break;
			//if pattern break
			case 0x0d:
				advik_ch_sfx_override[2] = 0;
				break;
			//if note cut
			case 0x0e:
				advik_sfx_ch3_cut_delay_enabled = 1;
				advik_sfx_ch3_delay_ticks_counter = advik_ch_sfx_order[2][advik_ch_sfx_current[2]+3] - 1;
				break;
			//if set tempo
			case 0x0f:
				advik_ch_sfx_ticks_per_row_value[2] = advik_ch_sfx_order[2][advik_ch_sfx_current[2]+3]-1;
				break;
			//if set furnace panning
			case 0x80:
				REG_SNDDMGCNT = (REG_SNDDMGCNT & 0xbbff) | ((advik_ch_sfx_order[2][advik_ch_sfx_current[2]+3] & 0x01) << 10) | ((advik_ch_sfx_order[2][advik_ch_sfx_current[2]+3] & 0x10) << 14);
		}
		if (advik_ch_sfx_order[2][advik_ch_sfx_current[2]] < 0xf0 && !advik_sfx_ch3_delay_enabled) {
			//if instrument isn't 0, retrigger note
			if (advik_ch_sfx_order[2][advik_ch_sfx_current[2]+1] > 0x00){
				REG_SND3CNT = 0x2000;
				//copy channel 3 waveform over
				REG_SND3SEL = 0;
				memcpy((void *)REG_WAVE_RAM, advik_sfx_current_waveforms[advik_ch_sfx_order[2][advik_ch_sfx_current[2]+1] - 1], 16);
				REG_SND3SEL = 0xC0;
			}
			advik_sfx_ch3_held_note = 0;
			if ((advik_sfx_current_wave_instruments[(advik_ch_sfx_order[2][advik_ch_sfx_current[2]+1] << 1)]) == SWAV_LEN_ON)
				REG_SND3FREQ = SFREQ_RESET | snd_freqs[advik_ch_sfx_order[2][advik_ch_sfx_current[2]]] | SFREQ_TIMED;
			else
				REG_SND3FREQ = SFREQ_RESET | snd_freqs[advik_ch_sfx_order[2][advik_ch_sfx_current[2]]];
			advik_sfx_ch3_previous_freq = snd_freqs[advik_ch_sfx_order[2][advik_ch_sfx_current[2]]];
		} else if (advik_ch_sfx_order[2][advik_ch_sfx_current[2]] == 0xfe) {
			//make sure held note is saved
			if (advik_sfx_ch3_held_note == 0) {
				advik_sfx_ch3_held_note = advik_sfx_ch3_previous_freq;
			}
		}
		advik_ch_sfx_current[2] += 4;
		advik_ch_sfx_ticks_per_row_counter[2] = advik_ch_sfx_ticks_per_row_value[2];
		//if end of order is reached, don't loop
		if (advik_ch_sfx_order[2][advik_ch_sfx_current[2]] == 0xff) {
			advik_ch_sfx_override[2] = 0;
			advik_sfx_ch3_held_note = 0;
		}
	}
}
static inline void cell_sfx_ch4_play(){
	if (advik_ch_sfx_ticks_per_row_counter[3] > 0) {
		advik_ch_sfx_ticks_per_row_counter[3]--;
		if (advik_sfx_ch4_delay_enabled > 0) {
			if (advik_sfx_ch4_delay_ticks_counter > 0) {
				advik_sfx_ch4_delay_ticks_counter--;
			} else {
				if (advik_ch_sfx_order[3][advik_ch_sfx_current[3]-3] > 0x00){
					REG_SND4CNT = advik_sfx_current_noise_instruments[advik_ch_sfx_order[3][advik_ch_sfx_current[3]-3] - 1] & SNOI_EXCLUDE_PACK;
				}
				if ((advik_sfx_current_noise_instruments[advik_ch_sfx_order[3][advik_ch_sfx_current[3]-3] - 1] & SSQR_LEN_MASK))
					REG_SND4FREQ = SFREQ_RESET | (SNOI_POLYNOM(advik_ch_sfx_order[3][advik_ch_sfx_current[3]-4]) & SNOI_EXCLUDE_UNPACK) | (SNOI_UNPACK(advik_sfx_current_noise_instruments[advik_ch_sfx_order[3][advik_ch_sfx_current[3]-4] - 1] & SNOI_SHORT_PACK)) | SFREQ_TIMED;
				else
					REG_SND4FREQ = SFREQ_RESET | (SNOI_POLYNOM(advik_ch_sfx_order[3][advik_ch_sfx_current[3]-4]) & SNOI_EXCLUDE_UNPACK) | (SNOI_UNPACK(advik_sfx_current_noise_instruments[advik_ch_sfx_order[3][advik_ch_sfx_current[3]-4] - 1] & SNOI_SHORT_PACK));
				advik_sfx_ch4_delay_enabled = 0;
			}
		} else if (advik_sfx_ch4_cut_delay_enabled > 1) {
			if (advik_sfx_ch4_delay_ticks_counter > 0) {
				advik_sfx_ch4_delay_ticks_counter--;
			} else {
				REG_SND4CNT = 0;
				advik_sfx_ch4_cut_delay_enabled = 0;
			}
		}
	} else {
		switch (advik_ch_sfx_order[3][advik_ch_sfx_current[3]+2]) {
			//if arpeggio
			// case 0x00:
				// if (advik_ch_sfx_order[3][advik_ch_sfx_current[3]+3] > 0) {
					// advik_sfx_ch4_arp_enabled = 1;
				// }
				// break;
			//if vibrato
			// case 0x04:
				// advik_sfx_ch4_vib_enabled = 1;
				// break;
			//if set master volume
			case 0x05:
				REG_SNDDMGCNT = (REG_SNDDMGCNT & 0xff00) | advik_ch_sfx_order[3][advik_ch_sfx_current[3]+3];
				break;
			//if note delay
			case 0x07:
				advik_sfx_ch4_delay_enabled = 1;
				advik_sfx_ch4_delay_ticks_counter = advik_ch_sfx_order[3][advik_ch_sfx_current[3]+3] - 1;
				break;
			//if set global panning
			case 0x08:
				REG_SNDDMGCNT = (REG_SNDDMGCNT & 0x00ff) | (advik_ch_sfx_order[3][advik_ch_sfx_current[3]+3] << 8);
				break;
			//if change timbre
			 // case 0x09:
				// REG_SND4CNT = (advik_sfx_current_noise_instruments[advik_ch_sfx_order[3][advik_ch_sfx_current[3]+1]] & 0xff00) | advik_ch_sfx_order[3][advik_ch_sfx_current[3]+3];
				// break;
			//if set volume
			case 0x0c:
				REG_SND4CNT = (advik_ch_sfx_order[3][advik_ch_sfx_current[3]+3] << 8);
				break;
			//if pattern break
			case 0x0d:
				advik_ch_sfx_override[3] = 0;
				break;
			//if note cut
			case 0x0e:
				advik_sfx_ch4_cut_delay_enabled = 1;
				advik_sfx_ch4_delay_ticks_counter = advik_ch_sfx_order[3][advik_ch_sfx_current[3]+3] - 1;
				break;
			//if set tempo
			case 0x0f:
				advik_ch_sfx_ticks_per_row_value[3] = advik_ch_sfx_order[3][advik_ch_sfx_current[3]+3]-1;
				break;
			//if set furnace panning
			case 0x80:
				REG_SNDDMGCNT = (REG_SNDDMGCNT & 0x77ff) | ((advik_ch_sfx_order[3][advik_ch_sfx_current[3]+3] & 0x01) << 11) | ((advik_ch_sfx_order[3][advik_ch_sfx_current[3]+3] & 0x10) << 15);
		}
		if (advik_ch_sfx_order[3][advik_ch_sfx_current[3]] < 0xf8 && !advik_sfx_ch4_delay_enabled) {
			//if instrument isn't 0, retrigger note
			if (advik_ch_sfx_order[3][advik_ch_sfx_current[3]+1] > 0x00){
				REG_SND4CNT = advik_sfx_current_noise_instruments[advik_ch_sfx_order[3][advik_ch_sfx_current[3]+1] - 1] & SNOI_EXCLUDE_PACK;
			}
			if ((advik_sfx_current_noise_instruments[advik_ch_sfx_order[3][advik_ch_sfx_current[3]+1] - 1] & SSQR_LEN_MASK))
				//Thanks to RichardULZ for this formula
				REG_SND4FREQ = SFREQ_RESET | (SNOI_POLYNOM(advik_ch_sfx_order[3][advik_ch_sfx_current[3]]) & SNOI_EXCLUDE_UNPACK) | (SNOI_UNPACK(advik_sfx_current_noise_instruments[advik_ch_sfx_order[3][advik_ch_sfx_current[3]] - 1] & SNOI_SHORT_PACK)) | SFREQ_TIMED;
			else
				REG_SND4FREQ = SFREQ_RESET | (SNOI_POLYNOM(advik_ch_sfx_order[3][advik_ch_sfx_current[3]]) & SNOI_EXCLUDE_UNPACK) | (SNOI_UNPACK(advik_sfx_current_noise_instruments[advik_ch_sfx_order[3][advik_ch_sfx_current[3]] - 1] & SNOI_SHORT_PACK));
		}
		advik_ch_sfx_current[3] += 4;
		advik_ch_sfx_ticks_per_row_counter[3] = advik_ch_sfx_ticks_per_row_value[3];
		//if end of order is reached, don't loop
		if (advik_ch_sfx_order[3][advik_ch_sfx_current[3]] == 0xff) {
			advik_ch_sfx_override[3] = 0;
		}
	}
}
static inline void cell_sfx_ch5_play(){
	if (advik_ch_sfx_ticks_per_row_counter[4] > 0) {
		advik_ch_sfx_ticks_per_row_counter[4]--;
		if (advik_sfx_ch5_delay_enabled > 0) {
			if (advik_sfx_ch5_delay_ticks_counter > 0) {
				advik_sfx_ch5_delay_ticks_counter--;
			} else {
				REG_DMA1CNT = 0;
			
				//set timer 0
				REG_TM0D = dma_snd_freqs[advik_ch_sfx_order[4][advik_ch_sfx_current[4]-4]];
				REG_TM0CNT = TM_ENABLE;
				
				//set DMA transfer to DAC 1 FIFO
				REG_DMA1SAD = (uint32_t)advik_sfx_current_dma_instruments[0][advik_ch_sfx_order[4][advik_ch_sfx_current[4]-3] - 1];
				REG_DMA1DAD = (uint32_t)&REG_FIFO_A;
				REG_DMA1CNT = DMA_DST_FIXED | DMA_REPEAT | DMA_32 | DMA_AT_REFRESH | DMA_ENABLE;
				
				advik_ch_sfx_sample_duration[0] = advik_sfx_current_dma_durations[0][advik_ch_sfx_order[4][advik_ch_sfx_current[4]-3] - 1];
				advik_sfx_ch5_delay_enabled = 0;
			}
		} else if (advik_sfx_ch5_portamento_direction == 1) {
			advik_sfx_ch5_portamento_freq += advik_ch_sfx_order[4][advik_ch_sfx_current[4]-1];
			//set timer 0
			REG_TM0D = advik_sfx_ch5_portamento_freq;
			advik_sfx_ch5_previous_freq = advik_sfx_ch5_portamento_freq;
		} else if (advik_sfx_ch5_portamento_direction == 2) {
			advik_sfx_ch5_portamento_freq -= advik_ch_sfx_order[4][advik_ch_sfx_current[4]-1];
			//set timer 0
			REG_TM0D = advik_sfx_ch5_portamento_freq;
			advik_sfx_ch5_previous_freq = advik_sfx_ch5_portamento_freq;
		} else if (advik_sfx_ch5_portamento_direction == 3) {
			if (advik_sfx_ch5_portamento_freq > advik_sfx_ch5_portamento_freq_goal){
				advik_sfx_ch5_portamento_freq -= advik_ch_sfx_order[4][advik_ch_sfx_current[4]-1];
			} else if (advik_sfx_ch5_portamento_freq < advik_sfx_ch5_portamento_freq_goal){
				advik_sfx_ch5_portamento_freq += advik_ch_sfx_order[4][advik_ch_sfx_current[4]-1];
			}
			//set timer 0
			REG_TM0D = advik_sfx_ch5_portamento_freq;
			advik_sfx_ch5_previous_freq = advik_sfx_ch5_portamento_freq;
		} else if (advik_sfx_ch5_cut_delay_enabled > 1) {
			if (advik_sfx_ch5_delay_ticks_counter > 0) {
				advik_sfx_ch5_delay_ticks_counter--;
			} else {
				REG_DMA1CNT = 0;
				advik_sfx_ch5_cut_delay_enabled = 0;
			}
		} else if (advik_sfx_ch5_arp_enabled > 0) {
			switch (advik_arp_index) {
				case 1:
					REG_TM0D = (dma_snd_freqs[advik_ch_sfx_order[4][advik_ch_sfx_current[4]-4] + (advik_ch_sfx_order[4][advik_ch_sfx_current[4]-1] >> 4)]);
					break;
				case 2:
					REG_TM0D = (dma_snd_freqs[advik_ch_sfx_order[4][advik_ch_sfx_current[4]-4] + (advik_ch_sfx_order[4][advik_ch_sfx_current[4]-1] & 0x0f)]);
					break;
				default:
					REG_TM0D = (dma_snd_freqs[advik_ch_sfx_order[4][advik_ch_sfx_current[4]-4]]);
			}
		} else if (advik_sfx_ch5_vib_enabled > 0) {
			advik_sfx_ch5_vib_ticks_counter += advik_ch_sfx_order[4][advik_ch_sfx_current[4]-1] >> 4;
			advik_sfx_ch5_vib_position = advik_sfx_ch5_vib_ticks_counter & 63;
			if (advik_ch_sfx_order[4][advik_ch_sfx_current[4]-4] < 0xf0)
				REG_TM0D = (dma_snd_freqs[advik_ch_sfx_order[4][advik_ch_sfx_current[4]-4]] - ((vib_table[advik_sfx_ch5_vib_position] * (advik_sfx_ch5_vib_depth)) >> 5));
			else
				REG_TM0D = (advik_sfx_ch5_held_note - ((vib_table[advik_sfx_ch5_vib_position] * (advik_sfx_ch5_vib_depth)) >> 5));
		}
		if (advik_ch_sfx_sample_duration[0]){
			advik_ch_sfx_sample_duration[0]--;
		} else {
			REG_DMA1CNT = 0;
		}
	} else {
		if (!advik_ch_sfx_command_linger[4]){
			advik_sfx_ch5_arp_enabled = 0;
			advik_sfx_ch5_portamento_direction = 0;
			advik_sfx_ch5_vib_enabled = 0;
			advik_sfx_ch5_vib_ticks_counter = 0;
			//restore notes after vibrato end
			if (advik_sfx_ch5_held_note > 0) {
				REG_TM0D = advik_sfx_ch5_held_note;
				advik_sfx_ch5_held_note = 0;
			}
		}
		switch (advik_ch_sfx_order[4][advik_ch_sfx_current[4]+2]) {
			//if arpeggio
			case 0x00:
				if (advik_ch_sfx_order[4][advik_ch_sfx_current[4]+3] > 0) {
					advik_sfx_ch5_arp_enabled = 1;
				} else if (advik_ch_sfx_order[4][advik_ch_sfx_current[4]+3] == 0 && advik_ch_sfx_command_linger[4]) {
					advik_sfx_ch5_arp_enabled = 0;
				}
				break;
			//if portamento up
			case 0x01:
				if (advik_ch_sfx_order[4][advik_ch_sfx_current[4]+3] > 0) {
					advik_sfx_ch5_portamento_direction = 1;
					if (advik_ch_sfx_order[4][advik_ch_sfx_current[4]] < 0xf0) {
						advik_sfx_ch5_portamento_freq = dma_snd_freqs[advik_ch_sfx_order[4][advik_ch_sfx_current[4]]];
					} else if (advik_ch_sfx_order[4][advik_ch_sfx_current[4]] == 0xfe) {
						advik_sfx_ch5_portamento_freq = advik_sfx_ch5_previous_freq;
					}
				} else if (advik_ch_sfx_order[4][advik_ch_sfx_current[4]+3] == 0 && advik_ch_sfx_command_linger[4]) {
					advik_sfx_ch5_portamento_direction = 0;
				}
				break;
			//if portamento down
			case 0x02:
				if (advik_ch_sfx_order[4][advik_ch_sfx_current[4]+3] > 0) {
					advik_sfx_ch5_portamento_direction = 2;
					if (advik_ch_sfx_order[4][advik_ch_sfx_current[4]] < 0xf0) {
						advik_sfx_ch5_portamento_freq = dma_snd_freqs[advik_ch_sfx_order[4][advik_ch_sfx_current[4]]];
					} else if (advik_ch_sfx_order[4][advik_ch_sfx_current[4]] == 0xfe) {
						advik_sfx_ch5_portamento_freq = advik_sfx_ch5_previous_freq;
					}
				} else if (advik_ch_sfx_order[4][advik_ch_sfx_current[4]+3] == 0 && advik_ch_sfx_command_linger[4]) {
					advik_sfx_ch5_portamento_direction = 0;
				}
				break;
			//if tone portamento
			case 0x03:
				if (advik_ch_sfx_order[4][advik_ch_sfx_current[4]+3] > 0) {
					advik_sfx_ch5_portamento_direction = 3;
					advik_sfx_ch5_portamento_freq = advik_sfx_ch5_previous_freq;
					if (advik_ch_sfx_order[4][advik_ch_sfx_current[4]] < 0xf0) {
						advik_sfx_ch5_portamento_freq_goal = dma_snd_freqs[advik_ch_sfx_order[4][advik_ch_sfx_current[4]]];
					}
				} else if (advik_ch_sfx_order[4][advik_ch_sfx_current[4]+3] == 0 && advik_ch_sfx_command_linger[4]) {
					advik_sfx_ch5_portamento_direction = 0;
				}
				break;
			//if vibrato
			case 0x04:
				advik_sfx_ch5_vib_depth = advik_ch_sfx_order[4][advik_ch_sfx_current[4]+3] & 0x0f;
				advik_sfx_ch5_vib_enabled = 1;
				if (advik_ch_sfx_order[4][advik_ch_sfx_current[4]+3] == 0 && advik_ch_sfx_command_linger[4]) {
					advik_sfx_ch5_vib_enabled = 0;
					if (advik_sfx_ch5_held_note > 0) {
						REG_TM0D = advik_sfx_ch5_held_note;
						advik_sfx_ch5_held_note = 0;
					}
				}
				break;
			//if set master volume
			case 0x05:
				REG_SNDDSCNT = (REG_SNDDSCNT & 0xfff3) | advik_ch_sfx_order[4][advik_ch_sfx_current[4]+3];
				break;
			//if note delay
			case 0x07:
				advik_sfx_ch5_delay_enabled = 1;
				advik_sfx_ch5_delay_ticks_counter = advik_ch_sfx_order[4][advik_ch_sfx_current[4]+3] - 1;
				break;
			//if set global panning
			case 0x08:
				REG_SNDDSCNT = (REG_SNDDSCNT & 0x00ff) | (advik_ch_sfx_order[4][advik_ch_sfx_current[4]+3] << 8);
				break;
			//if change timbre
			// case 0x09:
				// REG_SND1CNT = (advik_ch_sfx_current_square_instruments[advik_ch_sfx_order[0][advik_ch_sfx_current[0]+1]] & 0xff00) | advik_ch_sfx_order[0][advik_ch_sfx_current[0]+3];
				// break;
			//if change order
			//if set volume
			case 0x0c:
				REG_SNDDSCNT = (REG_SNDDSCNT & 0xfffb) | ((advik_ch_sfx_order[4][advik_ch_sfx_current[4]+3] & 1) << 2);
				break;
			//if pattern break
			case 0x0d:
				advik_ch_sfx_override[4] = 0;
				break;
			//if note cut
			case 0x0e:
				advik_sfx_ch5_cut_delay_enabled = 1;
				advik_sfx_ch5_delay_ticks_counter = advik_ch_sfx_order[4][advik_ch_sfx_current[4]+3] - 1;
				break;
			//if set tempo
			case 0x0f:
				advik_ch_sfx_ticks_per_row_value[4] = advik_ch_sfx_order[4][advik_ch_sfx_current[4]+3]-1;
				break;
			//if set furnace panning
			case 0x80:
				REG_SNDDSCNT = (REG_SNDDSCNT & 0xeeff) | ((advik_ch_sfx_order[4][advik_ch_sfx_current[4]+3] & 0x01) << 8) | ((advik_ch_sfx_order[4][advik_ch_sfx_current[4]+3] & 0x10) << 12);
		}
		if (advik_ch_sfx_order[4][advik_ch_sfx_current[4]] < 0xf0 && !advik_sfx_ch5_delay_enabled) {
			//if instrument isn't 0, retrigger note
			if (advik_ch_sfx_order[4][advik_ch_sfx_current[4]+1] > 0x00){
				REG_DMA1CNT = 0;
				//set DMA transfer to DAC 1 FIFO
				REG_DMA1SAD = (uint32_t)advik_sfx_current_dma_instruments[0][advik_ch_sfx_order[4][advik_ch_sfx_current[4]+1] - 1];
				REG_DMA1DAD = (uint32_t)&REG_FIFO_A;
				REG_DMA1CNT = DMA_DST_FIXED | DMA_REPEAT | DMA_32 | DMA_AT_REFRESH | DMA_ENABLE;
				
				advik_ch_sfx_sample_duration[0] = advik_sfx_current_dma_durations[0][advik_ch_sfx_order[4][advik_ch_sfx_current[4]+1] - 1];
			}
			advik_sfx_ch5_held_note = 0;
			//set timer 0
			REG_TM0D = dma_snd_freqs[advik_ch_sfx_order[4][advik_ch_sfx_current[4]]];
			REG_TM0CNT = TM_ENABLE;
			advik_sfx_ch5_previous_freq = dma_snd_freqs[advik_ch_sfx_order[4][advik_ch_sfx_current[4]]];
		} else if (advik_ch_sfx_order[4][advik_ch_sfx_current[4]] == 0xfe) {
			//make sure held note is saved
			if (advik_sfx_ch5_held_note == 0) {
				advik_sfx_ch5_held_note = advik_sfx_ch5_previous_freq;
			}
		}
		advik_ch_sfx_current[4] += 4;
		advik_ch_sfx_ticks_per_row_counter[4] = advik_ch_sfx_ticks_per_row_value[4];
		//if end of order is reached, don't loop
		if (advik_ch_sfx_order[4][advik_ch_sfx_current[4]] == 0xff) {
			advik_ch_sfx_override[4] = 0;
			advik_sfx_ch5_held_note = 0;
			REG_DMA1CNT = 0;
		}
	}
}
static inline void cell_sfx_ch6_play(){
	if (advik_ch_sfx_ticks_per_row_counter[5] > 0) {
		advik_ch_sfx_ticks_per_row_counter[5]--;
		if (advik_sfx_ch6_delay_enabled > 0) {
			if (advik_sfx_ch6_delay_ticks_counter > 0) {
				advik_sfx_ch6_delay_ticks_counter--;
			} else {
				REG_DMA2CNT = 0;
			
				//set timer 0
				REG_TM1D = dma_snd_freqs[advik_ch_sfx_order[5][advik_ch_sfx_current[5]-4]];
				REG_TM1CNT = TM_ENABLE;
				
				//set DMA transfer to DAC 2 FIFO
				REG_DMA2SAD = (uint32_t)advik_sfx_current_dma_instruments[1][advik_ch_sfx_order[5][advik_ch_sfx_current[5]-3] - 1];
				REG_DMA2DAD = (uint32_t)&REG_FIFO_B;
				REG_DMA2CNT = DMA_DST_FIXED | DMA_REPEAT | DMA_32 | DMA_AT_REFRESH | DMA_ENABLE;
				
				advik_ch_sfx_sample_duration[1] = advik_sfx_current_dma_durations[1][advik_ch_sfx_order[5][advik_ch_sfx_current[5]-3] - 1];
				advik_sfx_ch6_delay_enabled = 0;
			}
		} else if (advik_sfx_ch6_portamento_direction == 1) {
			advik_sfx_ch6_portamento_freq += advik_ch_sfx_order[5][advik_ch_sfx_current[5]-1];
			//set timer 0
			REG_TM1D = advik_sfx_ch6_portamento_freq;
			advik_sfx_ch6_previous_freq = advik_sfx_ch6_portamento_freq;
		} else if (advik_sfx_ch6_portamento_direction == 2) {
			advik_sfx_ch6_portamento_freq -= advik_ch_sfx_order[5][advik_ch_sfx_current[5]-1];
			//set timer 0
			REG_TM1D = advik_sfx_ch6_portamento_freq;
			advik_sfx_ch6_previous_freq = advik_sfx_ch6_portamento_freq;
		} else if (advik_sfx_ch6_portamento_direction == 3) {
			if (advik_sfx_ch6_portamento_freq > advik_sfx_ch6_portamento_freq_goal){
				advik_sfx_ch6_portamento_freq -= advik_ch_sfx_order[5][advik_ch_sfx_current[5]-1];
			} else if (advik_sfx_ch6_portamento_freq < advik_sfx_ch6_portamento_freq_goal){
				advik_sfx_ch6_portamento_freq += advik_ch_sfx_order[5][advik_ch_sfx_current[5]-1];
			}
			//set timer 0
			REG_TM1D = advik_sfx_ch6_portamento_freq;
			advik_sfx_ch6_previous_freq = advik_sfx_ch6_portamento_freq;
		} else if (advik_sfx_ch6_cut_delay_enabled > 1) {
			if (advik_sfx_ch6_delay_ticks_counter > 0) {
				advik_sfx_ch6_delay_ticks_counter--;
			} else {
				REG_DMA2CNT = 0;
				advik_sfx_ch6_cut_delay_enabled = 0;
			}
		} else if (advik_sfx_ch6_arp_enabled > 0) {
			switch (advik_arp_index) {
				case 1:
					REG_TM1D = (dma_snd_freqs[advik_ch_sfx_order[5][advik_ch_sfx_current[5]-4] + (advik_ch_sfx_order[5][advik_ch_sfx_current[5]-1] >> 4)]);
					break;
				case 2:
					REG_TM1D = (dma_snd_freqs[advik_ch_sfx_order[5][advik_ch_sfx_current[5]-4] + (advik_ch_sfx_order[5][advik_ch_sfx_current[5]-1] & 0x0f)]);
					break;
				default:
					REG_TM1D = (dma_snd_freqs[advik_ch_sfx_order[5][advik_ch_sfx_current[5]-4]]);
			}
		} else if (advik_sfx_ch6_vib_enabled > 0) {
			advik_sfx_ch6_vib_ticks_counter += advik_ch_sfx_order[5][advik_ch_sfx_current[5]-1] >> 4;
			advik_sfx_ch6_vib_position = advik_sfx_ch6_vib_ticks_counter & 63;
			if (advik_ch_sfx_order[5][advik_ch_sfx_current[5]-4] < 0xf0)
				REG_TM1D = (dma_snd_freqs[advik_ch_sfx_order[5][advik_ch_sfx_current[5]-4]] - ((vib_table[advik_sfx_ch6_vib_position] * (advik_sfx_ch6_vib_depth)) >> 5));
			else
				REG_TM1D = (advik_sfx_ch6_held_note - ((vib_table[advik_sfx_ch6_vib_position] * (advik_sfx_ch6_vib_depth)) >> 5));
		}
		if (advik_ch_sfx_sample_duration[1]){
			advik_ch_sfx_sample_duration[1]--;
		} else {
			REG_DMA2CNT = 0;
		}
	} else {
		if (!advik_ch_sfx_command_linger[5]){
			advik_sfx_ch6_arp_enabled = 0;
			advik_sfx_ch6_portamento_direction = 0;
			advik_sfx_ch6_vib_enabled = 0;
			advik_sfx_ch6_vib_ticks_counter = 0;
			//restore notes after vibrato end
			if (advik_sfx_ch6_held_note > 0) {
				REG_TM1D = advik_sfx_ch6_held_note;
				advik_sfx_ch6_held_note = 0;
			}
		}
		switch (advik_ch_sfx_order[5][advik_ch_sfx_current[5]+2]) {
			//if arpeggio
			case 0x00:
				if (advik_ch_sfx_order[5][advik_ch_sfx_current[5]+3] > 0) {
					advik_sfx_ch6_arp_enabled = 1;
				} else if (advik_ch_sfx_order[5][advik_ch_sfx_current[5]+3] == 0 && advik_ch_sfx_command_linger[5]) {
					advik_sfx_ch6_arp_enabled = 0;
				}
				break;
			//if portamento up
			case 0x01:
				if (advik_ch_sfx_order[5][advik_ch_sfx_current[5]+3] > 0) {
					advik_sfx_ch6_portamento_direction = 1;
					if (advik_ch_sfx_order[5][advik_ch_sfx_current[5]] < 0xf0) {
						advik_sfx_ch6_portamento_freq = dma_snd_freqs[advik_ch_sfx_order[5][advik_ch_sfx_current[5]]];
					} else if (advik_ch_sfx_order[5][advik_ch_sfx_current[5]] == 0xfe) {
						advik_sfx_ch6_portamento_freq = advik_sfx_ch6_previous_freq;
					}
				} else if (advik_ch_sfx_order[5][advik_ch_sfx_current[5]+3] == 0 && advik_ch_sfx_command_linger[5]) {
					advik_sfx_ch6_portamento_direction = 0;
				}
				break;
			//if portamento down
			case 0x02:
				if (advik_ch_sfx_order[5][advik_ch_sfx_current[5]+3] > 0) {
					advik_sfx_ch6_portamento_direction = 2;
					if (advik_ch_sfx_order[5][advik_ch_sfx_current[5]] < 0xf0) {
						advik_sfx_ch6_portamento_freq = dma_snd_freqs[advik_ch_sfx_order[5][advik_ch_sfx_current[5]]];
					} else if (advik_ch_sfx_order[5][advik_ch_sfx_current[5]] == 0xfe) {
						advik_sfx_ch6_portamento_freq = advik_sfx_ch6_previous_freq;
					}
				} else if (advik_ch_sfx_order[5][advik_ch_sfx_current[5]+3] == 0 && advik_ch_sfx_command_linger[5]) {
					advik_sfx_ch6_portamento_direction = 0;
				}
				break;
			//if tone portamento
			case 0x03:
				if (advik_ch_sfx_order[5][advik_ch_sfx_current[5]+3] > 0) {
					advik_sfx_ch6_portamento_direction = 3;
					advik_sfx_ch6_portamento_freq = advik_sfx_ch6_previous_freq;
					if (advik_ch_sfx_order[5][advik_ch_sfx_current[5]] < 0xf0) {
						advik_sfx_ch6_portamento_freq_goal = dma_snd_freqs[advik_ch_sfx_order[5][advik_ch_sfx_current[5]]];
					}
				} else if (advik_ch_sfx_order[5][advik_ch_sfx_current[5]+3] == 0 && advik_ch_sfx_command_linger[5]) {
					advik_sfx_ch6_portamento_direction = 0;
				}
				break;
			//if vibrato
			case 0x04:
				advik_sfx_ch6_vib_depth = advik_ch_sfx_order[5][advik_ch_sfx_current[5]+3] & 0x0f;
				advik_sfx_ch6_vib_enabled = 1;
				if (advik_ch_sfx_order[5][advik_ch_sfx_current[5]+3] == 0 && advik_ch_sfx_command_linger[5]) {
					advik_sfx_ch6_vib_enabled = 0;
					if (advik_sfx_ch6_held_note > 0) {
						REG_TM1D = advik_sfx_ch6_held_note;
						advik_sfx_ch6_held_note = 0;
					}
				}
				break;
			//if set master volume
			case 0x05:
				REG_SNDDSCNT = (REG_SNDDSCNT & 0xfff3) | advik_ch_sfx_order[5][advik_ch_sfx_current[5]+3];
				break;
			//if note delay
			case 0x07:
				advik_sfx_ch6_delay_enabled = 1;
				advik_sfx_ch6_delay_ticks_counter = advik_ch_sfx_order[5][advik_ch_sfx_current[5]+3] - 1;
				break;
			//if set global panning
			case 0x08:
				REG_SNDDSCNT = (REG_SNDDSCNT & 0x00ff) | (advik_ch_sfx_order[5][advik_ch_sfx_current[5]+3] << 8);
				break;
			//if change timbre
			// case 0x09:
				// REG_SND1CNT = (advik_ch_sfx_current_square_instruments[advik_ch_sfx_order[0][advik_current+1]] & 0xff00) | advik_ch_sfx_order[0][advik_current+3];
				// break;
			//if change order
			//if set volume
			case 0x0c:
				REG_SNDDSCNT = (REG_SNDDSCNT & 0xfff7) | ((advik_ch_sfx_order[5][advik_ch_sfx_current[5]+3] & 1) << 3);
				break;
			//if pattern break
			case 0x0d:
				advik_ch_sfx_override[5] = 0;
				break;
			//if note cut
			case 0x0e:
				advik_sfx_ch6_cut_delay_enabled = 1;
				advik_sfx_ch6_delay_ticks_counter = advik_ch_sfx_order[5][advik_ch_sfx_current[5]+3] - 1;
				break;
			//if set tempo
			case 0x0f:
				advik_ch_sfx_ticks_per_row_value[5] = advik_ch_sfx_order[5][advik_ch_sfx_current[5]+3]-1;
				break;
			//if set furnace panning
			case 0x80:
				REG_SNDDSCNT = (REG_SNDDSCNT & 0xddff) | ((advik_ch_sfx_order[5][advik_ch_sfx_current[5]+3] & 0x01) << 9) | ((advik_ch_sfx_order[5][advik_ch_sfx_current[5]+3] & 0x10) << 13);
		}
		if (advik_ch_sfx_order[5][advik_ch_sfx_current[5]] < 0xf0 && !advik_sfx_ch6_delay_enabled) {
			//if instrument isn't 0, retrigger note
			if (advik_ch_sfx_order[5][advik_ch_sfx_current[5]+1] > 0x00){
				REG_DMA2CNT = 0;
				//set DMA transfer to DAC 2 FIFO
				REG_DMA2SAD = (uint32_t)advik_sfx_current_dma_instruments[1][advik_ch_sfx_order[5][advik_ch_sfx_current[5]+1] - 1];
				REG_DMA2DAD = (uint32_t)&REG_FIFO_B;
				REG_DMA2CNT = DMA_DST_FIXED | DMA_REPEAT | DMA_32 | DMA_AT_REFRESH | DMA_ENABLE;
				
				advik_ch_sfx_sample_duration[1] = advik_sfx_current_dma_durations[1][advik_ch_sfx_order[5][advik_ch_sfx_current[5]+1] - 1];
			}
			advik_sfx_ch6_held_note = 0;
			//set timer 1
			REG_TM1D = dma_snd_freqs[advik_ch_sfx_order[5][advik_ch_sfx_current[5]]];
			REG_TM1CNT = TM_ENABLE;
			advik_sfx_ch6_previous_freq = dma_snd_freqs[advik_ch_sfx_order[5][advik_ch_sfx_current[5]]];
		} else if (advik_ch_sfx_order[5][advik_ch_sfx_current[5]] == 0xfe) {
			//make sure held note is saved
			if (advik_sfx_ch6_held_note == 0) {
				advik_sfx_ch6_held_note = advik_ch6_previous_freq;
			}
		}
		advik_ch_sfx_current[5] += 4;
		advik_ch_sfx_ticks_per_row_counter[5] = advik_ch_sfx_ticks_per_row_value[5];
		//if end of order is reached, don't loop
		if (advik_ch_sfx_order[5][advik_ch_sfx_current[5]] == 0xff) {
			advik_ch_sfx_override[5] = 0;
			REG_DMA2CNT = 0;
			advik_sfx_ch6_held_note = 0;
		}
	}
}

void cell_song_play() {
	if (advik_ticks_per_row_counter > 0) {
		
		advik_ticks_per_row_counter--;
		advik_arp_tick++;
		advik_arp_index = advik_arp_tick % 3;
		
		//channel 1
		if (advik_global_channels){
			if (advik_ch1_delay_enabled > 0) {
				if (advik_ch1_delay_ticks_counter > 0) {
					advik_ch1_delay_ticks_counter--;
				} else {
					if (advik_ch_current_order[0][advik_current-3] > 0x00){
						if (!advik_ch_sfx_override[0]){
						REG_SND1CNT = advik_current_square_instruments[advik_ch_current_order[0][advik_current-3] - 1];
						}
					}
					if (!advik_ch_sfx_override[0]){
					if ((advik_current_square_instruments[advik_ch_current_order[0][advik_current-3] - 1] & SSQR_LEN_MASK) < 63){
						REG_SND1FREQ = SFREQ_RESET | snd_freqs[advik_ch_current_order[0][advik_current-4]] | SFREQ_TIMED;
					}else{
						REG_SND1FREQ = SFREQ_RESET | snd_freqs[advik_ch_current_order[0][advik_current-4]];
					}
					}
					advik_ch1_delay_enabled = 0;
				}
			} else if (advik_ch1_portamento_direction == 1) {
				advik_ch1_portamento_freq += advik_ch_current_order[0][advik_current-1];
				if (!advik_ch_sfx_override[0]){
				REG_SND1FREQ = advik_ch1_portamento_freq;
				}
				advik_ch1_previous_freq = advik_ch1_portamento_freq;
			} else if (advik_ch1_portamento_direction == 2) {
				advik_ch1_portamento_freq -= advik_ch_current_order[0][advik_current-1];
				if (!advik_ch_sfx_override[0]){
				REG_SND1FREQ = advik_ch1_portamento_freq;
				}
				advik_ch1_previous_freq = advik_ch1_portamento_freq;
			} else if (advik_ch1_portamento_direction == 3) {
				if (advik_ch1_portamento_freq > advik_ch1_portamento_freq_goal){
					advik_ch1_portamento_freq -= advik_ch_current_order[0][advik_current-1];
				} else if (advik_ch1_portamento_freq < advik_ch1_portamento_freq_goal){
					advik_ch1_portamento_freq += advik_ch_current_order[0][advik_current-1];
				}
				if (!advik_ch_sfx_override[0]){
				REG_SND1FREQ = advik_ch1_portamento_freq;
				}
				advik_ch1_previous_freq = advik_ch1_portamento_freq;
			} else if (advik_ch1_cut_delay_enabled > 1) {
				if (advik_ch1_delay_ticks_counter > 0) {
					advik_ch1_delay_ticks_counter--;
				} else {
					if (!advik_ch_sfx_override[0]){
					REG_SND1CNT = 0;
					}
					advik_ch1_cut_delay_enabled = 0;
				}
			} else if (advik_ch1_arp_enabled > 0) {
				if (!advik_ch_sfx_override[0]){
				switch (advik_arp_index) {
					case 1:
						REG_SND1FREQ = (snd_freqs[advik_ch_current_order[0][advik_current-4] + (advik_ch_current_order[0][advik_current-1] >> 4)]);
						break;
					case 2:
						REG_SND1FREQ = (snd_freqs[advik_ch_current_order[0][advik_current-4] + (advik_ch_current_order[0][advik_current-1] & 0x0f)]);
						break;
					default:
						REG_SND1FREQ = (snd_freqs[advik_ch_current_order[0][advik_current-4]]);
				}
				}
			} else if (advik_ch1_vib_enabled > 0) {
				advik_ch1_vib_ticks_counter += advik_ch_current_order[0][advik_current-1] >> 4;
				advik_ch1_vib_position = advik_ch1_vib_ticks_counter & 63;
				if (!advik_ch_sfx_override[0]){
					if (advik_ch_current_order[0][advik_current-4] < 0xf0)
						REG_SND1FREQ = (snd_freqs[advik_ch_current_order[0][advik_current-4]] - ((vib_table[advik_ch1_vib_position] * (advik_ch1_vib_depth)) >> 5));
					else
						REG_SND1FREQ = (advik_ch1_held_note - ((vib_table[advik_ch1_vib_position] * (advik_ch1_vib_depth)) >> 5));
				}
			}
		}
		//channel 2
		if (advik_global_channels > 1){
			if (advik_ch2_delay_enabled > 0) {
				if (advik_ch2_delay_ticks_counter > 0) {
					advik_ch2_delay_ticks_counter--;
				} else {
					if (advik_ch_current_order[1][advik_current-3] > 0x00){
						if (!advik_ch_sfx_override[1]){
						REG_SND2CNT = advik_current_square_instruments[advik_ch_current_order[1][advik_current-3] - 1];
						}
					}
					if (!advik_ch_sfx_override[1]){
					if ((advik_current_square_instruments[advik_ch_current_order[1][advik_current-3] - 1] & SSQR_LEN_MASK) < 63){
						REG_SND2FREQ = SFREQ_RESET | snd_freqs[advik_ch_current_order[1][advik_current-4]] | SFREQ_TIMED;
					}else{
						REG_SND2FREQ = SFREQ_RESET | snd_freqs[advik_ch_current_order[1][advik_current-4]];
					}
					}
					advik_ch2_delay_enabled = 0;
				}
			} else if (advik_ch2_portamento_direction == 1) {
				advik_ch2_portamento_freq += advik_ch_current_order[1][advik_current-1];
				if (!advik_ch_sfx_override[1]){
				REG_SND2FREQ = advik_ch2_portamento_freq;
				}
				advik_ch2_previous_freq = advik_ch2_portamento_freq;
			} else if (advik_ch2_portamento_direction == 2) {
				advik_ch2_portamento_freq -= advik_ch_current_order[1][advik_current-1];
				if (!advik_ch_sfx_override[1]){
				REG_SND2FREQ = advik_ch2_portamento_freq;
				}
				advik_ch2_previous_freq = advik_ch2_portamento_freq;
			} else if (advik_ch2_portamento_direction == 3) {
				if (advik_ch2_portamento_freq > advik_ch2_portamento_freq_goal){
					advik_ch2_portamento_freq -= advik_ch_current_order[1][advik_current-1];
				} else if (advik_ch2_portamento_freq < advik_ch2_portamento_freq_goal){
					advik_ch2_portamento_freq += advik_ch_current_order[1][advik_current-1];
				}
				if (!advik_ch_sfx_override[1]){
				REG_SND2FREQ = advik_ch2_portamento_freq;
				}
				advik_ch2_previous_freq = advik_ch2_portamento_freq;
			} else if (advik_ch2_cut_delay_enabled > 1) {
				if (advik_ch2_delay_ticks_counter > 0) {
					advik_ch2_delay_ticks_counter--;
				} else {
					if (!advik_ch_sfx_override[1]){
					REG_SND2CNT = 0;
					}
					advik_ch2_cut_delay_enabled = 0;
				}
			} else if (advik_ch2_arp_enabled > 0) {
				if (!advik_ch_sfx_override[1]){
				switch (advik_arp_index) {
					case 1:
						REG_SND2FREQ = (snd_freqs[advik_ch_current_order[1][advik_current-4] + (advik_ch_current_order[1][advik_current-1] >> 4)]);
						break;
					case 2:
						REG_SND2FREQ = (snd_freqs[advik_ch_current_order[1][advik_current-4] + (advik_ch_current_order[1][advik_current-1] & 0x0f)]);
						break;
					default:
						REG_SND2FREQ = (snd_freqs[advik_ch_current_order[1][advik_current-4]]);
				}
				}
			} else if (advik_ch2_vib_enabled > 0) {
				advik_ch2_vib_ticks_counter += advik_ch_current_order[1][advik_current-1] >> 4;
				advik_ch2_vib_position = advik_ch2_vib_ticks_counter & 63;
				if (!advik_ch_sfx_override[1]){
				REG_SND2FREQ = (snd_freqs[advik_ch_current_order[1][advik_current-4]] - ((vib_table[advik_ch2_vib_position] * (advik_ch2_vib_depth)) >> 5));
				}
			}
		}
		//channel 3
		if (advik_global_channels > 2){
			if (advik_ch3_delay_enabled > 0) {
				if (advik_ch3_delay_ticks_counter > 0) {
					advik_ch3_delay_ticks_counter--;
				} else {
					if (!advik_ch_sfx_override[2]){
					if ((advik_current_wave_instruments[(advik_ch_current_order[2][advik_current-3] << 1)]) == SWAV_LEN_ON)
						REG_SND3FREQ = SFREQ_RESET | snd_freqs[advik_ch_current_order[2][advik_current-4]] | SFREQ_TIMED;
					else
						REG_SND3FREQ = SFREQ_RESET | snd_freqs[advik_ch_current_order[2][advik_current-4]];
					}
					advik_ch3_delay_enabled = 0;
				}
			} else if (advik_ch3_portamento_direction == 1) {
				advik_ch3_portamento_freq += advik_ch_current_order[2][advik_current-1];
				if (!advik_ch_sfx_override[2]){
				REG_SND3FREQ = advik_ch3_portamento_freq;
				}
				advik_ch3_previous_freq = advik_ch3_portamento_freq;
			} else if (advik_ch3_portamento_direction == 2) {
				advik_ch3_portamento_freq -= advik_ch_current_order[2][advik_current-1];
				if (!advik_ch_sfx_override[2]){
				REG_SND3FREQ = advik_ch3_portamento_freq;
				}
				advik_ch3_previous_freq = advik_ch3_portamento_freq;
			} else if (advik_ch3_portamento_direction == 3) {
				if (advik_ch3_portamento_freq > advik_ch3_portamento_freq_goal){
					advik_ch3_portamento_freq -= advik_ch_current_order[2][advik_current-1];
				} else if (advik_ch3_portamento_freq < advik_ch3_portamento_freq_goal){
					advik_ch3_portamento_freq += advik_ch_current_order[2][advik_current-1];
				}
				if (!advik_ch_sfx_override[2]){
				REG_SND3FREQ = advik_ch3_portamento_freq;
				}
				advik_ch3_previous_freq = advik_ch3_portamento_freq;
			} else if (advik_ch3_cut_delay_enabled > 1) {
				if (advik_ch3_delay_ticks_counter > 0) {
					advik_ch3_delay_ticks_counter--;
				} else {
					if (!advik_ch_sfx_override[2]){
					REG_SND3CNT = 0;
					}
					advik_ch3_cut_delay_enabled = 0;
				}
			} else if (advik_ch3_arp_enabled > 0) {
				if (!advik_ch_sfx_override[2]){
				switch (advik_arp_index) {
					case 1:
						REG_SND3FREQ = (snd_freqs[advik_ch_current_order[2][advik_current-4] + (advik_ch_current_order[2][advik_current-1] >> 4)]);
						break;
					case 2:
						REG_SND3FREQ = (snd_freqs[advik_ch_current_order[2][advik_current-4] + (advik_ch_current_order[2][advik_current-1] & 0x0f)]);
						break;
					default:
						REG_SND3FREQ = (snd_freqs[advik_ch_current_order[2][advik_current-4]]);
				}
				}
			} else if (advik_ch3_vib_enabled > 0) {
				advik_ch3_vib_ticks_counter += advik_ch_current_order[2][advik_current-1] >> 4;
				advik_ch3_vib_position = advik_ch3_vib_ticks_counter & 63;
				if (!advik_ch_sfx_override[2]){
				REG_SND3FREQ = (snd_freqs[advik_ch_current_order[2][advik_current-4]] - ((vib_table[advik_ch3_vib_position] * (advik_ch3_vib_depth)) >> 5));
				}
			}
		}
		//channel 4
		if (advik_global_channels > 3){
			if (advik_ch4_delay_enabled > 0) {
				if (advik_ch4_delay_ticks_counter > 0) {
					advik_ch4_delay_ticks_counter--;
				} else {
					if (!advik_ch_sfx_override[3]){
					if (advik_ch_current_order[3][advik_current-3] > 0x00){
						REG_SND4CNT = advik_current_noise_instruments[advik_ch_current_order[3][advik_current-3] - 1] & SNOI_EXCLUDE_PACK;
					}
					if ((advik_current_noise_instruments[advik_ch_current_order[3][advik_current-3] - 1] & SSQR_LEN_MASK))
						REG_SND4FREQ = SFREQ_RESET | (SNOI_POLYNOM(advik_ch_current_order[3][advik_current-4]) & SNOI_EXCLUDE_UNPACK) | (SNOI_UNPACK(advik_current_noise_instruments[advik_ch_current_order[3][advik_current-4] - 1] & SNOI_SHORT_PACK)) | SFREQ_TIMED;
					else
						REG_SND4FREQ = SFREQ_RESET | (SNOI_POLYNOM(advik_ch_current_order[3][advik_current-4]) & SNOI_EXCLUDE_UNPACK) | (SNOI_UNPACK(advik_current_noise_instruments[advik_ch_current_order[3][advik_current-4] - 1] & SNOI_SHORT_PACK));
					}
					advik_ch4_delay_enabled = 0;
				}
			} else if (advik_ch4_cut_delay_enabled > 1) {
				if (advik_ch4_delay_ticks_counter > 0) {
					advik_ch4_delay_ticks_counter--;
				} else {
					if (!advik_ch_sfx_override[3]){
					REG_SND4CNT = 0;
					}
					advik_ch4_cut_delay_enabled = 0;
				}
			}
		}
		//channel 5
		if (advik_global_channels > 4){
			if (advik_ch5_delay_enabled > 0) {
				if (advik_ch5_delay_ticks_counter > 0) {
					advik_ch5_delay_ticks_counter--;
				} else {
					if (!advik_ch_sfx_override[4]){
					REG_DMA1CNT = 0;
				
					//set timer 0
					REG_TM0D = dma_snd_freqs[advik_ch_current_order[4][advik_current-4]];
					REG_TM0CNT = TM_ENABLE;
					
					//set DMA transfer to DAC 1 FIFO
					REG_DMA1SAD = (uint32_t)advik_current_dma_instruments[advik_ch_current_order[4][advik_current-3] - 1];
					REG_DMA1DAD = (uint32_t)&REG_FIFO_A;
					REG_DMA1CNT = DMA_DST_FIXED | DMA_REPEAT | DMA_32 | DMA_AT_REFRESH | DMA_ENABLE;
					}
					advik_ch5_sample_duration = advik_current_dma_durations[advik_ch_current_order[4][advik_current-3] - 1];
					advik_ch5_delay_enabled = 0;
				}
			} else if (advik_ch5_portamento_direction == 1) {
				advik_ch5_portamento_freq += advik_ch_current_order[4][advik_current-1];
				if (!advik_ch_sfx_override[4]){
				//set timer 0
				REG_TM0D = advik_ch5_portamento_freq;
				}
				advik_ch5_previous_freq = advik_ch5_portamento_freq;
			} else if (advik_ch5_portamento_direction == 2) {
				advik_ch5_portamento_freq -= advik_ch_current_order[4][advik_current-1];
				if (!advik_ch_sfx_override[4]){
				//set timer 0
				REG_TM0D = advik_ch5_portamento_freq;
				}
				advik_ch5_previous_freq = advik_ch5_portamento_freq;
			} else if (advik_ch5_portamento_direction == 3) {
				if (advik_ch5_portamento_freq > advik_ch5_portamento_freq_goal){
					advik_ch5_portamento_freq -= advik_ch_current_order[4][advik_current-1];
				} else if (advik_ch5_portamento_freq < advik_ch5_portamento_freq_goal){
					advik_ch5_portamento_freq += advik_ch_current_order[4][advik_current-1];
				}
				if (!advik_ch_sfx_override[4]){
				//set timer 0
				REG_TM0D = advik_ch5_portamento_freq;
				}
				advik_ch5_previous_freq = advik_ch5_portamento_freq;
			} else if (advik_ch5_cut_delay_enabled > 1) {
				if (advik_ch5_delay_ticks_counter > 0) {
					advik_ch5_delay_ticks_counter--;
				} else {
					if (!advik_ch_sfx_override[4]){
					REG_DMA1CNT = 0;
					}
					advik_ch5_cut_delay_enabled = 0;
				}
			} else if (advik_ch5_arp_enabled > 0) {
				if (!advik_ch_sfx_override[4]){
				switch (advik_arp_index) {
					case 1:
						REG_TM0D = (dma_snd_freqs[advik_ch_current_order[4][advik_current-4] + (advik_ch_current_order[4][advik_current-1] >> 4)]);
						break;
					case 2:
						REG_TM0D = (dma_snd_freqs[advik_ch_current_order[4][advik_current-4] + (advik_ch_current_order[4][advik_current-1] & 0x0f)]);
						break;
					default:
						REG_TM0D = (dma_snd_freqs[advik_ch_current_order[4][advik_current-4]]);
				}
				}
			} else if (advik_ch5_vib_enabled > 0) {
				advik_ch5_vib_ticks_counter += advik_ch_current_order[4][advik_current-1] >> 4;
				advik_ch5_vib_position = advik_ch5_vib_ticks_counter & 63;
				if (!advik_ch_sfx_override[4]){
				REG_TM0D = (dma_snd_freqs[advik_ch_current_order[4][advik_current-4]] - ((vib_table[advik_ch5_vib_position] * (advik_ch5_vib_depth)) >> 5));
				}
			}
			if (advik_ch5_sample_duration){
				advik_ch5_sample_duration--;
			} else {
				if (!advik_ch_sfx_override[4]){
				REG_DMA1CNT = 0;
				}
			}
		}
		//channel 6
		if (advik_global_channels > 5){
			if (advik_ch6_delay_enabled > 0) {
				if (advik_ch6_delay_ticks_counter > 0) {
					advik_ch6_delay_ticks_counter--;
				} else {
					if (!advik_ch_sfx_override[5]){
					REG_DMA2CNT = 0;
				
					//set timer 0
					REG_TM1D = dma_snd_freqs[advik_ch_current_order[5][advik_current-4]];
					REG_TM1CNT = TM_ENABLE;
					
					//set DMA transfer to DAC 1 FIFO
					REG_DMA2SAD = (uint32_t)advik_current_dma_instruments[advik_ch_current_order[5][advik_current-3] - 1];
					REG_DMA2DAD = (uint32_t)&REG_FIFO_B;
					REG_DMA2CNT = DMA_DST_FIXED | DMA_REPEAT | DMA_32 | DMA_AT_REFRESH | DMA_ENABLE;
					}
					advik_ch6_sample_duration = advik_current_dma_durations[advik_ch_current_order[5][advik_current-3] - 1];
					advik_ch6_delay_enabled = 0;
				}
			} else if (advik_ch6_portamento_direction == 1) {
				advik_ch6_portamento_freq += advik_ch_current_order[5][advik_current-1];
				if (!advik_ch_sfx_override[5]){
				//set timer 0
				REG_TM1D = advik_ch6_portamento_freq;
				}
				advik_ch6_previous_freq = advik_ch6_portamento_freq;
			} else if (advik_ch6_portamento_direction == 2) {
				advik_ch6_portamento_freq -= advik_ch_current_order[5][advik_current-1];
				if (!advik_ch_sfx_override[5]){
				//set timer 0
				REG_TM1D = advik_ch6_portamento_freq;
				}
				advik_ch6_previous_freq = advik_ch6_portamento_freq;
			} else if (advik_ch6_portamento_direction == 3) {
				if (advik_ch6_portamento_freq > advik_ch6_portamento_freq_goal){
					advik_ch6_portamento_freq -= advik_ch_current_order[5][advik_current-1];
				} else if (advik_ch6_portamento_freq < advik_ch6_portamento_freq_goal){
					advik_ch6_portamento_freq += advik_ch_current_order[5][advik_current-1];
				}
				if (!advik_ch_sfx_override[5]){
				//set timer 0
				REG_TM1D = advik_ch6_portamento_freq;
				}
				advik_ch6_previous_freq = advik_ch6_portamento_freq;
			} else if (advik_ch6_cut_delay_enabled > 1) {
				if (advik_ch6_delay_ticks_counter > 0) {
					advik_ch6_delay_ticks_counter--;
				} else {
					if (!advik_ch_sfx_override[5]){
					REG_DMA2CNT = 0;
					}
					advik_ch6_cut_delay_enabled = 0;
				}
			} else if (advik_ch6_arp_enabled > 0) {
				if (!advik_ch_sfx_override[5]){
				switch (advik_arp_index) {
					case 1:
						REG_TM1D = (dma_snd_freqs[advik_ch_current_order[5][advik_current-4] + (advik_ch_current_order[5][advik_current-1] >> 4)]);
						break;
					case 2:
						REG_TM1D = (dma_snd_freqs[advik_ch_current_order[5][advik_current-4] + (advik_ch_current_order[5][advik_current-1] & 0x0f)]);
						break;
					default:
						REG_TM1D = (dma_snd_freqs[advik_ch_current_order[5][advik_current-4]]);
				}
				}
			} else if (advik_ch6_vib_enabled > 0) {
				advik_ch6_vib_ticks_counter += advik_ch_current_order[5][advik_current-1] >> 4;
				advik_ch6_vib_position = advik_ch6_vib_ticks_counter & 63;
				if (!advik_ch_sfx_override[5]){
				REG_TM1D = (dma_snd_freqs[advik_ch_current_order[5][advik_current-4]] - ((vib_table[advik_ch6_vib_position] * (advik_ch6_vib_depth)) >> 5));
				}
			}
			if (advik_ch6_sample_duration){
				advik_ch6_sample_duration--;
			} else {
				if (!advik_ch_sfx_override[5]){
				REG_DMA2CNT = 0;
				}
			}
		}
		
	} else {
		if (!advik_global_command_linger){
			advik_ch1_arp_enabled = 0;
			advik_ch1_portamento_direction = 0;
			advik_ch1_vib_enabled = 0;
			advik_ch1_vib_ticks_counter = 0;
			advik_ch2_arp_enabled = 0;
			advik_ch2_portamento_direction = 0;
			advik_ch2_vib_enabled = 0;
			advik_ch2_vib_ticks_counter = 0;
			advik_ch3_arp_enabled = 0;
			advik_ch3_portamento_direction = 0;
			advik_ch3_vib_enabled = 0;
			advik_ch3_vib_ticks_counter = 0;
			advik_ch5_arp_enabled = 0;
			advik_ch5_portamento_direction = 0;
			advik_ch5_vib_enabled = 0;
			advik_ch5_vib_ticks_counter = 0;
			advik_ch6_arp_enabled = 0;
			advik_ch6_portamento_direction = 0;
			advik_ch6_vib_enabled = 0;
			advik_ch6_vib_ticks_counter = 0;
			//restore notes after vibrato end
			if (advik_ch1_held_note > 0) {
				REG_SND1FREQ = advik_ch1_held_note;
				advik_ch1_held_note = 0;
			}
			if (advik_ch2_held_note > 0) {
				REG_SND2FREQ = advik_ch2_held_note;
				advik_ch2_held_note = 0;
			}
			if (advik_ch3_held_note > 0) {
				REG_SND3FREQ = advik_ch3_held_note;
				advik_ch3_held_note = 0;
			}
			if (advik_ch5_held_note > 0) {
				REG_TM0D = advik_ch5_held_note;
				advik_ch5_held_note = 0;
			}
			if (advik_ch6_held_note > 0) {
				REG_TM1D = advik_ch6_held_note;
				advik_ch6_held_note = 0;
			}
		}
		
		if (advik_change_order) {
			advik_change_order = 0;
			advik_current = advik_future;
			for (uint8_t i = 0; i < advik_global_channels; i++){
				advik_ch_current_order[i] = advik_global_current_order[advik_global_order_number+i];
			}
		}
		
		//if end of order is reached, loop
		if (advik_ch_current_order[0][advik_current] == 0xff) {
			advik_current = 0;
			if (advik_global_order_number < ((advik_global_order_length - 1) * advik_global_channels))
				advik_global_order_number += advik_global_channels;
			else
				advik_global_order_number = (advik_loop_point * advik_global_channels);
			
			for (uint8_t i = 0; i < advik_global_channels; i++){
				advik_ch_current_order[i] = advik_global_current_order[advik_global_order_number+i];
			}
		}
		
		//check current effect and value for channel 1
		if (advik_global_channels){
			switch (advik_ch_current_order[0][advik_current+2]) {
				//if arpeggio
				case 0x00:
					if (advik_ch_current_order[0][advik_current+3] > 0) {
						advik_ch1_arp_enabled = 1;
					} else if (advik_ch_current_order[0][advik_current+3] == 0 && advik_global_command_linger) {
						advik_ch1_arp_enabled = 0;
					}
					break;
				//if portamento up
				case 0x01:
					if (advik_ch_current_order[0][advik_current+3] > 0) {
						advik_ch1_portamento_direction = 1;
						if (advik_ch_current_order[0][advik_current] < 0xf0) {
							advik_ch1_portamento_freq = snd_freqs[advik_ch_current_order[0][advik_current]];
						} else if (advik_ch_current_order[0][advik_current] == 0xfe) {
							advik_ch1_portamento_freq = advik_ch1_previous_freq;
						}
					} else if (advik_ch_current_order[0][advik_current+3] == 0 && advik_global_command_linger) {
						advik_ch1_portamento_direction = 0;
					}
					break;
				//if portamento down
				case 0x02:
					if (advik_ch_current_order[0][advik_current+3] > 0) {
						advik_ch1_portamento_direction = 2;
						if (advik_ch_current_order[0][advik_current] < 0xf0) {
							advik_ch1_portamento_freq = snd_freqs[advik_ch_current_order[0][advik_current]];
						} else if (advik_ch_current_order[0][advik_current] == 0xfe) {
							advik_ch1_portamento_freq = advik_ch1_previous_freq;
						}
					} else if (advik_ch_current_order[0][advik_current+3] == 0 && advik_global_command_linger) {
						advik_ch1_portamento_direction = 0;
					}
					break;
				//if tone portamento
				case 0x03:
					if (advik_ch_current_order[0][advik_current+3] > 0) {
						advik_ch1_portamento_direction = 3;
						advik_ch1_portamento_freq = advik_ch1_previous_freq;
						if (advik_ch_current_order[0][advik_current] < 0xf0) {
							advik_ch1_portamento_freq_goal = snd_freqs[advik_ch_current_order[0][advik_current]];
						}
					} else if (advik_ch_current_order[0][advik_current+3] == 0 && advik_global_command_linger) {
						advik_ch1_portamento_direction = 0;
					}
					break;
				//if vibrato
				case 0x04:
					advik_ch1_vib_depth = advik_ch_current_order[0][advik_current+3] & 0x0f;
					advik_ch1_vib_enabled = 1;
					if (advik_ch_current_order[0][advik_current+3] == 0 && advik_global_command_linger) {
						advik_ch1_vib_enabled = 0;
						if (advik_ch1_held_note > 0) {
							REG_SND1FREQ = advik_ch1_held_note;
							advik_ch1_held_note = 0;
						}
					}
					break;
				//if set master volume
				case 0x05:
					REG_SNDDMGCNT = (REG_SNDDMGCNT & 0xff00) | advik_ch_current_order[0][advik_current+3];
					break;
				//if note delay
				case 0x07:
					advik_ch1_delay_enabled = 1;
					advik_ch1_delay_ticks_counter = advik_ch_current_order[0][advik_current+3] - 1;
					break;
				//if set global panning
				case 0x08:
					REG_SNDDMGCNT = (REG_SNDDMGCNT & 0x00ff) | (advik_ch_current_order[0][advik_current+3] << 8);
					break;
				//if change timbre
				case 0x09:
					REG_SND1CNT = (advik_current_square_instruments[advik_ch_current_order[0][advik_current+1]] & 0xff00) | advik_ch_current_order[0][advik_current+3];
					break;
				//if change order
				case 0x0b:
					advik_global_order_number = (advik_ch_current_order[0][advik_current+3] * advik_global_channels);
					advik_future = 0;
					advik_change_order = 1;
					break;
				//if set volume
				case 0x0c:
					REG_SND1CNT = (advik_current_square_instruments[advik_ch_current_order[0][advik_current+1]] & 0x00ff) | (advik_ch_current_order[0][advik_current+3] << 8);
					break;
				//if pattern break
				case 0x0d:
					if (advik_global_order_number < ((advik_global_order_length - 1) * advik_global_channels))
						advik_global_order_number += advik_global_channels;
					else
						advik_global_order_number = (advik_loop_point * advik_global_channels);
					
					advik_future = advik_ch_current_order[0][advik_current+3];
					advik_change_order = 1;
					break;
				//if note cut
				case 0x0e:
					advik_ch1_cut_delay_enabled = 1;
					advik_ch1_delay_ticks_counter = advik_ch_current_order[0][advik_current+3] - 1;
					break;
				//if set tempo
				case 0x0f:
					advik_ticks_per_row_value = advik_ch_current_order[0][advik_current+3] - 1;
					break;
				//if set furnace panning
				case 0x80:
					REG_SNDDMGCNT = (REG_SNDDMGCNT & 0xeeff) | ((advik_ch_current_order[0][advik_current+3] & 0x01) << 8) | ((advik_ch_current_order[0][advik_current+3] & 0x10) << 12);
			}
		}
		
		//check current effect and value for channel 2
		if (advik_global_channels > 1){
			switch (advik_ch_current_order[1][advik_current+2]) {
				//if arpeggio
				case 0x00:
					if (advik_ch_current_order[1][advik_current+3] > 0) {
						advik_ch2_arp_enabled = 1;
					} else if (advik_ch_current_order[1][advik_current+3] == 0 && advik_global_command_linger) {
						advik_ch2_arp_enabled = 0;
					}
					break;
				//if portamento up
				case 0x01:
					if (advik_ch_current_order[1][advik_current+3] > 0) {
						advik_ch2_portamento_direction = 1;
						if (advik_ch_current_order[1][advik_current] < 0xf0) {
							advik_ch2_portamento_freq = snd_freqs[advik_ch_current_order[1][advik_current]];
						} else if (advik_ch_current_order[1][advik_current] == 0xfe) {
							advik_ch2_portamento_freq = advik_ch2_previous_freq;
						}
					} else if (advik_ch_current_order[1][advik_current+3] == 0 && advik_global_command_linger) {
						advik_ch2_portamento_direction = 0;
					}
					break;
				//if portamento down
				case 0x02:
					if (advik_ch_current_order[1][advik_current+3] > 0) {
						advik_ch2_portamento_direction = 2;
						if (advik_ch_current_order[1][advik_current] < 0xf0) {
							advik_ch2_portamento_freq = snd_freqs[advik_ch_current_order[1][advik_current]];
						} else if (advik_ch_current_order[1][advik_current] == 0xfe) {
							advik_ch2_portamento_freq = advik_ch2_previous_freq;
						}
					} else if (advik_ch_current_order[1][advik_current+3] == 0 && advik_global_command_linger) {
						advik_ch2_portamento_direction = 0;
					}
					break;
				//if tone portamento
				case 0x03:
					if (advik_ch_current_order[1][advik_current+3] > 0) {
						advik_ch2_portamento_direction = 3;
						advik_ch2_portamento_freq = advik_ch2_previous_freq;
						if (advik_ch_current_order[1][advik_current] < 0xf0) {
							advik_ch2_portamento_freq_goal = snd_freqs[advik_ch_current_order[1][advik_current]];
						}
					} else if (advik_ch_current_order[1][advik_current+3] == 0 && advik_global_command_linger) {
						advik_ch2_portamento_direction = 0;
					}
					break;
				//if vibrato
				case 0x04:
					advik_ch2_vib_depth = advik_ch_current_order[1][advik_current+3] & 0x0f;
					advik_ch2_vib_enabled = 1;
					if (advik_ch_current_order[1][advik_current+3] == 0 && advik_global_command_linger) {
						advik_ch2_vib_enabled = 0;
						if (advik_ch2_held_note > 0) {
							REG_SND2FREQ = advik_ch2_held_note;
							advik_ch2_held_note = 0;
						}
					}
					break;
				//if set master volume
				case 0x05:
					REG_SNDDMGCNT = (REG_SNDDMGCNT & 0xff00) | advik_ch_current_order[1][advik_current+3];
					break;
				//if note delay
				case 0x07:
					advik_ch2_delay_enabled = 1;
					advik_ch2_delay_ticks_counter = advik_ch_current_order[1][advik_current+3] - 1;
					break;
				//if set global panning
				case 0x08:
					REG_SNDDMGCNT = (REG_SNDDMGCNT & 0x00ff) | (advik_ch_current_order[1][advik_current+3] << 8);
					break;
				//if change timbre
				case 0x09:
					REG_SND2CNT = (advik_current_square_instruments[advik_ch_current_order[1][advik_current+1]] & 0xff00) | advik_ch_current_order[1][advik_current+3];
					break;
				//if change order
				case 0x0b:
					advik_global_order_number = (advik_ch_current_order[1][advik_current+3] * advik_global_channels);
					advik_future = 0;
					advik_change_order = 1;
					break;
				//if set volume
				case 0x0c:
					REG_SND2CNT = (advik_current_square_instruments[advik_ch_current_order[1][advik_current+1]] & 0x00ff) | (advik_ch_current_order[1][advik_current+3] << 8);
					break;
				//if pattern break
				case 0x0d:
					if (advik_global_order_number < ((advik_global_order_length - 1) * advik_global_channels))
						advik_global_order_number += advik_global_channels;
					else
						advik_global_order_number = (advik_loop_point * advik_global_channels);
					
					advik_future = advik_ch_current_order[1][advik_current+3];
					advik_change_order = 1;
					break;
				//if note cut
				case 0x0e:
					advik_ch2_cut_delay_enabled = 1;
					advik_ch2_delay_ticks_counter = advik_ch_current_order[1][advik_current+3] - 1;
					break;
				//if set tempo
				case 0x0f:
					advik_ticks_per_row_value = advik_ch_current_order[1][advik_current+3]-1;
					break;
				//if set furnace panning
				case 0x80:
					REG_SNDDMGCNT = (REG_SNDDMGCNT & 0xddff) | ((advik_ch_current_order[1][advik_current+3] & 0x01) << 9) | ((advik_ch_current_order[1][advik_current+3] & 0x10) << 13);
			}
		}
		
		//check current effect and value for channel 3
		if (advik_global_channels > 2){
			switch (advik_ch_current_order[2][advik_current+2]) {
				//if arpeggio
				case 0x00:
					if (advik_ch_current_order[2][advik_current+3] > 0) {
						advik_ch3_arp_enabled = 1;
					} else if (advik_ch_current_order[2][advik_current+3] == 0 && advik_global_command_linger) {
						advik_ch3_arp_enabled = 0;
					}
					break;
				//if portamento up
				case 0x01:
					if (advik_ch_current_order[2][advik_current+3] > 0) {
						advik_ch3_portamento_direction = 1;
						if (advik_ch_current_order[2][advik_current] < 0xf0) {
							advik_ch3_portamento_freq = snd_freqs[advik_ch_current_order[2][advik_current]];
						} else if (advik_ch_current_order[2][advik_current] == 0xfe) {
							advik_ch3_portamento_freq = advik_ch3_previous_freq;
						}
					} else if (advik_ch_current_order[2][advik_current+3] == 0 && advik_global_command_linger) {
						advik_ch3_portamento_direction = 0;
					}
					break;
				//if portamento down
				case 0x02:
					if (advik_ch_current_order[2][advik_current+3] > 0) {
						advik_ch3_portamento_direction = 2;
						if (advik_ch_current_order[2][advik_current] < 0xf0) {
							advik_ch3_portamento_freq = snd_freqs[advik_ch_current_order[2][advik_current]];
						} else if (advik_ch_current_order[2][advik_current] == 0xfe) {
							advik_ch3_portamento_freq = advik_ch3_previous_freq;
						}
					} else if (advik_ch_current_order[2][advik_current+3] == 0 && advik_global_command_linger) {
						advik_ch3_portamento_direction = 0;
					}
					break;
				//if tone portamento
				case 0x03:
					if (advik_ch_current_order[2][advik_current+3] > 0) {
						advik_ch3_portamento_direction = 3;
						advik_ch3_portamento_freq = advik_ch3_previous_freq;
						if (advik_ch_current_order[2][advik_current] < 0xf0) {
							advik_ch3_portamento_freq_goal = snd_freqs[advik_ch_current_order[2][advik_current]];
						}
					} else if (advik_ch_current_order[2][advik_current+3] == 0 && advik_global_command_linger) {
						advik_ch3_portamento_direction = 0;
					}
					break;
				//if vibrato
				case 0x04:
					advik_ch3_vib_depth = advik_ch_current_order[2][advik_current+3] & 0x0f;
					advik_ch3_vib_enabled = 1;
					if (advik_ch_current_order[2][advik_current+3] == 0 && advik_global_command_linger) {
						advik_ch3_vib_enabled = 0;
						if (advik_ch3_held_note > 0) {
							REG_SND3FREQ = advik_ch3_held_note;
							advik_ch3_held_note = 0;
						}
					}
					break;
				//if set master volume
				case 0x05:
					REG_SNDDMGCNT = (REG_SNDDMGCNT & 0xff00) | advik_ch_current_order[2][advik_current+3];
					break;
				//if note delay
				case 0x07:
					advik_ch3_delay_enabled = 1;
					advik_ch3_delay_ticks_counter = advik_ch_current_order[2][advik_current+3] - 1;
					break;
				//if set global panning
				case 0x08:
					REG_SNDDMGCNT = (REG_SNDDMGCNT & 0x00ff) | (advik_ch_current_order[2][advik_current+3] << 8);
					break;
				//if change timbre
				case 0x09:
					//copy channel 3 waveform over
					REG_SND3SEL = 0;
					memcpy((void *)REG_WAVE_RAM, advik_current_waveforms[advik_ch_current_order[2][advik_current+3] - 1], 16);
					REG_SND3SEL = 0xC0;
					break;
				//if change order
				case 0x0b:
					advik_global_order_number = (advik_ch_current_order[2][advik_current+3] * advik_global_channels);
					advik_future = 0;
					advik_change_order = 1;
					break;
				//if set volume
				case 0x0c:
					REG_SND3CNT = (advik_ch_current_order[2][advik_current+3] << 8);
					break;
				//if pattern break
				case 0x0d:
					if (advik_global_order_number < ((advik_global_order_length - 1) * advik_global_channels))
						advik_global_order_number += advik_global_channels;
					else
						advik_global_order_number = (advik_loop_point * advik_global_channels);
					
					advik_future = advik_ch_current_order[2][advik_current+3];
					advik_change_order = 1;
					break;
				//if note cut
				case 0x0e:
					advik_ch3_cut_delay_enabled = 1;
					advik_ch3_delay_ticks_counter = advik_ch_current_order[2][advik_current+3] - 1;
					break;
				//if set tempo
				case 0x0f:
					advik_ticks_per_row_value = advik_ch_current_order[2][advik_current+3]-1;
					break;
				//if set furnace panning
				case 0x80:
					REG_SNDDMGCNT = (REG_SNDDMGCNT & 0xbbff) | ((advik_ch_current_order[2][advik_current+3] & 0x01) << 10) | ((advik_ch_current_order[2][advik_current+3] & 0x10) << 14);
			}
		}
		//check current effect and value for channel 4
		if (advik_global_channels > 3){
			switch (advik_ch_current_order[3][advik_current+2]) {
				//if arpeggio
				// case 0x00:
					// if (advik_ch_current_order[3][advik_current+3] > 0) {
						// advik_ch4_arp_enabled = 1;
					// }
					// break;
				//if vibrato
				// case 0x04:
					// advik_ch4_vib_enabled = 1;
					// break;
				//if set master volume
				case 0x05:
					REG_SNDDMGCNT = (REG_SNDDMGCNT & 0xff00) | advik_ch_current_order[3][advik_current+3];
					break;
				//if note delay
				case 0x07:
					advik_ch4_delay_enabled = 1;
					advik_ch4_delay_ticks_counter = advik_ch_current_order[3][advik_current+3] - 1;
					break;
				//if set global panning
				case 0x08:
					REG_SNDDMGCNT = (REG_SNDDMGCNT & 0x00ff) | (advik_ch_current_order[3][advik_current+3] << 8);
					break;
				//if change timbre
				 // case 0x09:
					// REG_SND4CNT = (advik_current_noise_instruments[advik_ch_current_order[3][advik_current+1]] & 0xff00) | advik_ch_current_order[3][advik_current+3];
					// break;
				//if change order
				case 0x0b:
					advik_global_order_number = (advik_ch_current_order[3][advik_current+3] * advik_global_channels);
					advik_future = 0;
					advik_change_order = 1;
					break;
				//if set volume
				case 0x0c:
					REG_SND4CNT = (advik_ch_current_order[3][advik_current+3] << 8);
					break;
				//if pattern break
				case 0x0d:
					if (advik_global_order_number < ((advik_global_order_length - 1) * advik_global_channels))
						advik_global_order_number += advik_global_channels;
					else
						advik_global_order_number = (advik_loop_point * advik_global_channels);
					
					advik_future = advik_ch_current_order[3][advik_current+3];
					advik_change_order = 1;
					break;
				//if note cut
				case 0x0e:
					advik_ch4_cut_delay_enabled = 1;
					advik_ch4_delay_ticks_counter = advik_ch_current_order[3][advik_current+3] - 1;
					break;
				//if set tempo
				case 0x0f:
					advik_ticks_per_row_value = advik_ch_current_order[3][advik_current+3]-1;
					break;
				//if set furnace panning
				case 0x80:
					REG_SNDDMGCNT = (REG_SNDDMGCNT & 0x77ff) | ((advik_ch_current_order[3][advik_current+3] & 0x01) << 11) | ((advik_ch_current_order[3][advik_current+3] & 0x10) << 15);
			}
		}
		
		//check current effect and value for channel 5
		if (advik_global_channels > 4){
			switch (advik_ch_current_order[4][advik_current+2]) {
				//if arpeggio
				case 0x00:
					if (advik_ch_current_order[4][advik_current+3] > 0) {
						advik_ch5_arp_enabled = 1;
					} else if (advik_ch_current_order[4][advik_current+3] == 0 && advik_global_command_linger) {
						advik_ch5_arp_enabled = 0;
					}
					break;
				//if portamento up
				case 0x01:
					if (advik_ch_current_order[4][advik_current+3] > 0) {
						advik_ch5_portamento_direction = 1;
						if (advik_ch_current_order[4][advik_current] < 0xf0) {
							advik_ch5_portamento_freq = dma_snd_freqs[advik_ch_current_order[4][advik_current]];
						} else if (advik_ch_current_order[4][advik_current] == 0xfe) {
							advik_ch5_portamento_freq = advik_ch5_previous_freq;
						}
					} else if (advik_ch_current_order[4][advik_current+3] == 0 && advik_global_command_linger) {
						advik_ch5_portamento_direction = 0;
					}
					break;
				//if portamento down
				case 0x02:
					if (advik_ch_current_order[4][advik_current+3] > 0) {
						advik_ch5_portamento_direction = 2;
						if (advik_ch_current_order[4][advik_current] < 0xf0) {
							advik_ch5_portamento_freq = dma_snd_freqs[advik_ch_current_order[4][advik_current]];
						} else if (advik_ch_current_order[4][advik_current] == 0xfe) {
							advik_ch5_portamento_freq = advik_ch5_previous_freq;
						}
					} else if (advik_ch_current_order[4][advik_current+3] == 0 && advik_global_command_linger) {
						advik_ch5_portamento_direction = 0;
					}
					break;
				//if tone portamento
				case 0x03:
					if (advik_ch_current_order[4][advik_current+3] > 0) {
						advik_ch5_portamento_direction = 3;
						advik_ch5_portamento_freq = advik_ch5_previous_freq;
						if (advik_ch_current_order[4][advik_current] < 0xf0) {
							advik_ch5_portamento_freq_goal = dma_snd_freqs[advik_ch_current_order[4][advik_current]];
						}
					} else if (advik_ch_current_order[4][advik_current+3] == 0 && advik_global_command_linger) {
						advik_ch5_portamento_direction = 0;
					}
					break;
				//if vibrato
				case 0x04:
					advik_ch5_vib_depth = advik_ch_current_order[4][advik_current+3] & 0x0f;
					advik_ch5_vib_enabled = 1;
					if (advik_ch_current_order[4][advik_current+3] == 0 && advik_global_command_linger) {
						advik_ch5_vib_enabled = 0;
						if (advik_ch5_held_note > 0) {
							REG_TM0D = advik_ch5_held_note;
							advik_ch5_held_note = 0;
						}
					}
					break;
				//if set master volume
				case 0x05:
					REG_SNDDSCNT = (REG_SNDDSCNT & 0xfff3) | advik_ch_current_order[4][advik_current+3];
					break;
				//if note delay
				case 0x07:
					advik_ch5_delay_enabled = 1;
					advik_ch5_delay_ticks_counter = advik_ch_current_order[4][advik_current+3] - 1;
					break;
				//if set global panning
				case 0x08:
					REG_SNDDSCNT = (REG_SNDDSCNT & 0x00ff) | (advik_ch_current_order[4][advik_current+3] << 8);
					break;
				//if change timbre
				// case 0x09:
					// REG_SND1CNT = (advik_current_square_instruments[advik_ch_current_order[0][advik_current+1]] & 0xff00) | advik_ch_current_order[0][advik_current+3];
					// break;
				//if change order
				case 0x0b:
					advik_global_order_number = (advik_ch_current_order[4][advik_current+3] * advik_global_channels);
					advik_future = 0;
					advik_change_order = 1;
					break;
				//if set volume
				case 0x0c:
					REG_SNDDSCNT = (REG_SNDDSCNT & 0xfffb) | ((advik_ch_current_order[4][advik_current+3] & 1) << 2);
					break;
				//if pattern break
				case 0x0d:
					if (advik_global_order_number < ((advik_global_order_length - 1) * advik_global_channels))
						advik_global_order_number += advik_global_channels;
					else
						advik_global_order_number = (advik_loop_point * advik_global_channels);
					
					advik_future = advik_ch_current_order[4][advik_current+3];
					advik_change_order = 1;
					break;
				//if note cut
				case 0x0e:
					advik_ch5_cut_delay_enabled = 1;
					advik_ch5_delay_ticks_counter = advik_ch_current_order[4][advik_current+3] - 1;
					break;
				//if set tempo
				case 0x0f:
					advik_ticks_per_row_value = advik_ch_current_order[4][advik_current+3]-1;
					break;
				//if set furnace panning
				case 0x80:
					REG_SNDDSCNT = (REG_SNDDSCNT & 0xeeff) | ((advik_ch_current_order[4][advik_current+3] & 0x01) << 8) | ((advik_ch_current_order[4][advik_current+3] & 0x10) << 12);
			}
		}
		
		//check current effect and value for channel 6
		if (advik_global_channels > 5){
			switch (advik_ch_current_order[5][advik_current+2]) {
				//if arpeggio
				case 0x00:
					if (advik_ch_current_order[5][advik_current+3] > 0) {
						advik_ch6_arp_enabled = 1;
					} else if (advik_ch_current_order[5][advik_current+3] == 0 && advik_global_command_linger) {
						advik_ch6_arp_enabled = 0;
					}
					break;
				//if portamento up
				case 0x01:
					if (advik_ch_current_order[5][advik_current+3] > 0) {
						advik_ch6_portamento_direction = 1;
						if (advik_ch_current_order[5][advik_current] < 0xf0) {
							advik_ch6_portamento_freq = dma_snd_freqs[advik_ch_current_order[5][advik_current]];
						} else if (advik_ch_current_order[5][advik_current] == 0xfe) {
							advik_ch6_portamento_freq = advik_ch6_previous_freq;
						}
					} else if (advik_ch_current_order[5][advik_current+3] == 0 && advik_global_command_linger) {
						advik_ch6_portamento_direction = 0;
					}
					break;
				//if portamento down
				case 0x02:
					if (advik_ch_current_order[5][advik_current+3] > 0) {
						advik_ch6_portamento_direction = 2;
						if (advik_ch_current_order[5][advik_current] < 0xf0) {
							advik_ch6_portamento_freq = dma_snd_freqs[advik_ch_current_order[5][advik_current]];
						} else if (advik_ch_current_order[5][advik_current] == 0xfe) {
							advik_ch6_portamento_freq = advik_ch6_previous_freq;
						}
					} else if (advik_ch_current_order[5][advik_current+3] == 0 && advik_global_command_linger) {
						advik_ch6_portamento_direction = 0;
					}
					break;
				//if tone portamento
				case 0x03:
					if (advik_ch_current_order[5][advik_current+3] > 0) {
						advik_ch6_portamento_direction = 3;
						advik_ch6_portamento_freq = advik_ch6_previous_freq;
						if (advik_ch_current_order[5][advik_current] < 0xf0) {
							advik_ch6_portamento_freq_goal = dma_snd_freqs[advik_ch_current_order[5][advik_current]];
						}
					} else if (advik_ch_current_order[5][advik_current+3] == 0 && advik_global_command_linger) {
						advik_ch6_portamento_direction = 0;
					}
					break;
				//if vibrato
				case 0x04:
					advik_ch6_vib_depth = advik_ch_current_order[5][advik_current+3] & 0x0f;
					advik_ch6_vib_enabled = 1;
					if (advik_ch_current_order[5][advik_current+3] == 0 && advik_global_command_linger) {
						advik_ch6_vib_enabled = 0;
						if (advik_ch6_held_note > 0) {
							REG_TM1D = advik_ch6_held_note;
							advik_ch6_held_note = 0;
						}
					}
					break;
				//if set master volume
				case 0x05:
					REG_SNDDSCNT = (REG_SNDDSCNT & 0xfff3) | advik_ch_current_order[5][advik_current+3];
					break;
				//if note delay
				case 0x07:
					advik_ch6_delay_enabled = 1;
					advik_ch6_delay_ticks_counter = advik_ch_current_order[5][advik_current+3] - 1;
					break;
				//if set global panning
				case 0x08:
					REG_SNDDSCNT = (REG_SNDDSCNT & 0x00ff) | (advik_ch_current_order[5][advik_current+3] << 8);
					break;
				//if change timbre
				// case 0x09:
					// REG_SND1CNT = (advik_current_square_instruments[advik_ch_current_order[0][advik_current+1]] & 0xff00) | advik_ch_current_order[0][advik_current+3];
					// break;
				//if change order
				case 0x0b:
					advik_global_order_number = (advik_ch_current_order[5][advik_current+3] * advik_global_channels);
					advik_future = 0;
					advik_change_order = 1;
					break;
				//if set volume
				case 0x0c:
					REG_SNDDSCNT = (REG_SNDDSCNT & 0xfff7) | ((advik_ch_current_order[5][advik_current+3] & 1) << 3);
					break;
				//if pattern break
				case 0x0d:
					if (advik_global_order_number < ((advik_global_order_length - 1) * advik_global_channels))
						advik_global_order_number += advik_global_channels;
					else
						advik_global_order_number = (advik_loop_point * advik_global_channels);
					
					advik_future = advik_ch_current_order[5][advik_current+3];
					advik_change_order = 1;
					break;
				//if note cut
				case 0x0e:
					advik_ch6_cut_delay_enabled = 1;
					advik_ch6_delay_ticks_counter = advik_ch_current_order[5][advik_current+3] - 1;
					break;
				//if set tempo
				case 0x0f:
					advik_ticks_per_row_value = advik_ch_current_order[5][advik_current+3]-1;
					break;
				//if set furnace panning
				case 0x80:
					REG_SNDDSCNT = (REG_SNDDSCNT & 0xddff) | ((advik_ch_current_order[5][advik_current+3] & 0x01) << 9) | ((advik_ch_current_order[5][advik_current+3] & 0x10) << 13);
			}
		}
		
		if (!advik_ch_sfx_override[0]){
			//check if notes are in range and there's no note delay for channel 1
			if (advik_global_channels){
				if (advik_ch_current_order[0][advik_current] < 0xf0 && !advik_ch1_delay_enabled) {
					//if instrument isn't 0, retrigger note
					if (advik_ch_current_order[0][advik_current+1] > 0x00){
						REG_SND1CNT = advik_current_square_instruments[advik_ch_current_order[0][advik_current+1] - 1];
					}
					advik_ch1_held_note = 0;
					if ((advik_current_square_instruments[advik_ch_current_order[0][advik_current+1] - 1] & SSQR_LEN_MASK))
						REG_SND1FREQ = SFREQ_RESET | snd_freqs[advik_ch_current_order[0][advik_current]] | SFREQ_TIMED;
					else
						REG_SND1FREQ = SFREQ_RESET | snd_freqs[advik_ch_current_order[0][advik_current]];
					advik_ch1_previous_freq = snd_freqs[advik_ch_current_order[0][advik_current]];
				} else if (advik_ch_current_order[0][advik_current] == 0xfe) {
					//make sure held note is saved
					if (advik_ch1_held_note == 0) {
						advik_ch1_held_note = advik_ch1_previous_freq;
					}
				}
			}
		}		
		
		if (!advik_ch_sfx_override[1]){
			//check if notes are in range and there's no note delay for channel 2
			if (advik_global_channels > 1){
				if (advik_ch_current_order[1][advik_current] < 0xf0 && !advik_ch2_delay_enabled) {
					//if instrument isn't 0, retrigger note
					if (advik_ch_current_order[1][advik_current+1] > 0x00){
						REG_SND2CNT = advik_current_square_instruments[advik_ch_current_order[1][advik_current+1] - 1];
					}
					advik_ch2_held_note = 0;
					if ((advik_current_square_instruments[advik_ch_current_order[1][advik_current+1] - 1] & SSQR_LEN_MASK))
						REG_SND2FREQ = SFREQ_RESET | snd_freqs[advik_ch_current_order[1][advik_current]] | SFREQ_TIMED;
					else
						REG_SND2FREQ = SFREQ_RESET | snd_freqs[advik_ch_current_order[1][advik_current]];
					advik_ch2_previous_freq = snd_freqs[advik_ch_current_order[1][advik_current]];
				} else if (advik_ch_current_order[1][advik_current] == 0xfe) {
					//make sure held note is saved
					if (advik_ch2_held_note == 0) {
						advik_ch2_held_note = advik_ch2_previous_freq;
					}
				}
			}
		}
		
		if (!advik_ch_sfx_override[2]){
			//check if notes are in range and there's no note delay for channel 3
			if (advik_global_channels > 2){
				if (advik_ch_current_order[2][advik_current] < 0xf0 && !advik_ch3_delay_enabled) {
					//if instrument isn't 0, retrigger note
					if (advik_ch_current_order[2][advik_current+1] > 0x00){
						REG_SND3CNT = 0x2000;
						//copy channel 3 waveform over
						REG_SND3SEL = 0;
						memcpy((void *)REG_WAVE_RAM, advik_current_waveforms[advik_ch_current_order[2][advik_current+1] - 1], 16);
						REG_SND3SEL = 0xC0;
					}
					advik_ch3_held_note = 0;
					if ((advik_current_wave_instruments[(advik_ch_current_order[2][advik_current+1] << 1)]) == SWAV_LEN_ON)
						REG_SND3FREQ = SFREQ_RESET | snd_freqs[advik_ch_current_order[2][advik_current]] | SFREQ_TIMED;
					else
						REG_SND3FREQ = SFREQ_RESET | snd_freqs[advik_ch_current_order[2][advik_current]];
					advik_ch3_previous_freq = snd_freqs[advik_ch_current_order[2][advik_current]];
				} else if (advik_ch_current_order[2][advik_current] == 0xfe) {
					//make sure held note is saved
					if (advik_ch3_held_note == 0) {
						advik_ch3_held_note = advik_ch3_previous_freq;
					}
				}
			}
		}
		
		if (!advik_ch_sfx_override[3]){
			//check if notes are in range and there's no note delay for channel 4
			if (advik_global_channels > 3){
				if (advik_ch_current_order[3][advik_current] < 0xf8 && !advik_ch4_delay_enabled) {
					//if instrument isn't 0, retrigger note
					if (advik_ch_current_order[3][advik_current+1] > 0x00){
						REG_SND4CNT = advik_current_noise_instruments[advik_ch_current_order[3][advik_current+1] - 1] & SNOI_EXCLUDE_PACK;
					}
					if ((advik_current_noise_instruments[advik_ch_current_order[3][advik_current+1] - 1] & SSQR_LEN_MASK))
						//Thanks to RichardULZ for this formula
						REG_SND4FREQ = SFREQ_RESET | (SNOI_POLYNOM(advik_ch_current_order[3][advik_current]) & SNOI_EXCLUDE_UNPACK) | (SNOI_UNPACK(advik_current_noise_instruments[advik_ch_current_order[3][advik_current] - 1] & SNOI_SHORT_PACK)) | SFREQ_TIMED;
					else
						REG_SND4FREQ = SFREQ_RESET | (SNOI_POLYNOM(advik_ch_current_order[3][advik_current]) & SNOI_EXCLUDE_UNPACK) | (SNOI_UNPACK(advik_current_noise_instruments[advik_ch_current_order[3][advik_current] - 1] & SNOI_SHORT_PACK));
				}
			}
		}
		
		if (!advik_ch_sfx_override[4]){
		//check if notes are in range and there's no note delay for channel 5
			if (advik_global_channels > 4){
				if (advik_ch_current_order[4][advik_current] < 0xf0 && !advik_ch5_delay_enabled) {
					//if instrument isn't 0, retrigger note
					if (advik_ch_current_order[4][advik_current+1] > 0x00){
						REG_DMA1CNT = 0;
						//set DMA transfer to DAC 1 FIFO
						REG_DMA1SAD = (uint32_t)advik_current_dma_instruments[advik_ch_current_order[4][advik_current+1] - 1];
						REG_DMA1DAD = (uint32_t)&REG_FIFO_A;
						REG_DMA1CNT = DMA_DST_FIXED | DMA_REPEAT | DMA_32 | DMA_AT_REFRESH | DMA_ENABLE;
						
						advik_ch5_sample_duration = advik_current_dma_durations[advik_ch_current_order[4][advik_current+1] - 1];
					}
					advik_ch5_held_note = 0;
					//set timer 0
					REG_TM0D = dma_snd_freqs[advik_ch_current_order[4][advik_current]];
					REG_TM0CNT = TM_ENABLE;
					advik_ch5_previous_freq = dma_snd_freqs[advik_ch_current_order[4][advik_current]];
				} else if (advik_ch_current_order[4][advik_current] == 0xfe) {
					//make sure held note is saved
					if (advik_ch5_held_note == 0) {
						advik_ch5_held_note = advik_ch5_previous_freq;
					}
				}
			}
		}
		
		if (!advik_ch_sfx_override[5]){
			//check if notes are in range and there's no note delay for channel 6
			if (advik_global_channels > 5){
				if (advik_ch_current_order[5][advik_current] < 0xf0 && !advik_ch6_delay_enabled) {
					//if instrument isn't 0, retrigger note
					if (advik_ch_current_order[5][advik_current+1] > 0x00){
						REG_DMA2CNT = 0;
						//set DMA transfer to DAC 2 FIFO
						REG_DMA2SAD = (uint32_t)advik_current_dma_instruments[advik_ch_current_order[5][advik_current+1] - 1];
						REG_DMA2DAD = (uint32_t)&REG_FIFO_B;
						REG_DMA2CNT = DMA_DST_FIXED | DMA_REPEAT | DMA_32 | DMA_AT_REFRESH | DMA_ENABLE;
						
						advik_ch6_sample_duration = advik_current_dma_durations[advik_ch_current_order[5][advik_current+1] - 1];
					}
					advik_ch6_held_note = 0;
					//set timer 1
					REG_TM1D = dma_snd_freqs[advik_ch_current_order[5][advik_current]];
					REG_TM1CNT = TM_ENABLE;
					advik_ch6_previous_freq = dma_snd_freqs[advik_ch_current_order[5][advik_current]];
				} else if (advik_ch_current_order[5][advik_current] == 0xfe) {
					//make sure held note is saved
					if (advik_ch6_held_note == 0) {
						advik_ch6_held_note = advik_ch6_previous_freq;
					}
				}
			}
		}
		advik_current += 4;
		advik_ticks_per_row_counter = advik_ticks_per_row_value;
		advik_arp_tick = 0;
	}
	
	if(advik_ch_sfx_override[0]){
		cell_sfx_ch1_play();
	}
	if(advik_ch_sfx_override[1]){
		cell_sfx_ch2_play();
	}
	if(advik_ch_sfx_override[2]){
		cell_sfx_ch3_play();
	}
	if(advik_ch_sfx_override[3]){
		cell_sfx_ch4_play();
	}
	if(advik_ch_sfx_override[4]){
		cell_sfx_ch5_play();
	}
	if(advik_ch_sfx_override[5]){
		cell_sfx_ch6_play();
	}
}