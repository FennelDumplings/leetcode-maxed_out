// prob709: To Lower Case

/*
 * https://leetcode-cn.com/problems/to-lower-case/
 */

#include <string>

using namespace std;

class Solution {
public:
    string toLowerCase(string str) {
        const int diff = 'a' - 'A';
        for(char &ch: str)
        {
            if(ch >= 'A' && ch <= 'Z')
                ch += diff;
        }
        return str;
    }
};
