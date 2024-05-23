#include <stdint.h>

#include "advikku_update.h"

#ifndef ADVIKKU_GLOBAL
#define ADVIKKU_GLOBAL

// --------------------------------------------------------------------
// GLOBAL PLAYER VARIABLES
// --------------------------------------------------------------------

// Advikku variables
extern uint16_t advik_start;
extern uint16_t advik_loop_point;
extern uint16_t advik_ticks_per_row_counter;
extern uint16_t advik_ticks_per_row_value;
extern uint16_t advik_current;

extern uint16_t advik_arp_tick;
extern uint16_t advik_arp_index;

// --------------------------------------------------------------------
// CHANNEL PLAYER VARIABLES
// --------------------------------------------------------------------

extern uint16_t advik_ch1_arp_enabled;

extern uint16_t advik_ch1_portamento_direction;
extern uint16_t advik_ch1_portamento_freq;
extern uint16_t advik_ch1_portamento_freq_goal;
extern uint16_t advik_ch1_previous_freq;

extern uint16_t advik_ch1_held_note;

extern uint16_t advik_ch1_vib_position;
extern uint16_t advik_ch1_vib_ticks_counter;
extern uint16_t advik_ch1_vib_enabled;

extern uint16_t advik_ch1_delay_ticks_counter;
extern uint16_t advik_ch1_delay_enabled;
extern uint16_t advik_ch1_cut_delay_enabled;

extern uint16_t advik_ch2_arp_enabled;

extern uint16_t advik_ch2_portamento_direction;
extern uint16_t advik_ch2_portamento_freq;
extern uint16_t advik_ch2_portamento_freq_goal;
extern uint16_t advik_ch2_previous_freq;

extern uint16_t advik_ch2_held_note;

extern uint16_t advik_ch2_vib_position;
extern uint16_t advik_ch2_vib_ticks_counter;
extern uint16_t advik_ch2_vib_enabled;

extern uint16_t advik_ch2_delay_ticks_counter;
extern uint16_t advik_ch2_delay_enabled;
extern uint16_t advik_ch2_cut_delay_enabled;

extern uint16_t advik_ch3_arp_enabled;

extern uint16_t advik_ch3_portamento_direction;
extern uint16_t advik_ch3_portamento_freq;
extern uint16_t advik_ch3_portamento_freq_goal;
extern uint16_t advik_ch3_previous_freq;

extern uint16_t advik_ch3_held_note;

extern uint16_t advik_ch3_vib_position;
extern uint16_t advik_ch3_vib_ticks_counter;
extern uint16_t advik_ch3_vib_enabled;

extern uint16_t advik_ch3_delay_ticks_counter;
extern uint16_t advik_ch3_delay_enabled;
extern uint16_t advik_ch3_cut_delay_enabled;

extern uint16_t advik_ch4_delay_ticks_counter;
extern uint16_t advik_ch4_delay_enabled;
extern uint16_t advik_ch4_cut_delay_enabled;

extern const uint8_t * const * advik_global_current_order;
extern const uint16_t * advik_current_square_instruments;
extern const uint16_t * advik_current_wave_instruments;
extern const uint16_t * advik_current_noise_instruments;

extern const uint8_t * advik_ch1_current_order;
extern const uint8_t * advik_ch2_current_order;
extern const uint8_t * advik_ch3_current_order;
extern const uint8_t * advik_ch4_current_order;

// --------------------------------------------------------------------
// TONE GENERATOR
// --------------------------------------------------------------------

extern const uint16_t snd_freqs[];
extern const int16_t vib_table[];

// --------------------------------------------------------------------
// MACROS 
// --------------------------------------------------------------------

#define REG_BASE		MEM_IO

#define MEM_EWRAM	0x02000000	//!< External work RAM
#define MEM_IWRAM	0x03000000	//!< Internal work RAM
#define MEM_IO		0x04000000	//!< I/O registers
#define MEM_PAL		0x05000000	//!< Palette. Note: no 8bit write !!
#define MEM_VRAM	0x06000000	//!< Video RAM. Note: no 8bit write !!
#define MEM_OAM		0x07000000	//!< Object Attribute Memory (OAM) Note: no 8bit write !!
#define MEM_ROM		0x08000000	//!< ROM. No write at all (duh)
#define MEM_SRAM	0x0E000000	//!< Static RAM. 8bit write only

#define SFREQ_HOLD				 0	//!< Continuous play
#define SFREQ_TIMED			0x4000	//!< Timed play
#define SFREQ_RESET			0x8000	//!< Reset sound

#define SFREQ_RATE_MASK		0x07FF
#define SFREQ_RATE_SHIFT		 0

// --- REG_SNDDMGCNT ---------------------------------------------------

