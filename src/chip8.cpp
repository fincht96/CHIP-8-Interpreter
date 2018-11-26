#include "chip8.h"


Chip8::Chip8(Memory* const mem)
	: m_pMem(mem), m_pGpu(NULL), m_pDelayTimer(NULL), m_pSoundTimer(NULL)
{

}


Chip8::Chip8(Memory* const mem, Graphics* const gpu, Timer* const delay_timer, Timer* const sound_timer)
	: m_pMem(mem), m_pGpu(gpu), m_pDelayTimer(delay_timer), m_pSoundTimer(sound_timer)
{
	m_pc = RAM_STRT_ADDR;
	m_sp = 0;
	m_i = 0;											// sp points to bottom of stack
	std::srand(static_cast<unsigned int>(std::time(nullptr)));	// set initial random number generation seed value to system clock time


	(*m_pMem)[0] = 0xF0;	// start addr: 0
	(*m_pMem)[1] = 0x90;	// 0
	(*m_pMem)[2] = 0x90;
	(*m_pMem)[3] = 0x90;
	(*m_pMem)[4] = 0xF0;

	(*m_pMem)[5] = 0x20;	// start addr: 5
	(*m_pMem)[6] = 0x60;	// 1
	(*m_pMem)[7] = 0x20;
	(*m_pMem)[8] = 0x20;
	(*m_pMem)[9] = 0x70;

	(*m_pMem)[10] = 0xF0;	// start addr: 10
	(*m_pMem)[11] = 0x10;	// 2
	(*m_pMem)[12] = 0xF0;
	(*m_pMem)[13] = 0x80;
	(*m_pMem)[14] = 0xF0;

	(*m_pMem)[15] = 0xF0;	// start addr: 15
	(*m_pMem)[16] = 0x10;	// 3
	(*m_pMem)[17] = 0xF0;
	(*m_pMem)[18] = 0x10;
	(*m_pMem)[19] = 0xF0;

	(*m_pMem)[20] = 0x90;	// start addr: 20
	(*m_pMem)[21] = 0x90;	// 4
	(*m_pMem)[22] = 0xF0;
	(*m_pMem)[23] = 0x10;
	(*m_pMem)[24] = 0x10;

	(*m_pMem)[25] = 0xF0;	// start addr: 25
	(*m_pMem)[26] = 0x80;	// 5
	(*m_pMem)[27] = 0xF0;
	(*m_pMem)[28] = 0x10;
	(*m_pMem)[29] = 0xF0;

	(*m_pMem)[30] = 0xF0;	// start addr: 30
	(*m_pMem)[31] = 0x80;	// 6
	(*m_pMem)[32] = 0xF0;
	(*m_pMem)[33] = 0x90;
	(*m_pMem)[34] = 0xF0;

	(*m_pMem)[35] = 0xF0;	// start addr: 35
	(*m_pMem)[36] = 0x10;	// 7
	(*m_pMem)[37] = 0x20;
	(*m_pMem)[38] = 0x40;
	(*m_pMem)[39] = 0x40;

	(*m_pMem)[40] = 0xF0;	// start addr: 40
	(*m_pMem)[41] = 0x90;	// 8
	(*m_pMem)[42] = 0xF0;
	(*m_pMem)[43] = 0x90;
	(*m_pMem)[44] = 0xF0;

	(*m_pMem)[45] = 0xF0;	// start addr: 45
	(*m_pMem)[46] = 0x90;	// 9
	(*m_pMem)[47] = 0xF0;
	(*m_pMem)[48] = 0x10;
	(*m_pMem)[49] = 0xF0;

	(*m_pMem)[50] = 0xF0;	// start addr: 50
	(*m_pMem)[51] = 0x90;	// A
	(*m_pMem)[52] = 0xF0;
	(*m_pMem)[53] = 0x90;
	(*m_pMem)[54] = 0x90;

	(*m_pMem)[55] = 0xE0;	// start addr: 55
	(*m_pMem)[56] = 0x90;	// B
	(*m_pMem)[57] = 0xE0;
	(*m_pMem)[58] = 0x90;
	(*m_pMem)[59] = 0xE0;

	(*m_pMem)[60] = 0xF0;	// start addr: 60
	(*m_pMem)[61] = 0x80;	// C
	(*m_pMem)[62] = 0x80;
	(*m_pMem)[63] = 0x80;
	(*m_pMem)[64] = 0xF0;

	(*m_pMem)[65] = 0xE0;	// start addr: 65
	(*m_pMem)[66] = 0x90;	// D
	(*m_pMem)[67] = 0x90;
	(*m_pMem)[68] = 0x90;
	(*m_pMem)[69] = 0xE0;

	(*m_pMem)[70] = 0xF0;	// start addr: 70
	(*m_pMem)[71] = 0x80;	// E
	(*m_pMem)[72] = 0xF0;
	(*m_pMem)[73] = 0x80;
	(*m_pMem)[74] = 0xF0;

	(*m_pMem)[75] = 0xF0;	// start addr: 75
	(*m_pMem)[76] = 0x80;	// F
	(*m_pMem)[77] = 0xF0;
	(*m_pMem)[78] = 0x80;
	(*m_pMem)[79] = 0x80;

}


