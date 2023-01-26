// prob1300: Sum of Mutated Array Closest to Target

/*
 * https://leetcode-cn.com/problems/sum-of-mutated-array-closest-to-target/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int findBestValue(vector<int>& arr, int target) {
        int maxx = arr[0];
        for(int i: arr) maxx = max(maxx, i);
        int left = 0, right = maxx;
        while(left < right)
        {
            int mid = (left + right) / 2;
            int sum = check(arr, mid);
            if(sum < target)
                left = mid + 1;
            else
                right = mid;
        }
        int ans = left;
        int s1 = check(arr, left);
        if(target - check(arr, left - 1) <= s1 - target)
            ans = left - 1;
        return ans;
    }

private:
    int check(const vector<int>& arr, int mid)
    {
        int ans = 0;
        for(int i: arr)
        {
            ans += min(i, mid);
        }
        return ans;
    }
};
