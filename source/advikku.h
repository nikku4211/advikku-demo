#include <stdint.h>

#ifndef ADVIKKU
#define ADVIKKU

// --------------------------------------------------------------------
// TONE GENERATOR
// --------------------------------------------------------------------

extern const uint16_t snd_freqs[];

// --------------------------------------------------------------------
// MACROS 
// --------------------------------------------------------------------

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

// --------------------------------------------------------------------
// PROTOTYPES 
// --------------------------------------------------------------------


// --------------------------------------------------------------------
// CONSTANTS
// --------------------------------------------------------------------


#endif