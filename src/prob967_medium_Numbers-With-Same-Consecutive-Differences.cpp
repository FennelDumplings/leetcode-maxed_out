// porb967: Numbers With Same Consecutive Differences

/*
 * https://leetcode-cn.com/problems/numbers-with-same-consecutive-differences/
 */


#include <vector>
#include <cmath>

using namespace std;

// DFS
class Solution {
public:
    vector<int> numsSameConsecDiff(int N, int K) {
        if(N == 1) return {0,1,2,3,4,5,6,7,8,9};
        vector<int> result;
        int item = 0; // item 自带 pos 信息
        dfs(0, item, N, K, result);
        return result;
    }

private:
    void dfs(int len, int& item, int N, int K, vector<int>& result)
    {
        if(len == N)
        {
            result.push_back(item);
            return;
        }

        if(len == 0)
        {
            for(int i = 1; i <= 9; ++i)
            {
                item *= 10;
                item += i;
                dfs(len + 1, item, N, K, result);
                item /= 10;
            }
        }
        else
        {
            int pre = item % 10;
            if(pre + K <= 9)
            {
                item *= 10;
                item += pre + K;
                dfs(len + 1, item, N, K, result);
                item /= 10;
            }
            if(K != 0 && pre - K >= 0)
            {
                item *= 10;
                item += pre - K;
                dfs(len + 1, item, N, K, result);
                item /= 10;
            }
        }
    }
};
