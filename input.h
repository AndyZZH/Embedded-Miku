
#ifndef __Input_H
#define __Input_H

enum eXBOXButton{
    XBOX_A,
    XBOX_B,
    XBOX_X,
    XBOX_Y,
    XBOX_NUM_TYPE // 4 button in total
};

void Input_init(void);
void Input_cleanup(void);

#endif