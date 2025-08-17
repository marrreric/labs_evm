#include <dos.h>
#include <conio.h>

const int x1 = 15, x2 = 65, y1 = 12, y2 = 23;
void customGetch(unsigned char* first, unsigned char* second) {
    union REGS r;
    r.h.ah = 0;
    int86(0x16, &r, &r);
    *first = r.h.al;
    *second = r.h.ah;
}

int customKbhit(void) {
    union REGS r;
    r.h.ah = 0x0B;
    int86(0x21, &r, &r);
    if (r.h.al == 0xFF)
	return 1;
    else
	return 0;
}

void moveLeft() {
    int x = wherex();
    int y = wherey();

    if (x > 1) {
	cprintf(" ");
	gotoxy(x - 1, y);
	cprintf("*");
	gotoxy(x - 1, y);
	delay(100);
    }
}

void moveRight() {
    int x = wherex();
    int y = wherey();

    if (x < (x2 - x1)) {
	cprintf(" ");
	gotoxy(x + 1, y);
	cprintf("*");
	gotoxy(x + 1, y);
	delay(100);
    }
}

int main() {
    textbackground(BLACK);
    clrscr();
    window(x1, y1, x2, y2);
    textbackground(WHITE);
    clrscr();
    textcolor(RED);

    int x = (x2 - x1) / 2;
    gotoxy(x, 1);
    cprintf("*");
    gotoxy(x, 1);


    while (1) {
	if (customKbhit()) {
	    unsigned char firstKey, secondKey;
	    customGetch(&firstKey, &secondKey);
	    if (firstKey == 0 || firstKey == 224) {
		switch (secondKey) {
		case 77:
		    moveRight();
		    break;
		case 75:
		    moveLeft();
		    break;
		}
	    }
	    else if (firstKey == 27) {
		break;
	    }
	}
    }
    return 0;
}

