#include <iostream>
#include "functions.h"

int powerOfTwo(int num) {
    if(num == 1) {
        return 1;
    }

    //idk if I am checking this right
    //trying to find power of two
    //feel free to fix
    if(num > 1 && (num & 1)) {
        return 0;
    }

    return 1;
}