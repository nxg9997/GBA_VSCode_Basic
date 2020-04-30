#include "helper.h"

uint16 input_cur = 0;
uint16 input_prev = 0;

void key_poll()
{
    input_prev = input_cur;
    input_cur = REG_KEYINPUT | KEY_MASK;
}

uint32 getKeyState(uint16 key_code)
{
    return !(input_cur & key_code);
}

uint16 wasKeyPressed(uint16 key_code)
{
    return (input_cur & ~input_prev) & key_code;
}

uint16 wasKeyReleased(uint16 key_code)
{
    return (~input_cur & input_prev) & key_code;
}