// prob1049: Last Stone Weight II

/*
 * https://leetcode-cn.com/problems/last-stone-weight-ii/
 */

#include <vector>
#include <set>

using namespace std;

class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        int W = 0;
        for(int i: stones) W += i;
        int target = W / 2;
        // 选，使得和 小于等于 target 同时尽可能接近 target
        set<int> setting({0}); // [0..i] 中所有小于等于 target 的和
        for(int cur: stones)
        {
            vector<int> addition;
            for(int sum: setting)
            {
                if(sum + cur <= target)
                    addition.push_back(sum + cur);
            }
            for(int a: addition)
                setting.insert(a);
        }
        int sum = *setting.rbegin();
        return W - 2 * sum;
    }
};
