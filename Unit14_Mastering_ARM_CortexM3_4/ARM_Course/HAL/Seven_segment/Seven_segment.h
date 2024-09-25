/*
 * Seven_segment.h
 *
 *  Created on: Dec 3, 2023
 *      Author: Elmag
 */

#ifndef SEVEN_SEGMENT_SEVEN_SEGMENT_H_
#define SEVEN_SEGMENT_SEVEN_SEGMENT_H_

#include "stm32f103x6_GPIO_Driver.h"

/* ============= Global Variable ================= */
GPIO_PinConfig_t PinConfig;

/* ===== 7 Segments Macros Definitions ===== */
#define ZERO 	0x01
#define ONE 	0x79
#define TWO 	0x24
#define THREE 	0x30
#define FOUR 	0x4C
#define FIVE 	0x12
#define SIX 	0x02
#define SEVEN 	0x19
#define EIGHT 	0x00
#define NINE 	0x10

/* ============= Functions Prototypes ============ */
void _7_segment_init(void);

#endif /* SEVEN_SEGMENT_SEVEN_SEGMENT_H_ */
