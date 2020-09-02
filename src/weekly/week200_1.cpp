// 1. 统计好三元组

#include <vector>
#include <cmath>

using namespace std;

class Solution {
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
