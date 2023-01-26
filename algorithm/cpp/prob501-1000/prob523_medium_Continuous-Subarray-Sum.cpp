// prob523: Continuous Subarray Sum

/*
 * Given a list of non-negative numbers and a target integer k,
 * write a function to check if the array has a continuous subarray of size at least 2
 * that sums up to a multiple of k, that is, sums up to n*k where n is also an integer.
 */

/*
 * Example 1:
 * Input: [23, 2, 4, 6, 7],  k=6
 * Output: True
 * Explanation: Because [2, 4] is a continuous subarray of size 2 and sums up to 6.
 * Example 2:
 * Input: [23, 2, 6, 4, 7],  k=6
 * Output: True
 * Explanation: Because [23, 2, 6, 4, 7] is an continuous subarray of size 5 and sums up to 42.
 */

/*
 * Note:
 * The length of the array won't exceed 10,000.
 * You may assume the sum of all the numbers is in the range of a signed 32-bit integer.
 */

#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        if(nums.empty()) return false;
        int n = nums.size();
        if(n == 1) return false;

        vector<int> sums(n + 1, 0);
        for(int i = 1; i < n + 1; ++i)
            sums[i] = sums[i - 1] + nums[i - 1];

        for(int i = 0; i <= n - 2; ++i)
        {
            for(int j = i + 2; j <= n; ++j)
            {
                int sum = sums[j] - sums[i];
                if(check(sum, k))
                    return true;
            }
        }
        return false;
    }

private:
    bool check(int sum, int k)
    {
        // sum = k * n, n 为整数
        if(sum == 0) return true;
        else if(k == 0) return false;
        return sum % k == 0;
    }
};


class Solution_2 {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        if(nums.empty()) return false;
        int n = nums.size();
        if(n == 1) return false;

        unordered_map<Sum, int, MyHash, MyCmp> mapping;
        mapping.insert({Sum(0, k), -1});

        int sum = 0;
        for(int i = 0; i < n; ++i)
        {
            sum += nums[i];
            Sum cur(sum, k);
            if(mapping.find(cur) == mapping.end())
                mapping.insert({cur, i});
            else if(i - mapping[cur] > 1)
                return true;
        }
        return false;
    }

private:
    struct Sum
    {
        int sum, k;
        Sum(int sum, int k):sum(sum),k(k){}
    };

    struct MyHash
    {
        int operator()(const Sum& item) const
        {
            if(item.k == 0) return item.sum;
            return item.sum % item.k;
        }
    };

    struct MyCmp
    {
        bool operator()(const Sum& item1, const Sum& item2) const
        {
            if(item1.k == 0) return item1.sum == item2.sum;
            return item1.sum % item1.k == item2.sum % item2.k;
        }
    };
};