Chip8::~Chip8()
{
}


void Chip8::update()
{



	uint16_t opcode = 0;
	Instr instr;


	// fetch, gets the instruction from memory and post increments pc
	opcode = (uint8_t)(*m_pMem)[m_pc];
	opcode <<= 8;
	opcode |= (uint8_t)(*m_pMem)[m_pc + 1];


	// decode, returns an instruction packet, containing pointer to instrucion and relevant data
	instr = decode(opcode);


	printf("Executing %04X at %04X , I:%02X SP:%02X, IC:%02X\n", opcode, m_pc, m_i, m_sp, instruction_count);

	for (unsigned x = 0; x < 16; x++)
	{
		printf("v[%d]:%02X, ", x, m_v[x]);
	}

	printf("\n\n");


	// execute, executes insction packet
	exec(instr);

	++instruction_count;
}


Chip8::Instr Chip8::decode(uint16_t opcode)
{
	Instr temp;


	switch (opcode & 0xF000)
	{

	case 0x0000:
		switch (opcode)
		{
			// 00E0 - CLS
		case 0x00E0:
			temp.CodeExec = &Chip8::op_CLS;
			break;

			// 00EE - RET
		case 0x00EE:
			temp.CodeExec = &Chip8::op_RET;
			break;

		default:
			printf("Opcode:  %04X\n", opcode);
			std::cin.get();
			break;
		}
		break;


		// 1nnn - JP addr
	case 0x1000:
		temp.CodeExec = &Chip8::op_JP;
		temp.data.addr = (opcode & 0x0FFF);
		break;

		// 2nnn - CALL addr
	case 0x2000:
		temp.CodeExec = &Chip8::op_CALL;
		temp.data.addr = (opcode & 0x0FFF);
		break;

		// 3xkk - SE Vx, byte
	case 0x3000:
		temp.CodeExec = &Chip8::op_SEXD;
		temp.data.x_reg = (opcode & 0x0F00) >> 8;
		temp.data.value = (opcode & 0x00FF);
		break;

		// 4xkk - SNE Vx, byte
	case 0x4000:
		temp.CodeExec = &Chip8::op_SNEXD;
		temp.data.x_reg = (opcode & 0x0F00) >> 8;
		temp.data.value = (opcode & 0x00FF);
		break;

		// 5xy0 - SE Vx, Vy
	case 0x5000:
		temp.CodeExec = &Chip8::op_SEXY;
		temp.data.x_reg = (opcode & 0x0F00) >> 8;
		temp.data.y_reg = (opcode & 0x00F0) >> 4;
		break;

		// 6xkk - LD Vx, byte
	case 0x6000:
		temp.CodeExec = &Chip8::op_LD;
		temp.data.x_reg = (opcode & 0x0F00) >> 8;
		temp.data.value = (opcode & 0x00FF);
		break;

		// 7xkk - ADD Vx, byte
	case 0x7000:
		temp.CodeExec = &Chip8::op_ADD;
		temp.data.x_reg = (opcode & 0x0F00) >> 8;
		temp.data.value = (opcode & 0x00FF);
		break;


	case 0x8000:
		temp.data.x_reg = (opcode & 0x0F00) >> 8;
		temp.data.y_reg = (opcode & 0x00F0) >> 4;

		switch (opcode & 0x000F)
		{
			// 8xy0 - LD Vx, Vy
		case 0x0000:
			temp.CodeExec = &Chip8::op_LDXY;
			break;

			// 8xy1 - OR Vx, Vy
		case 0x0001:
			temp.CodeExec = &Chip8::op_OR;
			break;

			// 8xy2 - AND Vx, Vy
		case 0x0002:
			temp.CodeExec = &Chip8::op_AND;
			break;

			// 8xy3 - XOR Vx, Vy
		case 0x0003:
			temp.CodeExec = &Chip8::op_XOR;
			break;

			// 8xy4 - ADD Vx, Vy
		case 0x0004:
			temp.CodeExec = &Chip8::op_ADDXY;
			break;

			// 8xy5 - SUB Vx, Vy
		case 0x0005:
			temp.CodeExec = &Chip8::op_SUB;
			break;

			// 8xy6 - SHR Vx {, Vy}
		case 0x0006:
			temp.CodeExec = &Chip8::op_SHR;
			break;

			// 8xy7 - SUBN Vx, Vy
		case 0x0007:
			temp.CodeExec = &Chip8::op_SUBN;
			break;

			// 8xyE - SHL Vx {, Vy}
		case 0x000E:
			temp.CodeExec = &Chip8::op_SHL;
			break;

		default:
			printf("Opcode:  %04X\n", opcode);
			std::cin.get();
			break;

		}
		break;

		// 9xy0 - SNE Vx, Vy
	case 0x9000:
		temp.CodeExec = &Chip8::op_SNEXY;
		temp.data.x_reg = (opcode & 0x0F00) >> 8;
		temp.data.y_reg = (opcode & 0x00F0) >> 4;
		break;

		// Annn - LD I, addr
	case 0xA000:
		temp.CodeExec = &Chip8::op_LDI;
		temp.data.addr = (opcode & 0x0FFF);
		break;

		// Bnnn - JP V0, addr
	case 0xB000:
		temp.CodeExec = &Chip8::op_JPOFF;
		temp.data.addr = (opcode & 0x0FFF);
		break;

		// Cxkk - RND Vx, byte
	case 0xC000:
		temp.CodeExec = &Chip8::op_RND;
		temp.data.x_reg = (opcode & 0x0F00) >> 8;
		temp.data.value = (opcode & 0x00FF);
		break;

		// Dxyn - DRW Vx, Vy, nibble
	case 0xD000:
		temp.CodeExec = &Chip8::op_DRW;
		temp.data.x_reg = (opcode & 0x0F00) >> 8;
		temp.data.y_reg = (opcode & 0x00F0) >> 4;
		temp.data.value = (opcode & 0x000F);
		break;


	case 0xE000:
		temp.data.x_reg = (opcode & 0x0F00) >> 8;
		switch (opcode & 0x00FF)
		{
			// Ex9E - SKP Vx
		case 0x009E:
			temp.CodeExec = &Chip8::op_SKP;
			break;

			// ExA1 - SKNP Vx
		case 0x00A1:
			temp.CodeExec = &Chip8::op_SKNP;
			break;

		default:
			printf("Opcode:  %04X\n", opcode);
			std::cin.get();
		}

		break;

	case 0xF000:
		temp.data.x_reg = (opcode & 0x0F00) >> 8;
		switch (opcode & 0x00FF)
		{
			// Fx07 - LD Vx, DT
		case 0x0007:
			temp.CodeExec = &Chip8::op_LDXDT;
			break;

			// Fx0A - LD Vx, K
		case 0x000A:
			temp.CodeExec = &Chip8::op_LDXK;
			break;

			// Fx15 - LD DT, Vx
		case 0x0015:
			temp.CodeExec = &Chip8::op_LDDTX;
			break;

			// Fx18 - LD ST, Vx
		case 0x0018:
			temp.CodeExec = &Chip8::op_LDSTX;
			break;

			// Fx1E - ADD I, Vx
		case 0x001E:
			temp.CodeExec = &Chip8::op_ADIX;
			break;

			// Fx29 - LD F, Vx
		case 0x0029:
			temp.CodeExec = &Chip8::op_LDFX;
			break;

			// Fx33 - LD B, Vx
		case 0x0033:
			temp.CodeExec = &Chip8::op_LDBX;
			break;

			// Fx55 - LD [I], Vx
		case 0x0055:
			temp.CodeExec = &Chip8::op_LDIX;
			break;

			// Fx65 - LD Vx, [I]
		case 0x0065:
			temp.CodeExec = &Chip8::op_LDXI;
			break;

		default:
			printf("Opcode:  %04X\n", opcode);
			std::cin.get();
			break;

		}
		break;

	default:
		printf("Opcode:  %04X\n", opcode);
		std::cin.get();
		break;
	}


	if (temp.CodeExec == NULL)
	{
		std::cout << "ERROR, OPCODE NOT FOUND.\n";
		std::cin.get();
	}

	return temp;
}


