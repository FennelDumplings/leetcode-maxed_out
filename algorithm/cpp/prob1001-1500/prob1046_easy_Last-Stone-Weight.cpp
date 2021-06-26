// prob106: Last Stone Weight

/*
 * https://leetcode-cn.com/problems/last-stone-weight/
 */

#include <vector>
#include <set>

using namespace std;

class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        multiset<int> setting(stones.begin(), stones.end());
        while(setting.size() > 1)
        {
            int y = *setting.rbegin();
            setting.erase(--setting.end());
            int x = *setting.rbegin();
            setting.erase(--setting.end());
            if(x < y)
                setting.insert(y - x);
        }
        return *setting.begin();
    }
};
