#ifndef CHIP8_MAIN_H
#define CHIP8_MAIN_H

#include <stdint.h>

typedef struct {
	uint8_t  mem  [4096];
	uint8_t  disp [64*32];
	uint8_t  V    [16];
	uint16_t stack[16];

	uint8_t  delay;
	uint8_t  sound;
	uint8_t  SP;
	uint16_t PC;
	uint16_t I;
} Chip8;

typedef enum {
	RESULT_OK,
	RESULT_INVALID_INSTRUCTION,
} Result;

Result chip8_execop(Chip8* chip8, uint16_t op);

#endif /* end of include guard: CHIP8_MAIN_H */
