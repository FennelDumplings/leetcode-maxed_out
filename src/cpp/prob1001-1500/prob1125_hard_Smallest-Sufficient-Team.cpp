// prob1125: Smallest Sufficient Team

/*
 * https://leetcode-cn.com/problems/smallest-sufficient-team/
 */

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& people) {
        mapping = unordered_map<string, int>();
        int id = 0;
        for(const string &s: req_skills)
            mapping[s] = id++;
        int n = people.size();
        peo = vector<int>(n);
        for(int i = 0; i < n; ++i)
        {
            for(const string &s: people[i])
            {
                if(mapping.count(s) == 0)
                    continue;
                peo[i] |= 1 << mapping[s];
            }
        }
        K = id;
        dp = vector<vector<int>>(n + 1, vector<int>((1 << K), -1));
        solve(0, 0);
        return get_path();
    }

private:
    unordered_map<string, int> mapping;
    vector<int> peo;
    int K;
    vector<vector<int>> dp;

    vector<int> get_path()
    {
        vector<int> path;
        int n = peo.size();
        int state = 0;
        int target = (1 << K) - 1;
        for(int i = 0; i < n; ++i)
        {
            if(dp[i][state] == 0)
                return path;
            if(dp[i][state] == 1 + dp[i + 1][state | peo[i]])
            {
                path.push_back(i);
                state |= peo[i];
            }
        }
        if(state == target)
            return path;
        return {-1};
    }

    int solve(int i, int state)
    {
        if(dp[i][state] != -1)
            return dp[i][state];

        if(state == (1 << K) - 1)
            return dp[i][state] = 0;
        int n = peo.size();
        if(i == n)
            return dp[i][state] = -2;

        // state > 0 && i < n

        // 选 peo[i]
        int x = solve(i + 1, state | peo[i]);
        // 不选 peo[i]
        int y = solve(i + 1, state);
        if(x == -2 && y == -2)
            return dp[i][state] = -2;
        else if(y == -2 || x + 1 <= y)
        {
            dp[i][state] = 1 + x;
        }
        else
            dp[i][state] = y;
        return dp[i][state];
    }
};
