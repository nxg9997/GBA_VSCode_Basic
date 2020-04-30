typedef unsigned char      uint8;
typedef unsigned short     uint16;
typedef unsigned int       uint32;
typedef unsigned char      bool;

#define REG_DISPLAYCONTROL *(volatile unsigned int*)0x04000000
#define VIDEOMODE_3         0x0003
#define BGMODE_2            0x0400
#define SCREENBUFFER        (volatile uint16*)0x06000000
#define SCREEN_W            240
#define SCREEN_H            160

#define REG_VCOUNT          *(volatile uint16*)0x04000006

#define REG_KEYINPUT        (* (volatile uint16*) 0x4000130)

#define KEY_A        0x0001
#define KEY_B        0x0002
#define KEY_SELECT   0x0004
#define KEY_START    0x0008
#define KEY_RIGHT    0x0010
#define KEY_LEFT     0x0020
#define KEY_UP       0x0040
#define KEY_DOWN     0x0080
#define KEY_R        0x0100
#define KEY_L        0x0200

#define KEY_MASK     0xFC00