/*!	\defgroup grpAudioSDMG	Tone Generator, Control Flags
	\ingroup grpMemBits
	\brief	Bits for REG_SNDDMGCNT (aka REG_SOUNDCNT_L)
*/
/*!	\{	*/


#define SDMG_LSQR1		0x0100	//!< Enable channel 1 on left 
#define SDMG_LSQR2		0x0200	//!< Enable channel 2 on left
#define SDMG_LWAVE		0x0400	//!< Enable channel 3 on left
#define SDMG_LNOISE		0x0800	//!< Enable channel 4 on left	
#define SDMG_RSQR1		0x1000	//!< Enable channel 1 on right
#define SDMG_RSQR2		0x2000	//!< Enable channel 2 on right
#define SDMG_RWAVE		0x4000	//!< Enable channel 3 on right
#define SDMG_RNOISE		0x8000	//!< Enable channel 4 on right

#define SDMG_LVOL_MASK	0x0007
#define SDMG_LVOL_SHIFT		 0
#define SDMG_LVOL(n)	((n)<<SDMG_LVOL_SHIFT)

#define SDMG_RVOL_MASK	0x0070
#define SDMG_RVOL_SHIFT		 4
#define SDMG_RVOL(n)	((n)<<SDMG_RVOL_SHIFT)


// Unshifted values
#define SDMG_SQR1		0x01
#define SDMG_SQR2		0x02
#define SDMG_WAVE		0x04
#define SDMG_NOISE		0x08


#define SDMG_BUILD(_lmode, _rmode, _lvol, _rvol)	\
	( ((_rmode)<<12) | ((_lmode)<<8) | (((_rvol)&7)<<4) | ((_lvol)&7) )

#define SDMG_BUILD_LR(_mode, _vol) SDMG_BUILD(_mode, _mode, _vol, _vol)

/*!	\}	/defgroup	*/

// --- REG_SNDDSCNT ----------------------------------------------------

/*!	\defgroup grpAudioSDS	Direct Sound Flags
	\ingroup grpMemBits
	\brief	Bits for REG_SNDDSCNT (aka REG_SOUNDCNT_H)
*/
/*!	\{	*/

#define SDS_DMG25			 0	//!< Tone generators at 25% volume
#define SDS_DMG50		0x0001	//!< Tone generators at 50% volume
#define SDS_DMG100		0x0002	//!< Tone generators at 100% volume
#define SDS_A50			 0	//!< Direct Sound A at 50% volume
#define SDS_A100		0x0004	//!< Direct Sound A at 100% volume
#define SDS_B50			 0	//!< Direct Sound B at 50% volume
#define SDS_B100		0x0008	//!< Direct Sound B at 100% volume
#define SDS_AR			0x0100	//!< Enable Direct Sound A on right
#define SDS_AL			0x0200	//!< Enable Direct Sound A on left
#define SDS_ATMR0			 0	//!< Direct Sound A to use timer 0
#define SDS_ATMR1		0x0400	//!< Direct Sound A to use timer 1
#define SDS_ARESET		0x0800	//!< Reset FIFO of Direct Sound A
#define SDS_BR			0x1000	//!< Enable Direct Sound B on right
#define SDS_BL			0x2000	//!< Enable Direct Sound B on left
#define SDS_BTMR0			 0	//!< Direct Sound B to use timer 0
#define SDS_BTMR1		0x4000	//!< Direct Sound B to use timer 1
#define SDS_BRESET		0x8000	//!< Reset FIFO of Direct Sound B

#define SSQR_DUTY1_8		 0	//!< 12.5% duty cycle (#-------)
#define SSQR_DUTY1_4	0x0040	//!< 25% duty cycle (##------)
#define SSQR_DUTY1_2	0x0080	//!< 50% duty cycle (####----)
#define SSQR_DUTY3_4	0x00C0	//!< 75% duty cycle (######--) Equivalent to 25%
#define SSQR_INC			 0x0800	//!< Increasing volume
#define SSQR_DEC		0x0000	//!< Decreasing volume

#define SSQR_LEN_MASK	0x003F
#define SSQR_LEN_SHIFT		 0
#define SSQR_LEN(n)		((n)<<SSQR_LEN_SHIFT)

#define SSQR_DUTY_MASK	0x00C0
#define SSQR_DUTY_SHIFT		 6
#define SSQR_DUTY(n)	((n)<<SSQR_DUTY_SHIFT)

#define SSQR_TIME_MASK	0x0700
#define SSQR_TIME_SHIFT		 8
#define SSQR_TIME(n)	((n)<<SSQR_TIME_SHIFT)

#define SSQR_IVOL_MASK	0xF000
#define SSQR_IVOL_SHIFT		12
#define SSQR_IVOL(n)	((n)<<SSQR_IVOL_SHIFT)

