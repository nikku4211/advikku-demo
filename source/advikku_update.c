#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "advikku_global.h"
#include "advikku_update.h"

void cell_song_play() {
	if (advik_ticks_per_row_counter > 0) {
		
		advik_ticks_per_row_counter--;
		advik_arp_tick++;
		advik_arp_index = advik_arp_tick % 3;
		//channel 1
		if (advik_ch1_delay_enabled > 0) {
			if (advik_ch1_delay_ticks_counter > 0) {
				advik_ch1_delay_ticks_counter--;
			} else {
				if (advik_ch1_current_order[advik_current-3] > 0x00){
					REG_SND1CNT = advik_current_square_instruments[advik_ch1_current_order[advik_current-3] - 1];
				}
				REG_SND1FREQ = SFREQ_RESET | snd_freqs[advik_ch1_current_order[advik_current-4]];
				advik_ch1_delay_enabled = 0;
			}
		} else if (advik_ch1_portamento_direction == 1) {
			advik_ch1_portamento_freq += advik_ch1_current_order[advik_current-1];
			REG_SND1FREQ = advik_ch1_portamento_freq;
			advik_ch1_previous_freq = advik_ch1_portamento_freq;
		} else if (advik_ch1_portamento_direction == 2) {
			advik_ch1_portamento_freq -= advik_ch1_current_order[advik_current-1];
			REG_SND1FREQ = advik_ch1_portamento_freq;
			advik_ch1_previous_freq = advik_ch1_portamento_freq;
		} else if (advik_ch1_portamento_direction == 3) {
			if (advik_ch1_portamento_freq > advik_ch1_portamento_freq_goal){
				advik_ch1_portamento_freq -= advik_ch1_current_order[advik_current-1];
			} else if (advik_ch1_portamento_freq < advik_ch1_portamento_freq_goal){
				advik_ch1_portamento_freq += advik_ch1_current_order[advik_current-1];
			}
			REG_SND1FREQ = advik_ch1_portamento_freq;
			advik_ch1_previous_freq = advik_ch1_portamento_freq;
		} else if (advik_ch1_cut_delay_enabled > 1) {
			if (advik_ch1_delay_ticks_counter > 0) {
				advik_ch1_delay_ticks_counter--;
			} else {
				REG_SND1CNT = 0;
				advik_ch1_cut_delay_enabled = 0;
			}
		} else if (advik_ch1_arp_enabled > 0) {
			switch (advik_arp_index) {
				case 1:
					REG_SND1FREQ = (snd_freqs[advik_ch1_current_order[advik_current-4] + (advik_ch1_current_order[advik_current-1] >> 4)]);
					break;
				case 2:
					REG_SND1FREQ = (snd_freqs[advik_ch1_current_order[advik_current-4] + (advik_ch1_current_order[advik_current-1] & 0x0f)]);
					break;
				default:
					REG_SND1FREQ = (snd_freqs[advik_ch1_current_order[advik_current-4]]);
			}
		} else if (advik_ch1_vib_enabled > 0) {
			advik_ch1_vib_ticks_counter += advik_ch1_current_order[advik_current-1] >> 4;
			advik_ch1_vib_position = advik_ch1_vib_ticks_counter & 63;
			REG_SND1FREQ = (snd_freqs[advik_ch1_current_order[advik_current-4]] - ((vib_table[advik_ch1_vib_position] * (advik_ch1_current_order[advik_current-1] & 0x0f)) >> 5));
		}
		//channel 2
		if (advik_ch2_delay_enabled > 0) {
			if (advik_ch2_delay_ticks_counter > 0) {
				advik_ch2_delay_ticks_counter--;
			} else {
				if (advik_ch2_current_order[advik_current-3] > 0x00){
					REG_SND2CNT = advik_current_square_instruments[advik_ch2_current_order[advik_current-3] - 1];
				}
				REG_SND2FREQ = SFREQ_RESET | snd_freqs[advik_ch2_current_order[advik_current-4]];
				advik_ch2_delay_enabled = 0;
			}
		} else if (advik_ch2_portamento_direction == 1) {
			advik_ch2_portamento_freq += advik_ch2_current_order[advik_current-1];
			REG_SND2FREQ = advik_ch2_portamento_freq;
			advik_ch2_previous_freq = advik_ch2_portamento_freq;
		} else if (advik_ch2_portamento_direction == 2) {
			advik_ch2_portamento_freq -= advik_ch2_current_order[advik_current-1];
			REG_SND2FREQ = advik_ch2_portamento_freq;
			advik_ch2_previous_freq = advik_ch2_portamento_freq;
		}  else if (advik_ch2_cut_delay_enabled > 1) {
			if (advik_ch2_delay_ticks_counter > 0) {
				advik_ch2_delay_ticks_counter--;
			} else {
				REG_SND2CNT = 0;
				advik_ch2_cut_delay_enabled = 0;
			}
		} else if (advik_ch2_arp_enabled > 0) {
			switch (advik_arp_index) {
				case 1:
					REG_SND2FREQ = (snd_freqs[advik_ch2_current_order[advik_current-4] + (advik_ch2_current_order[advik_current-1] >> 4)]);
					break;
				case 2:
					REG_SND2FREQ = (snd_freqs[advik_ch2_current_order[advik_current-4] + (advik_ch2_current_order[advik_current-1] & 0x0f)]);
					break;
				default:
					REG_SND2FREQ = (snd_freqs[advik_ch2_current_order[advik_current-4]]);
			}
		} else if (advik_ch2_vib_enabled > 0) {
			advik_ch2_vib_ticks_counter += advik_ch2_current_order[advik_current-1] >> 4;
			advik_ch2_vib_position = advik_ch2_vib_ticks_counter & 63;
			REG_SND2FREQ = (snd_freqs[advik_ch2_current_order[advik_current-4]] - ((vib_table[advik_ch2_vib_position] * (advik_ch2_current_order[advik_current-1] & 0x0f)) >> 5));
		}
		//channel 3
		if (advik_ch3_delay_enabled > 0) {
			if (advik_ch3_delay_ticks_counter > 0) {
				advik_ch3_delay_ticks_counter--;
			} else {
				REG_SND3FREQ = SFREQ_RESET | snd_freqs[advik_ch3_current_order[advik_current-4]];
				advik_ch3_delay_enabled = 0;
			}
		} else if (advik_ch3_portamento_direction == 1) {
			advik_ch3_portamento_freq += advik_ch3_current_order[advik_current-1];
			REG_SND3FREQ = advik_ch3_portamento_freq;
			advik_ch3_previous_freq = advik_ch3_portamento_freq;
		} else if (advik_ch3_portamento_direction == 2) {
			advik_ch3_portamento_freq -= advik_ch3_current_order[advik_current-1];
			REG_SND3FREQ = advik_ch3_portamento_freq;
			advik_ch3_previous_freq = advik_ch3_portamento_freq;
		}  else if (advik_ch3_cut_delay_enabled > 1) {
			if (advik_ch3_delay_ticks_counter > 0) {
				advik_ch3_delay_ticks_counter--;
			} else {
				REG_SND3CNT = 0;
				advik_ch3_cut_delay_enabled = 0;
			}
		} else if (advik_ch3_arp_enabled > 0) {
			switch (advik_arp_index) {
				case 1:
					REG_SND3FREQ = (snd_freqs[advik_ch3_current_order[advik_current-4] + (advik_ch3_current_order[advik_current-1] >> 4)]);
					break;
				case 2:
					REG_SND3FREQ = (snd_freqs[advik_ch3_current_order[advik_current-4] + (advik_ch3_current_order[advik_current-1] & 0x0f)]);
					break;
				default:
					REG_SND3FREQ = (snd_freqs[advik_ch3_current_order[advik_current-4]]);
			}
		} else if (advik_ch3_vib_enabled > 0) {
			advik_ch3_vib_ticks_counter += advik_ch3_current_order[advik_current-1] >> 4;
			advik_ch3_vib_position = advik_ch3_vib_ticks_counter & 63;
			REG_SND3FREQ = (snd_freqs[advik_ch3_current_order[advik_current-4]] - ((vib_table[advik_ch3_vib_position] * (advik_ch3_current_order[advik_current-1] & 0x0f)) >> 5));
		}
		//channel 4
		if (advik_ch4_delay_enabled > 0) {
			if (advik_ch4_delay_ticks_counter > 0) {
				advik_ch4_delay_ticks_counter--;
			} else {
				if (advik_ch4_current_order[advik_current-3] > 0x00){
					REG_SND4CNT = advik_current_noise_instruments[advik_ch4_current_order[advik_current-3] - 1] & SNOI_EXCLUDE_PACK;
				}
				REG_SND4FREQ = SFREQ_RESET | advik_ch4_current_order[advik_current-4] | (SNOI_UNPACK(advik_current_noise_instruments[advik_ch4_current_order[advik_current-4] - 1] & SNOI_SHORT_PACK));
				advik_ch4_delay_enabled = 0;
			}
		} else if (advik_ch4_cut_delay_enabled > 1) {
			if (advik_ch4_delay_ticks_counter > 0) {
				advik_ch4_delay_ticks_counter--;
			} else {
				REG_SND4CNT = 0;
				advik_ch4_cut_delay_enabled = 0;
			}
		}
	} else {
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
		
		//if end of order is reached, loop
		if (advik_ch1_current_order[advik_current] == 0xff) {
			advik_current = advik_loop_point;
		}
		
		//check current effect and value for channel 1
		switch (advik_ch1_current_order[advik_current+2]) {
			//if arpeggio
			case 0x00:
				if (advik_ch1_current_order[advik_current+3] > 0) {
					advik_ch1_arp_enabled = 1;
				}
				break;
			//if portamento up
			case 0x01:
				if (advik_ch1_current_order[advik_current+3] > 0) {
					advik_ch1_portamento_direction = 1;
					if (advik_ch1_current_order[advik_current] < 0xf0) {
						advik_ch1_portamento_freq = snd_freqs[advik_ch1_current_order[advik_current]];
					} else if (advik_ch1_current_order[advik_current] == 0xfe) {
						advik_ch1_portamento_freq = advik_ch1_previous_freq;
					}
				}
				break;
			//if portamento down
			case 0x02:
				if (advik_ch1_current_order[advik_current+3] > 0) {
					advik_ch1_portamento_direction = 2;
					if (advik_ch1_current_order[advik_current] < 0xf0) {
						advik_ch1_portamento_freq = snd_freqs[advik_ch1_current_order[advik_current]];
					} else if (advik_ch1_current_order[advik_current] == 0xfe) {
						advik_ch1_portamento_freq = advik_ch1_previous_freq;
					}
				}
				break;
			//if tone portamento
			case 0x03:
				if (advik_ch1_current_order[advik_current+3] > 0) {
					advik_ch1_portamento_direction = 3;
					advik_ch1_portamento_freq = advik_ch1_previous_freq;
					if (advik_ch1_current_order[advik_current] < 0xf0) {
						advik_ch1_portamento_freq_goal = snd_freqs[advik_ch1_current_order[advik_current]];
					}
				}
				break;
			//if vibrato
			case 0x04:
				advik_ch1_vib_enabled = 1;
				break;
			//if set master volume
			case 0x05:
				REG_SNDDMGCNT = (REG_SNDDMGCNT & 0xff00) | advik_ch1_current_order[advik_current+3];
				break;
			//if note delay
			case 0x07:
				advik_ch1_delay_enabled = 1;
				advik_ch1_delay_ticks_counter = advik_ch1_current_order[advik_current+3] - 1;
				break;
			//if set global panning
			case 0x08:
				REG_SNDDMGCNT = (REG_SNDDMGCNT & 0x00ff) | (advik_ch1_current_order[advik_current+3] << 8);
				break;
			//if change timbre
			case 0x09:
				REG_SND1CNT = (advik_current_square_instruments[advik_ch1_current_order[advik_current+1]] & 0xff00) | advik_ch1_current_order[advik_current+3];
				break;
			//if set volume
			case 0x0c:
				REG_SND1CNT = (advik_current_square_instruments[advik_ch1_current_order[advik_current+1]] & 0x00ff) | (advik_ch1_current_order[advik_current+3] << 8);
				break;
			//if note cut
			case 0x0e:
				advik_ch1_cut_delay_enabled = 1;
				advik_ch1_delay_ticks_counter = advik_ch1_current_order[advik_current+3] - 1;
				break;
			//if set tempo
			case 0x0f:
				advik_ticks_per_row_value = advik_ch1_current_order[advik_current+3];
				break;
		}
		//check current effect and value for channel 2
		switch (advik_ch2_current_order[advik_current+2]) {
			//if arpeggio
			case 0x00:
				if (advik_ch2_current_order[advik_current+3] > 0) {
					advik_ch2_arp_enabled = 1;
				}
				break;
			//if portamento up
			case 0x01:
				if (advik_ch2_current_order[advik_current+3] > 0) {
					advik_ch2_portamento_direction = 1;
					if (advik_ch2_current_order[advik_current] < 0xf0) {
						advik_ch2_portamento_freq = snd_freqs[advik_ch2_current_order[advik_current]];
					} else if (advik_ch2_current_order[advik_current] == 0xfe) {
						advik_ch2_portamento_freq = advik_ch2_previous_freq;
					}
				}
				break;
			//if portamento down
			case 0x02:
				if (advik_ch2_current_order[advik_current+3] > 0) {
					advik_ch2_portamento_direction = 2;
					if (advik_ch2_current_order[advik_current] < 0xf0) {
						advik_ch2_portamento_freq = snd_freqs[advik_ch2_current_order[advik_current]];
					} else if (advik_ch2_current_order[advik_current] == 0xfe) {
						advik_ch2_portamento_freq = advik_ch2_previous_freq;
					}
				}
				break;
			//if tone portamento
			case 0x03:
				if (advik_ch2_current_order[advik_current+3] > 0) {
					advik_ch2_portamento_direction = 3;
					if (advik_ch2_current_order[advik_current] < 0xf0) {
						advik_ch2_portamento_freq = advik_ch2_previous_freq;
						advik_ch2_portamento_freq_goal = snd_freqs[advik_ch2_current_order[advik_current]];
					} else if (advik_ch2_current_order[advik_current] == 0xfe) {
						advik_ch2_portamento_freq_goal = advik_ch2_previous_freq;
					}
				}
				break;
			//if vibrato
			case 0x04:
				advik_ch2_vib_enabled = 1;
				break;
			//if set master volume
			case 0x05:
				REG_SNDDMGCNT = (REG_SNDDMGCNT & 0xff00) | advik_ch2_current_order[advik_current+3];
				break;
			//if note delay
			case 0x07:
				advik_ch2_delay_enabled = 1;
				advik_ch2_delay_ticks_counter = advik_ch2_current_order[advik_current+3] - 1;
				break;
			//if set global panning
			case 0x08:
				REG_SNDDMGCNT = (REG_SNDDMGCNT & 0x00ff) | (advik_ch2_current_order[advik_current+3] << 8);
				break;
			//if change timbre
			case 0x09:
				REG_SND2CNT = (advik_current_square_instruments[advik_ch2_current_order[advik_current+1]] & 0xff00) | advik_ch2_current_order[advik_current+3];
				break;
			//if set volume
			case 0x0c:
				REG_SND2CNT = (advik_current_square_instruments[advik_ch2_current_order[advik_current+1]] & 0x00ff) | (advik_ch2_current_order[advik_current+3] << 8);
				break;
			//if note cut
			case 0x0e:
				advik_ch2_cut_delay_enabled = 1;
				advik_ch2_delay_ticks_counter = advik_ch2_current_order[advik_current+3] - 1;
				break;
			//if set tempo
			case 0x0f:
				advik_ticks_per_row_value = advik_ch2_current_order[advik_current+3];
				break;
		}
		//check current effect and value for channel 3
		switch (advik_ch3_current_order[advik_current+2]) {
			//if arpeggio
			case 0x00:
				if (advik_ch3_current_order[advik_current+3] > 0) {
					advik_ch3_arp_enabled = 1;
				}
				break;
			//if portamento up
			case 0x01:
				if (advik_ch3_current_order[advik_current+3] > 0) {
					advik_ch3_portamento_direction = 1;
					if (advik_ch3_current_order[advik_current] < 0xf0) {
						advik_ch3_portamento_freq = snd_freqs[advik_ch3_current_order[advik_current]];
					} else if (advik_ch3_current_order[advik_current] == 0xfe) {
						advik_ch3_portamento_freq = advik_ch3_previous_freq;
					}
				}
				break;
			//if portamento down
			case 0x02:
				if (advik_ch3_current_order[advik_current+3] > 0) {
					advik_ch3_portamento_direction = 2;
					if (advik_ch3_current_order[advik_current] < 0xf0) {
						advik_ch3_portamento_freq = snd_freqs[advik_ch3_current_order[advik_current]];
					} else if (advik_ch3_current_order[advik_current] == 0xfe) {
						advik_ch3_portamento_freq = advik_ch3_previous_freq;
					}
				}
				break;
			//if tone portamento
			case 0x03:
				if (advik_ch3_current_order[advik_current+3] > 0) {
					advik_ch3_portamento_direction = 3;
					if (advik_ch3_current_order[advik_current] < 0xf0) {
						advik_ch3_portamento_freq = advik_ch3_previous_freq;
						advik_ch3_portamento_freq_goal = snd_freqs[advik_ch3_current_order[advik_current]];
					} else if (advik_ch3_current_order[advik_current] == 0xfe) {
						advik_ch3_portamento_freq_goal = advik_ch3_previous_freq;
					}
				}
				break;
			//if vibrato
			case 0x04:
				advik_ch3_vib_enabled = 1;
				break;
			//if set master volume
			case 0x05:
				REG_SNDDMGCNT = (REG_SNDDMGCNT & 0xff00) | advik_ch3_current_order[advik_current+3];
				break;
			//if note delay
			case 0x07:
				advik_ch3_delay_enabled = 1;
				advik_ch3_delay_ticks_counter = advik_ch3_current_order[advik_current+3] - 1;
				break;
			//if set global panning
			case 0x08:
				REG_SNDDMGCNT = (REG_SNDDMGCNT & 0x00ff) | (advik_ch3_current_order[advik_current+3] << 8);
				break;
			//if change timbre
			// case 0x09:
				// REG_SND3CNT = (advik_current_wave_instruments[advik_ch3_current_order[advik_current+1]] & 0xff00) | advik_ch3_current_order[advik_current+3];
				// break;
			//if set volume
			case 0x0c:
				REG_SND3CNT = (advik_ch3_current_order[advik_current+3] << 8);
				break;
			//if note cut
			case 0x0e:
				advik_ch3_cut_delay_enabled = 1;
				advik_ch3_delay_ticks_counter = advik_ch3_current_order[advik_current+3] - 1;
				break;
			//if set tempo
			case 0x0f:
				advik_ticks_per_row_value = advik_ch3_current_order[advik_current+3];
				break;
		}
		//check current effect and value for channel 4
		switch (advik_ch4_current_order[advik_current+2]) {
			//if arpeggio
			// case 0x00:
				// if (advik_ch4_current_order[advik_current+3] > 0) {
					// advik_ch4_arp_enabled = 1;
				// }
				// break;
			//if vibrato
			// case 0x04:
				// advik_ch4_vib_enabled = 1;
				// break;
			//if set master volume
			case 0x05:
				REG_SNDDMGCNT = (REG_SNDDMGCNT & 0xff00) | advik_ch4_current_order[advik_current+3];
				break;
			//if note delay
			case 0x07:
				advik_ch4_delay_enabled = 1;
				advik_ch4_delay_ticks_counter = advik_ch4_current_order[advik_current+3] - 1;
				break;
			//if set global panning
			case 0x08:
				REG_SNDDMGCNT = (REG_SNDDMGCNT & 0x00ff) | (advik_ch4_current_order[advik_current+3] << 8);
				break;
			//if change timbre
			 // case 0x09:
				// REG_SND4CNT = (advik_current_noise_instruments[advik_ch4_current_order[advik_current+1]] & 0xff00) | advik_ch4_current_order[advik_current+3];
				// break;
			//if set volume
			case 0x0c:
				REG_SND4CNT = (advik_ch4_current_order[advik_current+3] << 8);
				break;
			//if note cut
			case 0x0e:
				advik_ch4_cut_delay_enabled = 1;
				advik_ch4_delay_ticks_counter = advik_ch4_current_order[advik_current+3] - 1;
				break;
			//if set tempo
			case 0x0f:
				advik_ticks_per_row_value = advik_ch4_current_order[advik_current+3];
				break;
		}
		
		//check if notes are in range and there's no note delay for channel 1
		if (advik_ch1_current_order[advik_current] < 0xf0 && !advik_ch1_delay_enabled) {
			//if instrument isn't 0, retrigger note
			if (advik_ch1_current_order[advik_current+1] > 0x00){
				REG_SND1CNT = advik_current_square_instruments[advik_ch1_current_order[advik_current+1] - 1];
			}
			advik_ch1_held_note = 0;
			REG_SND1FREQ = SFREQ_RESET | snd_freqs[advik_ch1_current_order[advik_current]];
			advik_ch1_previous_freq = snd_freqs[advik_ch1_current_order[advik_current]];
		} else if (advik_ch1_current_order[advik_current] == 0xfe) {
			//make sure held note is saved
			if (advik_ch1_held_note == 0) {
				advik_ch1_held_note = SFREQ_RESET | snd_freqs[advik_ch1_current_order[advik_current-4]];
			}
		}
		//check if notes are in range and there's no note delay for channel 2
		if (advik_ch2_current_order[advik_current] < 0xf0 && !advik_ch2_delay_enabled) {
			//if instrument isn't 0, retrigger note
			if (advik_ch2_current_order[advik_current+1] > 0x00){
				REG_SND2CNT = advik_current_square_instruments[advik_ch2_current_order[advik_current+1] - 1];
			}
			advik_ch2_held_note = 0;
			REG_SND2FREQ = SFREQ_RESET | snd_freqs[advik_ch2_current_order[advik_current]];
			advik_ch2_previous_freq = snd_freqs[advik_ch2_current_order[advik_current]];
		} else if (advik_ch2_current_order[advik_current] == 0xfe) {
			//make sure held note is saved
			if (advik_ch2_held_note == 0) {
				advik_ch2_held_note = SFREQ_RESET | snd_freqs[advik_ch2_current_order[advik_current-4]];
			}
		}
		//check if notes are in range and there's no note delay for channel 3
		if (advik_ch3_current_order[advik_current] < 0xf0 && !advik_ch3_delay_enabled) {
			//if instrument isn't 0, retrigger note
			if (advik_ch3_current_order[advik_current+1] > 0x00){
				REG_SND3CNT = 0x2000;
			}
			advik_ch3_held_note = 0;
			REG_SND3FREQ = SFREQ_RESET | snd_freqs[advik_ch3_current_order[advik_current]];
			advik_ch3_previous_freq = snd_freqs[advik_ch3_current_order[advik_current]];
		} else if (advik_ch3_current_order[advik_current] == 0xfe) {
			//make sure held note is saved
			if (advik_ch3_held_note == 0) {
				advik_ch3_held_note = SFREQ_RESET | snd_freqs[advik_ch3_current_order[advik_current-4]];
			}
		}
		//check if notes are in range and there's no note delay for channel 4
		if (advik_ch4_current_order[advik_current] < 0xf8 && !advik_ch4_delay_enabled) {
			//if instrument isn't 0, retrigger note
			if (advik_ch4_current_order[advik_current+1] > 0x00){
				REG_SND4CNT = advik_current_noise_instruments[advik_ch4_current_order[advik_current+1] - 1] & SNOI_EXCLUDE_PACK;
			}
			REG_SND4FREQ = SFREQ_RESET | advik_ch4_current_order[advik_current] | (SNOI_UNPACK(advik_current_noise_instruments[advik_ch4_current_order[advik_current+1] - 1] & SNOI_SHORT_PACK));
			
		}
		advik_current += 4;
		advik_ticks_per_row_counter = advik_ticks_per_row_value;
		advik_arp_tick = 0;
	}
	
}