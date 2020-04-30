#include "definitions.h"

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point pos;
    Point prev_pos;
    Point size;
    uint16 color;
} Rectangle;

uint16 MakeColor(uint8 red, uint8 green, uint8 blue);

Rectangle MakeRect(Point _pos, Point _size, uint16 _color);

Point MakePoint(int x, int y);

void DrawRect(Rectangle rect);

void key_poll();

uint32 getKeyState(uint16 key_code);

uint16 wasKeyPressed(uint16 key_code);
uint16 wasKeyReleased(uint16 key_code);