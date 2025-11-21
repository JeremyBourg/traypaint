#include "raylib.h"
#include <string.h>
#include <stdio.h>

#define MAX_LINES 4096

struct Line {
	int xs, ys, xe, ye;
	Color color;
};

void drawLines(struct Line lines[]) {
	for(int i=0; i<MAX_LINES; ++i) {
		DrawLine(lines[i].xs,
				lines[i].ys,
				lines[i].xe,
				lines[i].ye,
				lines[i].color);
	}
}

int main(void) {
	char *title = "traypaint;";
	int w, h;
	w=h=0;
	InitWindow(w, h, title);

	SetExitKey(KEY_CAPS_LOCK);

	int xstart, ystart, xend, yend, xendl, yendl;
	int cnt=0;
	xendl = yendl = -1;
	struct Line lines[MAX_LINES];
	memset(lines, 0, sizeof(lines));

	Color colors[] = {
		BLACK,
		DARKGRAY,
		GRAY,
		LIGHTGRAY,
		WHITE,
		YELLOW,
		ORANGE,
		PINK,
		RED,
		GREEN,
		BLUE,
		PURPLE,
	};

	Color currentColor=BLACK;
	while(!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(RAYWHITE);

		w = GetRenderWidth();
		h = GetRenderHeight();

		// Draw data
		drawLines(lines);

		// Color boxes
		int cbw = (w/2) /
			(sizeof(colors)/sizeof(colors[0]));
		int cbh = cbw;
		for(size_t i=0; i < sizeof(colors)/sizeof(colors[0]); ++i) {
			DrawRectangle(cbw*i, h-cbh, cbw, cbh, colors[i]);

			// Color selection
			if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				Vector2 pos = GetMousePosition();

				if (pos.x >= cbw*i && pos.x < cbw*(i+1) &&
						pos.y >= h-cbh && pos.y < h)
					currentColor = colors[i];
			}
		}

		// Get mouse position
		if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			xstart = GetMouseX();
			ystart = GetMouseY();
		}
		if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			xend = GetMouseX();
			yend = GetMouseY();
			if(xendl != -1 && yendl != -1)
				DrawLine(xstart, ystart, xendl, yendl, RAYWHITE);
			DrawLine(xstart, ystart, xend, yend, currentColor);
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
			tmp.color = currentColor;

			if(cnt < MAX_LINES)
				lines[cnt++] = tmp;
		}

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
