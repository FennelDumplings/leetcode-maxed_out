// prob1137: N-th Tribonacci Number

/*
 * The Tribonacci sequence Tn is defined as follows:
 * T0 = 0, T1 = 1, T2 = 1, and Tn+3 = Tn + Tn+1 + Tn+2 for n >= 0.
 * Given n, return the value of Tn.
 */

/*
 * 0 <= n <= 37
 * The answer is guaranteed to fit within a 32-bit integer, ie. answer <= 2^31 - 1.
 */

#include <vector>

using namespace std;

using ll = long long;

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
                    ans.mat[i][j] += ((ll)mat[i][k] * matrix.mat[k][j]);
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
    int tribonacci(int n) {
        if(n == 0) return 0;
        if(n == 1) return 1;
        if(n == 2) return 1;
        Matrix mat(3);
        mat.assign(0, 0, 1);
        mat.assign(0, 1, 1);
        mat.assign(0, 2, 1);
        mat.assign(1, 0, 1);
        mat.assign(2, 1, 1);
        Matrix mat_power = mat ^ (n - 2);
        int result = mat_power.get(0, 0) + mat_power.get(0, 1);
        return result;
    }
};

