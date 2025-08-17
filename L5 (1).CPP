#include <iostream.h>
#include <graphics.h>
#include <stdlib.h>
#include <time.h>
#include <dos.h>
#include <conio.h>

enum FLAGS {
    CHANGESTYLE,
    EXIT,
    DEFAULT
};

FLAGS fl = DEFAULT;
void interrupt (*oldHandler)(...);
void interrupt handler(...) {

    unsigned char scanCode = inp(0x60); //scancode will be placed at 0x60
    if (scanCode == 0x3D) {
	fl = CHANGESTYLE;
    } else if (scanCode == 0x01) {
	fl = EXIT;
    } else {
	fl = DEFAULT;
    }
    oldHandler();
}

int main() {
    oldHandler = getvect(0x09);
    setvect(0x09, handler);
    int graphDr = DETECT, graphMode;
    initgraph(&graphDr, &graphMode, "..\\BGI");
    int error = graphresult();
    if (error != grOk) return error;
    srand(time(NULL));
    unsigned char text[2];
    text[0] = rand() % 93 + 33;
    text[1] = '\0';
    int x = getmaxx() / 2;
    int y = getmaxy() / 2;
    int style = 0;
    while (fl != EXIT) {
	switch (fl) {
	case DEFAULT:
		setcolor(WHITE);
		outtextxy(x, y, text);
		break;
	case CHANGESTYLE:
		setcolor(BLACK);
		outtextxy(x, y, text);
		style = (style + 1) % 5;
		settextstyle(style, HORIZ_DIR, 0);
		fl = DEFAULT;
		break;
	}

    }
    closegraph();
    setvect(0x09, oldHandler);
    return 0;
}
