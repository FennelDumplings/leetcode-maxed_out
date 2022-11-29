// prob808: Soup Servings

/*
 * There are two types of soup: type A and type B. Initially we have N ml of each type of soup. There are four kinds of operations:
 * Serve 100 ml of soup A and 0 ml of soup B
 * Serve 75 ml of soup A and 25 ml of soup B
 * Serve 50 ml of soup A and 50 ml of soup B
 * Serve 25 ml of soup A and 75 ml of soup B
 * When we serve some soup, we give it to someone and we no longer have it.  Each turn,
 * we will choose from the four operations with equal probability 0.25. If the remaining volume of soup is not enough to complete the operation,
 * we will serve as much as we can.  We stop once we no longer have some quantity of both types of soup.
 * Note that we do not have the operation where all 100 ml's of soup B are used first.
 * Return the probability that soup A will be empty first, plus half the probability that A and B become empty at the same time.
 */

/*
 * Notes:
 * 0 <= N <= 10^9.
 * Answers within 10^-6 of the true value will be accepted as correct.
 */

/*
 * Example:
 * Input: N = 50
 * Output: 0.625
 * Explanation:
 * If we choose the first two operations, A will become empty first. For the third operation, A and B will become
 * empty at the same time. For the fourth operation, B will become empty first. So the total probability of A becoming
 * empty first plus half the probability that A and B become empty at the same time, is 0.25 * (1 + 1 + 0.5 + 0) = 0.625.
 */

#include <vector>

using namespace std;

class Solution {
public:
    double soupServings(int N) {
        if(N % 25 == 0)
            N /= 25;
        else
            N = N / 25 + 1;
        if(N >= 500)
            return 1.0;

        vector<vector<double> > dp(N + 1, vector<double>(N + 1, 0));
        for(int i = 0; i <= N; ++i)
            for(int j = 0; j <= N; ++j)
            {
                if(j < 0 || j > N)
                    continue;
                double ans = 0.0;
                if(i == 0)
                    ans = 1.0;
                if(i == 0 && j == 0)
                    ans = 0.5;
                if(i > 0 && j > 0)
                {
                    ans = 0.25 * (dp[relu(i - 4)][j] + dp[relu(i - 3)][j - 1]
                            + dp[relu(i - 2)][relu(j - 2)] + dp[relu(i - 1)][relu(j - 3)]);
                }
                dp[i][j] = ans;
            }
        return dp[N][N];
    }

private:
    int relu(int x)
    {
        return max(0, x);
    }
};
