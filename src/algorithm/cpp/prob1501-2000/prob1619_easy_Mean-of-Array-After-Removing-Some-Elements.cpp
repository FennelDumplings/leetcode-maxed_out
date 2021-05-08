// prob1619: Mean of Array After Removing Some Elements

/*
 * https://leetcode-cn.com/problems/mean-of-array-after-removing-some-elements/
 */

#include <vector>
#include <algorithm>

using namespace std;

const double RATIO = 0.05;
const double EPS = 1e-10;

class Solution {
public:
    double trimMean(vector<int>& arr) {
        int n = arr.size();
        int skip = RATIO * n;
        // [skip, n - 1 - skip]
        sort(arr.begin(), arr.end());
        int ans = 0;
        for(int i = skip; i < n - skip; ++i)
            ans += arr[i];
        return (double)ans / (n - skip * 2);
    }
};
