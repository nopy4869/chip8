#include <signal.h>

//Found at:
//http://stackoverflow.com/questions/8236/how-do-you-determine-the-size-of-a-file-in-c
//
#include <sys/stat.h>

off_t fsize(const char *filename) {
    struct stat st; 

    if (stat(filename, &st) == 0)
        return st.st_size;

    return -1; 
}

FILE *game;
int badlines;

void reloadgame()
{
	int x;
	int loop;
	int looop;
	for(loop = 0; loop < 16; loop++)
		cpu.V[loop] = 0;
	for(loop = (512+cpu.romsize); loop < 4096; loop++)
		cpu.memory[loop] = 0;
	for(loop = 0; loop < 32; loop++)
		for(looop = 0; looop < 64; looop++)
			cpu.gfx[looop][loop] = 0;
	for(loop = 0; loop < 16; loop++)
		cpu.stack[loop] = 0;
	for(loop = 0; loop < 16; loop++)
		cpu.key[loop] = 0;
	cpu.sp = 0;
	cpu.dt = 0;
	cpu.st = 0;
	cpu.I = 0;
	cpu.pc = 512;
	cpu.op = 0;
	cpu.opcode[0] = 0;
	cpu.opcode[1] = 0;
	cpu.drawflag = 1;
	cpu.currcount = 0;
	cpu.currcount--;
	cpu.lastcount = 0;
	for(x = 0; x < 80; x++)
	{
		cpu.memory[x] = bitmap[x];
	}
	for(x = 0; x < 58; x++)
	{
		cpu.memory[x+80] = loader[x];
	}
	srand(cpu.romsize);
};

void initcpu()
{
	int x;
	int loop;
	int looop;
	for(loop = 0; loop < 16; loop++)
		cpu.V[loop] = 0;
	for(loop = 0; loop < 4096; loop++)
		cpu.memory[loop] = 0;
	for(loop = 0; loop < 64; loop++)
		for(looop = 0; looop < 32; looop++)
			cpu.gfx[loop][looop] = 0;
	for(loop = 0; loop < 16; loop++)
		cpu.stack[loop] = 0;
	for(loop = 0; loop < 16; loop++)
		cpu.key[loop] = 0;
	cpu.sp = 0;
	cpu.dt = 0;
	cpu.st = 0;
	cpu.I = 0;
	cpu.pc = 512;
	cpu.op = 0;
	cpu.opcode[0] = 0;
	cpu.opcode[1] = 0;
	cpu.drawflag = 0;
	cpu.dbug = 0;
	cpu.classic = 0;
	cpu.SDL = 1;
	cpu.currcount = 0;
	cpu.currcount--;
	cpu.lastcount = 0;
	for(x = 0; x < 80; x++)
	{
		cpu.memory[x] = bitmap[x];
	}
	for(x = 0; x < 58; x++)
	{
		cpu.memory[x+80] = loader[x];
	}
	wprintw(stdscr, "Turn on dbug?\n");
	wrefresh(stdscr);
	if(bie() == 'y')
		cpu.dbug = 1;
	wprintw(stdscr, "Turn on classic mode?\n");
	wrefresh(stdscr);
	if(bie() == 'y')
		cpu.classic = 1;
	if(cpu.dbug == 1)
	{
		wprintw(stdscr, "Turn on \"stepthru mode\"?\n");
		wrefresh(stdscr);
		if(bie() == 'y')
			cpu.stepthru = 1;
	}
	wprintw(stdscr, "Turn off SDL mode?\n");
	wrefresh(stdscr);
	if(bie() == 'y')
		cpu.SDL = 0;
	if(cpu.SDL == 1)
	{
		wprintw(stdscr, "Start paused?\n");
		wrefresh(stdscr);
		if(bie() == 'y')
			cpu.ispaused = 1;
	}
	wprintw(stdscr, "CPU initialized!\n");
	if(cpu.dbug == 1)
		wprintw(stdscr, "Dbug is on!\n");
	if(cpu.classic == 1)
		wprintw(stdscr, "Classic interpreter mode is on!\n");
	wrefresh(stdscr);
	srand(cpu.romsize);
	hang(1);
};

