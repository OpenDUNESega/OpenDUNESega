#include "tools.h"

static uint8 s_randomSeed[4];

uint8 Tools_Random_256(void) {
    uint8 seed1 = (s_randomSeed[1] << 1) | BitArray_Test(s_randomSeed+3, 1);
    uint8 seed2 = (s_randomSeed[2] << 1) | BitArray_Test(s_randomSeed+1, 7);
    uint8 seed3 = (((!BitArray_Test(s_randomSeed+2, 7))^(BitArray_Test(s_randomSeed+3, 2))^BitArray_Test(s_randomSeed+3, 0)) << 7) | (s_randomSeed[3] >> 1);
    
    s_randomSeed[1] = seed1;
    s_randomSeed[2] = seed2;
    s_randomSeed[3] = seed3;
    
    return s_randomSeed[2] ^ s_randomSeed[3];
}
