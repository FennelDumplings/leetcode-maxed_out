// interview57-2: 和为s的连续正数序列

/*
 * https://leetcode-cn.com/problems/he-wei-sde-lian-xu-zheng-shu-xu-lie-lcof/
 */

#include <vector>
#include <deque>

using namespace std;


class Solution {
public:
    vector<vector<int>> findContinuousSequence(int target) {
        int max_left = target / 2;
        int left = 1;
        int sum = 0;
        vector<vector<int>> result;
        deque<int> path;
        int right = 1;
        while(left <= max_left)
        {
            while(sum < target)
            {
                sum += right;
                path.push_back(right);
                ++right;
            }
            while(sum >= target)
            {
                if(sum == target)
                    result.push_back(vector<int>(path.begin(), path.end()));
                path.pop_front();
                sum -= left;
                ++left;
            }
        }
        return result;
    }
};
