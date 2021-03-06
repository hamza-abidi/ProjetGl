#include "input.h"
#include <stdio.h>
#include <unistd.h>

#define UP 'z'
#define RIGHT 'd'
#define DOWN 's'
#define LEFT 'q'
#define ESC 27;

Input::Input() {
	old_tio = new termios;
	tcgetattr(STDIN_FILENO, old_tio);
	
	struct termios new_tio;
	new_tio = *old_tio;
	new_tio.c_lflag &=(~ICANON & ~ECHO);
	tcsetattr(STDIN_FILENO,TCSANOW,&new_tio);
}

Input::~Input() {
	tcsetattr(STDIN_FILENO,TCSANOW,old_tio);
}

unsigned char Input::keyboard() {
	unsigned char c;
	do {
		c = getchar();
		if(c == 27) {
			if(getchar() == 91) {
				c = getchar();
				switch(c) {
				case 65:
					return UP;
					break;
				case 66:
					return DOWN;
					break;
				case 67:
					return RIGHT;
					break;
				case 68:
					return LEFT;
					break;
				}
			}
			else return ESC;
		}
		if(c == UP | c == RIGHT | c == DOWN | c == DOWN) return c;
	} while(true);

}
