// prob321: Create Maximum Number

/*
 * Given two arrays of length m and n with digits 0-9 representing two numbers. Create the maximum number of length k <= m + n
 * from digits of the two. The relative order of the digits from the same array must be preserved. Return an array of the k digits.
 * Note: You should try to optimize your time and space complexity.
 */

/*
 * Example 1:
 * Input:
 * nums1 = [3, 4, 6, 5]
 * nums2 = [9, 1, 2, 5, 8, 3]
 * k = 5
 * Output:
 * [9, 8, 6, 5, 3]
 * Example 2:
 * Input:
 * nums1 = [6, 7]
 * nums2 = [6, 0, 4]
 * k = 5
 * Output:
 * [6, 7, 6, 0, 4]
 * Example 3:
 * Input:
 * nums1 = [3, 9]
 * nums2 = [8, 9]
 * k = 3
 * Output:
 * [9, 8, 9]
 */

#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<int> result;
        int n1 = nums1.size(), n2 = nums2.size();
        for(int k1 = 0; k1 <= k; ++k1)
        {
            int k2 = k - k1;
            if(k1 > n1 || k2 > n2)
                continue;
            result = max(result, merge(solve(nums1, k1), solve(nums2, k2)));
        }
        return result;
    }

private:
    vector<int> solve(const vector<int>& nums, int k)
    {
        if(k == 0) return {};
        vector<int> result;
        int n = nums.size();
        int k_delete = n - k;
        for(int i = 0; i < n; ++i)
        {
            while(!result.empty() && result.back() < nums[i] && k_delete > 0)
            {
                result.pop_back();
                --k_delete;
            }
            result.push_back(nums[i]);
        }
        // 取前 k 个
        result.resize(k);
        return result;
    }

    vector<int> merge(const vector<int>& vec1, const vector<int>& vec2)
    {
        vector<int> result;
        auto s1 = vec1.cbegin();
        auto e1 = vec1.cend();
        auto s2 = vec2.cbegin();
        auto e2 = vec2.cend();
        while(s1 != e1 || s2 != e2)
            result.push_back(lexicographical_compare(s1, e1, s2, e2) ? *s2++ : *s1++);
        return result;
    }
};
