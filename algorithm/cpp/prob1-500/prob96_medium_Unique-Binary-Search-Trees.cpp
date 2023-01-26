// prob96: Unique Binary Search Trees

/*
 * Given n, how many structurally unique BST's (binary search trees) that store values 1 ... n?
 */

/*
 * Example:
 * Input: 3
 * Output: 5
 * Explanation:
 * Given n = 3, there are a total of 5 unique BST's:
 *
 *    1         3     3      2      1
 *     \       /     /      / \      \
 *      3     2     1      1   3      2
 *     /     /       \                 \
 *    2     1         2                 3
 */

#include <vector>

using namespace std;

// 卡特兰数模板
class Solution {
public:
    int numTrees(int n) {
        if(n < 1) return 0;
        return _catalan(n);
    }

private:
    using ll = long long;

    // C(n) = C(n-1) * (4 * n - 2) / (n + 1)
    // C(1) = 1
    int _catalan(int n)
    {
        if(n == 1) return 1;
        int result = 1;
        for(int k = 2; k <= n; ++k)
            result = result * (k * 4 - 2) / (k + 1);
        return result;
    }
};

// DP
class Solution_2 {
public:
    int numTrees(int n) {
        vector<int> dp(n + 1);
        dp[0] = 1;
        for(int i = 1; i <= n; i++)
        {
            dp[i] = 0;
            for(int j = 1; j <= i; j++)
                dp[i] += dp[j - 1] * dp[i - j];
        }
        return dp[n];
    }
};
