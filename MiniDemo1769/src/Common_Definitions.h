#ifndef __COMMON_DEFINITIONS_H__
#define __COMMON_DEFINITIONS_H__

#include "lpc_types.h"

/*************************************************************
 * Definicje portów, do których podłączone są diody
 */
#define LED_RED_PORT	 	(2)
#define LED_RED_PIN	 	(0)
#define LED_GREEN_PORT	 	(2)
#define LED_GREEN_PIN	 	(1)
#define LED_BLUE_PORT	 	(0)
#define LED_BLUE_PIN	 	(26)
// te diody są zamontowane wyłącznie na płytce REV D
#define LED_RED_PORT_ALT 	(0)
#define LED_RED_PIN_ALT	 	(22)
#define LED_GREEN_PORT_ALT	(3)
#define LED_GREEN_PIN_ALT	(25)
#define LED_BLUE_PORT_ALT	(3)
#define LED_BLUE_PIN_ALT	(26)

#endif //__COMMON_DEFINITIONS_H__