void Chip8::exec(Instr instr)
{
	(*this.*instr.CodeExec)(instr.data);
}


// // 00E0 - CLS (Clear the display)
void Chip8::op_CLS(InstrData)
{
	m_pc += 2;
	m_pGpu->clearDisplay();
}


// 00EE - RET (Return from a subroutine)
void Chip8::op_RET(InstrData)
{
	// decrements sp and reads entry
	m_pc = m_stack[--m_sp] + 2;
}


// 1nnn - JP addr (Jump to location nnn)
void Chip8::op_JP(InstrData data)
{
	m_pc = data.addr;
}


// 2nnn - CALL addr (Call subroutine at nnn)
void Chip8::op_CALL(InstrData data)
{
	// stores current pc on stack and post increments sp
	m_stack[m_sp++] = m_pc;

	// jumps to address specified
	m_pc = data.addr;
}


// 3xkk - SE Vx, byte (Skip next instruction if Vx == kk)
void Chip8::op_SEXD(InstrData data)
{
	m_pc += 2;

	if (m_v[data.x_reg] == data.value)
		m_pc += 2;		// skips instruction
}


// 4xkk - SNE Vx, byte (Skip next instruction if Vx != kk)
void Chip8::op_SNEXD(InstrData data)
{
	m_pc += 2;

	if (m_v[data.x_reg] != data.value)
		m_pc += 2;		// skips instruction
}


