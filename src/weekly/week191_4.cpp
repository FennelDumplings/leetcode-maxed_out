// 20200531
// 4. 两个盒子中颜色不同的球数量相同的概率

#include <vector>
#include <unordered_map>

using namespace std;

class Solution2 {
public:
    double getProbability(vector<int>& balls) {
        int state = 0;
        int k = balls.size();
        int sum = 0;
        for(int i = 0; i < k; ++i)
        {
            sum += balls[i];
            state |= (balls[i] << (4 * i));
        }
        unordered_map<int, double> dp;
        solve(state, dp, k, sum);
        return dp[state];
    }

private:
    void solve(int state, unordered_map<int, double>& dp, int k, int n)
    {
        if(dp.find(state) != dp.end())
            return;

        if(n == 4)
        {
            dp[state] = base(state);
            return;
        }

        for(int i = 0; i < k; ++i)
        {
            << (4 * i)
            if(state & ())
            for(int j = 0; j < k; ++j)
            {
                //
            }
        }
    }

    double base(int state)
    {
        // state 有 4 个球
    }
};

//
class Solution {
public:
    double getProbability(vector<int>& balls) {
        int sum = 0;
        for(int i = 0; i < k; ++i)
            sum += balls[i];
        int ans = 0;
        dfs(balls, ans);
        return double(ans) /
    }

private:
    void dfs(vector<int>& balls, int& ans)
    {
        //
    }
};
