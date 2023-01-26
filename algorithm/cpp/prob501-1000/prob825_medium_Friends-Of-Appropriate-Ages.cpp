// prob825: Friends Of Appropriate Ages

/*
 * https://leetcode-cn.com/problems/friends-of-appropriate-ages/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int numFriendRequests(vector<int>& ages) {
        const int MAX_AGE = 120;
        vector<int> cnts(MAX_AGE + 1);
        for(int age: ages)
            ++cnts[age];
        int ans = 0;
        for(int i = 1; i <= MAX_AGE; ++i)
        {
            for(int j = 1; j <= MAX_AGE; ++j)
            {
                if(j <= i * 0.5 + 7) continue;
                if(j > i) continue;
                if(j > 100 && i < 100) continue;
                ans += cnts[i] * cnts[j];
                if(i == j)
                    ans -= cnts[i];
            }
        }
        return ans;
    }
};