// 5xy0 - SE Vx, Vy (Skip next instruction if Vx == Vy)
void Chip8::op_SEXY(InstrData data)
{
	m_pc += 2;

	if (m_v[data.x_reg] == m_v[data.y_reg])
		m_pc += 2;
}


// 6xkk - LD Vx, byte (Set Vx = kk)
void Chip8::op_LD(InstrData data)
{
	m_pc += 2;
	m_v[data.x_reg] = (uint8_t)data.value;
}


// 7xkk - ADD Vx, byte (Set Vx = Vx + kk)
void Chip8::op_ADD(InstrData data)
{
	m_pc += 2;
	m_v[data.x_reg] += (uint8_t)data.value;
}


// 8xy0 - LD Vx, Vy (Set Vx = Vy)
void Chip8::op_LDXY(InstrData data)
{
	m_pc += 2;
	m_v[data.x_reg] = (uint8_t)m_v[data.y_reg];
}


// 8xy1 - OR Vx, Vy (Set Vx = Vx OR Vy)
void Chip8::op_OR(InstrData data)
{
	m_pc += 2;
	m_v[data.x_reg] = (uint8_t)m_v[data.x_reg] | (uint8_t)m_v[data.y_reg];
}


// 8xy2 - AND Vx, Vy (Set Vx = Vx AND Vy)
void Chip8::op_AND(InstrData data)
{
	m_pc += 2;
	m_v[data.x_reg] = (uint8_t)m_v[data.x_reg] & (uint8_t)m_v[data.y_reg];
}


