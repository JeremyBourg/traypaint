/*
 * traypaint - tiny raylib paint application
 * Copyright (C) 2025 Jérémy Bourg
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "raylib.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_LINES 4096
#define PADDING 50

int w, h, cw, ch;

struct Line {
	Vector2 start, end;
	Color color;
};

bool veccmp(Vector2 v1, Vector2 v2) {
	return (v1.x == v2.x && v1.y == v2.y);
}

void clampVector2(Vector2 *v, int cw, int ch) {
	if(v->x < PADDING)
		v->x = PADDING;
	if(v->y < PADDING)
		v->y = PADDING;
	if(v->x >= cw+PADDING)
		v->x = cw+PADDING;
	if(v->y >= ch+PADDING)
		v->y = ch+PADDING;
}

Vector2 getCanvasPos() {
	Vector2 v = GetMousePosition();
	clampVector2(&v, cw, ch);
	return v;
}

void drawLines(struct Line lines[]) {
	for(int i=0; i<MAX_LINES; ++i) {
		DrawLineV(lines[i].start,
				lines[i].end,
				lines[i].color);
	}
}

int main(void) {
	char *title = "traypaint;";

	w=h=cw=ch=0;
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(600, 400, title);

	SetExitKey(KEY_Q);

	Vector2 startpos, endpos, endposl;
	int cnt=0;
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
		ClearBackground(LIGHTGRAY);

		w = GetRenderWidth();
		h = GetRenderHeight();

		// Draw canvas
		cw = GetRenderWidth() - PADDING*2;
		ch = GetRenderHeight() - PADDING*2;
		DrawRectangle(PADDING, PADDING, cw, ch, RAYWHITE);

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
			startpos = getCanvasPos();
		}
		if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			endpos = getCanvasPos();
			DrawLineV(startpos, endposl, RAYWHITE);
			DrawLineV(startpos, endpos, currentColor);
		}
		if(!veccmp(endposl, endpos))
			endposl = endpos;

		if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
			struct Line tmp;
			tmp.start = startpos;
			tmp.end = endpos;
			tmp.color = currentColor;

			if(cnt < MAX_LINES)
				lines[cnt++] = tmp;
		}

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
