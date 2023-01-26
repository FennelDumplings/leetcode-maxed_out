
#include <vector>

using namespace std;

class Solution {
public:
    int maxUncrossedLines(vector<int>& A, vector<int>& B) {
        int nA = A.size(), nB = B.size();
        vector<vector<int>> dp(nA + 1, vector<int>(nB + 1));
        for(int i = 1; i <= nA; ++i)
            for(int j = 1; j <= nB; ++j)
            {
                if(A[i - 1] == B[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        return dp[nA][nB];
    }
};