int loadgame()
{
	char filename [9];
	int loadgamex;
	int x;
	wprintw(stdscr, "Please type the file's filename.\nDO NOT HIT ENTER!!!!!\nDO NOT HIT ESCAPE UNLESS YOU WANT TO END FILENAME INPUT!!!!!\nPressing ESCAPE right now will exit the program.\n");
	wrefresh(stdscr);
	for(x = 0; x < 12; x++)
	{
		filename [x] = bie();
		if((filename[x] == '\n') || (filename[x] == 27))
		{
			filename[x] = 0;
			x = 26;
		}
	}
	cpu.romsize = fsize(filename);
	if(cpu.romsize == -1)
	{
		return 1;
	}
	game = fopen(filename, "rb+");
	if(game == 0)
	{
		return 1;
	}
	char read;
	wprintw(stdscr, "This game has %d bytes\n", cpu.romsize);
	wrefresh(stdscr);
	for(loadgamex = 0;loadgamex < cpu.romsize;loadgamex++)
	{
		x = fread(&read,1,1,game);
		if(x != 1)
		{
			wprintw(stdscr, "Error reading file: %d bytes read.\n",x);
			return 1;
//			break;
		}
		cpu.memory[loadgamex+512] = read;
		wprintw(stdscr, "%02X",cpu.memory[loadgamex+512]);
		wrefresh(stdscr);
	}
	fclose(game);
	wprintw(stdscr, "\nGame\n(whose entirety is printed above (EXCITING ^.^))\nloaded into RAM!\n");
	wrefresh(stdscr);
	hang(3);
	return 0;
};

void ONNN ()
{
	disasmnum = 0;
	//rca1802 program at address NNN
	badlines++;
	if(cpu.dbug == 1)
		mvwprintw(botlin2, 0, 0, "\nUnimplemented opcode (0NNN) #%d",badlines);
	wrefresh(stdscr);
}

void OOEO ()
{
	disasmnum = 1;
	//Clears screen
	int loop;
	int looop;
	cpu.drawflag = 1;
	for(loop = 0; loop < 32; loop++)
		for(looop = 0; looop < 64; looop++)
			cpu.gfx[looop][loop] = 0;
}

void OOEE ()
{
	disasmnum = 2;
	//returns from a subroutine
	cpu.sp = cpu.sp - 1;
	cpu.pc = cpu.stack[cpu.sp];
}

void INNN (unsigned short opcode)
{
	disasmnum = 3;
	//Jumps to address NNN
	opcode = opcode - 0x1000;
	cpu.pc = opcode-2;
}

void ZNNN (unsigned short opcode)
{
	disasmnum = 4;
	//calls subroutine at NNN
	cpu.stack[cpu.sp] = cpu.pc;
	cpu.sp = cpu.sp + 1;
	opcode = opcode - 0x2000;
	cpu.pc = opcode-2;
}

void TXNN (unsigned short opcode)
{
	disasmnum = 5;
	//Skips next instruction if VX equals NN
	int NN;
	int X;
	opcode = opcode - 0x3000;
	X = opcode >> 8;
	NN = opcode - (X << 8);
	if(cpu.V[X] == NN)
		cpu.pc += 2;
}

void HXNN (unsigned short opcode)
{
	disasmnum = 6;
	//Skips next instruction if VX doesn't equal NN
	int NN;
	int X;
	opcode = opcode - 0x4000;
	X = opcode >> 8;
	NN = opcode - (X << 8);
	if(cpu.V[X] != NN)
		cpu.pc += 2;
}

void SXYO (unsigned short opcode)
{
	disasmnum = 7;
	//Skips next instruction if VX equals VY
	int X;
	int Y;
	opcode = opcode - 0x5000;
	opcode = opcode >> 4;
	X = opcode >> 4;
	Y = opcode - (X << 4);
	if(cpu.V[X] == cpu.V[Y])
		cpu.pc += 2;
}

void bXNN (unsigned short opcode)
{
	disasmnum = 8;
	//Sets VX to NN
	int NN;
	int X;
	opcode = opcode - 0x6000;
	X = opcode >> 8;
	NN = opcode - (X << 8);
	cpu.V[X] = NN;
}

void sevenXNN (unsigned short opcode)
{
	disasmnum = 9;
	//Adds NN to VX
	int NN;
	int X;
	opcode = opcode - 0x7000;
	X = opcode >> 8;
	NN = opcode - (X << 8);
	cpu.V[X] += NN;
}

