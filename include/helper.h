#include "definitions.h"

// - Structure definitions
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

typedef struct {
    Rectangle shape;
    Rectangle tracer;
    bool active;
} GameObject;

// - Constructors
uint16 MakeColor(uint8 red, uint8 green, uint8 blue);

Rectangle MakeRect(Point _pos, Point _size, uint16 _color);

Point MakePoint(int x, int y);

GameObject MakeGameObject(Rectangle _shape);

// - Collision Detection
bool AABB(GameObject a, GameObject b);

// - Drawing Functions
void DrawRect(Rectangle rect);

void DrawGameObject(GameObject g, bool _tracer);

// - Input Handling
void key_poll();

uint32 getKeyState(uint16 key_code);

uint16 wasKeyPressed(uint16 key_code);

uint16 wasKeyReleased(uint16 key_code);

// - Other
void MoveObject(GameObject* obj, char axis, int amt);

void AddPoints(Point* a, Point b);