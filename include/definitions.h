typedef unsigned char      uint8;
typedef unsigned short     uint16;
typedef unsigned int       uint32;

#define REG_DISPLAYCONTROL *(volatile unsigned int*)0x04000000
#define VIDEOMODE_3         0x0003
#define BGMODE_2            0x0400
#define SCREENBUFFER        (volatile uint16*)0x06000000
#define SCREEN_W            240
#define SCREEN_H            160

#define REG_VCOUNT          *(volatile uint16*)0x04000006