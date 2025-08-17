#define _USE_MATH_DEFINES
#include <graphics.h>
#include <stdlib.h>
#include <dos.h>
#include <stdio.h>
#include <math.h>

#define INFINITY (1.0 / 0.0)

const int XL = 20, YL = 45, XR = 520, YR = 325;
const int startY = (YR + YL) / 2, startX = XL + 5, gap = 20;

void drawAxis() {
	setbkcolor(BLACK);
	setcolor(WHITE);
	line(startX, startY, XR - 5, startY); //OX
	line(startX, YL + 5, startX, YR - 5); //OY
	outtextxy(XL - textwidth("y") - 2, YL + 5, "y");
	outtextxy(XR - 5, startY + textheight("x") + 2, "x");
	outtextxy(startX - textwidth("0") - 4, startY, "0");
	for (int x = startX + gap, y = startY, cnt = 1; x < XR - 5; cnt++, x += gap) {
		line(x, y - 2, x, y + 2);
		char num[3] = "\0";
		sprintf(num, "%d", cnt);
		outtextxy(x - textwidth(num) / 2, y + 2 + textheight(num), num);
	}
	for (x = startX, y = startY - gap, cnt = 1; y > YL + 5; cnt++, y -= gap) {
		line(x - 2, y, x + 2, y);
		char num[3] = "\0";
		sprintf(num, "%d", cnt);
		outtextxy(x - textwidth(num) - 2, y - textheight(num) / 2, num);
	}
	for (x = startX, y = startY + gap, cnt = -1; y <= YR - 5; cnt--, y += gap) {
		line(x - 2, y, x + 2, y);
		char num[3] = "\0";
		sprintf(num, "%d", cnt);
		outtextxy(x - textwidth(num) - 2, y - textheight(num) / 2, num);
	}
}

void createWindow() {
	setviewport(YL, XL, YR, XR, 1);
}
double func(double x) {
	return pow(sin(x), 3) - pow(cos(x), 3);
}

double _rnd(double val) {
	return int(val * 100.0) / 100.0;
}

void drawPlot() {
	setlinestyle(DASHED_LINE, 0, NORM_WIDTH);
	line(startX + M_PI / 2 * gap, YL + 5, startX + M_PI / 2 * gap, YR - 5);
	line(startX + M_PI * 6 * gap, YL + 5, startX + M_PI * 6 * gap, YR - 5);
	double y;
	for (double x = M_PI / 2; x <= 6 * M_PI; x += 0.05) {
		y = func(_rnd(x));
		putpixel(startX + x * 20, startY - _rnd(y) * 20, YELLOW);
		delay(5);
	}

}


void setMax(double* maxCoords) {
	double maxX = 0.0, maxY = -INFINITY;
	for (double x = M_PI / 2; x <= 6 * M_PI; x += 0.05) {
		double y = func(_rnd(x));

		if (y > maxY) {
			maxY = y;
			maxX = x;
		}
	}

	maxCoords[0] = maxX;
	maxCoords[1] = maxY;

	setcolor(RED);
	int centerX = startX + maxX * 20;
	int centerY = startY - _rnd(maxY) * 20;
	for (int dx = -4; dx <= 4; dx++) {
		for (int dy = -4; dy <= 4; dy++) {
			if (dx * dx + dy * dy <= 16) {
				putpixel(centerX + dx, centerY + dy, RED);
			}
		}
	}

	char coordStr[50];
	sprintf(coordStr, "Max y = %.2lf", maxY);
	outtextxy(startX + maxX * 25, startY - _rnd(maxY) * 25 - 15, coordStr);
}




int main() {
	int graphDr = DETECT, graphMode;
	initgraph(&graphDr, &graphMode, "..\\BGI");
	int error = graphresult();
	if (error != grOk) return error;
	createWindow();
	drawAxis();

	double maxCoords[2];

	drawPlot();

	setMax(maxCoords);

	system("Pause");
	closegraph();
	return 0;
}