// interview08.01: Three Steps Problem LCCI

/*
 * A child is running up a staircase with n steps and can hop either 1 step, 2 steps, or 3 steps at a time.
 * Implement a method to count how many possible ways the child can run up the stairs. The result may be large,
 * so return it modulo 1000000007.
 */

/*
 * Example1:
 *
 *  Input: n = 3
 *  Output: 4
 * Example2:
 *
 *  Input: n = 5
 *  Output: 13
 */

/*
 * Note:
 * 1 <= n <= 1000000
 */

#include <vector>

using namespace std;

// DP
class Solution_2 {
public:
    int waysToStep(int n) {
        if(n == 1) return 1;
        if(n == 2) return 2;
        int MOD = 1000000007;
        vector<int> dp(4);
        dp[0] = 1, dp[1] = 1, dp[2] = 2;
        for(int i = 3; i <= n; ++i)
        {
            dp[3] = ((dp[0] + dp[1]) % MOD + dp[2]) % MOD;
            dp[0] = dp[1];
            dp[1] = dp[2];
            dp[2] = dp[3];
        }
        return dp[3];
    }
};

// 矩阵快速幂
using ll = long long;
const int MOD = 1e9 + 7;

class Matrix {
public:
    Matrix(int m){
        M = m;
        mat = vector<vector<int> >(M, vector<int>(M, 0));
    }

    void assign(int i, int j, int val)
    {
        mat[i][j] = val;
    }

    int get(int i, int j)
    {
        return mat[i][j];
    }

    void init()
    {
        for(int i = 0; i < M; ++i)
            for(int j = 0; j < M; ++j)
                mat[i][j] = 0;
        for(int i = 0; i < M; ++i)
            mat[i][i] = 1;
    }

    Matrix operator*(const Matrix& matrix) const
    {
        Matrix ans(M);
        for(int i = 0; i < M; ++i)
            for(int j = 0; j < M; ++j)
                for(int k = 0; k < M; ++k)
                    ans.mat[i][j] = (ans.mat[i][j] + ((ll)mat[i][k] * matrix.mat[k][j]) % MOD) % MOD;
        return ans;
    }

    Matrix operator^(int n) const
    {
        Matrix ans(M);
        ans.init();
        Matrix A = *this; // 拷贝出来用于自乘
        while(n)
        {
            if(n & 1) ans = ans * A;
            A = A * A;
            n >>= 1;
        }
        return ans;
    }

    void operator=(const Matrix& matrix)
    {
        for(int i = 0; i < M; ++i)
            for(int j = 0; j < M; ++j)
                mat[i][j] = matrix.mat[i][j];
    }

private:
    vector<vector<int> > mat;
    int M;
};

class Solution {
public:
    int waysToStep(int n) {
        if(n == 1) return 1;
        if(n == 2) return 2;
        Matrix mat(3);
        mat.assign(0, 0, 1);
        mat.assign(0, 1, 1);
        mat.assign(0, 2, 1);
        mat.assign(1, 0, 1);
        mat.assign(2, 1, 1);
        Matrix mat_power = mat ^ (n - 2);
        int result = (((mat_power.get(0, 0) * 2) % MOD + mat_power.get(0, 1)) % MOD + mat_power.get(0, 2)) % MOD;
        return result;
    }
};
