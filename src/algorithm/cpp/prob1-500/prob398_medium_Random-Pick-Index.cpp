// prob398: Random Pick Index

/*
 * https://leetcode-cn.com/problems/random-pick-index/
 */

#include <vector>
#include <random>
#include <unordered_map>

using namespace std;

class Solution {
public:
    Solution(vector<int>& nums) {
        int random_seed = rand();
        dre = std::default_random_engine(random_seed);
        dr = std::uniform_real_distribution<double>(0.0, 1.0);
        for(int j = 0; j < (int)nums.size(); ++j)
            mapping[nums[j]].push_back(j);
    }

    int pick(int target) {
        int m = 1;
        int ans = -1;
        const vector<int> &nums = mapping[target];
        for(int i = 0; i < (int)nums.size(); ++i)
        {
            if(i < m)
                ans = nums[i];
            else
            {
                int random_idx = floor((i + 1) * dr(dre));
                if(random_idx < m)
                    ans = nums[i];
            }
        }
        return ans;
    }

private:
    std::default_random_engine dre;
    std::uniform_real_distribution<double> dr;

    unordered_map<int, vector<int>> mapping;
};
