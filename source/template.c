
#include <tonc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "advikku_global.h"

#include "bg0.h"
#include "bg1.h"
#include "../music/BasicDog.h"
#include "zetakick_bin.h"
#include "zetasnare_bin.h"

IWRAM_DATA uint32_t fifo_sample_1[1018];

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
	advik_ch1_current_order = advik_global_current_order[0];
	advik_ch2_current_order = advik_global_current_order[1];
	advik_ch3_current_order = advik_global_current_order[2];
	advik_ch4_current_order = advik_global_current_order[3];
	advik_ticks_per_row_value = advik_ch1_current_order[advik_current];
	advik_current++;
	advik_loop_point = advik_start = advik_current;
}

IWRAM_CODE void isr_master();
IWRAM_CODE void hbl_grad_direct();

void vct_wait();
void vct_wait_nest();

// Function pointers to master isrs.
const fnptr master_isrs[2]=
{
	(fnptr)isr_master,
	(fnptr)hbl_grad_direct
};

// (1) Uses tonc_isr_master.s'  isr_master() as a switchboard
void hbl_grad_routed()
{
	u32 clr= REG_VCOUNT/8;
	pal_bg_mem[0]= RGB15(clr, 0, 31-clr);
}

void fifofum(){
	REG_DMA1CNT = 0;
}

//---------------------------------------------------------------------------------
// Program entry point
//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------

	init_pic();

	// enable vblank register
	irq_init(master_isrs[0]);
	irq_add(II_VBLANK, NULL);
	
	REG_BG0CNT= BG_CBB(0) | BG_SBB(30) | BG_4BPP | BG_REG_32x32;
	REG_BG1CNT= BG_CBB(1) | BG_SBB(31) | BG_4BPP | BG_REG_32x32;
	REG_DISPCNT= DCNT_MODE0 | DCNT_BG0 | DCNT_BG1;
	
	// 3 2 1 make some noise
	
	//clear DAC FIFO buffer
	memset32((void *)REG_FIFO_A, 0x0000, 1);
	//copy some sample bytes to IWRAM
	memcpy32(fifo_sample_1, zetakick_bin, (1018 >> 2));
	//copy a sample byte to the DAC FIFO
	memcpy32((void *)REG_FIFO_A, fifo_sample_1, (4 >> 2));
	
	// turn sound on
	REG_SNDSTAT= SSTAT_ENABLE;
	// snd1 on left/right ; both full volume
	REG_SNDDMGCNT = 0;
	// DMG ratio to 100%
	REG_SNDDSCNT= SDS_DMG100 | SDS_A100 | SDS_AR | SDS_AL | SDS_ATMR0 | SDS_ARESET;
	
	//set timer 0
	REG_TM0D = 65024;
	REG_TM0CNT = TM_ENABLE;
	
	//set DMA transfer to DAC FIFO
	REG_DMA1SAD = (u32)fifo_sample_1;
	REG_DMA1DAD = REG_FIFO_A;
	REG_DMA1CNT = DMA_DST_FIXED | DMA_REPEAT | DMA_16 | DMA_AT_REFRESH | DMA_ENABLE;
	
	//set timer 1
	REG_TM1D = 65536 - zetakick_bin_size;
	REG_TM1CNT = TM_CASCADE | TM_IRQ | TM_ENABLE;
	
	irq_add(II_TIMER1, NULL);
	
	//copy channel 3 waveform over
	REG_SND3SEL = 0;
	tonccpy((void *)REG_WAVE_RAM, basicSaw, 16);
	REG_SND3SEL = 0xC0;
	
	advik_global_current_order = basicSong;
	advik_current_square_instruments = basicSquareInstruments;
	advik_current_wave_instruments = basicWaveInstruments;
	advik_current_noise_instruments = basicNoiseInstruments;
	
	cell_song_setup();

	while (1) {
		VBlankIntrWait();
		cell_song_play();
	}
}


