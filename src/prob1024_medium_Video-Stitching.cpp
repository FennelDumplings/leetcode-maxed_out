// prob1024: Video Stitching

/*
 * https://leetcode-cn.com/problems/video-stitching/
 */

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// 贪心
struct Cmp
{
    bool operator()(const vector<int>& clip1, const vector<int>& clip2) const
    {
        return clip1[0] < clip2[0];
    }
};

class Solution {
public:
    int videoStitching(vector<vector<int>>& clips, int T) {
        sort(clips.begin(), clips.end(), Cmp());
        int right = 0;
        int ans = 0;
        int n = clips.size();
        int iter = 0;
        while(right < T)
        {
            int max_right = right;
            while(iter < n && clips[iter][0] <= right)
            {
                max_right = max(max_right, clips[iter][1]);
                ++iter;
            }
            if(right == max_right)
                return -1;
            ++ans;
            right = max_right;
        }
        return ans;
    }
};

// DP
class Solution_2 {
public:
    int videoStitching(vector<vector<int>>& clips, int T) {
        int n = clips.size();
        vector<int> dp(T + 1, n + 1);
        dp[0] = 0;
        for(int i = 1; i <= T; ++i)
            for(const vector<int>& clip: clips)
                if(clip[0] < i && i <= clip[1])
                    dp[i] = min(dp[i], dp[clip[0]] + 1);
        if(dp[T] == n + 1) return -1;
        return dp[T];
    }
};
