#include "Intellisense.h"
#include "helper.h"

uint8 colorSwap = 0;

// - used to prevent tearing (only draw in VDRAW)
void vsync()
{
  while (REG_VCOUNT >= 160);
  while (REG_VCOUNT < 160);
}

// - Draw a screen-sized bitmap
void Draw(unsigned short* imgPtr)
{
	int x,y;
	for(x = 0; x < 240; ++x){
		for( y = 0; y < 160; ++y){
			(SCREENBUFFER)[x+y*240] = *imgPtr++;
		}
	}
}

// - used to test stuff
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

// - used to test stuff
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

	// - create a red bitmap
	unsigned short img[240*160] = {0x0000};

	uint16 color = MakeColor(31,0,0);
	for(unsigned int i = 0; i < 240*160; i++)
	{
		img[i] = color;
	}
	
	int t = 0;

	// - define some basic colors
	uint16 white = MakeColor(31,31,31);
	uint16 black = MakeColor(0,0,0);

	uint8 dir = 1;

	// - create gameobjects for breakout
	Point paddle = MakePoint(20,5);

	Rectangle rect = MakeRect(MakePoint(SCREEN_W / 2 - paddle.x/2, SCREEN_H - 20),MakePoint(paddle.x,paddle.y),white);
	Rectangle rect2 = MakeRect(MakePoint(50,50),MakePoint(20,20),MakeColor(0,0,31));
	GameObject player = MakeGameObject(rect);
	GameObject block = MakeGameObject(rect2);

	GameObject blocks[20];

	int ind = 0;
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 2; j++){
			blocks[ind] = MakeGameObject(MakeRect(MakePoint(i * 10 + i + SCREEN_W / 4 + 5, j * 10 + j + SCREEN_H / 4), MakePoint(10, 10), MakeColor(i * 2, j * 2, 31)));
			ind++;
		}
	}

	GameObject ball = MakeGameObject(MakeRect(MakePoint(SCREEN_W / 2 - 3, SCREEN_H / 2 + 3), MakePoint(6, 6), white));
	Point ballSpd = MakePoint(0, 1);
	
	int x = 0;
	int speed = 2;

	// - define game variables
	int lives = 3;
	int play = false;
	int points = 0;

	/*DrawFourDigit(1234, MakePoint(5,5));
	DrawFourDigit(5678, MakePoint(5,18));
	DrawFourDigit(90,   MakePoint(5,30));*/

	while(1){
		vsync();

		bool keypressed = false;

		key_poll();

		// - press A to play the game
		if(wasKeyPressed(KEY_A)){
			play = true;
		}

		if(!play) continue;

		// - control paddle
		if ( getKeyState(KEY_LEFT) )
        {
			MoveObject(&player, 'x', -speed);
			keypressed = true;
        }
		if ( getKeyState(KEY_RIGHT) )
        {
			MoveObject(&player, 'x', speed);
			keypressed = true;
        }

		// - prevent paddle from going off the screen
		if(player.shape.pos.x < 0){
			player.shape.pos.x = 0;
		}
		else if(player.shape.pos.x + paddle.x > SCREEN_W){
			player.shape.pos.x = SCREEN_W - paddle.x;
		}

		// - Move the ball
		MoveObject(&ball,'x',ballSpd.x);
		MoveObject(&ball,'y',ballSpd.y);

		if(ballSpd.x > 3) ballSpd.x = 3;
		if(ballSpd.x < -3) ballSpd.x = -3;

		// - test collision detection
		if(AABB(player, block)){
			player.shape.color = MakeColor(31,0,0);
		}
		else{
			player.shape.color = white;
		}

		// - Draw the player and ball
		DrawGameObject(player,true);
		DrawGameObject(ball,true);

		bool flipBallY = false;
		bool flipBallX = false;

		// - ball-player collision
		if(AABB(player,ball)){
			flipBallY = true;
			int playerC = player.shape.pos.x + player.shape.size.x / 2;
			int ballC = ball.shape.pos.x + ball.shape.size.x / 2;

			int val = ballC - playerC;

			ballSpd.x += val;
		}

		// - ball-boundary collisions
		if(ball.shape.pos.x <= 0){
			//ball.shape.pos.x = 0;
			flipBallX = true;
		}
		else if(ball.shape.pos.x + ball.shape.size.x >= SCREEN_W){
			//ball.shape.pos.x = SCREEN_W - ball.shape.size.x;
			flipBallX = true;
		}

		if(ball.shape.pos.y <= 0){
			//ball.shape.pos.y = 0;
			flipBallY = true;
		}
		else if(ball.shape.pos.y >= SCREEN_H){
			// game over or -1 life
			//flipBallY = true;
			lives--;
			play = false;
			ballSpd = MakePoint(0, 1);
			ball.shape.pos = MakePoint(SCREEN_W / 2 - 3, SCREEN_H / 2 + 3);
			if(lives <= 0){
				break;
			}
		}

		// - ball-block collisions and block drawing
		for(int i = 0; i < 20; i++){
			if(!(blocks[i].active)) continue;
			if(AABB(ball,blocks[i])){
				if(ball.shape.pos.x < blocks[i].shape.pos.x || ball.shape.pos.x + ball.shape.size.x > blocks[i].shape.pos.x + blocks[i].shape.size.x)
					flipBallX = true;
				if(ball.shape.pos.y < blocks[i].shape.pos.y || ball.shape.pos.y + ball.shape.size.y > blocks[i].shape.pos.y + blocks[i].shape.size.y)
					flipBallY = true;
				blocks[i].active = false;
				DrawRect(MakeRect(blocks[i].shape.pos,blocks[i].shape.size,black));
				points += 10;
			}
			else DrawGameObject(blocks[i], false);
		}

		// - flip ball direction if necessary
		if(flipBallY){
			ballSpd.y = -ballSpd.y;
		}

		if(flipBallX){
			ballSpd.x = -ballSpd.x;
		}
		
		DrawFourDigit(points, MakePoint(5,5));
	}

	// - draw red screen on game over
	Draw(&img);
	
	return 0;
}