void eightXYO (unsigned short opcode)
{
	disasmnum = 10;
	//sets VX to VY
	int X;
	int Y;
	opcode = opcode - 0x8000;
	opcode = opcode >> 4;
	X = opcode >> 4;
	Y = opcode - (X << 4);
	cpu.V[X] = cpu.V[Y];
}

void eightXYI (unsigned short opcode)
{
	disasmnum = 11;
	//sets VX to VX or VY
	int X;
	int Y;
	opcode = opcode - 0x8001;
	opcode = opcode >> 4;
	X = opcode >> 4;
	Y = opcode - (X << 4);
	cpu.V[X] = cpu.V[X] | cpu.V[Y];
}

void eightXYZ (unsigned short opcode)
{
	disasmnum = 12;
	//sets VX to VX and VY
	int X;
	int Y;
	opcode = opcode - 0x8002;
	opcode = opcode >> 4;
	X = opcode >> 4;
	Y = opcode - (X << 4);
	cpu.V[X] = cpu.V[X] & cpu.V[Y];
}

void eightXYthree (unsigned short opcode)
{
	disasmnum = 13;
	//sets VX to VX xor VY
	int X;
	int Y;
	opcode = opcode - 0x8003;
	opcode = opcode >> 4;
	X = opcode >> 4;
	Y = opcode - (X << 4);
	cpu.V[X] = cpu.V[X] ^ cpu.V[Y];
}

void eightXYfour (unsigned short opcode)
{
	disasmnum = 14;
	//Adds VY to VX with carry bit support!
	int X;
	int Y;
	int Z;
	opcode = opcode - 0x8004;
	opcode = opcode >> 4;
	X = opcode >> 4;
	Y = opcode - (X << 4);
	Z = cpu.V[X] + cpu.V[Y];
	if(Z > 255)
	{
		cpu.V[15] = 1;
	};
	if(Z <= 255)
	{
		cpu.V[15] = 0;
	};
	cpu.V[X] = cpu.V[X] + cpu.V[Y];
}

void eightXYS (unsigned short opcode)
{
	disasmnum = 15;
	//Subtracts VY from VX with borrow bit support!
	int X;
	int Y;
	int Z;
	opcode = opcode - 0x8005;
	opcode = opcode >> 4;
	X = opcode >> 4;
	Y = opcode - (X << 4);
	Z = cpu.V[X] - cpu.V[Y];
	if(Z < 0)
	{
		cpu.V[15] = 0;
	};
	if(Z >= 0)
	{
		cpu.V[15] = 1;
	};
	cpu.V[X] = cpu.V[X] - cpu.V[Y];
}

void eightXYb (unsigned short opcode)
{
	disasmnum = 16;
	if(cpu.classic == 0)
	{
		//Shifts VX right 1 bit
		int X;
		opcode = opcode - 0x8006;
		X = opcode >> 8;
		cpu.V[15] = (cpu.V[X] << 7) >> 7;
		cpu.V[X] = cpu.V[X] >> 1;
	}
	if(cpu.classic == 1)
	{
		//Shifts VY right 1 bit and store it in VX
		int X;
		int Y;
		opcode = opcode - 0x8006;
		opcode = opcode >> 4;
		X = opcode >> 4;
		Y = opcode - (X << 4);
		cpu.V[15] = (cpu.V[Y] << 7) >> 7;
		cpu.V[X] = cpu.V[Y] >> 1;
	}
}

void eightXY7 (unsigned short opcode)
{
	disasmnum = 17;
	//Subtracts VX from VY and stores in VX, with borrow bit support!
	int X;
	int Y;
	int Z;
	opcode = opcode - 0x8007;
	opcode = opcode >> 4;
	X = opcode >> 4;
	Y = opcode - (X << 4);
	Z = cpu.V[Y] - cpu.V[X];
	if(Z < 0)
	{
		cpu.V[15] = 0;
	};
	if(Z >= 0)
	{
		cpu.V[15] = 1;
	};
	cpu.V[X] = cpu.V[Y] - cpu.V[X];
}

