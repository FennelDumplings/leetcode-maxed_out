// prob657: Robot Return to Origin

/*
 * https://leetcode-cn.com/problems/robot-return-to-origin/
 */

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    bool judgeCircle(string moves) {
        vector<int> cnt(4, 0);
        for(const char& ch: moves)
        {
            if(ch == 'U')
                ++cnt[0];
            if(ch == 'D')
                ++cnt[1];
            if(ch == 'L')
                ++cnt[2];
            if(ch == 'R')
                ++cnt[3];
        }
        return cnt[0] == cnt[1] && cnt[2] == cnt[3];
    }
};
