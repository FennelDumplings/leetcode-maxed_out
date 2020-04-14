// prob473: Matchsticks to Square

/*
 * Remember the story of Little Match Girl? By now, you know exactly what matchsticks the little match girl has,
 * please find out a way you can make one square by using up all those matchsticks. You should not break any stick,
 * but you can link them up, and each matchstick must be used exactly one time.
 * Your input will be several matchsticks the girl has, represented with their stick length.
 * Your output will either be true or false, to represent whether you could make one square using all the
 * matchsticks the little match girl has.
 */

/*
 * Example 1:
 * Input: [1,1,2,2,2]
 * Output: true
 * Explanation: You can form a square with length 2, one side of the square came two sticks with length 1.
 * Example 2:
 * Input: [3,3,3,3,4]
 * Output: false
 * Explanation: You cannot find a way to form a square with all the matchsticks.
 */

/*
 * Note:
 * The length sum of the given matchsticks is in the range of 0 to 10^9.
 * The length of the given matchstick array will not exceed 15.
 */

#include <vector>
#include <algorithm>

using namespace std;

// DFS + 搜索顺序
class Solution {
public:
    bool makesquare(vector<int>& nums) {
        if(nums.empty()) return false;
        int sum = 0;
        int maxx = 0;
        for(int num: nums)
        {
            sum += num;
            maxx = max(maxx, num);
        }
        int c = sum / 4;
        if(c * 4 != sum) return false;
        if(maxx > c) return false;
        vector<int> lens(4, c); // 4条边的剩余长度
        sort(nums.begin(), nums.end(), greater<int>());
        return dfs(nums, lens, 0, (int)nums.size());
    }

private:
    bool dfs(const vector<int>& nums, vector<int>& lens, int pos, int n)
    {
        if(pos == n) return true;

        int cur = nums[pos];
        for(int i = 0; i < 4; ++i)
        {
            if(lens[i] >= cur)
            {
                lens[i] -= cur;
                if(dfs(nums, lens, pos + 1, n))
                    return true;
                lens[i] += cur;
            }
        }
        return false;
    }
};
