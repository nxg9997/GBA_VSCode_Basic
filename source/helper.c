#include "helper.h"

// - Creates a GBA color value (0-31 are acceptable values)
uint16 MakeColor(uint8 red, uint8 green, uint8 blue)
{
    return red | green << 5 | blue << 10;
}

// - Makes a Rectangle object
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

// - Makes a Point object
Point MakePoint(int x, int y)
{
    Point p;
    p.x = x;
    p.y = y;
    return p;
}

// - Makes a GameObject
GameObject MakeGameObject(Rectangle _shape)
{
    GameObject go;
    go.shape = _shape;
    go.tracer = _shape;
    go.tracer.color = MakeColor(0,0,0);
    go.active = true;

    return go;
}

// - Draws a Rectangle
void DrawRect(Rectangle rect)
{
    if(rect.pos.x < 0 || rect.pos.y < 0) return;
    int xDiff = rect.size.x;
    int yDiff = rect.size.y;
    int x,y;
	for(x = 0; x < xDiff; ++x){
		for( y = 0; y < yDiff; ++y){
            /*if(x == 0 || x == xDiff - 1 || y == 0 || y == yDiff - 1)
			    (SCREENBUFFER)[(rect.pos.x + x)+(rect.pos.y + y)*240] = MakeColor(31,0,0);
			else*/
                (SCREENBUFFER)[(rect.pos.x + x)+(rect.pos.y + y)*240] = rect.color;
		}
	}
}

// - Collision Detection
bool AABB(GameObject a, GameObject b)
{
    if (a.shape.pos.x < b.shape.pos.x + b.shape.size.x &&
        a.shape.pos.x + a.shape.size.x > b.shape.pos.x &&
        a.shape.pos.y < b.shape.pos.y + b.shape.size.y &&
        a.shape.pos.y + a.shape.size.y > b.shape.pos.y) {
            return true;
    }

    return false;
}

// - Move a GameObject around (must use this method for proper tracer)
void MoveObject(GameObject* obj, char axis, int amt)
{
    //obj->tracer.pos = obj->shape.pos;
    /*int x = obj->shape.pos.x;
    int y = obj->shape.pos.y;*/
    if(axis == 'y')
    {
        obj->tracer.pos.y = obj->shape.pos.y;
        obj->shape.pos.y += amt;


        //obj->tracer.pos.y = obj->shape.pos.y - obj->shape.size.y - amt;
        //obj->tracer.size.y = amt;
        //obj->tracer.size.x = obj->shape.size.x;

        /*if(amt > 0)
            y = obj->shape.pos.y - amt;
        if(amt < 0)
            y = obj->shape.pos.y + amt;*/
    }

    if(axis == 'x')
    {
        obj->tracer.pos.x = obj->shape.pos.x;
        obj->shape.pos.x += amt;

        //obj->tracer.pos.x = obj->shape.pos.x - obj->shape.size.x - amt;
        //obj->tracer.size.x = amt;
        //obj->tracer.size.y = obj->shape.size.y;

        /*if(amt > 0)
            x = obj->shape.pos.x - amt;
        if(amt < 0)
            x = obj->shape.pos.x + amt;*/
    }
    
   // obj->tracer.pos = MakePoint(x,y);
}

// - Draws a GameObject, with the option to draw a tracer to cover its previous draw
void DrawGameObject(GameObject g, bool _tracer)
{
    if(_tracer) DrawRect(g.tracer);
    DrawRect(g.shape);
}

// - Adds a point to a point
void AddPoints(Point* a, Point b)
{
    a->x += b.x;
    a->y += b.y;
}