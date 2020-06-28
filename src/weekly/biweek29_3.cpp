// 20200627
// 3.

#include <vector>

using namespace std;

class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int n = nums.size();
        int left = 0;
        vector<int> vec;
        while(left < n)
        {
            int cur = nums[left];
            int right = left + 1;
            while(right < n && nums[right] == cur)
                ++right;
            int len = right - left;
            if(cur == 1)
                vec.push_back(len);
            else
            {
                if(len == 1)
                    vec.push_back(-1);
                else
                    vec.push_back(-2);
            }
            left = right;
        }
        if(vec.size() == 1)
        {
            if(vec[0] > 0)
                return vec[0] - 1;
            else
                return 0;
        }
        left = 0;
        int N = vec.size();
        int result = 0;
        while(left < N)
        {
            if(vec[left] < 0)
            {
                ++left;
                continue;
            }
            int cand = vec[left];
            if(left + 2 < N && vec[left + 1] == -1)
                cand += vec[left + 2];
            result = max(result, cand);
            ++left;
        }
        return result;
    }
};

