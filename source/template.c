
#include <tonc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "advikku_global.h"

#include "bg1.h"
#include "bg2.h"
#include "../music/blank.h"
#include "../sfx/punch.h"
#include "../sfx/punchhitnoise.h"
#include "../sfx/punchhitpulse.h"
#include "../sfx/levelup.h"
#include "../sfx/enemyspot.h"
#include "../sfx/enemydeath.h"
#include "../sfx/chestopen.h"
#include "../sfx/buttonpress.h"

void init_pic() {
	// Load palette
	memcpy32(&pal_bg_mem[32], bg1_pal, (sizeof(bg1_pal) >> 2));
	// Load tiles into CBB 2
	memcpy32(&tile_mem[2][0], bg1_char, (sizeof(bg1_char) >> 2));
	// Load map into SBB 28
	memcpy32(&se_mem[28][0], bg1_screen, (sizeof(bg1_screen) >> 2));
	// Load palette
	memcpy32(&pal_bg_mem[16], bg2_pal, (sizeof(bg2_pal) >> 2));
	// Load tiles into CBB 1
	memcpy32(&tile_mem[1][0], bg2_char, (sizeof(bg2_char) >> 2));
	// Load map into SBB 31
	memcpy32(&se_mem[31][0], bg2_screen, (sizeof(bg2_screen) >> 2));
}

IWRAM_CODE void isr_master();
IWRAM_CODE void hbl_grad_direct();

// Function pointers to master isrs.
const fnptr master_isrs[2]=
{
	(fnptr)isr_master,
	(fnptr)hbl_grad_direct
};

//---------------------------------------------------------------------------------
// Program entry point
//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------

	init_pic();

	// enable vblank register
	irq_init(master_isrs[0]);
	irq_add(II_VBLANK, NULL);
	
	tte_init_se(0, BG_CBB(0) | BG_SBB(29), 0, CLR_WHITE, 0, NULL, NULL);
	tte_init_con();
	REG_BG1CNT= BG_CBB(1) | BG_SBB(31) | BG_4BPP | BG_REG_32x32;
	REG_BG2CNT= BG_CBB(2) | BG_SBB(28) | BG_4BPP | BG_REG_32x32;
	REG_DISPCNT= DCNT_MODE0 | DCNT_BG0 | DCNT_BG1 | DCNT_BG2;
	
	// 3 2 1 make some noise
	
	// turn sound on
	REG_SNDSTAT= SSTAT_ENABLE;
	// snd1 on left/right ; both full volume
	REG_SNDDMGCNT = SDMG_BUILD_LR(SDMG_SQR1 | SDMG_SQR2 | SDMG_WAVE | SDMG_NOISE, 6);
	// DMG ratio to 100%
	REG_SNDDSCNT= SDS_DMG100 | SDS_A100 | SDS_AR | SDS_AL | SDS_ATMR0 | SDS_ARESET | SDS_B100 | SDS_BR | SDS_BL |SDS_BTMR1 | SDS_BRESET;
	
	//set timer 0
	//REG_TM0D = DMA_SAMPLE_PITCH(8192);
	//REG_TM0CNT = TM_ENABLE;
	
	cell_song_setup(blankSongStruct);
	
	tte_printf("Advikku sound engine\nbeta v0.2 initialised");

	while (1) {
		VBlankIntrWait();
		key_poll();
		//cell_song_update();
		
		cell_sfx_update();
		
		SBB_CLEAR_ROW(29, 10);
		
		// Play test sound on pulse 1
		if(key_hit(KEY_B))
			cell_sfx_setup(punchSFXStruct, 3);
		if(key_hit(KEY_A)){
			cell_sfx_setup(punchhitnoisepartSFXStruct, 3);
			cell_sfx_setup(punchhitpulsepartSFXStruct, 0);
		}
		if(key_hit(KEY_UP))
			cell_sfx_setup(levelupSFXStruct, 0);
		if(key_hit(KEY_DOWN))
			cell_sfx_setup(enemyspotSFXStruct, 2);
		if(key_hit(KEY_LEFT))
			cell_sfx_setup(enemydeathSFXStruct, 2);
		if(key_hit(KEY_RIGHT))
			cell_sfx_setup(chestopenSFXStruct, 0);
		if(key_hit(KEY_START))
			cell_sfx_setup(buttonpressSFXStruct, 0);
	}
}


