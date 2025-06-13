#include "chip8.h"
#include "display/display.h"
#include <stdio.h>

typedef enum {
	ERR_NONE,
	ERR_INVALID_INSTRUCTION,
	ERR_STACKOVERFLOW,
} Err;

static void handle_err(Chip8* chip8, uint16_t op, Err err) {
	switch (err) {
		case ERR_INVALID_INSTRUCTION:
			fprintf(stderr, "Invalid Instruction %x at pc = %x\n", op, chip8->PC);
			break;
		default:
			break;
	}
}

int chip8_execop(Chip8* chip8, uint16_t op) {
	Err err = ERR_NONE;

	switch (op & 0xf000) {
		case 0x0000:
			switch (op & 0x0fff) {
				case 0xe0: // clear display
					display_clear();
					break;
				case 0xee: // ret
					chip8->PC = chip8->stack[chip8->SP--];
					break;
				default:
					err = ERR_INVALID_INSTRUCTION;
					break;
			}
			break;

		case 0x1000: // jmp 0xnnn
			chip8->PC = op & 0x0fff;
			break;
		
		case 0x2000: // call 0xnnn
			if (chip8->SP == STACK_LEN - 1) {
				err = ERR_STACKOVERFLOW;
				break;
			}
			chip8->stack[++chip8->SP] = chip8->PC;
			chip8->PC = op & 0x0fff;
			break;

		case 0x3000: // 0x3xkk, if vx == kk, skip instruction
			if (chip8->V[(op & 0x0f00) >> 8] == (op & 0x00ff))
				chip8->PC += 2;
			break;

		case 0x4000: // 0x4xkk, if vx != kk, skip instruction
			if (chip8->V[(op & 0x0f00) >> 8] != (op & 0x00ff))
				chip8->PC += 2;
			break;

		case 0x5000:
		case 0x6000:
		case 0x7000:
		case 0x8000:
		case 0x9000:
		case 0xa000:
		case 0xb000:
		case 0xc000:
		case 0xd000:
		case 0xe000:
		case 0xf000:
	}

	if (err != ERR_NONE) {
		handle_err(chip8, op, err);
		return 1;
	}
	return 0;
}
