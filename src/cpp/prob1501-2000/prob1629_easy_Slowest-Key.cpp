// prob1629: Slowest Key

/*
 * https://leetcode-cn.com/problems/slowest-key/
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    char slowestKey(vector<int>& releaseTimes, string keysPressed) {
        int n = releaseTimes.size();
        int prev = 0;
        int ans = 0;
        char key;
        for(int i = 0; i < n; ++i)
        {
            int t = releaseTimes[i];
            char ch = keysPressed[i];
            if(ans < t - prev)
            {
                ans = t - prev;
                key = ch;
            }
            else if(ans == t - prev && key < ch)
                key  = ch;
            prev = t;
        }
        return key;
    }
};
