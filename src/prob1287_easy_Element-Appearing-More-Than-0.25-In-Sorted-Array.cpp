// prob1287: Element Appearing More Than 25% In Sorted Array

/*
 * Given an integer array sorted in non-decreasing order, there is exactly one integer in the array that occurs more than 25% of the time.
 * Return that integer.
 */

/*
 * Example 1:
 * Input: arr = [1,2,2,6,6,6,6,7,10]
 * Output: 6
 */

/*
 * Constraints:
 * 1 <= arr.length <= 10^4
 * 0 <= arr[i] <= 10^5
 */

#include <vector>

using namespace std;

class Solution {
public:
    int findSpecialInteger(vector<int>& arr) {
        int n = arr.size();
        if(n <= 3) return arr[0];
        int target = n / 4 + 1;
        int left = 0;
        while(left < n)
        {
            int right = left;
            int cur = arr[left];
            while(right < n && arr[right] == cur)
                ++right;
            int len = right - left;
            if(len >= target)
                return cur;
            left = right;
        }
        return -1;
    }
};
