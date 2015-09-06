struct chipeight
	{
		unsigned char V[16];
		unsigned char memory[4096];
		unsigned char gfx[64][32];
		unsigned short stack[16];
		unsigned char key[16];
		unsigned short sp;
		unsigned char dt;
		unsigned char st;
		unsigned short I;
		unsigned short pc;
		unsigned short pcp;
		unsigned char opcode[2];
		unsigned short op;
		unsigned char drawflag;
		unsigned char dbug;
		unsigned char SDL;
		unsigned char ispaused;
		unsigned char classic;
		unsigned char stepthru;
		unsigned int romsize;
		unsigned int tick;
		Uint64 currcount;
		Uint64 lastcount;
	} cpu;

int SCREEN_SCALE = 16;
int SCREEN_WIDTH;
int SCREEN_HEIGHT;
int disasmnum;

SDL_Window* sWindow = NULL;
SDL_Surface* sScreen = NULL;
SDL_Event e;
SDL_AudioSpec device;
SDL_AudioDeviceID devicenum;
struct sound
	{
		SDL_AudioSpec* meta;
		Uint32 length;
		Uint8 **buffer;
	} beepsound;

WINDOW *dbgwin;
WINDOW *disasmwin;
WINDOW *srcwin;
WINDOW *keywin;
WINDOW *botlin;
WINDOW *botlin2;
