#include <numeric>
#include "raylib.h"
#include "raymath.h"

#define Width 800
#define Height 600
#define CellSize 25
#define CellBoarder 5

#define CellRow Width  / CellSize
#define CellCol Height / CellSize

enum CellType : uint16_t {
	Empty = 0,
	Snake = 1,
	Food  = 2
};
CellType cells[CellRow][CellCol];

void genFood() {
	int32_t foodX = -1, foodY = -1;
	do {
		foodX = GetRandomValue(0, CellRow);
		foodY = GetRandomValue(0, CellCol);
	} while (cells[foodX][foodY] != CellType::Empty);
	cells[foodX][foodY] = CellType::Food;
}

void reset() {
	for (uint32_t x = 0; x < CellRow; x++) {
		for (uint32_t y = 0; y < CellCol; y++) {
			cells[x][y] = CellType::Empty;
		}
	}
	genFood();
}

void drawGame() {
	for (uint32_t x = 0; x < CellRow; x++) {
		for (uint32_t y = 0; y < CellCol; y++) {
			uint32_t cx = x * CellSize + CellBoarder;
			uint32_t cy = y * CellSize + CellBoarder;
			uint32_t cs = CellSize - 2 * CellBoarder;

			switch (cells[x][y]) {
			case CellType::Empty:
				DrawRectangle(cx, cy, cs, cs, { 102, 102, 153, 255 });
				break;
			case CellType::Snake:
				DrawRectangle(cx, cy, cs, cs, { 0, 255, 153, 255 });
				break;
			case CellType::Food:
				DrawRectangle(cx, cy, cs, cs, { 255, 0, 102, 255 });
				break;
			default:
				DrawRectangle(cx, cy, cs, cs, { 255, 0, 0, 255 });
				break;
			}
		}
	}
}

int main(int argc, char* argv[]) {
	InitWindow(Width, Height, "Snake");
	//SetWindowState(FLAG_VSYNC_HINT); // VSYNC
	
	reset();
	while(!WindowShouldClose()) {
		BeginDrawing();
			ClearBackground({ 45, 45, 45, 255 });
			drawGame();
			//DrawFPS(0, 0);
		EndDrawing();
	}
	CloseWindow();
}
