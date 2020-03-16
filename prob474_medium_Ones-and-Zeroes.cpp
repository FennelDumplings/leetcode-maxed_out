// prob474: Ones and Zeroes

/*
 * In the computer world, use restricted resource you have to generate maximum benefit is what we always want to pursue.
 * For now, suppose you are a dominator of m 0s and n 1s respectively. On the other hand, there is an array with strings consisting of only 0s and 1s.
 * Now your task is to find the maximum number of strings that you can form with given m 0s and n 1s. Each 0 and 1 can be used at most once.
 */

/*
 * Note:
 * The given numbers of 0s and 1s will both not exceed 100
 * The size of given string array won't exceed 600.
 */

/*
 * Example 1:
 * Input: Array = {"10", "0001", "111001", "1", "0"}, m = 5, n = 3
 * Output: 4
 * Explanation: This are totally 4 strings can be formed by the using of 5 0s and 3 1s, which are “10,”0001”,”1”,”0”
 * Example 2:
 * Input: Array = {"10", "0", "1"}, m = 1, n = 1
 * Output: 2
 * Explanation: You could form "10", but then you'd have nothing left. Better form "0" and "1".
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        if(strs.empty()) return 0;
        int N = strs.size();
        int V1 = m, V2 = n; // 二维费用背包的两个容量

        vector<int> v1(N, 0); // 0 个数
        vector<int> v2(N, 0); // 1 个数
        for(int i = 0; i < N; ++i)
        {
            string str = strs[i];
            for(char c: str)
            {
                if(c == '0')
                    ++v1[i];
                else
                    ++v2[i];
            }
        }

        vector<vector<int> > dp(V1 + 1, vector<int>(V2 + 1, 0));
        for(int i = 0; i < N; ++i)
            for(int j = V1; j >= v1[i]; --j)
                for(int k = V2; k >= v2[i]; --k)
                    dp[j][k] = max(dp[j][k], dp[j - v1[i]][k - v2[i]] + 1);

        return dp[V1][V2];
    }
};
