#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#define LX 15
#define LY 12
#define RX 65
#define RY 23
#define DELAY 0.4
#define STR_STEP 2

void scroll(char ch, char cl, char dh, char dl, char attr) {
	union REGS r;
	r.h.ah = 7;
	r.h.al = 1;
	r.h.ch = ch;
	r.h.cl = cl;
	r.h.dh = dh;
	r.h.dl = dl;
	r.h.bh = attr;
	int86(0x10, &r, &r);
}

int main() {
	const char* colors[] = {
		"BLACK", "BLUE", "GREEN", "CYAN", "RED", "MAGENTA", "BROWN", "LIGHTGRAY",
		"DARKGREY", "LIGHTBLUE", "LIGHTGREEN", "LIGHTCYAN", "LIGHTRED", "LIGHTMAGENTA", "YELLOW", "WHITE"
	};
	window(LX, LY, RX, RY);
	system("cls");
	for (int b = 0; b < 8; b++) {
		for (int t = 0; t < 16; t++) {
			for (int j = 0; j < STR_STEP; j++ ) insline();
			textbackground(b);
			gotoxy(1, 1);
			for (int w = LX; w <= RX; w++) cprintf(" ");
			gotoxy(1, 1);
			textcolor(t);
			cprintf("text = %s, back = %s", colors[t], colors[b]);
			delay(DELAY * 1000);
			scroll(LX, RY, RX, LY, b);
		}
	}
	return 0;
}