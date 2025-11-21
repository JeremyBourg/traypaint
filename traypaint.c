#include "raylib.h"
#include <string.h>
#include <stdio.h>

#define MAX_LINES 4096

struct Line {
	int xs, ys, xe, ye;
};

void drawLines(struct Line lines[], Color color) {
	for(int i=0; i<MAX_LINES; ++i) {
		DrawLine(lines[i].xs,
				lines[i].ys,
				lines[i].xe,
				lines[i].ye,
				color);
	}
}

int main(void) {
	char *title = "traypaint;";

	InitWindow(0, 0, title);
	int w = GetRenderWidth();
	int h = GetRenderHeight();
	SetExitKey(KEY_CAPS_LOCK);
	printf("Width: %d\nHeight: %d\n", w, h);

	int xstart, ystart, xend, yend, xendl, yendl;
	int cnt=0;
	xendl = yendl = -1;
	struct Line lines[MAX_LINES];
	memset(lines, 0, sizeof(lines));

	while(!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(RAYWHITE);

		if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			xstart = GetMouseX();
			ystart = GetMouseY();
		}
		if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			xend = GetMouseX();
			yend = GetMouseY();
			if(xendl != -1 && yendl != -1)
				DrawLine(xstart, ystart, xendl, yendl, RAYWHITE);
			DrawLine(xstart, ystart, xend, yend, RED);
		}
		if(xendl != xend)
			xendl = xend;
		if(yendl != yend)
			yendl = yend;

		if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
			struct Line tmp;
			tmp.xs = xstart;
			tmp.ys = ystart;
			tmp.xe = xend;
			tmp.ye = yend;

			if(cnt < MAX_LINES)
				lines[cnt++] = tmp;
		}

		drawLines(lines, RED);
		EndDrawing();
	}

	CloseWindow();

	return 0;
}
