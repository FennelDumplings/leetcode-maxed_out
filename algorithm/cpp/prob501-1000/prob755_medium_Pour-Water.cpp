// prob755: Pour Water

/*
 * https://leetcode-cn.com/problems/pour-water/
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> pourWater(vector<int>& heights, int V, int K) {
        int n = heights.size();
        vector<int> result = heights;
        while(V--)
        {
            int i = K;
            int pos = K;
            while(i > 0 && result[i - 1] <= result[i])
            {
                if(result[i - 1] < result[i])
                    pos = i - 1;
                --i;
            }
            if(i < K && result[i] < result[K])
            {
                ++result[pos];
                continue;
            }
            i = K;
            pos = K;
            while(i < n - 1 && result[i + 1] <= result[i])
            {
                if(result[i + 1] < result[i])
                    pos = i + 1;
                ++i;
            }
            if(i > K && result[i] < result[K])
            {
                ++result[pos];
                continue;
            }
            ++result[K];
        }
        return result;
    }
};
