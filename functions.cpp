#include <iostream>
#include "functions.h"

// check for power of two
// return 0 if true
// return 1 if false
int powerOfTwo(int num) {
    if(num != 0 && (num & (num - 1)) == 0 ) {
        return 0;
    }

    return 1;
}
