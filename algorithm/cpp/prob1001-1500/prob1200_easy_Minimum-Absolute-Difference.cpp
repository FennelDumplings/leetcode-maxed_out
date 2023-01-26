// prob1201: Minimum Absolute Difference

/*
 * https://leetcode-cn.com/problems/minimum-absolute-difference/
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> minimumAbsDifference(vector<int>& arr) {
        sort(arr.begin(), arr.end());
        int n = arr.size();
        if(n == 2)
            return {{arr[0], arr[1]}};
        int minx = arr[1] - arr[0];
        for(int i = 2; i < n; ++i)
            minx = min(minx, arr[i] - arr[i - 1]);
        vector<vector<int>> result;
        for(int i = 1; i < n; ++i)
            if(arr[i] - arr[i - 1] == minx)
                result.push_back({arr[i - 1], arr[i]});
        return result;
    }
};
