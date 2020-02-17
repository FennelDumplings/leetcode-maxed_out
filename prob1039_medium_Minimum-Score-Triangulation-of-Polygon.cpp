// prob1039: Minimum Score Triangulation of Polygon

/*
 * Given N, consider a convex N-sided polygon with vertices labelled A[0], A[i], ..., A[N-1] in clockwise order.
 * Suppose you triangulate the polygon into N-2 triangles.
 * For each triangle, the value of that triangle is the product of the labels of the vertices,
 * and the total score of the triangulation is the sum of these values over all N-2 triangles in the triangulation.
 * Return the smallest possible total score that you can achieve with some triangulation of the polygon.
 */

/*
 * Example 1:
 * Input: [1,2,3]
 * Output: 6
 * Input: [3,7,4,5]
 * Output: 144
 * Example 3:
 * Input: [1,3,1,4,1,5]
 * Output: 13
 */

/*
 * Note:
 * 3 <= A.length <= 50
 * 1 <= A[i] <= 100
 */

#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    int minScoreTriangulation(vector<int>& A) {
        int n = A.size();
        if(n == 3) return A[0] * A[1] * A[2];

        vector<vector<int> > dp(n, vector<int>(n, 0));
        for(int j = 2; j < n; ++j)
            for(int i = j - 2; i >= 0; --i)
            {
                // dp[0][2] 开始
                int mx = INT_MAX;
                for(int k = i + 1; k <= j - 1; ++k)
                    mx = min(mx, dp[i][k] + dp[k][j] + A[i] * A[j] * A[k]);
                dp[i][j] = mx;
            }
        return dp[0][n - 1];
    }
};
