#include <iostream.h>
#include <dos.h>
#include <conio.h>

#define LX 15
#define LY 12
#define RX 65
#define RY 23
#define DELAY 0.4
#define STR_STEP 2

int main() {
    
    const char* colors[] = {
        "BLACK", "BLUE", "GREEN", "CYAN", "RED", "MAGENTA", "BROWN", "LIGHTGRAY",
        "DARKGREY", "LIGHTBLUE", "LIGHTGREEN", "LIGHTCYAN", "LIGHTRED", "LIGHTMAGENTA", "YELLOW", "WHITE"
    };
    window(LX, LY, RX, RY);
    clrscr();

    for (int b = 0; b < 8; b++) {
        for (int t = 0; t < 16; t++) {
            insline();
            insline();
            textbackground(b);
            gotoxy(1, 1); 
            for (int i = LX; i <= RX; i++) {
                cprintf(" "); 
            }
            textcolor(t);
            gotoxy(1, 1);
            cprintf("text = %s, back =  %s", colors[t], colors[b]);
            delay(DELAY * 1000);
            
        }
    }
    
    return 0;
}