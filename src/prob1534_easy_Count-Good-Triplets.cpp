// prob1534: Count Good Triplets

/*
 * https://leetcode-cn.com/problems/count-good-triplets/
 */

#include <vector>
#include <cmath>

using namespace std;


class Solution_2 {
public:
    int countGoodTriplets(vector<int>& arr, int a, int b, int c) {
        int n = arr.size();
        int ans = 0;
        for(int i = 0; i < n - 2; ++i)
            for(int j = i + 1; j < n - 1; ++j)
                for(int k = j + 1; k < n; ++k)
                {
                    if(abs(arr[i] - arr[j]) <= a && abs(arr[j] - arr[k]) <= b && abs(arr[i] - arr[k]) <= c)
                        ++ans;
                }
        return ans;
    }
};

class Solution {
public:
    int countGoodTriplets(vector<int>& arr, int a, int b, int c) {
        int n = arr.size();
        int ans = 0;
        vector<int> sums(1001, 0); // 0~1000
        for(int j = 0; j < n - 1; ++j)
        {
            for(int k = j + 1; k < n; ++k)
            {
                if(abs(arr[j] - arr[k]) > b) continue;
                int l = max(max(arr[j] - a, arr[k] - c), 0);
                int r = min(min(arr[j] + a, arr[k] + c), 1000);
                if(l > r)
                    continue;
                // [0..j-1] 上 l <= arr[i] <= r 有多少个
                ans += sums[r];
                if(l > 0)
                    ans -= sums[l - 1];
            }
            // [arr[j]..1000] +1
            for(int x = arr[j]; x <= 1000; ++x)
                ++sums[x];
        }
        return ans;
    }
};
