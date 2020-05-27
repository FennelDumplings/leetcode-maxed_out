// prob158: Read N Characters Given Read4 II - Call multiple times

/*
 * Ref Prob157
 * Your method read may be called multiple times.
 */

/*
 * Note:
 *
 * Consider that you cannot manipulate the file directly, the file is only accesible for read4 but not for read.
 * The read function may be called multiple times.
 * Please remember to RESET your class variables declared in Solution, as static/class variables are persisted across multiple test cases. Please see here for more details.
 * You may assume the destination buffer array, buf, is guaranteed to have enough space for storing n characters.
 * It is guaranteed that in a given test case the same buffer buf is called by read.
 */

/**
 * The read4 API is defined in the parent class Reader4.
 *     int read4(char *buf);
 */

#include <string>

using namespace std;

int read4(char *buf);

class Solution {
public:
    /**
     * @param buf Destination buffer
     * @param n   Number of characters to read
     * @return    The number of actual characters read
     */
    int read(char *buf, int n) {
        if(n == 0) return 0;
        if(remainder_len >= n)
        {
            for(int i = remainder_len - 1; i >= remainder_len - n; --i)
            {
                *buf = remainder[i];
                buf = buf + 1;
            }
            remainder_len -= n;
            return n;
        }
        else
        {
            for(int i = remainder_len - 1; i >= 0; --i)
            {
                *buf = remainder[i];
                buf = buf + 1;
            }
            n -= remainder_len;
        }
        int cnt = (n + 3) / 4; // 1, 2, 3, 4 -> 1
        int char_num = remainder_len, num = 0;
        for(int i = 0; i < cnt; ++i)
        {
            num = read4(buf);
            char_num += num;
            buf = buf + num;
            if(num < 4) break;
        }
        if(char_num - remainder_len > n)
        {
            int diff = char_num - remainder_len - n;
            char_num -= diff;
            for(int i = 0; i < diff; ++i)
            {
                remainder[i] = *(buf - i - 1);
                *(buf - i - 1) = '\0';
            }
            remainder_len = diff;
        }
        else
            remainder_len = 0;
        return char_num;
    }

private:
    char remainder[4] = {' ', ' ', ' ', '\0'};
    int remainder_len = 0;
};
