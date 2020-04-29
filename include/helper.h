#include "definitions.h"

typedef struct {
    unsigned int x;
    unsigned int y;
} Point;

typedef struct {
    Point pos;
    Point size;
    uint16 color;
} Rectangle;

uint16 MakeColor(uint8 red, uint8 green, uint8 blue);

Rectangle MakeRect(Point _pos, Point _size, uint16 _color);

Point MakePoint(int x, int y);

void DrawRect(Rectangle* rect);