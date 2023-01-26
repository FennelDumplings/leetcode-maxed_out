// prob276: Paint Fence

/*
 * There is a fence with n posts, each post can be painted with one of the k colors.
 * You have to paint all the posts such that no more than two adjacent fence posts have the same color.
 * Return the total number of ways you can paint the fence.
 * Note:
 * n and k are non-negative integers.
 */

/*
 * Example:
 * Input: n = 3, k = 2
 * Output: 6
 * Explanation: Take c1 as color 1, c2 as color 2. All possible ways are:
 *
 *             post1  post2  post3
 *  -----      -----  -----  -----
 *    1         c1     c1     c2
 *    2         c1     c2     c1
 *    3         c1     c2     c2
 *    4         c2     c1     c1 
 *    5         c2     c1     c2
 *    6         c2     c2     c1
 */

class Solution {
public:
    // f[1] = k
    // f[2] = k^2
    // f[i] = (k - 1) * (f[i - 1] - f[i - 2])
    // f[n]
    int numWays(int n, int k) {
        if(k == 0 || n == 0) return 0;
        if(n == 1) return k;
        if(n == 2) return k * k;
        if(k == 1) return 0;
        int f1 = k, f2 = k * k;
        int f3;
        for(int i = 3; i <= n; ++i)
        {
            f3 = (k - 1) * (f2 + f1);
            f1 = f2;
            f2 = f3;
        }
        return f3;
    }
};

// 和前一个颜色相同，此时说明前一个的栅栏的颜色应与更前面一个栅栏的颜色不同，更前一个栅栏的涂色方法有 F(n - 2) 种，前一个栅栏的涂色方式有 (k - 1) 种，所以此时情况应为 F(n - 2) * (k - 1)
// 和前一个颜色不同，前一个栅栏的涂色方法有 F(n - 1) 种，当前栅栏的涂色方式有 (k - 1) 种，此时情况应为 F(n - 1) * (k - 1)
// 所以递推公式应为 F(n) = F(n - 2) * (k - 1) + F(n - 1) * (k - 1)
