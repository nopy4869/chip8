#include <stdio.h>
void ExitHard();
void resize(char ud);

int hang (int howlonghang)
{
	int x;
	for(x=0;x<howlonghang;x++)
	{
		usleep(999999);
		usleep(1);
	}
	return 0;
};

int bi ()
{
	noecho();
	cbreak();
	nodelay(stdscr, FALSE);
	int read = getch();
//	if(cpu.stepthru == 1)
//		return '2';
	return read;
};

int bie ()
{
	echo();
	cbreak();
	nodelay(stdscr, FALSE);
	int read = getch();
	noecho();
	return read;
};

int nbi ()
{
	noecho();
	cbreak();
	nodelay(stdscr, TRUE);
	int read = getch();
	noecho();
	if(cpu.stepthru == 1)
		return '2';
	return read;
};

void input(char type)
{
	char inp;
	int x;
	int y;
	for(x = 0; x < 16; x++)
	{
		if(cpu.key[x] > 0)
			cpu.key[x] -= 1;
	}
	if(type == 'b')
	{
		inp = bi();
		for(y = 0; y < 16; y++)
		{
			if(inp == keymap[y])
				cpu.key[y] = 50;
		}
	}
	if(type == 'n')
	{
		for(x = 0; x < 16; x++)
		{
			inp = nbi();
			for(y = 0; y < 16; y++)
			{
				if(inp == keymap[y])
					cpu.key[y] = 50;
			}
		}
	}
};

void keypadclear()
{
	int x;
	for(x = 0; x < 16; x++)
	{
		cpu.key[x] = 0;
	}
};

void SDLinput()
{
	while( SDL_PollEvent( &e ) != 0 )
	{
		if (e.type == SDL_QUIT)
		{
			ExitHard();
		}
		if (e.type == SDL_KEYDOWN)
		{
			if(e.key.keysym.scancode == SDL_SCANCODE_1)
			{
				cpu.key[1] = 1;
			}
			if(e.key.keysym.scancode == SDL_SCANCODE_2)
			{
				cpu.key[2] = 1;
			}
			if(e.key.keysym.scancode == SDL_SCANCODE_3)
			{
				cpu.key[3] = 1;
			}
			if(e.key.keysym.scancode == SDL_SCANCODE_4)
			{
				cpu.key[12] = 1;
			}
			if(e.key.keysym.scancode == SDL_SCANCODE_Q)
			{
				cpu.key[4] = 1;
			}
			if(e.key.keysym.scancode == SDL_SCANCODE_W)
			{
				cpu.key[5] = 1;
			}
			if(e.key.keysym.scancode == SDL_SCANCODE_E)
			{
				cpu.key[6] = 1;
			}
			if(e.key.keysym.scancode == SDL_SCANCODE_R)
			{
				cpu.key[13] = 1;
			}
			if(e.key.keysym.scancode == SDL_SCANCODE_A)
			{
				cpu.key[7] = 1;
			}
			if(e.key.keysym.scancode == SDL_SCANCODE_S)
			{
				cpu.key[8] = 1;
			}
			if(e.key.keysym.scancode == SDL_SCANCODE_D)
			{
				cpu.key[9] = 1;
			}
			if(e.key.keysym.scancode == SDL_SCANCODE_F)
			{
				cpu.key[14] = 1;
			}
			if(e.key.keysym.scancode == SDL_SCANCODE_Z)
			{
				cpu.key[10] = 1;
			}
			if(e.key.keysym.scancode == SDL_SCANCODE_X)
			{
				cpu.key[0] = 1;
			}
			if(e.key.keysym.scancode == SDL_SCANCODE_C)
			{
				cpu.key[11] = 1;
			}
			if(e.key.keysym.scancode == SDL_SCANCODE_V)
			{
				cpu.key[15] = 1;
			}
			
			
			if(e.key.keysym.scancode == SDL_SCANCODE_P)
			{
				cpu.ispaused = cpu.ispaused ^ 1;
			}
			
			
		}
		if (e.type == SDL_KEYUP)
		{
			if(e.key.keysym.scancode == SDL_SCANCODE_1)
			{
				cpu.key[1] = 0;
			}
			if(e.key.keysym.scancode == SDL_SCANCODE_2)
			{
				cpu.key[2] = 0;
			}
			if(e.key.keysym.scancode == SDL_SCANCODE_3)
			{
				cpu.key[3] = 0;
			}
			if(e.key.keysym.scancode == SDL_SCANCODE_4)
			{
				cpu.key[12] = 0;
			}
			if(e.key.keysym.scancode == SDL_SCANCODE_Q)
			{
				cpu.key[4] = 0;
			}
			if(e.key.keysym.scancode == SDL_SCANCODE_W)
			{
				cpu.key[5] = 0;
			}
			if(e.key.keysym.scancode == SDL_SCANCODE_E)
			{
				cpu.key[6] = 0;
			}
			if(e.key.keysym.scancode == SDL_SCANCODE_R)
			{
				cpu.key[13] = 0;
			}
			if(e.key.keysym.scancode == SDL_SCANCODE_A)
			{
				cpu.key[7] = 0;
			}
			if(e.key.keysym.scancode == SDL_SCANCODE_S)
			{
				cpu.key[8] = 0;
			}
			if(e.key.keysym.scancode == SDL_SCANCODE_D)
			{
				cpu.key[9] = 0;
			}
			if(e.key.keysym.scancode == SDL_SCANCODE_F)
			{
				cpu.key[14] = 0;
			}
			if(e.key.keysym.scancode == SDL_SCANCODE_Z)
			{
				cpu.key[10] = 0;
			}
			if(e.key.keysym.scancode == SDL_SCANCODE_X)
			{
				cpu.key[0] = 0;
			}
			if(e.key.keysym.scancode == SDL_SCANCODE_C)
			{
				cpu.key[11] = 0;
			}
			if(e.key.keysym.scancode == SDL_SCANCODE_V)
			{
				cpu.key[15] = 0;
			}
			if(e.key.keysym.scancode == SDL_SCANCODE_LEFTBRACKET)
			{
				resize(0);
			}
			if(e.key.keysym.scancode == SDL_SCANCODE_RIGHTBRACKET)
			{
				resize(1);
			}
		}
	}
}
