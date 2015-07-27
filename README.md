# chip8
A not so simple Chip8 emulator

Hosted is everything you need to run the emulator and play Pong!
Pong rom is in the public domain, in addition to beep.wav.

The controls are as follows:

123C    \   1234
456D  == \  qwer
789E  == /  asdf
A0BF    /   zxcv

[ decreases screen scale
] incrases screen scale

P pauses the emulator

Bugs:
-Debug mode doesn't work with SDL.
-Audio might occasionally stutter, haven't heard it though 

Todo:
-remove Ncurses mode, it's slow and hacky
-fix debug mode to work with SDL
-add built in controls display

Notes:
-Requires > SDL 2.0.4 to build, due to the audio code
-Slows down as you increase the screen scale
