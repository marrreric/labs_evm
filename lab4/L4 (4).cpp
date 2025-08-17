#include <dos.h>
#include <conio.h>
#include <iostream.h>

const int x1 = 15, x2 = 65, y1 = 12, y2 = 23;

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
        if (kbhit()) {
            int key = getch();
            if (key == 0 || key == 224) {
                key = getch();
                switch (key) {
                case 77:
                    moveRight();
                    break;
                case 75:
                    moveLeft();
                    break;
                }
            }
            else if (key == 27) {
                break;
            }
        }
    }
    return 0;
}

