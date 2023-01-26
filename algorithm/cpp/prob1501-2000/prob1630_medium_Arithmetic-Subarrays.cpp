// prob1630: Arithmetic Subarrays

/*
 * https://leetcode-cn.com/problems/arithmetic-subarrays/
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<bool> checkArithmeticSubarrays(vector<int>& nums, vector<int>& l, vector<int>& r) {
        int m = l.size();
        vector<bool> result(m);
        for(int i = 0; i < m; ++i)
        {
            int left = l[i], right = r[i];
            result[i] = true;
            if(left + 1 == right)
                continue;
            vector<int> cand(nums.begin() + left, nums.begin() + right + 1);
            sort(cand.begin(), cand.end());
            int d = cand[1] - cand[0];
            for(int j = 2; j < (int)cand.size(); ++j)
                if(cand[j] - cand[j - 1] != d)
                {
                    result[i] = false;
                    break;
                }
        }
        return result;
    }
};
