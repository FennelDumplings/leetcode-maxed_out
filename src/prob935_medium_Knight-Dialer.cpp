// prob935: Knight Dialer

/*
 * Since the answer may be large, output the answer modulo 10^9 + 7.
 */

#include <vector>

using namespace std;

using ll = long long;

// vector<vector<int>> 中第二位长度不同
// dp[i][s] 第 i 步，且当前数字为 s 的不同方案数
class Solution {
public:
    int knightDialer(int N) {
        vector<vector<int> > path(10, vector<int>());
        path[0].push_back(4), path[0].push_back(6);
        path[1].push_back(6), path[1].push_back(8);
        path[2].push_back(7), path[2].push_back(9);
        path[3].push_back(4), path[3].push_back(8);
        path[4].push_back(3), path[4].push_back(9), path[4].push_back(0);
        path[6].push_back(1), path[6].push_back(7), path[6].push_back(0);
        path[7].push_back(2), path[7].push_back(6);
        path[8].push_back(1), path[8].push_back(3);
        path[9].push_back(2), path[9].push_back(4);

        const int M = 1e9 + 7;

        vector<vector<int> > dp(N, vector<int>(10, 0));
        for(int s = 0; s < 10; ++s)
            dp[0][s] = 1;

        for(int i = 1; i < N; ++i)
            for(int s = 0; s < 10; ++s)
                for(int k = 0; k < (int)path[s].size(); ++k)
                    dp[i][s] = (dp[i][s] + dp[i - 1][path[s][k]]) % M;

        int ans = 0;
        for(int s = 0; s < 10; ++s)
            ans = (ans + dp[N - 1][s]) % M;
        return ans;
    }
};

// 把状态分组
// A{1,3,7,9},B{2,8},C{4,6},D{0}
class Solution_2 {
public:
    int knightDialer(int N) {
        if(N == 1) return 10;
        const int M = 1e9 + 7;
        using ll = long long;
        vector<vector<int> > dp(2, vector<int>(4, 1)); // 状态分成4组, 步数的维可滚动
        // dp[1] 这一行的4个1是第1步4组状态的答案，接下来跳N-1步
        for(int i = 2; i <= N; ++i)
        {
            dp[i % 2][0] = ((ll)dp[(i - 1) % 2][1] + dp[(i - 1) % 2][2]) % M;
            dp[i % 2][1] = (2 * (ll)dp[(i - 1) % 2][0]) % M;
            dp[i % 2][2] = ((2 * (ll)dp[(i - 1) % 2][0]) % M + dp[(i - 1) % 2][3]) % M;
            dp[i % 2][3] = (2 * (ll)dp[(i - 1) % 2][2]) % M;
        }
        int result = 0;
        result = (result + 4 * (ll)dp[N % 2][0] % M) % M;
        result = (result + 2 * (ll)dp[N % 2][1] % M) % M;
        result = (result + 2 * (ll)dp[N % 2][2] % M) % M;
        result = (result + 1 * (ll)dp[N % 2][3] % M) % M;
        return result;
    }
};

// 状态分组基础上矩阵快速幂优化
// 递推式写成矩阵形式
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
                    ans.mat[i][j] += (((ll)mat[i][k] * matrix.mat[k][j])) % MOD;
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
    const int MOD = 1e9 + 7;
    using ll = long long;
};

class Solution_3 {
public:
    int knightDialer(int N) {
        if(N == 1) return 10;
        const int M = 1e9 + 7;
        using ll = long long;

        Matrix mat(4);
        mat.assign(0, 1, 1);
        mat.assign(0, 2, 1);
        mat.assign(1, 0, 2);
        mat.assign(2, 0, 2);
        mat.assign(2, 3, 1);
        mat.assign(3, 2, 2);

        Matrix power_mat = mat ^ (N - 1);

        int result = 0;
        vector<int> factor({4, 2, 2, 1});
        for(int i = 0; i < 4; ++i)
        {
            int row_sum = 0;
            row_sum = (row_sum + (ll)power_mat.get(i, 0)) % M;
            row_sum = (row_sum + (ll)power_mat.get(i, 1)) % M;
            row_sum = (row_sum + (ll)power_mat.get(i, 2)) % M;
            row_sum = (row_sum + (ll)power_mat.get(i, 3)) % M;
            result = (result + (factor[i] * (ll)row_sum)) % M;
        }
        return result;
    }
};
