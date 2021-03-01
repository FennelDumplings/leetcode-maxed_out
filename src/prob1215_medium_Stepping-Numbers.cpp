// prob1215: Stepping Numbers

/*
 * https://leetcode-cn.com/problems/stepping-numbers/
 */

#include <vector>
#include <cmath>
#include <climits>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> countSteppingNumbers(int low, int high) {
        vector<int> cand;
        dfs(9, true, 0, cand, high);
        vector<int> result;
        for(int x: cand)
        {
            if(x >= low)
                result.push_back(x);
        }
        return result;
    }

private:
    void dfs(int i, bool zero, int x, vector<int>& result, const int high)
    {
        if(i == -1)
        {
            result.push_back(x);
            return;
        }
        if(zero)
        {
            dfs(i - 1, true, x, result, high);
            for(int d = 1; d <= 9; ++d)
                if(x <= high - (d * pow(10, i)))
                    dfs(i - 1, false, x + (d * pow(10, i)), result, high);
            return;
        }
        // 上一位数
        int d = ((x / (int)pow(10, i + 1)) % 10);
        if(d > 0 && x <= high - ((d - 1) * pow(10, i)))
            dfs(i - 1, false, x + (d - 1) * pow(10, i), result, high);
        if(d < 9 && x <= high - ((d + 1) * pow(10, i)))
            dfs(i - 1, false, x + (d + 1) * pow(10, i), result, high);
    }
};
