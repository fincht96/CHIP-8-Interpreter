
#ifndef CHIP8_H
#define CHIP8_H

#include <stdio.h>
#include <stdint.h>
#include "constants.h"
#include "memory.h"
#include <cstdlib>			// for std::rand() and std::srand()
#include <ctime>			// for std::time()
#include "SFML/Window.hpp"
#include "input.h"
#include "timer.h"
#include "graphics.h"


class Chip8
{

private:

	uint64_t instruction_count = 0;


	Memory* const m_pMem;						// points to memory object
	Timer* const m_pDelayTimer;			// points to delay timer
	Timer* const m_pSoundTimer;			// points to sound timer
	Graphics* const m_pGpu;					// points to graphics object

	uint16_t m_stack[48];						// up to 48 levels deep, used to store addresses
	uint8_t m_v[NUM_REGS] = { 0 };	// 16 8-bit registers
	uint16_t m_i;										// address register
	uint16_t m_pc;									// program counter
	uint8_t m_sp;										// stack pointer

	struct InstrData
	{
		uint16_t addr = 0;		// holds addr value
		uint8_t value = 0;		// holds data value
		uint8_t x_reg = 0;		// holds x register
		uint8_t y_reg = 0;		// holds y register
	};


	struct Instr
	{
		void(Chip8::*CodeExec)(InstrData) = NULL;		// points to exec code
		InstrData data;							// holds data regarding specific instruction
	};


	Instr decode(uint16_t opcode);	// decodes the instruction and returns Instr packet
	void exec(Instr instr);			// executes a given instruction


	// 34 exec operations

	void op_CLS(InstrData);				// clears screen
	void op_RET(InstrData);				// returns from sub routine
	void op_JP(InstrData data);			// jumps to address NNNN
	void op_CALL(InstrData data);		// calls subroutine at NNNN and stores return address
	void op_SEXD(InstrData data);		// skips next instr if Vx == data
	void op_SNEXD(InstrData data);		// skips next instr if Vx != data
	void op_SEXY(InstrData data);		// skips next instr if Vx == Vy
	void op_LD(InstrData data);			// loads data byte into Vx
	void op_ADD(InstrData data);		// adds Vx and  data byte and stores in Vx
	void op_LDXY(InstrData data);		// loads Vy into Vx			---
	void op_OR(InstrData data);			// set Vx = Vx OR Vy
	void op_AND(InstrData data);		// set Vx = Vx AND Vy
	void op_XOR(InstrData data);		// set Vx = VX XOR Vy
	void op_ADDXY(InstrData data);		// set Vx = Vx + Vy, VF = carry
	void op_SUB(InstrData data);		// set Vx = Vx - Vy, set VF = NOT borrow
	void op_SHR(InstrData data);		// set Vx = Vx SHR 1
	void op_SUBN(InstrData data);		// set Vx = Vy - Vx
	void op_SHL(InstrData data);		// set Vx = Vx SHL 1
	void op_SNEXY(InstrData data);		// skip next instr if Vx != Vy
	void op_LDI(InstrData data);		// register I set to NNN
	void op_JPOFF(InstrData data);		// jump to location NNN + V0
	void op_RND(InstrData data);		// set Vx = ran byte AND kk
	void op_DRW(InstrData data);		// display n-byte sprite starting at I at (Vx, Vy), set VF = collision
	void op_SKP(InstrData data);		// skip next instr if key with value Vx is pressed
	void op_SKNP(InstrData data);		// skip next instr if key with the value Vx is not pressed
	void op_LDXDT(InstrData data);		// set Vx = Delay timer value
	void op_LDXK(InstrData data);		// wait for key press and store key value in Vx
	void op_LDDTX(InstrData data);		// set Delay timer = Vx
	void op_LDSTX(InstrData data);		// set Sound timer = Vx
	void op_ADIX(InstrData data);		// set I = I + Vx;
	void op_LDFX(InstrData data);		// set I = location of sprite for digit Vx
	void op_LDBX(InstrData data);		// store BCD of Vx in mem locations I, I+1 and I+2
	void op_LDIX(InstrData data);		// store registers V0 through Vx in mem starting from location I
	void op_LDXI(InstrData data);		// read registers through V0 to Vx into mem, starting at addr in I

public:
	Chip8(Memory* const mem);
	Chip8(Memory* const mem, Graphics* const gpu, Timer* const delay_timer, Timer* const sound_timer);
	void update();			// fetches and then increments pc, decodes instruction, executes instruction
	~Chip8();

};



#endif
