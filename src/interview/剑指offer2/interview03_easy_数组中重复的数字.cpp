// 面03: 数组中重复的数字

/*
 * 找出数组中重复的数字。
 * 在一个长度为 n 的数组 nums 里的所有数字都在 0～n-1 的范围内。数组中某些数字是重复的，但不知道有几个数字重复了，
 * 也不知道每个数字重复了几次。请找出数组中任意一个重复的数字。
 */

/*
 * 示例 1：
 * 输入：
 * [2, 3, 1, 0, 2, 5, 3]
 * 输出：2 或 3
 */

/*
 * 限制：
 * 2 <= n <= 100000
 */

#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
        int n = nums.size();
        vector<bool> appear(n, false);
        for(int i = 0; i < n; ++i)
        {
            if(appear[nums[i]])
                return nums[i];
            else
                appear[nums[i]] = true;
        }
        return -1;
    }
};

// unordered_set 比 vector 慢
class Solution_2 {
public:
    int findRepeatNumber(vector<int>& nums) {
        int n = nums.size();
        unordered_set<int> setting;
        for(int i = 0; i < n; ++i)
        {
            if(setting.find(nums[i]) != setting.end())
                return nums[i];
            else
                setting.insert(nums[i]);
        }
        return -1;
    }
};

// 排序后 nums[i] = i
class Solution_3 {
public:
    int findRepeatNumber(vector<int>& nums) {
        int n = nums.size();
        for(int i = 0; i < n; ++i)
        {
            if(nums[i] == i) continue;
            while(nums[i] != i)
            {
                if(nums[i] == nums[nums[i]])
                    return nums[i];
                int tmp = nums[nums[i]];
                nums[nums[i]] = nums[i];
                nums[i] = tmp;
            }
        }
        return -1;
    }
};
