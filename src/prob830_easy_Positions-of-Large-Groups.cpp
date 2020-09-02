// prob830: Positions of Large Groups

/*
 * https://leetcode-cn.com/problems/positions-of-large-groups/
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<vector<int>> largeGroupPositions(string S) {
        int n = S.size();
        int left = 0;
        vector<vector<int>> result;
        while(left < n)
        {
            int right = left + 1;
            while(right < n && S[right] == S[left])
                ++right;
            if(right - left >= 3)
            {
                result.push_back({left, right - 1});
            }
            left = right;
        }
        return result;
    }
};
