
#include <vector>
#include <unordered_map>

using namespace std;

class Solution_2 {
public:
    int furthestBuilding(vector<int>& heights, int bricks, int ladders) {
        int n = heights.size();
        vector<int> diff;
        vector<int> idxs;
        for(int i = 0; i < n - 1; ++i)
            if(heights[i + 1] > heights[i])
            {
                diff.push_back(heights[i + 1] - heights[i]);
                idxs.push_back(i);
            }
        idxs.push_back(n - 1);
        int m = diff.size();
        dp = vector<unordered_map<int, unordered_map<int, int>>>(m);
        int max_pos = solve(diff, 0, bricks, ladders);
        return idxs[max_pos];
    }

private:
    vector<unordered_map<int, unordered_map<int, int>>> dp;

    int solve(const vector<int>& diff, int i, int b, int l)
    {
        int m = diff.size();
        if(i == m)
            return i;
        if(dp[i].count(b) > 0 && dp[i][b].count(l))
            return dp[i][b][l];
        dp[i][b][l] = i;
        if(l > 0)
            dp[i][b][l] = max(dp[i][b][l], solve(diff, i + 1, b, l - 1));
        if(b >= diff[i])
            dp[i][b][l] = max(dp[i][b][l], solve(diff, i + 1, b - diff[i], l));
        return dp[i][b][l];
    }
};

#include <queue>

class Solution {
public:
    int furthestBuilding(vector<int>& heights, int bricks, int ladders) {
        int n = heights.size();
        vector<int> diff;
        vector<int> idxs;
        for(int i = 0; i < n - 1; ++i)
            if(heights[i + 1] > heights[i])
            {
                diff.push_back(heights[i + 1] - heights[i]);
                idxs.push_back(i);
            }
        int m = diff.size();
        if(m == 0)
            return n - 1;
        priority_queue<int, vector<int>, greater<int>> pq;
        int i = 0;
        while(i < m && ladders > 0)
        {
            pq.push(diff[i]);
            ++i;
            --ladders;
        }
        while(i < m && !pq.empty() && bricks >= pq.top())
        {
            pq.pop();
            bricks -= pq.top();
            pq.push(diff[i]);
            ++i;
        }
        if(i < m && bricks >= diff[i])
        {
            bricks -= diff[i];
            ++i;
        }
        if(i == m)
            return n - 1;
        return idxs[i];
    }
};