void eightXYE (unsigned short opcode)
{
	disasmnum = 18;
	if(cpu.classic == 0)
	{
		//Shifts VX left 1 bit
		int X;
		opcode = opcode - 0x800E;
		X = opcode >> 8;
		cpu.V[15] = (cpu.V[X] >> 7) << 7;
		cpu.V[X] = cpu.V[X] << 1;
	}
	if(cpu.classic == 1)
	{
		//Shifts VY left 1 bit then stores it in VX
		int X;
		int Y;
		opcode = opcode - 0x8000;
		opcode = opcode >> 4;
		X = opcode >> 4;
		Y = opcode - (X << 4);
		cpu.V[15] = (cpu.V[Y] >> 7) << 7;
		cpu.V[X] = cpu.V[Y] << 1;
	}
}

void nineXYO (unsigned short opcode)
{
	disasmnum = 19;
	//Skips the next instruction if VX != VY
	int X;
	int Y;
	opcode = opcode - 0x9000;
	opcode = opcode >> 4;
	X = opcode >> 4;
	Y = opcode - (X << 4);
	if(cpu.V[X] != cpu.V[Y])
		cpu.pc +=2;
}

void ANNN (unsigned short opcode)
{
	disasmnum = 20;
	//Sets I to address NNN
	opcode = opcode - 0xA000;
	cpu.I = opcode;
}

void BNNN (unsigned short opcode)
{
	disasmnum = 21;
	//Jumps to address NNN + V[0]
	opcode = opcode - 0xB000;
	cpu.pc = ((opcode + cpu.V[0])-2);
}

void CXNN (unsigned short opcode)
{
	disasmnum = 22;
	//sets V[X] to a random number and NN
	int X;
	unsigned short Z;
	char bit;
	opcode = opcode - 0xC000;
	X = opcode >> 8;
	opcode = opcode << 8;
	opcode = opcode >> 8;
	bit = opcode;
//	srand(bit);
	Z = rand();
	cpu.V[X] = bit & Z;
}

void DXYN (unsigned short opcode)
{
	disasmnum = 23;
	//prints the sprite at location I in ram of size (8,N) to the screen at V[X] V[Y]
	unsigned char X;
	unsigned char Y;
	unsigned char N;
	unsigned char l;
	unsigned char m;
	unsigned short temp;
//	unsigned char sprite[16];
//	unsigned char line[8];
	cpu.drawflag = 1;
	opcode = opcode - 0xD000;
	X = opcode >> 8;
	temp = opcode - (X << 8);
	Y = temp >> 4;
	temp = Y << 4;
	N = opcode - (X << 8) - temp;
	cpu.V[15] = 0;
	for(l = 0; l < N; l++)
	{
/*		for(m = 0; m < 8; m++)
		{
			line[m] = (sprite[l] << m) >> (7-m);
			cpu.gfx[(cpu.V[X]+m)%64][(cpu.V[Y]+l)%32] += line[m];
			if(line[m] > 1)
			{
				cpu.V[15] = 1;
				cpu.gfx[(cpu.V[X]+m)%64][(cpu.V[Y]+l)%32] = 0;
			}
		}
		
	}*/
		for(m = 0; m < 8; m++)
		{
			if((cpu.gfx[(cpu.V[X]+m)%64][cpu.V[Y]+l] + ((cpu.memory[cpu.I+l] & (0x01 << (7-m))) >> (7-m))) > 1)
			{
				cpu.V[15] = 1;
				cpu.gfx[(cpu.V[X]+m)%64][cpu.V[Y]+l] = 0;
			}
			else if((cpu.gfx[(cpu.V[X]+m)%64][cpu.V[Y]+l] + ((cpu.memory[cpu.I+l] & (0x01 << (7-m))) >> (7-m))) == 1)
			{
				cpu.gfx[(cpu.V[X]+m)%64][cpu.V[Y]+l] = 1;
			}
			else if((cpu.gfx[(cpu.V[X]+m)%64][cpu.V[Y]+l] + ((cpu.memory[cpu.I+l] & (0x01 << (7-m))) >> (7-m))) == 0)
			{
				cpu.gfx[(cpu.V[X]+m)%64][cpu.V[Y]+l] = 0;
			}
		}
	}
}

void EXnineE (unsigned short opcode)
{
	disasmnum = 24;
	//Skips next instruction if key at V[X] is pressed
	int X;
	opcode = opcode - 0xE09E;
	X = opcode >> 8;
	if(cpu.key[cpu.V[X]] > 0)
		cpu.pc +=2;
}

