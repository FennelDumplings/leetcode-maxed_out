// prob826: Most Profit Assigning Work

/*
 * https://leetcode-cn.com/problems/most-profit-assigning-work/
 */

#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Work
{
    int diff;
    int pro;
    Work():diff(-1),pro(-1){}
    Work(int d, int p):diff(d),pro(p){}
};

struct Cmp
{
    bool operator()(const Work& w1, const Work& w2) const
    {
        return w1.diff < w2.diff;
    }
};

class Solution {
public:
    int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {
        int m = profit.size();
        vector<Work> works(m);
        for(int i = 0; i < m; ++i)
        {
            works[i].diff = difficulty[i];
            works[i].pro = profit[i];
        }
        sort(works.begin(), works.end(), Cmp());
        sort(worker.begin(), worker.end());
        int n = worker.size();
        priority_queue<int> cand_profits;
        int work_iter = 0;
        int ans = 0;
        for(int i = 0; i < n; ++i)
        {
            while(work_iter < m && works[work_iter].diff <= worker[i])
            {
                cand_profits.push(works[work_iter].pro);
                ++work_iter;
            }
            if(!cand_profits.empty())
                ans += cand_profits.top();
        }
        return ans;
    }
};
