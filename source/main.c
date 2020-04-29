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

int main()
{
	//set GBA rendering context to MODE 3 Bitmap Rendering
	REG_DISPLAYCONTROL = VIDEOMODE_3 | BGMODE_2;

	unsigned short img[240*160] = {0x0000};

	uint16 color = MakeColor(31,31,31);
	for(unsigned int i = 0; i < 240*160; i++)
	{
		img[i] = color;
	}

	Rectangle rect = MakeRect(MakePoint(10,10),MakePoint(20,20),MakeColor(31,0,0));
	
	int t = 0;
	while(1){
		vsync();
		//Draw(img);
		DrawRect(&rect);
		rect.pos.x += 20;
		if(rect.pos.x >= SCREEN_W){
			rect.pos.x = 0;
			rect.pos.y += 20;
		}
		if(rect.pos.y >= SCREEN_H){
			rect.pos.y = 0;
			rect.color = MakeColor(t,0,0);
			t++;
			if(t > 31){
				t = 0;
			}
		}
	}
	return 0;
}