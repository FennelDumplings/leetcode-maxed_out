// prob1176: Diet Plan Performance

/*
 * https://leetcode-cn.com/problems/diet-plan-performance/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int dietPlanPerformance(vector<int>& calories, int k, int lower, int upper) {
        int n = calories.size();
        int sum = 0;
        for(int i = 0; i < k; ++i)
            sum += calories[i];
        int ans = 0;
        for(int i = k; i < n; ++i)
        {
            if(sum > upper)
                ++ans;
            else if(sum < lower)
                --ans;
            sum -= calories[i - k];
            sum += calories[i];
        }
        if(sum > upper)
            ++ans;
        else if(sum < lower)
            --ans;
        return ans;
    }
};
