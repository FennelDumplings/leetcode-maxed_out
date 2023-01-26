// prob1189: Maximum Number of Balloons

/*
 * https://leetcode-cn.com/problems/maximum-number-of-balloons/
 */

#include <string>

using namespace std;

class Solution {
public:
    int maxNumberOfBalloons(string text) {
        int nb = 0, na = 0, nl = 0, no = 0, nn = 0;
        for(const char &ch: text)
        {
            switch(ch)
            {
                case('b'): ++nb; break;
                case('a'): ++na; break;
                case('l'): ++nl; break;
                case('o'): ++no; break;
                case('n'): ++nn;
            }
        }
        int ans = nb;
        ans = min(ans, na);
        ans = min(ans, nn);
        ans = min(ans, nl / 2);
        ans = min(ans, no / 2);
        return ans;
    }
};