// 8xy3 - XOR Vx, Vy (Set Vx = Vx XOR Vy)
void Chip8::op_XOR(InstrData data)
{
	m_pc += 2;
	m_v[data.x_reg] = (uint8_t)m_v[data.x_reg] ^ (uint8_t)m_v[data.y_reg];
}


// 8xy4 - ADD Vx, Vy (Set Vx = Vx + Vy, set VF = carry)
void Chip8::op_ADDXY(InstrData data)
{
	m_pc += 2;

	m_v[0xF] = 0;

	if (m_v[data.y_reg] > (255 - m_v[data.x_reg]))
		m_v[0xF] = 1;


	m_v[data.x_reg] += m_v[data.y_reg];
}


// 8xy5 - SUB Vx, Vy (Set Vx = Vx - Vy, set VF = NOT borrow)
void Chip8::op_SUB(InstrData data)
{
	m_pc += 2;
	m_v[0xF] = 0;

	if (m_v[data.x_reg] >= m_v[data.y_reg])
		m_v[0xF] = 1;

	m_v[data.x_reg] = (uint8_t)(m_v[data.x_reg] - m_v[data.y_reg]);
}


// 8xy6 - SHR Vx {, Vy} (Set Vx = Vx SHR 1)
void Chip8::op_SHR(InstrData data)
{
	m_pc += 2;
	m_v[0x0F] = 0;

	if (m_v[data.x_reg] & 0x1)
		m_v[0x0F] = 1;		// sets flag register

	m_v[data.x_reg] /= 2;
}


// 8xy7 - SUBN Vx, Vy (Set Vx = Vy - Vx, set VF = NOT borrow)
void Chip8::op_SUBN(InstrData data)
{
	m_pc += 2;
	m_v[0x0F] = 0;

	if (m_v[data.y_reg] > m_v[data.x_reg])
		m_v[0x0F] = 1;		// sets flag register

	m_v[data.x_reg] = m_v[data.y_reg] - m_v[data.x_reg];
}


// 8xyE - SHL Vx {, Vy} (Set Vx = Vx SHL 1)
void Chip8::op_SHL(InstrData data)
{
	m_pc += 2;
	m_v[0x0F] = 0;

	if (m_v[data.x_reg] & 0x80)
		m_v[0x0F] = 1;		// sets flag register

	m_v[data.x_reg] *= 2;
}


// 9xy0 - SNE Vx, Vy (Skip next instruction if Vx != Vy)
void Chip8::op_SNEXY(InstrData data)
{
	m_pc += 2;

	if ((uint8_t)m_v[data.x_reg] != (uint8_t)m_v[data.y_reg])
		m_pc += 2;
}


// Annn - LD I, addr (Set I = nnn)
void Chip8::op_LDI(InstrData data)
{
	m_pc += 2;
	m_i = data.addr;
}


// Bnnn - JP V0, addr (Jump to location nnn + V0)
void Chip8::op_JPOFF(InstrData data)
{
	m_pc = data.addr + m_v[0];
}


// Cxkk - RND Vx, byte (Set Vx = random byte AND kk)
void Chip8::op_RND(InstrData data)
{
	m_pc += 2;
	m_v[data.x_reg] = std::rand() & data.value;
}


