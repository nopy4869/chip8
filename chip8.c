/*
Chip 8 emulator ^.^
Some code may have come from:
http://www.multigesture.net/articles/how-to-write-an-emulator-chip-8-interpreter/
*/

#ifndef LINUX
	#define LINUX 1
#endif

#define true TRUE
#define false FALSE

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <curses.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include "chip8tables.c"
#include "chip8common.c"
#include "chip8input.h"  // custom input library ^.^
#include "chip8video.h"  // custom output library ^.^
#include "chip8dbg.h"    // custom library made for ease of use debugging ^.^
#include "chip8cpu.h"    // custom chip8 cpu library ^.^
#include "chip8SDL.h"    // custom SDL functionality ^.^ 

int nruncycle();
void sruncycle();

int main(int argc, char **argv) 
{
	// Initialize the Chip8 system and load the game into the memory
	initscr();
	cbreak();
	dbgwin = derwin(stdscr,36,20,0,65);
	srcwin = derwin(stdscr,(LINES-35),64,33,0);
	keywin = derwin(stdscr,5,5,36,65);
	botlin = derwin(stdscr,1,64,(LINES-1),0);
	botlin2 = derwin(stdscr,1,64,(LINES-2),0);
	scrollok(stdscr,TRUE);
	scrollok(botlin, FALSE);
	scrollok(botlin2, TRUE);
	colorcheck();
	initcpu();
	if(loadgame() == 1)
	{
		wprintw(stdscr, "Unable to load game.\n");
		wrefresh(stdscr);
		hang(3);
		endwin();
		return 1;
	}
	if(cpu.stepthru == 1)
	{
		cyclemem();
	}
	cpu.tick = 0;
	char fail;
	if(cpu.SDL == 1)
	{
		fail = SDLInit();
		if(fail != 0)
		{
			wclear(stdscr);
			wprintw(stdscr, "SDL init failed: Error code %d\n", fail);
			wrefresh(stdscr);
			hang(3);
			endwin();
			return 1;
		}
		sruncycle();
	}
	else
		nruncycle();
	return 0;
} 

int nruncycle()
{
	for(;;)
	{
		if(cpu.stepthru == 1)
		{
			if(cpu.dt > 0)
				cpu.dt--;
			if(cpu.st > 0)
				cpu.st--;
		}
		usleep(500);
		if((cpu.tick % 2) == 0)
		{
			if(cpu.dt > 0)
				cpu.dt--;
			if(cpu.st > 0)
				cpu.st--;
		}
		if(cpu.st > 0)
		{
			printf("\b\n");
		}
		if(cycle() == 1)
		{
			wclear(stdscr);
			wprintw(stdscr, "This shouldn't be possible...\nOh well, it failed to emulate this cycle... Shutting down now!\n");
			wrefresh(stdscr);
			hang(3);
			endwin();
			return 1;
		}
		if(cpu.drawflag == 1)
			printscreen();
		input('n');
		cpu.tick += 1;
	}
}

void sruncycle()
{
	for(;;)
	{
		if(cpu.ispaused == 0)
		{
			if(cpu.stepthru == 1)
			{
				if(cpu.dt > 0)
					cpu.dt--;
				if(cpu.st > 0)
					cpu.st--;
			}
			usleep(500);
			if((cpu.tick % 2) == 0)
			{
				if(cpu.dt > 0)
					cpu.dt--;
				if(cpu.st > 0)
					cpu.st--;
			}
			if(cpu.st > 0)
			{
				SDLBeep(1);
			}
//			else
//			{
//				SDLBeep(0);
//			}
			if(cycle() == 1)
			{
				wclear(stdscr);
				wprintw(stdscr, "This shouldn't be possible...\nOh well, it failed to emulate this cycle... Shutting down now!\n");
				wrefresh(stdscr);
				hang(3);
				endwin();
				ExitHard();
			}
			if(cpu.drawflag == 1)
				drawscreen();
			SDLinput();
			cpu.tick += 1;
		}
		else
		{
			SDLinput();
		}
	}
}