void EXAI (unsigned short opcode)
{
	disasmnum = 25;
	//Skips next instruction if key at V[X] is not pressed
	int X;
	opcode = opcode - 0xE0A1;
	X = opcode >> 8;
	if(cpu.key[cpu.V[X]] == 0)
		cpu.pc +=2;
}

void FXOseven (unsigned short opcode)
{
	disasmnum = 26;
	//Sets V[X] to the value of the delay timer
	int X;
	opcode = opcode - 0xF007;
	X = opcode >> 8;
	cpu.V[X] = cpu.dt;
}

void FXOA (unsigned short opcode)
{
	disasmnum = 27;
	//Waits for a key, then stores it in V[X]
	int X;
	int x;
	opcode = opcode - 0xF00A;
	X = opcode >> 8;
	keypadclear();
	input('b');
	for(x = 0; x < 16; x++)
	{
		if(cpu.key[x] == 1)
			cpu.V[X] = x;
	}
}

void FXIS (unsigned short opcode)
{
	disasmnum = 28;
	//Sets V[X] to the value of the delay timer
	int X;
	opcode = opcode - 0xF015;
	X = opcode >> 8;
	cpu.dt = cpu.V[X];
}

void FXIeight (unsigned short opcode)
{
	disasmnum = 29;
	//Sets V[X] to the value of the sound timer
	int X;
	opcode = opcode - 0xF018;
	X = opcode >> 8;
	cpu.st = cpu.V[X];
}

void FXIE (unsigned short opcode)
{
	disasmnum = 30;
	//Adds V[X] to I
	int X;
	unsigned int z;
	opcode = opcode - 0xF01E;
	X = opcode >> 8;
	z = cpu.I + cpu.V[X];
	cpu.V[15] = 0;
	if(z > 4095)
		cpu.V[15] = 1;
	cpu.I += cpu.V[X];
}

void FXZnine (unsigned short opcode)
{
	disasmnum = 31;
	//Sets I to the sprite for the value at V[X]
	int X;
	opcode = opcode - 0xF029;
	X = opcode >> 8;
	cpu.I = cpu.V[X] * 5;
}

void FXTT (unsigned short opcode)
{
	disasmnum = 32;
	//Stores the BCD of V[X] across I, I+1, and I+2
	int X;
	char h, t, o;
	opcode = opcode - 0xF033;
	X = opcode >> 8;
	h = cpu.V[X]/100;
	t = (cpu.V[X]/10)%10;
	o = cpu.V[X]%10;
	cpu.memory[cpu.I] = h;
	cpu.memory[cpu.I+1] = t;
	cpu.memory[cpu.I+2] = o;
}

void FXSS (unsigned short opcode)
{
	disasmnum = 33;
	//Stores the value of V[0] through V[X] in memory starting at I
	int X;
	int x;
	opcode = opcode - 0xF055;
	X = opcode >> 8;
	for(x = 0; x <= X; x++)
	{
		cpu.memory[cpu.I+x] = cpu.V[x];
	}
	if(cpu.classic == 1)
		cpu.I += (X + 1);
}

void FXbS (unsigned short opcode)
{
	disasmnum = 34;
	//Stores in V[0] through V[X] the data in memory starting at I
	int X;
	int x;
	opcode = opcode - 0xF065;
	X = opcode >> 8;
	for(x = 0; x <= X; x++)
	{
		cpu.V[x] = cpu.memory[cpu.I+x];
	}
	if(cpu.classic == 1)
		cpu.I += (X + 1);
}

unsigned char fn(unsigned char opone)
{
	opone = opone >> 4;
	return opone;
}

unsigned char ln(unsigned char optwo)
{
	optwo = optwo << 4;
	optwo = optwo >> 4;
	return optwo;
}

