// prob659: Split Array into Consecutive Subsequences

/*
 * https://leetcode-cn.com/problems/split-array-into-consecutive-subsequences/
 */

#include <vector>
#include <unordered_map>
#include <set>

using namespace std;

class Solution {
public:
    bool isPossible(vector<int>& nums) {
        multiset<int> hands;
        for(int i: nums)
            hands.insert(i);
        auto iter = hands.begin();
        unordered_map<int, int> mapping; // mapping[i] := 以 i 为结尾的顺子个数
        while(iter != hands.end())
        {
            int cur = *iter;
            if(mapping[cur - 1] > 0)
            {
                --mapping[cur - 1];
                ++mapping[cur];
                iter = hands.erase(iter);
            }
            else if(hands.count(cur + 1) && hands.count(cur + 2))
            {
                hands.erase(hands.find(cur + 1));
                hands.erase(hands.find(cur + 2));
                iter = hands.erase(iter);
                ++mapping[cur + 2];
            }
            else
                return false;
        }
        return true;
    }
};

