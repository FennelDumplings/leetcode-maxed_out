// prob190: Reverse Bits

/*
 * Reverse bits of a given 32 bits unsigned integer.
 */

/*
 * Follow up:
 * If this function is called many times, how would you optimize it?
 */

#include <stdint.h>

class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t result = 0;
        for(int i = 0; i <= 31; ++i)
            if(n & (1 << i))
                result |= (1 << (31 - i));
        return result;
    }
};