int cycle()
{
	if(cpu.pc >= 4096)
	{
		wprintw(stdscr, "Reached the end of RAM?!?!?\nExiting now.\n");
		return 1;
	}
	cpu.opcode[0] = cpu.memory[cpu.pc];
	cpu.opcode[1] = cpu.memory[cpu.pc+1];
	char a;
	char b;
	char test;
	a = fn(cpu.opcode[0]);
	b = ln(cpu.opcode[1]);
	cpu.op = cpu.opcode[0] << 8;
	cpu.op += cpu.opcode[1];
	SDL_GetNumAudioDevices(0);
	mvwprintw(botlin, 0,0, "OP:%04X PC:%d(%04X) Tick:%d Screen Scale:%d Audio Device:%d %s\n", cpu.op, cpu.pc, cpu.pc, cpu.tick, SCREEN_SCALE, devicenum, SDL_GetAudioDeviceName(0, 0));
	wrefresh(botlin);
	a = fn(cpu.opcode[0]);
	b = ln(cpu.opcode[1]);
	cpu.pcp = cpu.pc;
	if(cpu.op == 0x00E0)
		OOEO();
	else if(cpu.op == 0x00EE)
		OOEE();
	switch (a)
	{
		case 0:
			ONNN();
			break;
		case 1:
			INNN(cpu.op);
			break;
		 case 2:
			ZNNN(cpu.op);
			break;
		case 3:
			TXNN(cpu.op);
			break;
		case 4:
			HXNN(cpu.op);
			break;
		case 5:
			SXYO(cpu.op);
			break;
		case 6:
			bXNN(cpu.op);
			break;
		case 7:
			sevenXNN(cpu.op);
			break;
		case 8:
			switch (b)
			{
				case 0:
					eightXYO(cpu.op);
					break;
				case 1:
					eightXYI(cpu.op);
					break;
				case 2:
					eightXYZ(cpu.op);
					break;
				case 3:
					eightXYthree(cpu.op);
					break;
				case 4:
					eightXYfour(cpu.op);
					break;
				case 5:
					eightXYS(cpu.op);
					break;
				case 6:
					eightXYb(cpu.op);
					break;
				case 7:
					eightXY7(cpu.op);
					break;
				case 14:
					eightXYE(cpu.op);
					break;
			}
			break;
		case 9:
			nineXYO(cpu.op);
			break;
		case 10:
			ANNN(cpu.op);
			break;
		case 11:
			BNNN(cpu.op);
			break;
		case 12:
			CXNN(cpu.op);
			break;
		case 13:
			DXYN(cpu.op);
			break;
		case 14:
			if(cpu.opcode[1] == 0x9E)
				EXnineE(cpu.op);
			else if(cpu.opcode[1] == 0xA1)
				EXAI(cpu.op);
			break;
		case 15:
			switch (cpu.opcode[1])
			{
				case 0x07:
					FXOseven(cpu.op);
					break;
				case 0x0A:
					FXOA(cpu.op);
					break;
				case 0x15:
					FXIS(cpu.op);
					break;
				case 0x18:
					FXIeight(cpu.op);
					break;
				case 0x1E:
					FXIE(cpu.op);
					break;
				case 0x29:
					FXZnine(cpu.op);
					break;
				case 0x33:
					FXTT(cpu.op);
					break;
				case 0x55:
					FXSS(cpu.op);
					break;
				case 0x65:
					FXbS(cpu.op);
					break;
			}
			break;
		default:
			if(cpu.dbug == 1)
			{
				disasmnum = 35;
				wprintw(botlin2, "\nUnrecognized opcode: %04X", cpu.op);
				badlines++;
			}
			break;
	}
	if(cpu.dbug == 1)
	{
//		mvwprintw(botlin, 0,0, "OP:%04X PC:%d(%04X) Tick:%d\n", cpu.op, cpu.pc, cpu.pc, cpu.tick);
//		wrefresh(botlin);
		cyclemem();
		if(cpu.stepthru == 1)
		{
			test = bi();
			if(test == 'b')
				cpu.dt = 0;
			if(test == 'r')
			{
				reloadgame();
				cpu.pc-=2;
			}
		}
	}
	cpu.pc += 2;
	return 0;
};

int clockrate()
{
	time_t temp;
	int x;
	int y;
	int z;
	int r;
	int startime;
	int currtime;
	startime = time(&temp);
	hang(1);
	for(x = 0; currtime == startime ;x++)
	{
		currtime = time(&temp);
	}
	for(x = 0; currtime == startime ;x++)
	{
		currtime = time(&temp);
	}
	for(y = 0; currtime == startime ;y++)
	{
		currtime = time(&temp);
	}
	for(z = 0; currtime == startime ;z++)
	{
		currtime = time(&temp);
	}
	r = x+y+z;
	r = r/3;
	return r;
};

void ExitHard()
{
	SDL_Quit();
	exit(1);
}
