// interview21: 调整数组顺序使奇数位于偶数前面

/*
 * https://leetcode-cn.com/problems/diao-zheng-shu-zu-shun-xu-shi-qi-shu-wei-yu-ou-shu-qian-mian-lcof/
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> exchange(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(nums.begin(), nums.end());
        int left = 0, right = n - 1;
        while(left < right)
        {
            if(result[left] & 1)
            {
                ++left;
            }
            else
            {
                swap(result[left], result[right]);
                --right;
            }
        }
        return result;
    }
};
