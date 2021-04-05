
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int magicTower(vector<int>& nums) {
        using ll = long long;
        ll sum = 1;
        for(int x: nums) sum += x;
        if(sum <= 0)
            return -1;
        // 一定可以通关
        sum = 1;
        priority_queue<int> pq;
        queue<int> q;
        for(int x: nums) q.push(x);
        int ans = 0;
        while(!q.empty())
        {
            int x = q.front();
            q.pop();
            sum += x;
            if(sum > 0)
            {
                if(x < 0)
                    pq.push(-x);
            }
            else
            {
                ++ans;
                pq.push(-x);
                q.push(-pq.top());
                sum += pq.top();
                pq.pop();
            }
        }
        return ans;
    }
};
