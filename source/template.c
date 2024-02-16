
#include <tonc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "advikku.h"

#include "bg0.h"
#include "bg1.h"
#include "../music/BasicDog.h"

// Advikku variables
u16 advik_start = 0;
u16 advik_loop_point = 1;
u16 advik_ticks_per_row_counter = 6;
u16 advik_ticks_per_row_value = 6;
u16 advik_current = 0;

void init_pic() {
	// Load palette
	memcpy32(&pal_bg_mem[16], bg0_pal, (sizeof(bg0_pal) >> 2));
	// Load tiles into CBB 1
	memcpy32(&tile_mem[1][0], bg0_char, (sizeof(bg0_char) >> 2));
	// Load map into SBB 31
	memcpy32(&se_mem[31][0], bg0_screen, (sizeof(bg0_screen) >> 2));
	// Load palette
	memcpy32(&pal_bg_mem[0], bg1_pal, (sizeof(bg1_pal) >> 2));
	// Load tiles into CBB 0
	memcpy32(&tile_mem[0][0], bg1_char, (sizeof(bg1_char) >> 2));
	// Load map into SBB 30
	memcpy32(&se_mem[30][0], bg1_screen, (sizeof(bg1_screen) >> 2));
}

void cell_song_setup() {
	advik_ticks_per_row_counter = advik_ticks_per_row_value = basicSong[advik_current];
	advik_current++;
	advik_loop_point = advik_start = advik_current;
}

void cell_song_play() {
	if (advik_ticks_per_row_counter > 0) {
		advik_ticks_per_row_counter--;
	} else {
		
		if (basicSong[advik_current] == 0xff) {
			advik_current = advik_loop_point;
		} 
		
		REG_SND1CNT = basicInstruments[basicSong[advik_current+1]];
		if (basicSong[advik_current] < 0xf0) {
			REG_SND1FREQ = SFREQ_RESET | snd_freqs[basicSong[advik_current]];
		}
		
		switch (basicSong[advik_current+2]) {
			case 0x05:
				REG_SNDDMGCNT = (REG_SNDDMGCNT & 0xff00) | basicSong[advik_current+3];
				break;
			case 0x08:
				REG_SNDDMGCNT = (REG_SNDDMGCNT & 0x00ff) | (basicSong[advik_current+3] << 8);
				break;
			case 0x09:
				REG_SND1CNT = (basicInstruments[basicSong[advik_current+1]] & 0xff00) | basicSong[advik_current+3];
				break;
			case 0x0c:
				REG_SND1CNT = (basicInstruments[basicSong[advik_current+1]] & 0x00ff) | (basicSong[advik_current+3] << 8);
				break;
			case 0x0f:
				advik_ticks_per_row_value = basicSong[advik_current+3];
				break;
		}
		advik_current += 4;
		advik_ticks_per_row_counter = advik_ticks_per_row_value;
	}
}

//---------------------------------------------------------------------------------
// Program entry point
//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------

	init_pic();

	// enable hblank register
	irq_init(NULL);
	irq_add(II_VBLANK, NULL);
	
	REG_BG0CNT= BG_CBB(0) | BG_SBB(30) | BG_4BPP | BG_REG_32x32;
	REG_BG1CNT= BG_CBB(1) | BG_SBB(31) | BG_4BPP | BG_REG_32x32;
	REG_DISPCNT= DCNT_MODE0 | DCNT_BG0 | DCNT_BG1;
	
	// 3 2 1 make some noise
	
	// turn sound on
	REG_SNDSTAT= SSTAT_ENABLE;
	// snd1 on left/right ; both full volume
	REG_SNDDMGCNT = SDMG_BUILD_LR(SDMG_SQR1, 7);
	// DMG ratio to 100%
	REG_SNDDSCNT= SDS_DMG100;

	// no sweep
	REG_SND1SWEEP= SSW_OFF;
	// envelope: vol=12, decay, max step time (7) ; 50% duty
	REG_SND1CNT= SSQR_ENV_BUILD(12, 0, 7) | SSQR_DUTY1_2;
	REG_SND1FREQ= 0;
	
	cell_song_setup();

	while (1) {
		VBlankIntrWait();
		cell_song_play();
	}
}


