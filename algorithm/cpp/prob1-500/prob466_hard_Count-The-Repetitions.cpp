// prob466: Count The Repetitions

/*
 * https://leetcode-cn.com/problems/count-the-repetitions/
 */

#include <vector>
#include <string>

using namespace std;

// TLE
class Solution {
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
        int len1 = s1.size(), len2 = s2.size();
        int idx2 = 0, cnt2 = 0; // S1 遍历完一次，s2 循环了多少次

        for(int i = 0; i < n1; ++i)
            for(int idx1 = 0; idx1 < len1; ++idx1)
            {
                if(s1[idx1] == s2[idx2])
                    ++idx2;
                if(idx2 == len2)
                {
                    ++cnt2;
                    idx2 = 0;
                }
            }
        return cnt2 / n2;
    }
};

// 循环节优化
class Solution_2 {
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
        int len1 = s1.size(), len2 = s2.size();
        if(len1 == 0 || len2 == 0 || n1 == 0 || n2 == 0)
            return 0;
        int idx2 = 0, cnt2 = 0; // S1 遍历完一次，s2 循环了多少次
        vector<int> times(n1); // times[i] := s1 循环 i 次后，s2 循环了几次
        vector<int> next(n1); // next[i] := s1 循环 i 次后，s2 下一个匹配的下标

        // 同样是暴力遍历，但是找出循环节就直接退出暴力
        for(int i = 0; i < n1; ++i)
        {
            for(int idx1 = 0; idx1 < len1; ++idx1)
            {
                if(s1[idx1] == s2[idx2])
                    ++idx2;
                if(idx2 == len2)
                {
                    ++cnt2;
                    idx2 = 0;
                }
            }
            times[i] = cnt2;
            next[i] = idx2;
            // 循环节出现：一定 s1 至少遍历完一遍，当前 idx2 与第 1 次遍历完 s1 时相同 (idx2 == next[0])
            if(i > 0 && idx2 == next[0])
            {
                // 第一部分： 交错前
                int head = times[0]; // 交错前的部分
                // 第 2 部分：中间循环部分
                // (n1 - 1)，要减去 1 个，因为从 s1 已经循环了一次开始，才出现的循环节
                // (n1 - 1) / i 表示剩下的部分有多少个红色大括号段（循环节）
                // times[i] - times[0] 表示：每个循环节里出现了几个 s2
                // ((n1 - 1) / i) * (times[i] - times[0]) 就表示中间那部分里面 s2 出现的次数
                int middle = ((n1 - 1) / i) * (times[i] - times[0]);

                // 第 3 部分：交错后
                // (n1 - 1) % i 相对于 (n1 - 1) / i 而言，就是不能整除的部分
                // 减去 times[0] 是因为计算 times[i] 的时候计算的是前缀和，head 这部分已经计算过了，要把它删掉（写成两部分的和也可以）
                int end = times[(n1 - 1) % i] - times[0];

                // 总结：一下子计算出 loopTimesOnS2，是这个解法优化的地方
                return (head + middle + end) / n2;
            }
        }
        return cnt2 / n2;
    }
};


// 倍增优化DP
class Solution_3 {
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
        using ll = long long;
        int len1 = s1.size(),len2 = s2.size();
        const int K = 30;
        vector<vector<ll>> dp(len1, vector<ll>(K, 0));
        int l1 = 0,l2 = 0;
        for(int i = 0; i < len1; ++i)
        {
            l1 = i; l2 = 0;
            while(l2<len2)
            {
                while(l1 < n1 * len1 && s1[l1 % len1] != s2[l2])
                    l1++;
                l1++;
                l2++;
            }
            dp[i][0] = l1 - i;
        }
        for(int k = 1; k < K; ++k)
            for(int i = 0; i < len1; ++i)
            {
                dp[i][k] = dp[i][k - 1] + dp[(i + dp[i][k - 1]) % len1][k - 1];
            }
        long long int ans = 0;
        int begin = 0;
        for(int k = 29; k >= 0; k--)
            while((begin + dp[(begin % len1)][k]) <= n1 * len1)
            {
                ans += (1 << k);
                begin += dp[(begin % len1)][k];
            }
        return ans / n2;
    }
};