// Dxyn - DRW Vx, Vy, nibble (display n-byte sprite starting at I at (Vx, Vy), set VF = collision)
void Chip8::op_DRW(InstrData data)
{
	m_pc += 2;

	m_v[0xF] = 0;

	// loops through each sprite line
	for (unsigned y = 0; y < data.value; y++)
	{
		// reads sprite line data
		uint8_t spr_line = (*m_pMem)[m_i + y];

		for (unsigned x = 0; x < 8; x++)
		{
			// reads specific bit from sprite line
			uint8_t spr_bit = (spr_line >> (7 - x)) & 0x01;

			// reads specific bit from gpu memory
			uint8_t gpu_bit = m_pGpu->getPixel(Vec2(m_v[data.x_reg] + x, m_v[data.y_reg] + y));


			// sets flag register if both bits are '1'
			if ((gpu_bit > 0) && (spr_bit > 0))
				m_v[0xF] = 1;

			// xors the bits and writes back to gpu memory
			m_pGpu->setPixel(spr_bit ^ gpu_bit, Vec2(m_v[data.x_reg] + x, m_v[data.y_reg] + y));

		}
	}

}


// Ex9E - SKP Vx (Skip next instruction if key with the value of Vx is pressed)
void Chip8::op_SKP(InstrData data)
{
	m_pc += 2;

	if (m_v[data.x_reg] == Input::getKeyPress())
		m_pc += 2;

}


// ExA1 - SKNP Vx (Skip next instruction if key with the value of Vx is not pressed)
void Chip8::op_SKNP(InstrData data)
{
	m_pc += 2;

	if (m_v[data.x_reg] != Input::getKeyPress())
		m_pc += 2;
}


// Fx07 - LD Vx, DT (Set Vx = delay timer value)
void Chip8::op_LDXDT(InstrData data)
{
	m_pc += 2;
	m_v[data.x_reg] = m_pDelayTimer->getTimer();
}


// Fx0A - LD Vx, K (Waits for key press and then stores result in Vx)
void Chip8::op_LDXK(InstrData data)
{
	m_pc += 2;
	uint8_t keyNumber = 255;

	while (!(keyNumber < 16))
	{
		keyNumber = Input::getKeyPress();
	}

	m_v[data.x_reg] = keyNumber;	// stores key press result
}


// Fx15 - LD DT, Vx (Set delay timer = Vx)
void Chip8::op_LDDTX(InstrData data)
{
	m_pc += 2;
	m_pDelayTimer->setTimer(m_v[data.x_reg]);
}


// Fx18 - LD ST, Vx (Set sound timer = Vx)
void Chip8::op_LDSTX(InstrData data)
{
	m_pc += 2;
	m_pSoundTimer->setTimer(m_v[data.x_reg]);
}


// Fx1E - ADD I, Vx (Set I = I + Vx)
void Chip8::op_ADIX(InstrData data)
{
	m_pc += 2;
	m_i += m_v[data.x_reg];
}


// Fx29 - LD F, Vx (set I = location of sprite for digit Vx)
void Chip8::op_LDFX(InstrData data)
{
	m_pc += 2;
	m_i = m_v[data.x_reg] * MEM_OFFSET;
}


// Fx33 - LD B, Vx (store BCD of Vx in mem locations I, I+1 and I+2)
void Chip8::op_LDBX(InstrData data)
{
	m_pc += 2;
	// count number of 100's
	uint8_t num_hundreds = m_v[data.x_reg] / 100;

	// count number of 10's
	uint8_t num_tens = (m_v[data.x_reg] - num_hundreds * 100) / 10;

	// count number of 1's
	uint8_t num_ones = (m_v[data.x_reg] - (num_hundreds * 100) - (num_tens * 10));


	(*m_pMem)[m_i] = num_hundreds;
	(*m_pMem)[m_i + 1] = num_tens;
	(*m_pMem)[m_i + 2] = num_ones;
}


// Fx55 - LD [I], Vx (store registers V0 through Vx into memory starting from location I)
void Chip8::op_LDIX(InstrData data)
{
	m_pc += 2;

	for (unsigned i = 0; i <= data.x_reg; i++)
		(*m_pMem)[m_i + i] = m_v[i];
}


// Fx65 - LD Vx, [I] (fills V0 through Vx from mem, starting at addr in I)
void Chip8::op_LDXI(InstrData data)
{
	m_pc += 2;

	for (unsigned i = 0; i <= data.x_reg; i++)
		m_v[i] = (*m_pMem)[m_i + i];
}
