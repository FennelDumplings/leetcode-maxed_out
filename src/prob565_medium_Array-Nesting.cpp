// prob565: Array Nesting

/*
 * https://leetcode-cn.com/problems/array-nesting/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int arrayNesting(vector<int>& nums) {
        if(nums.empty()) return 0;
        int n = nums.size();
        vector<bool> visited(n, false);
        int ans = 1;
        for(int i = 0; i < n; ++i)
        {
            if(visited[i]) continue;
            visited[i] = true;
            int sum = 1;
            int j = i;
            while(!visited[nums[j]])
            {
                j = nums[j];
                visited[j] = true;
                ++sum;
            }
            ans = max(ans, sum);
        }
        return ans;
    }
};
