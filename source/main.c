#include "Intellisense.h"
#include "helper.h"

uint8 colorSwap = 0;

void vsync()
{
  while (REG_VCOUNT >= 160);
  while (REG_VCOUNT < 160);
}

void Draw(unsigned short* imgPtr)
{
	int x,y;
	for(x = 0; x < 240; ++x){
		for( y = 0; y < 160; ++y){
			(SCREENBUFFER)[x+y*240] = *imgPtr++;
		}
	}
}

void ChangeColor(unsigned short* imgPtr)
{ //0x0909 32bit red 2400
	unsigned short color = *imgPtr;
	//const uint16 white = MakeColor(31,31,31);
	switch(colorSwap){
		case 0:
			color = MakeColor(31,0,0);
			colorSwap++;
			break;
		case 1:
			color = MakeColor(0,31,0);
			colorSwap++;
			break;
		case 2:
			color = MakeColor(0,0,31);
			colorSwap++;
			break;
		default:
			color = MakeColor(31,31,31);
			colorSwap = 0;
			break;
	}

	for(unsigned int i = 0; i < 240*160; i++)
	{
		*imgPtr = color;
		imgPtr++;
	}
}

void drawRect(int left, int top, int width, int height, uint16 clr)
{
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
    	   (SCREENBUFFER)[(top + y) * SCREEN_W + left + x] = clr;
        }
    }
}



int main()
{
	//set GBA rendering context to MODE 3 Bitmap Rendering
	REG_DISPLAYCONTROL = VIDEOMODE_3 | BGMODE_2;

	unsigned short img[240*160] = {0x0000};

	uint16 color = MakeColor(31,0,0);
	for(unsigned int i = 0; i < 240*160; i++)
	{
		img[i] = color;
	}
	
	int t = 0;
	uint16 white = MakeColor(31,31,31);
	uint16 black = MakeColor(0,0,0);
	uint8 dir = 1;

	Rectangle rect = MakeRect(MakePoint(0,0),MakePoint(10,10),white);
	Rectangle rect2 = MakeRect(MakePoint(0,0),MakePoint(10,10),black);

	Draw(&img);
	int x = 0;
	while(1){
		vsync();

		

		bool keypressed = 0;

		key_poll();
        if ( getKeyState(KEY_DOWN) )
        {
			rect2.pos = rect.pos;
            rect.pos.y += 10;
			keypressed = 1;
        }
		else if ( getKeyState(KEY_UP) )
        {
			rect2.pos = rect.pos;
            rect.pos.y -= 10;
			keypressed = 1;
        }
		else if ( getKeyState(KEY_LEFT) )
        {
			rect2.pos = rect.pos;
            rect.pos.x -= 10;
			keypressed = 1;
        }
		if ( getKeyState(KEY_RIGHT) )
        {
			rect2.pos = rect.pos;
            rect.pos.x += 10;
			keypressed = 1;
        }
		
		if(keypressed){
			DrawRect(rect2);

			DrawRect(rect);
		}

		
		/*
		if ( x > SCREEN_W * (SCREEN_H/10)) x = 0;
		if (x)
		{
			int last = x - 10;
			drawRect(last % SCREEN_W, (last / SCREEN_W) * 10, 10, 10,MakeColor(0,0,0));
		}

		drawRect(x % SCREEN_W, (x / SCREEN_W) * 10, 10, 10,MakeColor(31,31,31));
		x += 10;
		*/
	}
	return 0;
}