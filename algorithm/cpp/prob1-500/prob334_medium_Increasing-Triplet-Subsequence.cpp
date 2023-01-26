// prob334: Increasing Triplet Subsequence

/*
 * https://leetcode-cn.com/problems/increasing-triplet-subsequence/
 */

#include <vector>
#include <deque>

using namespace std;

class Solution_3 {
public:
    bool increasingTriplet(vector<int>& nums) {
        deque<int> deq;
        for(int i: nums)
        {
            if(deq.empty())
                deq.push_back(i);
            else if(deq.size() == 1)
            {
                if(deq.back() >= i)
                    deq.pop_back();
                deq.push_back(i);
            }
            else if(deq.size() == 2)
            {
                if(i > deq.back())
                    return true;
                else
                {
                    if(i > deq.front())
                        deq.pop_back();
                    deq.push_back(i);
                }
            }
            else
            {
                int r = deq.back();
                deq.pop_back();
                if(i > deq.back())
                    return true;
                if(i > r)
                {
                    deq.pop_front();
                    deq.pop_front();
                    deq.push_back(r);
                }
                deq.push_back(i);
            }
        }
        return false;
    }
};

#include <climits>

class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        int n = nums.size();
        int l = INT_MAX, r = INT_MAX;
        for(int i = 0; i < n; ++i)
        {
            if(nums[i] <= l)
                l = nums[i];
            else if(nums[i] <= r)
                r = nums[i];
            else
                return true;
        }
        return false;
    }
};
