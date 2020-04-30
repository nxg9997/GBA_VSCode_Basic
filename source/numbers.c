#include "helper.h"

// - Draw a single-digit number
void DrawNum(int num, Point pos)
{
    if(num == 0){
        for(int x = 0; x < 6; ++x){
            for(int y = 0; y < 11; ++y){
                if(x == 0 || x == 5 || y == 0 || y == 10)
                    (SCREENBUFFER)[(pos.x + x)+(pos.y + y)*240] = MakeColor(31,31,31);
            }
        }
    }
    else if(num == 1){
        for(int x = 0; x < 5; ++x){
            for(int y = 0; y < 11; ++y){
                if(x == 4)
                    (SCREENBUFFER)[(pos.x + x)+(pos.y + y)*240] = MakeColor(31,31,31);
            }
        }
    }
    else if(num == 2){
        for(int x = 0; x < 6; ++x){
            for(int y = 0; y < 3; ++y)
                (SCREENBUFFER)[(pos.x + x)+(pos.y + (5 * y))*240] = MakeColor(31,31,31);
        }
        for(int y = 0; y < 6; ++y){
            (SCREENBUFFER)[(pos.x + 5)+(pos.y + y)*240] = MakeColor(31,31,31);
        }
        for(int y = 5; y < 10; ++y){
            (SCREENBUFFER)[(pos.x)+(pos.y + y)*240] = MakeColor(31,31,31);
        }
    }
    else if(num == 3){
        for(int x = 0; x < 6; ++x){
            for(int y = 0; y < 3; ++y)
                (SCREENBUFFER)[(pos.x + x)+(pos.y + (5 * y))*240] = MakeColor(31,31,31);
        }
        for(int y = 0; y < 10; ++y){
            (SCREENBUFFER)[(pos.x + 5)+(pos.y + y)*240] = MakeColor(31,31,31);
        }
    }
    else if(num == 4){
        for(int x = 0; x < 5; ++x){
            (SCREENBUFFER)[(pos.x + x)+(pos.y + 5)*240] = MakeColor(31,31,31);
        }
        for(int y = 0; y < 5; ++y){
            (SCREENBUFFER)[(pos.x)+(pos.y + y)*240] = MakeColor(31,31,31);
        }
        for(int y = 0; y < 11; ++y){
            (SCREENBUFFER)[(pos.x + 5)+(pos.y + y)*240] = MakeColor(31,31,31);
        }
    }
    else if(num == 5){
        for(int x = 0; x < 6; ++x){
            for(int y = 0; y < 3; ++y)
                (SCREENBUFFER)[(pos.x + x)+(pos.y + (5 * y))*240] = MakeColor(31,31,31);
        }
        for(int y = 0; y < 6; ++y){
            (SCREENBUFFER)[(pos.x)+(pos.y + y)*240] = MakeColor(31,31,31);
        }
        for(int y = 5; y < 10; ++y){
            (SCREENBUFFER)[(pos.x + 5)+(pos.y + y)*240] = MakeColor(31,31,31);
        }
    }
    else if(num == 6){
        for(int x = 0; x < 6; ++x){
            for(int y = 0; y < 3; ++y)
                (SCREENBUFFER)[(pos.x + x)+(pos.y + (5 * y))*240] = MakeColor(31,31,31);
        }
        for(int y = 0; y < 10; ++y){
            (SCREENBUFFER)[(pos.x)+(pos.y + y)*240] = MakeColor(31,31,31);
        }
        for(int y = 5; y < 10; ++y){
            (SCREENBUFFER)[(pos.x + 5)+(pos.y + y)*240] = MakeColor(31,31,31);
        }
    }
    else if(num == 7){
        for(int x = 0; x < 6; ++x){
            (SCREENBUFFER)[(pos.x + x)+(pos.y)*240] = MakeColor(31,31,31);
            for(int y = 0; y < 11; ++y){
                if(x == 5)
                    (SCREENBUFFER)[(pos.x + x)+(pos.y + y)*240] = MakeColor(31,31,31);
            }
        }
    }
    else if(num == 8){
        for(int x = 0; x < 6; ++x){
            for(int y = 0; y < 3; ++y)
                (SCREENBUFFER)[(pos.x + x)+(pos.y + (5 * y))*240] = MakeColor(31,31,31);
        }
        for(int y = 0; y < 10; ++y){
            for(int x = 0; x < 2; ++x)
                (SCREENBUFFER)[(pos.x + 5 * x)+(pos.y + y)*240] = MakeColor(31,31,31);
        }
    }
    else if(num == 9){
        for(int x = 0; x < 5; ++x){
            for(int y = 0; y < 2; ++y)
                (SCREENBUFFER)[(pos.x + x)+(pos.y + 5 * y)*240] = MakeColor(31,31,31);
        }
        for(int y = 0; y < 5; ++y){
            (SCREENBUFFER)[(pos.x)+(pos.y + y)*240] = MakeColor(31,31,31);
        }
        for(int y = 0; y < 11; ++y){
            (SCREENBUFFER)[(pos.x + 5)+(pos.y + y)*240] = MakeColor(31,31,31);
        }
    }
}

// - Draw a 4-digit number
void DrawFourDigit(unsigned int num, Point pos)
{
    int vals[4] = {0,0,0,0};
    for(int i = 0; i < 4; i++){
        int count = 0;
        while(num % 10 != 0){
            count++;
            num--;
        }
        vals[i] = count;
        num /= 10;
    }
    
    DrawRect(MakeRect(MakePoint(pos.x,pos.y),MakePoint(26,11),MakeColor(0,0,0)));

    if(vals[3]) DrawNum(vals[3], MakePoint(pos.x,pos.y));
    if(vals[2] || vals[3]) DrawNum(vals[2], MakePoint(pos.x + 7, pos.y));
    if(vals[1] || vals[2]) DrawNum(vals[1], MakePoint(pos.x + 14, pos.y));
    DrawNum(vals[0], MakePoint(pos.x + 21, pos.y));
}