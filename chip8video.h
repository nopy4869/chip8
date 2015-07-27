void printscreen ()
{
	int x;
	int y;
	clear();
	mvwprintw(stdscr, 0,0,"");
	for(y = 0; y < 32; y++)
	{
		for(x = 0; x < 64; x++)
			{
				if(cpu.gfx[x][y] == 0)
					wprintw(stdscr, " ");
				if(cpu.gfx[x][y] == 1)
					wprintw(stdscr, "#");
			}
			wprintw(stdscr, "|\n");
	}
	for(x = 0; x < 64; x++)
	{
		wprintw(stdscr, "-");
	}
	wprintw(stdscr, "+");
	cpu.drawflag = 0;
	wrefresh(stdscr);
};
