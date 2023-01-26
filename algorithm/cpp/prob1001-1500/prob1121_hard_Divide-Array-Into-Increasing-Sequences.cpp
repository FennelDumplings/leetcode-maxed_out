// prob1121: Divide Array Into Increasing Sequences

/*
 * https://leetcode-cn.com/problems/divide-array-into-increasing-sequences/
 */

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool canDivideIntoSubsequences(vector<int>& nums, int K) {
        if(K == 1) return true;
        int n = nums.size();
        unordered_map<int, int> mapping;
        for(int i = 0; i < n; ++i)
            ++mapping[nums[i]];
        int t = 0;
        for(auto i: mapping)
            if(i.second > t)
                t = i.second;
        return t * K <= n;
    }
};
