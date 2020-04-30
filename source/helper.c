#include "helper.h"


uint16 MakeColor(uint8 red, uint8 green, uint8 blue)
{
    return red | green << 5 | blue << 10;
}

Rectangle MakeRect(Point _pos, Point _size, uint16 _color)
{
    Rectangle rect;
    rect.pos = _pos;
    rect.size = _size;
    rect.color = _color;
    rect.prev_pos.x = -1;
    rect.prev_pos.y = -1;

    return rect;
}

Point MakePoint(int x, int y)
{
    Point p;
    p.x = x;
    p.y = y;
    return p;
}

void DrawRect(Rectangle rect)
{
    if(rect.pos.x < 0 || rect.pos.y < 0) return;
    int xDiff = rect.size.x;
    int yDiff = rect.size.y;
    int x,y;
	for(x = 0; x < xDiff; ++x){
		for( y = 0; y < yDiff; ++y){
			(SCREENBUFFER)[(rect.pos.x + x)+(rect.pos.y + y)*240] = rect.color;
		}
	}
}