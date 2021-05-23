
#include <string>
#include <vector>

using namespace std;


class Solution0 {
public:
    bool canReach(string s, int minJump, int maxJump) {
        int n = s.size();
        if(s[n - 1] != '0')
            return false;
        dp = vector<int>(n, -1);
        dp[n - 1] = 1;
        return solve(s, 0, minJump, maxJump) == 1;
    }

private:
    vector<int> dp;

    int solve(const string& s, int i, const int minJump, const int maxJump)
    {
        if(dp[i] != -1)
            return dp[i];
        int n = s.size();
        for(int j = i + minJump; j <= min(i + maxJump, n - 1); ++j)
        {
            if(s[j] == '0')
                if(solve(s, j, minJump, maxJump) == 1)
                    return dp[i] = 1;
        }
        return dp[i] = 0;
    }
};

class Solution1 {
public:
    bool canReach(string s, int minJump, int maxJump) {
        int n = s.size();
        if(s[n - 1] != '0')
            return false;
        for(int i = 0; i < n; ++i)
            if(s[i] == '0')
                idxs.push_back(i);
        dp = vector<int>(n, -1);
        dp[n - 1] = 1;
        return solve(s, 0, minJump, maxJump) == 1;
    }

private:
    vector<int> dp;
    vector<int> idxs;

    int solve(const string& s, int i, const int minJump, const int maxJump)
    {
        if(dp[i] != -1)
            return dp[i];
        auto it = lower_bound(idxs.begin(), idxs.end(), i + minJump);
        while(it != idxs.end() && *it <= i + maxJump)
        {
            if(solve(s, *it, minJump, maxJump) == 1)
                return dp[i] = 1;
            ++it;
        }
        return dp[i] = 0;
    }
};

#include <queue>
#include <unordered_set>

class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {
        int n = s.size();
        if(s[n - 1] != '0')
            return false;
        vector<int> idxs;
        for(int i = 0; i < n; ++i)
            if(s[i] == '0')
                idxs.push_back(i);
        queue<int> q;
        q.push(0);
        int idx_iter = 1;
        while(!q.empty())
        {
            int i = q.front();
            q.pop();
            while(idx_iter < (int)idxs.size() && idxs[idx_iter] <= min(n - 1, i + maxJump))
            {
                if(i + minJump <= idxs[idx_iter])
                    q.push(idxs[idx_iter]);
                ++idx_iter;
            }
            if(idx_iter == (int)idxs.size())
                return true;
        }
        return false;
    }
};