#define SWAV_LEN_MASK 0x00FF
#define SWAV_LEN_SHIFT	0
#define SWAV_LEN(n)	((n)<<SWAV_LEN_SHIFT)

#define SWAV_LEN_ON	0x4000
#define SWAV_LEN_OFF	0x0000

#define SWAV_VOL75	0x8000
#define SWAV_VOL0	0x0000
#define SWAV_VOL100	0x2000
#define SWAV_VOL50	0x4000
#define SWAV_VOL25	0x6000

#define SNOI_FREQ_MASK 0x0007
#define SNOI_FREQ_SHIFT	0
#define SNOI_FREQ(n) ((n)<<SNOI_FREQ_SHIFT)

#define SNOI_OCTAVE_MASK 0x00F0
#define SNOI_OCTAVE_SHIFT	4
#define SNOI_OCTAVE(n) ((n)<<SNOI_OCTAVE_SHIFT)

#define SNOI_SHORT 0x0008
#define SNOI_LONG 0x0000

#define SNOI_SHORT_PACK 0x0040
#define SNOI_LONG_PACK 0x0000

#define SNOI_UNPACK_SHIFT 3
#define SNOI_UNPACK(n) ((n)>>SNOI_UNPACK_SHIFT)

#define SNOI_EXCLUDE_PACK 0xFFDF

// === SOUND REGISTERS ===
// sound regs, partially following pin8gba's nomenclature

//! \name Channel 1: Square wave with sweep
//\{
#define REG_SND1SWEEP		*(volatile uint16_t*)(REG_BASE+0x0060)	//!< Channel 1 Sweep
#define REG_SND1CNT			*(volatile uint16_t*)(REG_BASE+0x0062)	//!< Channel 1 Control
#define REG_SND1FREQ		*(volatile uint16_t*)(REG_BASE+0x0064)	//!< Channel 1 frequency
//\}

//! \name Channel 2: Simple square wave
//\{
#define REG_SND2CNT			*(volatile uint16_t*)(REG_BASE+0x0068)	//!< Channel 2 control
#define REG_SND2FREQ		*(volatile uint16_t*)(REG_BASE+0x006C)	//!< Channel 2 frequency
//\}

//! \name Channel 3: Wave player
//\{
#define REG_SND3SEL			*(volatile uint16_t*)(REG_BASE+0x0070)	//!< Channel 3 wave select
#define REG_SND3CNT			*(volatile uint16_t*)(REG_BASE+0x0072)	//!< Channel 3 control
#define REG_SND3FREQ		*(volatile uint16_t*)(REG_BASE+0x0074)	//!< Channel 3 frequency
//\}

//! \name Channel 4: Noise generator
//\{
#define REG_SND4CNT			*(volatile uint16_t*)(REG_BASE+0x0078)	//!< Channel 4 control
#define REG_SND4FREQ		*(volatile uint16_t*)(REG_BASE+0x007C)	//!< Channel 4 frequency
//\}

//! \name Sound control
//\{
#define REG_SNDCNT			*(volatile uint32_t*)(REG_BASE+0x0080)	//!< Main sound control
#define REG_SNDDMGCNT		*(volatile uint16_t*)(REG_BASE+0x0080)	//!< DMG channel control
#define REG_SNDDSCNT		*(volatile uint16_t*)(REG_BASE+0x0082)	//!< Direct Sound control
#define REG_SNDSTAT			*(volatile uint16_t*)(REG_BASE+0x0084)	//!< Sound status
#define REG_SNDBIAS			*(volatile uint16_t*)(REG_BASE+0x0088)	//!< Sound bias
//\}

//! \name Sound buffers
//\{
#define REG_WAVE_RAM		 (volatile uint32_t*)(REG_BASE+0x0090)	//!< Channel 3 wave buffer

#define REG_WAVE_RAM0		*(volatile uint32_t*)(REG_BASE+0x0090)
#define REG_WAVE_RAM1		*(volatile uint32_t*)(REG_BASE+0x0094)
#define REG_WAVE_RAM2		*(volatile uint32_t*)(REG_BASE+0x0098)
#define REG_WAVE_RAM3		*(volatile uint32_t*)(REG_BASE+0x009C)

#define REG_FIFO_A			*(volatile uint32_t*)(REG_BASE+0x00A0)	//!< DSound A FIFO
#define REG_FIFO_B			*(volatile uint32_t*)(REG_BASE+0x00A4)	//!< DSound B FIFO
//\}

// --------------------------------------------------------------------
// DMA
// --------------------------------------------------------------------

// --------------------------------------------------------------------
// PROTOTYPES 
// --------------------------------------------------------------------


// --------------------------------------------------------------------
// CONSTANTS
// --------------------------------------------------------------------


#endif