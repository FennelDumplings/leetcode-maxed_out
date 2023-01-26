// prob496: Next Greater Element I

/*
 * You are given two arrays (without duplicates) nums1 and nums2 where nums1’s elements are subset of nums2.
 * Find all the next greater numbers for nums1's elements in the corresponding places of nums2.
 * The Next Greater Number of a number x in nums1 is the first greater number to its right in nums2.
 * If it does not exist, output -1 for this number.
 */

/*
 * Example 1:
 * Input: nums1 = [4,1,2], nums2 = [1,3,4,2].
 * Output: [-1,3,-1]
 * Explanation:
 *     For number 4 in the first array, you cannot find the next greater number for it in the second array, so output -1.
 *     For number 1 in the first array, the next greater number for it in the second array is 3.
 *     For number 2 in the first array, there is no next greater number for it in the second array, so output -1.
 * Example 2:
 * Input: nums1 = [2,4], nums2 = [1,2,3,4].
 * Output: [3,-1]
 * Explanation:
 *     For number 2 in the first array, the next greater number for it in the second array is 3.
 *     For number 4 in the first array, there is no next greater number for it in the second array, so output -1.
 */

/*
 * Note:
 * All elements in nums1 and nums2 are unique.
 * The length of both nums1 and nums2 would not exceed 1000.
 */

#include <vector>
#include <stack>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        if(nums2.empty() || nums1.empty()) return vector<int>();
        stack<int> st;
        st.push(nums2.size() - 1);
        unordered_map<int, int> mapping;
        for(int i = nums2.size() - 2; i >= 0; --i)
        {
            while(!st.empty() && nums2[st.top()] < nums2[i])
            {
                int cur = st.top();
                st.pop();
                if(st.empty())
                    mapping[nums2[cur]] = -1;
                else
                    mapping[nums2[cur]] = nums2[st.top()];
            }
            st.push(i);
        }
        while(!st.empty())
        {
            int cur = st.top();
            st.pop();
            if(st.empty())
                mapping[nums2[cur]] = -1;
            else
                mapping[nums2[cur]] = nums2[st.top()];
        }
        int n = nums1.size();
        vector<int> result(n, 0);
        for(int i = 0; i < n; ++i)
            result[i] = mapping[nums1[i]];
        return result;
    }
};
